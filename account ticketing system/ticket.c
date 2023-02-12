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
#include <ctype.h>
#include <string.h>
#include "account.h"
#include "commonHelpers.h"
#include "ticket.h"

int highestAccountNo(const struct Account *account, int max) {
    int highest = -1, i;
    for (i = 0; i < max; i++) {
        if (account[i].accountNo > highest) highest = account[i].accountNo;
    }
    return highest;
}

int highestTicketNo(const struct Ticket *ticket, int max) {
    int highest = -1, i;
    for (i = 0; i < max; i++) {
        if (ticket[i].ticketNo > highest) highest = ticket[i].ticketNo;
    }
    return highest;
}

int loadAccounts(struct Account *account, int accSize) {
    FILE *fp = NULL;
    int c, nrecs = 0;

    fp = fopen("accounts.txt", "r");
    if (fp != NULL) {
        do {

            fscanf(fp, "%d~%c~%[^~]~%d~%lf~%[^(\n|~)]", &account[nrecs].accountNo, &account[nrecs].accType, account[nrecs].person.fullName,
                &account[nrecs].person.birthYear, &account[nrecs].person.householdIncome, account[nrecs].person.country);
            c = fgetc(fp);
            if (c != '\n') fscanf(fp, "%[^~]~%s\n", account[nrecs].userLogin.loginName, account[nrecs].userLogin.password);
            nrecs++;
        } while ((feof(fp) == 0) && (nrecs < accSize));
        fclose(fp);
    }
    
    return nrecs;
}

int loadTickets(struct Ticket *ticket, int ticketSize) {
    FILE* fp = NULL;
    int c, nrecs = 0, i;

    fp = fopen("tickets.txt", "r");
    if (fp != NULL) {
        do {
            fscanf(fp, "%d|%d|%d|%[^|]|%d|", &ticket[nrecs].ticketNo, &ticket[nrecs].accountNo, &ticket[nrecs].status, ticket[nrecs].subjectLine, &ticket[nrecs].messageCounter);
            for (i = 0; i < ticket[nrecs].messageCounter; i++) {
                fscanf(fp, "%c|%[^|]|%[^|]|", &ticket[nrecs].messages[i].accType, ticket[nrecs].messages[i].fullName, ticket[nrecs].messages[i].messageDetails);
            }
            c = fgetc(fp);
            if (c == '\n') nrecs++;
            
        } while ((feof(fp) == 0) && (nrecs < ticketSize));

        fclose(fp);
    }
    return nrecs;
}

int saveAccounts(struct Account *account, int accSize) {
    FILE* fp = NULL;
    int counter, numAccount = 0;

    fp = fopen("accounts.txt", "w");
    if (fp != NULL) {
        for (counter = 0; counter < accSize; counter++) {
            if (&account[counter].accountNo != 0) {
                numAccount++;
                fprintf(fp, "%d~%c~%s~%d~%.2lf~%s", account[counter].accountNo, account[counter].accType, account[counter].person.fullName,
                account[counter].person.birthYear, account[counter].person.householdIncome, account[counter].person.country);
                if(account[counter].userLogin.loginName != 0) fprintf(fp, "~%s~%s", account[counter].userLogin.loginName, account[counter].userLogin.password);
                fprintf(fp, "\n");
            }
        }
        fclose(fp);
    }
    else printf("Failed to open file\n");
    return numAccount;
}

int saveTickets(struct Ticket *ticket, int ticketSize) {
    FILE* fp = NULL;
    int counter, numTickets = 0, i;

    fp = fopen("tickets.txt", "w");
    if (fp != NULL) {
        for (counter = 0; counter < ticketSize; counter++) {
            if (ticket[counter].ticketNo != 0) {
                numTickets++;
                fprintf(fp, "%d|%d|%d|%s|%d|", ticket[counter].ticketNo, ticket[counter].accountNo, ticket[counter].status, ticket[counter].subjectLine, ticket[counter].messageCounter);
                for (i = 0; i < ticket[counter].messageCounter; i++) {
                    fprintf(fp, "%c|%s|%s|", ticket[counter].messages[i].accType, ticket[counter].messages[i].fullName, ticket[counter].messages[i].messageDetails);
                }
                fprintf(fp, "\n");
            }
        }
        fclose(fp);
    }
    else printf("Failed to open file\n");
    return numTickets;
}

void listNewTickets(struct Ticket *tickets, int max) {
    int i, j, ticketSelection = -1, ticketFound = 0, ticketToPrint;
    do {
        displayStatusHeader();
        for (i = 0; i < max; i++) {
            if (tickets[i].status == 1 && tickets[i].messageCounter == 1)
                printf("%06d %05d %-15s %6s %-30s %5d\n", tickets[i].ticketNo, tickets[i].accountNo,
                    tickets[i].messages->fullName, tickets[i].status == 1 ? "ACTIVE" : "CLOSED", tickets[i].subjectLine, tickets[i].messageCounter);
        }
        printf("------ ----- --------------- ------ ------------------------------ --------\n\n");
        printf("Enter the ticket number to view the messages or\n");
        printf("0 to return to previous menu: ");
        ticketSelection = getInteger();
        printf("\n");
        if (ticketSelection != 0) {
            for (i = 0; i < max; i++) {
                if (tickets[i].ticketNo == ticketSelection && tickets[i].messageCounter >= 1 && tickets[i].status == 1) {
                    ticketFound = 1;
                    ticketToPrint = i;
                }
            }
            if (ticketFound == 1) {
                printf("================================================================================\n");
                printf("%06d (%s) Re: %s\n", tickets[ticketToPrint].ticketNo,
                    tickets[ticketToPrint].status == 1 ? "ACTIVE" : "CLOSED", tickets[ticketToPrint].subjectLine);
                printf("================================================================================\n");
                for (j = 0; j < tickets[ticketToPrint].messageCounter; j++) { 
                    printf("%s (%s):\n", tickets[ticketToPrint].messages[j].accType == 'A' ? "AGENT" : "CUSTOMER",
                        tickets[ticketToPrint].messages[j].fullName);
                    printf("   %s\n\n", tickets[ticketToPrint].messages[j].messageDetails);
                }
            }
            else {
                printf("ERROR: Invalid ticket number.\n\n");
            }
            pauseExecution();
        }
    } while (ticketSelection != 0);
    ticketFound = 0;
}

void listActiveTickets(struct Ticket *tickets, int max) {
    int i, j, ticketSelection = -1, ticketFound = 0, ticketToPrint;
    do {
        displayStatusHeader();
        for (i = 0; i < max; i++) {
            if (tickets[i].status == 1 && tickets[i].messageCounter >= 1)
                printf("%06d %05d %-15s %6s %-30s %5d\n", tickets[i].ticketNo, tickets[i].accountNo,
                    tickets[i].messages->fullName, tickets[i].status == 1 ? "ACTIVE" : "ClOSED",
                    tickets[i].subjectLine, tickets[i].messageCounter);
        }
        printf("------ ----- --------------- ------ ------------------------------ --------\n\n");
        printf("Enter the ticket number to view the messages or\n");
        printf("0 to return to previous menu: ");
        ticketSelection = getInteger();
        printf("\n");
        if (ticketSelection != 0) {
            for (i = 0; i < max; i++) {
                if (tickets[i].ticketNo == ticketSelection && tickets[i].messageCounter >= 1 && tickets[i].status >= 1) {
                    ticketFound = 1;
                    ticketToPrint = i;
                }
            }
            if (ticketFound == 1) {
                printf("================================================================================\n");
                printf("%06d (%s) Re: %s\n", tickets[ticketToPrint].ticketNo,
                    tickets[ticketToPrint].status == 1 ? "ACTIVE" : "CLOSED", tickets[ticketToPrint].subjectLine);
                printf("================================================================================\n");
                for (j = 0; j < tickets[ticketToPrint].messageCounter; j++) {
                    printf("%s (%s):\n", tickets[ticketToPrint].messages[j].accType == 'A' ? "AGENT" : "CUSTOMER",
                        tickets[ticketToPrint].messages[j].fullName);
                    printf("   %s\n\n", tickets[ticketToPrint].messages[j].messageDetails);
                }

            }
            else {
                printf("ERROR: Invalid ticket number.\n\n");
            }
            pauseExecution();
        }
    } while (ticketSelection != 0);
    ticketFound = 0;
}

void listClosedTickets(struct Ticket *tickets, int max) {
    int i, j, ticketSelection = -1, ticketFound = 0, ticketToPrint;
    do {
            displayStatusHeader();
            for (i = 0; i < max; i++) {
                if (tickets[i].status == 0 && tickets[i].messageCounter >= 1)
                    printf("%06d %05d %-15s %6s %-30s %5d\n", tickets[i].ticketNo, tickets[i].accountNo,
                        tickets[i].messages->fullName, tickets[i].status == 1 ? "ACTIVE" : "CLOSED",
                        tickets[i].subjectLine, tickets[i].messageCounter);
            }
            printf("------ ----- --------------- ------ ------------------------------ --------\n\n");
            printf("Enter the ticket number to view the messages or\n");
            printf("0 to return to previous menu: ");
            ticketSelection = getInteger();
            printf("\n");
            if (ticketSelection != 0) {
                for (i = 0; i < max; i++) {
                    if (tickets[i].ticketNo == ticketSelection && tickets[i].messageCounter >= 1 && tickets[i].status == 0) {
                        ticketFound = 1;
                        ticketToPrint = i;
                    }
                }
                if (ticketFound == 1) {
                    printf("================================================================================\n");
                    printf("%06d (%s) Re: %s\n", tickets[ticketToPrint].ticketNo,
                        tickets[ticketToPrint].status == 1 ? "ACTIVE" : "CLOSED", tickets[ticketToPrint].subjectLine);
                    printf("================================================================================\n");
                    for (j = 0; j < tickets[ticketToPrint].messageCounter; j++) {
                        printf("%s (%s):\n", tickets[ticketToPrint].messages[j].accType == 'A' ? "AGENT" : "CUSTOMER",
                            tickets[ticketToPrint].messages[j].fullName);
                        printf("   %s\n\n", tickets[ticketToPrint].messages[j].messageDetails);
                    }
                }
                else {
                    printf("ERROR: Invalid ticket number.\n\n");
                }
                pauseExecution();
            }
            } while (ticketSelection != 0);
            ticketFound = 0;
}

void addNewTicket(struct Account *accounts, struct Ticket *tickets, int maxAcc, int maxTicket) {
    int accountNo, i, j, found = 0, accountIndex = -1, highestTicket;
    char toAddTicket;

    printf("Enter the account#: ");
    accountNo = getInteger();
    printf("\n");
    for (j = 0; j < maxAcc; j++) {
        if (accounts[j].accountNo == accountNo) accountIndex = j;
    }
    if (accounts[accountIndex].accType == 'A') {
        printf("ERROR: Agent accounts can't have tickets!\n\n");
        pauseExecution();
    }
    else {
        displayAccountDetailHeader();
        displayAccountDetailRecord(&accounts[accountIndex]);

        for (i = 0; i < maxTicket; i++) {
            if ((found == 0) && (tickets[i].ticketNo == 0)) {

                printf("\nAdd a new ticket for this customer? ([Y]es|[N]o): ");
                toAddTicket = getCharOption("YN");
                if (toAddTicket == 'Y') {
                    highestTicket = highestTicketNo(tickets, maxTicket);
                    highestTicket++;
                    tickets[i].ticketNo = highestTicket;
                    printf("\nNew Ticket (Ticket#:%06d)\n", highestTicket);
                    printf("----------------------------------------\n");
                    tickets[i].status = 1;
                    tickets[i].accountNo = accounts[accountIndex].accountNo;

                    printf("Enter the ticket SUBJECT (30 chars. maximum): ");
                    getCString(tickets[i].subjectLine, 0, 30);
                    printf("\n");

                    printf("Enter the ticket message details (150 chars. maximum). Press the ENTER key to submit:\n");
                    getCString(tickets[i].messages[0].messageDetails, 0, 150);
                    tickets[i].messageCounter = 1;

                    tickets[i].messages[0].accType = accounts[accountIndex].accType;
                    printf("\n*** New ticket created! ***\n\n");
                    pauseExecution();
                    strcpy(tickets[i].messages[0].fullName, accounts[accountIndex].person.fullName);
                    found = 1;
                }
            }
        }
        if (found == 0 && toAddTicket != 'N') printf("ERROR: Ticket listing is FULL, call ITS Support!\n\n");
    }
}

void manageTicket(struct Ticket *tickets, const struct Account loggedInAcc, int max) {
    int found = 0, manageSelection = -1, ticketNo, ticketIndex, messageLimit = 20, index, i;
    char toChangeStatus;

    printf("Enter ticket number: ");
    ticketNo = getInteger();
    for (i = 0; i < max; i++) {
        if ((found == 0) && (tickets[i].ticketNo == ticketNo)) {
            found = 1;
            ticketIndex = i;
        }
    }
    do {
        if (found == 1) {
            printf("\n----------------------------------------\n");
            printf("Ticket %06d - Update Options\n", tickets[ticketIndex].ticketNo);
            printf("----------------------------------------\n");
            printf("Status  : %s\n", tickets[ticketIndex].status == 1 ? "ACTIVE" : "CLOSED");
            printf("Subject : %s\n", tickets[ticketIndex].subjectLine);
            printf("Acct#   : %d\n", tickets[ticketIndex].accountNo);
            printf("Customer: %s\n", tickets[ticketIndex].messages->fullName);
            printf("----------------------------------------\n");
            printf("1) Add CUSTOMER message\n");
            printf("2) Add AGENT message\n");
            printf("3) Close ticket\n");
            printf("4) Re-activate ticket\n");
            printf("0) Done\n");
            printf("Selection: ");
            manageSelection = getIntFromRange(0, 4);
            printf("\n");
            switch (manageSelection) {
            case 1:
                if (tickets[ticketIndex].status != 1) printf("ERROR: Ticket is closed - new messages are not permitted.\n");
                else {

                    if (tickets[ticketIndex].messageCounter == messageLimit) printf("ERROR: Message limit has been reached, call ITS Support!\n");
                    else {
                        index = tickets[ticketIndex].messageCounter;
                        printf("Enter the ticket message details (150 chars. maximum). Press the ENTER key to submit:\n");
                        getCString(tickets[ticketIndex].messages[index].messageDetails, 0, 150);
                        strcpy(tickets[ticketIndex].messages[index].fullName, tickets[ticketIndex].messages[0].fullName);
                        tickets[ticketIndex].messages[index].accType = 'C';
                        tickets[ticketIndex].messageCounter++;
                    }
                }
                break;
            case 2:
                if (tickets[ticketIndex].status != 1) printf("ERROR: Ticket is closed - new messages are not permitted.\n");
                else {

                    if (tickets[ticketIndex].messageCounter == messageLimit) printf("ERROR: Message limit has been reached, call ITS Support!\n");
                    else {
                        index = tickets[ticketIndex].messageCounter;
                        printf("Enter the ticket message details (150 chars. maximum). Press the ENTER key to submit:\n");
                        getCString(tickets[ticketIndex].messages[index].messageDetails, 0, 150);
                        strcpy(tickets[ticketIndex].messages[index].fullName, loggedInAcc.person.fullName);
                        tickets[ticketIndex].messages[index].accType = 'A';
                        tickets[ticketIndex].messageCounter++;
                    }
                }
                break;
            case 3:
                if (tickets[ticketIndex].status == 0) printf("ERROR: Ticket is already closed!\n");
                else {
                    printf("Are you sure you CLOSE this ticket? ([Y]es|[N]o): ");
                    toChangeStatus = getCharOption("YN");
                    if (toChangeStatus == 'Y') {
                        tickets[ticketIndex].status = 0;
                        printf("\n*** Ticket closed! ***\n");
                    }
                }
                break;
            case 4:
                if (tickets[ticketIndex].status == 1) printf("ERROR: Ticket is already active!\n");
                else {
                    printf("Are you sure you want to RE-ACTIVATE this closed ticket? ([Y]es|[N]o): ");
                    toChangeStatus = getCharOption("YN");
                    if (toChangeStatus == 'Y') {
                        tickets[ticketIndex].status = 1;
                        printf("\n*** Ticket re-activated! ***\n");
                    }
                }
                break;
            case 0:
                break;
            }
        }
    } while (manageSelection != 0);
}