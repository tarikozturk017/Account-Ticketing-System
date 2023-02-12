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

#ifndef COMMON_HELPERS_H_
#define COMMON_HELPERS_H_
 // this function calculates the current year
int currentYear(void);
// this function clears the buffer
void clearStandardInputBuffer(void);
// this function prompts user to enter an integer
int getInteger(void);
// this function prompts user to enter a positive integer
int getPositiveInteger(void);
// this function prompts user to enter a double
double getDouble(void);
// this function prompts user to enter a positive double
double getPositiveDouble(void);
// this function prompts user to enter an integer between the received bounds
int getIntFromRange(int lowerBound, int upperBound);
// this function prompts user to enter a character and checks if it is in received string
char getCharOption(const char* validChars);
// this function prompts user to enter a string that's length between receieved integers
void getCString(char* cstringValue, int min, int max);
// This function takes a string, a char and max length of the string, and returns if it is true or not
int isCharInString(char* string, char c, int max);

#endif // !COMMON_HELPERS_H_