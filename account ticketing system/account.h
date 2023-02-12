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

#ifndef ACCOUNT_H_
#define ACCOUNT_H_

#include "ticket.h"
#include "accountTicketingUI.h"
#include "commonHelpers.h"

struct Person {
    char fullName[30];
    int birthYear;
    double householdIncome;
    char country[30];
};

struct UserLogin {
    char loginName[11];
    char password[9];
};

struct Account {
    int accountNo;
    char accType;
    struct Person person;
    struct UserLogin userLogin;
};
// This function prompts user to enter account number and account type
void getAccount(struct Account* account);
// This function prompts user to enter the full name, the birth year, the household income, and the country
void getPerson(struct Person* person);
// This function prompts user to enter the login name and the password
void getUserLogin(struct UserLogin* userLogin);
// This function updates the Account structure array
void updateAccount(struct Account* account);
// This function updates the Person structure array
void updatePerson(struct Person* person);
// This function updates the UserLogin structure array
void updateUserLogin(struct UserLogin* userLogin);

#endif // !ACCOUNT_H_