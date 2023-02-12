/*
    ==================================================
    Assignment #2 Milestone #4
    ==================================================
    Name    : Tarik Ozturk
    ID      : 155237209
    Email   : tozturk1@myseneca.ca
    Section : NCC
 */

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>
#include "account.h"
#include "accountTicketingUI.h"
#include "commonHelpers.h"
#include "ticket.h"

void displayAccountDetailHeader(void) {
    printf("Acct# Acct.Type Full Name       Birth Income      Country    Login      Password\n");
    printf("----- --------- --------------- ----- ----------- ---------- ---------- --------\n");
}



void displayAccountDetailRecord(const struct Account* account) {
    int passLen = 8;
    char hiddenPass[9]; 

    int i;
    for (i = 0; i < passLen + 1; i++) {
        if (i % 2 == 1) {
            hiddenPass[i] = '*';
        }
        else {
            hiddenPass[i] = account->userLogin.password[i];
        }
    }

    printf("%05d %-9s %-15s %5d %11.2lf %-10s %-10s %8s\n", account->accountNo, account->accType == 'A' ? "AGENT" : "CUSTOMER", account->person.fullName, account->person.birthYear, account->person.householdIncome, account->person.country, account->userLogin.loginName, hiddenPass);
}

void applicationStartup(struct AccountTicketingData *accountTicketingData) {
    int returnedIndex;
    do {
        do {
            returnedIndex = menuLogin(accountTicketingData->accounts, accountTicketingData->ACCOUNT_MAX_SIZE);
            if (returnedIndex != -1 && returnedIndex != -3) menuAgent(*accountTicketingData, &accountTicketingData->accounts[returnedIndex]);
        } while (returnedIndex == -3);
    } while (returnedIndex != -1);
    printf("==============================================\n");
    printf("Account Ticketing System - Terminated\n");
    printf("==============================================\n");
}

int menuLogin(const struct Account *account, int max) {
    int selection, accountIndex = -2, enteredNo, found = 0, maxNameLen = 50, nameComp, passComp, remainingAttempts = 3;
    char toContinue;
    char tempLogName[100] = { 0 };
    char tempLogPass[100] = { 0 };

    do {
        printf("==============================================\n");
        printf("Account Ticketing System - Login\n");
        printf("==============================================\n");
        printf("1) Login to the system\n");
        printf("0) Exit application\n");
        printf("----------------------------------------------\n\n");
        printf("Selection: ");

        selection = getIntFromRange(0, 1);
        
        if (selection == 1) {
            do {
                printf("\nEnter the account#: ");
                enteredNo = getInteger();
                int i;
                for (i = 0; i < max; i++) {
                    if ((found != 1) && (account[i].accountNo == enteredNo) && (account[i].accType == 'A')) {
                        accountIndex = i;
                        found = 1;
                    }
                }
                
                printf("User Login        : ");
                getCString(tempLogName, 0, maxNameLen);
                
                nameComp = strcmp(account[accountIndex].userLogin.loginName, tempLogName);
                
                printf("Password          : ");
                getCString(tempLogPass, 0, maxNameLen);
                passComp = strcmp(account[accountIndex].userLogin.password, tempLogPass);
               
                if ((found != 1) || (nameComp != 0) || (passComp != 0)) {
                    remainingAttempts--;
                    printf("INVALID user login/password combination! [attempts remaining:%d]\n", remainingAttempts);
                    found = 0;
                    accountIndex = -2;
                }
                else printf("\n");
            } while (((found != 1) || (nameComp != 0) || (passComp != 0)) && (remainingAttempts > 0)) ;
            if (remainingAttempts == 0) {
                printf("\nERROR:  Access Denied.\n\n");
                pauseExecution();
                accountIndex = -3;
            }
        }

        else if (selection == 0) {
            printf("\n");
            printf("Are you sure you want to exit? ([Y]es|[N]o): ");
            toContinue = getCharOption("yYnN");
            if (toContinue == 'y' || toContinue == 'Y') accountIndex = -1;
            printf("\n");
        }       
    } while (accountIndex == -2);
    return accountIndex;
}

void menuAgent(struct AccountTicketingData accountTicketingData, const struct Account *loggedInAcc) {
    int selection = -1, accountNo, found, i, j, highest, removedTickets = 0, savedAccs, savedTicks;
    char confirmation;
    do {
    found = 0;
    printf("AGENT: %s (%5d)\n", loggedInAcc->person.fullName, loggedInAcc->accountNo);
    printf("==============================================\n");
    printf("Account Ticketing System - Agent Menu\n");
    printf("==============================================\n");
    printf("1) Add a new account\n");
    printf("2) Modify an existing account\n");
    printf("3) Remove an account\n");
    printf("4) List accounts: detailed view\n");
    printf("----------------------------------------------\n");
    printf("5) List new tickets\n");
    printf("6) List active tickets\n");
    printf("7) List closed tickets\n");
    printf("8) Add a new ticket\n");
    printf("9) Manage a ticket\n");
    printf("----------------------------------------------\n");
    printf("0) Logout\n\n");
    printf("Selection: ");
        selection = getIntFromRange(0, 9);
        printf("\n");
        switch (selection) {
        case 1:

            highest = highestAccountNo(accountTicketingData.accounts, accountTicketingData.ACCOUNT_MAX_SIZE);
            highest++;

            for (i = 0; i < accountTicketingData.ACCOUNT_MAX_SIZE; i++) {
                if ((found == 0) && (accountTicketingData.accounts[i].accountNo == 0)) {
                    accountTicketingData.accounts[i].accountNo = highest;
                    getAccount(&accountTicketingData.accounts[i]);
                    printf("*** New account added! ***\n\n");
                    found = 1;
                }
            }
            if (found == 0) printf("ERROR: Account listing is FULL, call ITS Support!\n\n");
            pauseExecution();
            found = 0;
            break;
        case 2:
            printf("Enter the account#: ");
            accountNo = getInteger();
            printf("\n");
            for (i = 0; i < accountTicketingData.ACCOUNT_MAX_SIZE; i++) {
                if ((found == 0) && (accountTicketingData.accounts[i].accountNo == accountNo)) {
                    updateAccount(&accountTicketingData.accounts[i]);
                    found = 1;
                }
            }
            if (found == 0) printf("ERROR there is no such account\n");
            break;
        case 3:
            printf("Enter the account#: ");
            accountNo = getInteger();
            printf("\n");
            for (i = 0; i < accountTicketingData.ACCOUNT_MAX_SIZE; i++) {
                if ((found == 0) && (accountTicketingData.accounts[i].accountNo == accountNo)) {
                    found = 1;

                    if (accountNo == loggedInAcc->accountNo) {
                        printf("ERROR: You can't remove your own account!\n\n");
                        pauseExecution();
                    }
                    else {
                        displayAccountDetailHeader();
                        displayAccountDetailRecord(&accountTicketingData.accounts[i]);
                        printf("\nAre you sure you want to remove this record? ([Y]es|[N]o): ");
                        confirmation = getCharOption("YyNn");
                        if (confirmation == 'Y' || confirmation == 'y') {
                            for (j = 0; j < accountTicketingData.TICKET_MAX_SIZE; j++) {
                                if (accountTicketingData.tickets[j].accountNo == accountNo) {
                                    accountTicketingData.tickets[j].ticketNo = '\0';
                                    removedTickets++;
                                    accountTicketingData.tickets[j].messageCounter = 0;
                                }
                            }
                        }
                        accountTicketingData.accounts[i].accountNo = 0;
                        printf("\n*** Account Removed! (%d ticket(s) removed) ***\n\n", removedTickets);
                        pauseExecution();
                        removedTickets = 0;
                    }

                }
            }
            break;
        case 4:
            displayAllAccountDetailRecords(accountTicketingData.accounts, accountTicketingData.ACCOUNT_MAX_SIZE);
            printf("\n");
            pauseExecution();
            break;

        case 5:
            listNewTickets(accountTicketingData.tickets, accountTicketingData.TICKET_MAX_SIZE);
            break;
        case 6:
            listActiveTickets(accountTicketingData.tickets, accountTicketingData.TICKET_MAX_SIZE);
            break;
        case 7:
            listClosedTickets(accountTicketingData.tickets, accountTicketingData.TICKET_MAX_SIZE);
            break;
        case 8:
            addNewTicket(accountTicketingData.accounts, accountTicketingData.tickets, accountTicketingData.ACCOUNT_MAX_SIZE, accountTicketingData.TICKET_MAX_SIZE);
            break;
        case 9:
            manageTicket(accountTicketingData.tickets, *loggedInAcc, accountTicketingData.TICKET_MAX_SIZE);
            break;
        case 0:
            savedAccs = saveAccounts(accountTicketingData.accounts, ACCOUNT_SIZE);
            savedTicks = saveTickets(accountTicketingData.tickets, TICKET_SIZE);
            printf("Saving session modifications...\n");
            printf("   %d account(s) saved.\n", savedAccs);
            printf("   %d ticket(s) saved.\n", savedTicks);
            printf("### LOGGED OUT ###\n\n");
            break;
        }
    } while (selection > 0 && selection <= 9);
}

void displayAllAccountDetailRecords(const struct Account *account, int max) {
    int i;
    displayAccountDetailHeader();
    for (i = 0; i < max; i++) {
        if (account[i].accountNo > 0) {
            displayAccountDetailRecord(&account[i]);
        }
    }
}

void displayStatusHeader(void) {
    printf("------ ----- --------------- ------ ------------------------------ --------\n");
    printf("Ticket Acct# Full Name       Status Subject                        Messages\n");
    printf("------ ----- --------------- ------ ------------------------------ --------\n");
}

// Pause execution until user enters the enter key
void pauseExecution(void)
{
    printf("<< ENTER key to Continue... >>");
    clearStandardInputBuffer();
    putchar('\n');
}
