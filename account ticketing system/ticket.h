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

#ifndef TICKET_H_
#define TICKET_H_

#define ACCOUNT_SIZE 15
#define TICKET_SIZE 17

#include "account.h"
#include "accountTicketingUI.h"
#include "commonHelpers.h"


struct Message {
    char accType;
    char fullName[30];
    char messageDetails[150];
};

struct Ticket {
    int ticketNo;
    int accountNo;
    int status;
    char subjectLine[30];
    int messageCounter;
    struct Message messages[20];
};

// This function takes account structure array and integer max and returns the highest account number
int highestAccountNo(const struct Account *account, int max);
// This function takes ticket structure array and integer max and returns the highest account number
int highestTicketNo(const struct Ticket *ticket, int max);
// takes account array, and max account as parameters, and loads the account
int loadAccounts(struct Account *account, int accSize);
// takes ticket array, and max ticket as parameters, and loads the tickets
int loadTickets(struct Ticket *ticket, int ticketSize);
// takes account array, and max account as parameters, and saves the accounts
int saveAccounts(struct Account *account, int accSize);
// takes ticket array, and max ticket as parameters, and saves the tickets
int saveTickets(struct Ticket *ticket, int ticketSize);
// takes ticket array, and max ticket as parameters, and lists new tickets
void listNewTickets(struct Ticket *tickets, int max);
// takes ticket array, and max ticket as parameters, and lists active tickets
void listActiveTickets(struct Ticket *tickets, int max);
// takes ticket array, and max ticket as parameters, and lists closed tickets
void listClosedTickets(struct Ticket *tickets, int max);
// takes ticket array, and max ticket as parameters, and adds a new ticket
void addNewTicket(struct Account *accounts, struct Ticket *tickets, int maxAcc, int maxTicket);
// takes ticket array, logged in account addres, and max ticket as parameters, and manages tickets
void manageTicket(struct Ticket *tickets, const struct Account loggedInAcc, int max);
#endif // !TICKET_H_