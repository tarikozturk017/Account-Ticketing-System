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

void getAccount(struct Account* account) {
    char* accountTypes = "AC";

    printf("New Account Data (Account#:%d)\n", account->accountNo);
    printf("----------------------------------------\n");
    printf("Enter the account type (A=Agent | C=Customer): ");
    account->accType = getCharOption(accountTypes);
    printf("\n");
    getPerson(&account->person);
    if (account->accType == 'A') {
        getUserLogin(&account->userLogin);
    }
    else {
        *account->userLogin.loginName = '\0';
        *account->userLogin.password = '\0';
    }
}

void getPerson(struct Person* person) {
    int maxName = 30, i;
    int maxBirthYear = 2003;
    int minBirthYear = 1911;

    printf("Person Data Input\n");
    printf("----------------------------------------\n");

    printf("Enter the person's full name (%d chars max): ", maxName);
    getCString(person->fullName, 0, maxName);

    int curYear = currentYear();
    printf("Enter birth year (current age must be between %d and %d): ", curYear - maxBirthYear, curYear - minBirthYear);
    person->birthYear = getIntFromRange(minBirthYear, maxBirthYear);

    printf("Enter the household Income: $");
    person->householdIncome = getPositiveDouble();

    printf("Enter the country (%d chars max.): ", maxName);
    getCString(person->country, 0, maxName);
    int lenCountry = strlen(person->country);
    for (i = 0; i < lenCountry; i++) person->country[i] = toupper(person->country[i]);
    printf("\n");
}

void getUserLogin(struct UserLogin* userLogin) {
    int loginMaxChar = 10;
    int passwLen = 8, whiteSpaceFound, upperRequirment = 0, lowerRequirment = 0, 
        digitRequirment = 0, symbolCharsReq = 0, i, symbolLen = 9;
    char* symbolChars = " !@#$%^&*";

    printf("User Login Data Input\n");
    printf("----------------------------------------\n");
    
    do {
        whiteSpaceFound = 1;
        printf("Enter user login (%d chars max): ", loginMaxChar);
        getCString(userLogin->loginName, 0, loginMaxChar);
        int lenLogName = strlen(userLogin->loginName);
        for (i = 0; i < lenLogName; i++) {
            if (userLogin->loginName[i] == ' ') {
                whiteSpaceFound = 0;
                printf("ERROR:  The user login must NOT contain whitespace characters.\n");
            }
        }
    } while (whiteSpaceFound == 0);
    

    do {
        upperRequirment = 0, lowerRequirment = 0, digitRequirment = 0, symbolCharsReq = 0;
        printf("Enter the password (must be %d chars in length): ", passwLen);
        getCString(userLogin->password, passwLen, passwLen);
        for (i = 0; i < passwLen; i++) {
            if (isupper(userLogin->password[i]) != 0) upperRequirment++;
            else if (islower(userLogin->password[i]) != 0) lowerRequirment++;
            else if (isdigit(userLogin->password[i]) != 0) digitRequirment++;
            else if (isCharInString(symbolChars, userLogin->password[i], symbolLen) != 0) symbolCharsReq++;
        }
        if ((upperRequirment != 2) || (lowerRequirment != 2) || (digitRequirment != 2) || (symbolCharsReq != 2)) {
            printf("SECURITY: Password must contain 2 of each:\n");
            printf("          Digit: 0-9\n");
            printf("          UPPERCASE character\n");
            printf("          lowercase character\n");
            printf("          symbol character:%s\n", symbolChars);
        }
    } while ((upperRequirment != 2) || (lowerRequirment != 2) || (digitRequirment != 2) || (symbolCharsReq != 2));
    printf("\n");
    }

void updateAccount(struct Account* account) {
    int selection;
    char newType;

    do {
        printf("Update Account: %5d (%s)\n", account->accountNo, account->person.fullName);
        printf("----------------------------------------\n");
        printf("1) Update account type (current value: %c)\n", account->accType);
        printf("2) Person\n");
        printf("3) Login\n");
        printf("0) Done\n");
        printf("Selection: ");
        selection = getIntFromRange(0, 3);
        printf("\n");
        switch (selection)
        {
        case 1:
            printf("Enter the account type (A=Agent | C=Customer): ");
            newType = getCharOption("AC");
            printf("\n");
            account->accType = newType;
            if (newType == 'A') {
                printf("Agent type accounts require a user login.  Please enter this information now:\n\n");
                getUserLogin(&account->userLogin);
            }
            else if (newType == 'C') {
                *account->userLogin.loginName = '\0';
                *account->userLogin.password = '\0';
            }
            break;
    
        case 2:
            updatePerson(&account->person);
            break;
    
        case 3:
            if (account->accType == 'C') {
                printf("ERROR:  Customer account types don't have user logins!\n\n");
            }
            else {
                updateUserLogin(&account->userLogin);
            }
            break;
        case 0:
            break;
        }
    } while (selection > 0 && selection <= 3);
}

void updatePerson(struct Person* person) {
    int selection, maxName = 30, i;

    do {
        printf("Person Update Options\n");
        printf("----------------------------------------\n");
        printf("1) Full name (current value: %s)\n", person->fullName);
        printf("2) Household Income (current value: $%.2lf)\n", person->householdIncome);
        printf("3) Country (current value: %s)\n", person->country);
        printf("0) Done\n");
        printf("Selection: ");
        selection = getIntFromRange(0, 3);
        printf("\n");
        switch (selection)
        {
        case 1:
            printf("Enter the person's full name (%d chars max): ", maxName);
            getCString(person->fullName, 0, maxName);
            printf("\n");
            break;

        case 2:
            printf("Enter the household Income: $");
            person->householdIncome = getPositiveDouble();
            printf("\n");
            break;

        case 3:
            printf("Enter the country (%d chars max.): ", maxName);
            getCString(person->country, 0, maxName);
            int lenCountry = strlen(person->country);
            for (i = 0; i < lenCountry; i++) {
                person->country[i] = toupper(person->country[i]);
            }
            printf("\n");
            break;

        case 0:
            break;
        }
    } while (selection > 0 && selection <= 3);
}

void updateUserLogin(struct UserLogin* userLogin) {
    int selection, passwLen = 8, upperRequirment = 0, lowerRequirment = 0,
        digitRequirment = 0, symbolCharsReq = 0, i, symbolLen = 9;
    char* symbolChars = " !@#$%^&*";

    do {
    printf("User Login: %s - Update Options\n", userLogin->loginName);
    printf("----------------------------------------\n");
    printf("1) Password\n");
    printf("0) Done\n");
    printf("Selection: ");

    selection = getIntFromRange(0, 1);
    printf("\n");
    switch (selection)
    {
    case 1:
        do {
            printf("Enter the password (must be %d chars in length): ", passwLen);
            getCString(userLogin->password, passwLen, passwLen);
            for (i = 0; i < passwLen; i++) {
                if (isupper(userLogin->password[i]) != 0) upperRequirment++;
                else if (islower(userLogin->password[i]) != 0) lowerRequirment++;
                else if (isdigit(userLogin->password[i]) != 0) digitRequirment++;
                else if (isCharInString(symbolChars, userLogin->password[i], symbolLen) != 0) symbolCharsReq++;
            }
            if ((upperRequirment < 2) || (lowerRequirment < 2) || (digitRequirment < 2) || (symbolCharsReq < 2)) {
                printf("SECURITY: Password must contain 2 of each:\n");
                printf("          Digit: 0-9\n");
                printf("          UPPERCASE character\n");
                printf("          lowercase character\n");
                printf("          symbol character:%s\n", symbolChars);
            }
        } while ((upperRequirment < 2) || (lowerRequirment < 2) || (digitRequirment < 2) || (symbolCharsReq < 2));
        printf("\n");
        break;
    case 0:
        break;
    }
    } while (selection == 1);
}