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
#include "commonHelpers.h"
#include <time.h>
#include "ticket.h"

 // Uses the time.h library to obtain current year information
 // Get the current 4-digit year from the system
int currentYear(void)
{
    time_t currentTime = time(NULL);
    return localtime(&currentTime)->tm_year + 1900;
}
// As demonstrated in the course notes: 
// https://ict.senecacollege.ca//~ipc144/pages/content/formi.html#buf
// Empty the standard input buffer
void clearStandardInputBuffer(void)
{
    while (getchar() != '\n')
    {
        ; // On purpose: do nothing
    }
}

int getInteger(void) {
    char newLine = 'x';
    int value;

    do {
        scanf("%d%c", &value, &newLine);
        if (newLine != '\n') {
            clearStandardInputBuffer();
            printf("ERROR: Value must be an integer: ");
        }
    } while (newLine != '\n');

    return value;
}

int getPositiveInteger(void) {
    char newLine = 'x';
    int value;

    do {
        scanf("%d%c", &value, &newLine);

        if (newLine != '\n' || value <= 0) {
            printf("ERROR: Value must be a positive integer greater than zero: ");
            if (newLine != '\n')  clearStandardInputBuffer();
        }
    } while (newLine != '\n' || value <= 0);
    return value;
}
double getDouble(void) {
    char newLine = 'x';
    double value;

    do {
        scanf("%lf%c", &value, &newLine);
        if (newLine != '\n') {
            clearStandardInputBuffer();
            printf("ERROR: Value must be a double floating-point number: ");
        }
    } while (newLine != '\n');
    return value;
}

double getPositiveDouble() {
    char newLine = 'x';
    double value;

    do {
        scanf("%lf%c", &value, &newLine);

        if (newLine != '\n' || value <= 0.0) {
            if (newLine != '\n') {
                printf("ERROR: Value must be a double floating-point number: ");
            }
            else if (newLine == '\n' && value <= 0.0) {
                printf("ERROR: Value must be a positive double floating-point number: ");
            }
            if (newLine != '\n')  clearStandardInputBuffer();
        }
    } while (newLine != '\n' || value <= 0.0);
    return value;
}

int getIntFromRange(int lowerBound, int upperBound) {
    int value;

    do {
        value = getInteger();
        if ((value < lowerBound || value > upperBound)) {
            printf("ERROR: Value must be between %d and %d inclusive: ", lowerBound, upperBound);    
        }
    } while ((value < lowerBound || value > upperBound));
    return value;
}


char getCharOption(const char* validChars) {
    char value, newLine = 'x';
    int found = 0;
    do {
        scanf("%c%c", &value, &newLine);
        if (newLine != '\n') {
            clearStandardInputBuffer();
            printf("ERROR: Character must be one of [%s]: ", validChars);
        }
        else {
            int i;
            for (i = 0; validChars[i] != '\0'; i++) {
                if (value == validChars[i]) {
                    found = 1;
                    value = validChars[i];
                }
            }
            if (found != 1) {
                printf("ERROR: Character must be one of [%s]: ", validChars);
            }
        }

    } while (newLine != '\n' || found != 1);
    return value;
}

void getCString(char* cString, int min, int max) {
    char local[50], newLine = '\n';
    int length;

    do {
        scanf("%[^\n]s%c", local, &newLine);
        if (newLine != '\n') {
            clearStandardInputBuffer();
        }
        else {
            
            length = strlen(local);
            if ((newLine != '\n' || length < min || length > max)) {
                if (max == min && length != max) {
                    printf("ERROR: String length must be exactly %d chars: ", max);
                }
                else if (length < min) {
                    printf("ERROR: String length must be between %d and %d chars: ", min, max);
                }
                else if (length > max) {
                    printf("ERROR: String length must be no more than %d chars: ", max);
                }
            }
        }
        clearStandardInputBuffer();
    } while (newLine != '\n' || length < min || length > max);

    if (cString != NULL) {
        strcpy(cString, local);
    }
}

int isCharInString(char* string, char c, int max) {
    int i, found = 0;
    for (i = 0; i < max; i++) {
        if (c == string[i]) found = 1;
    }
    return found;
}