#pragma once
/*
    ==================================================
    Assignment #2 Milestone #4
    ==================================================
    Name    : Tarik Ozturk
    ID      : 155237209
    Email   : tozturk1@myseneca.ca
    Section : NCC
 */

#ifndef ACCOUNT_TICKETING_UI_H_
#define ACCOUNT_TICKETING_UI_H_

#include "ticket.h"
#include "account.h"
#include "commonHelpers.h"

struct AccountTicketingData
{
    struct Account* accounts; // array of accounts
    const int ACCOUNT_MAX_SIZE; // maximum elements for account array
    struct Ticket* tickets; // array of tickets
    const int TICKET_MAX_SIZE; // maximum elements for ticket array
};

 // This function displays the header of account details
void displayAccountDetailHeader(void);
// This function displays the records of account details
void displayAccountDetailRecord(const struct Account *account);
// This function starts the application
void applicationStartup(struct AccountTicketingData *accountTicketingData);
// This function sets the login menu
int menuLogin(const struct Account *account, int max);
// This function sets the agent menu
void menuAgent(struct AccountTicketingData accountTicketingData, const struct Account *loggedInAcc);
// This function displays all the accounts records
void displayAllAccountDetailRecords(const struct Account *account, int max);
// Displays the header of status
void displayStatusHeader(void);
// Pause execution until user enters the enter key
void pauseExecution(void);
#endif // !ACCOUNT_TICKETING_UI_H_