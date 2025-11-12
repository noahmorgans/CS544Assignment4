#include <stdio.h>
#include <string.h>
#include <ctype.h>

int isPositiveInteger(char token[]);
int isNegativeInteger(char token[]);
int isBinaryNumber(char token[]);
int isGuid(char token[]);
int isPositiveFloatingPoint(char token[]);
int isNegativeFloatingPoint(char token[]);

int main() {

    char token[100];
    printf("Enter a token to identify, EOF to stop:\n");
    scanf("%s", token);

    while(!feof(stdin)) {

        if (isPositiveInteger(token))
            printf("The token is a positive integer\n");        
        else if (isNegativeInteger(token))
            printf("The token is a negative integer\n");
        else if (isBinaryNumber(token))
            printf("The token is a binary number\n");        
        else if (isGuid(token))
            printf("The token is a guid\n");
        else if (isPositiveFloatingPoint(token))
            printf("The token is a positive floating-point number\n");       
        else if (isNegativeFloatingPoint(token))
            printf("The token is a negative floating-point number\n");
        else
            printf("The token cannot be identified\n");
    
        printf("Enter a token to identify, EOF to stop:\n");
        scanf("%99s", token);
    }

    return 0;
}

int isPositiveInteger(char token[]) {

    for (int i = 0; i < strlen(token); i++) {
        if (!isdigit(token[i]))
            return 0;
    }

    return 1;
}

int isNegativeInteger(char token[]) {

    if (token[0] != '-')
        return 0;

    for (int i = 1; i < strlen(token); i++) {
        if (!isdigit(token[i]))
            return 0;
    }

    return 1;
}

int isBinaryNumber(char token[]) {

    if (token[0] != '0')
        return 0;

    if (token[1] != 'b')
        return 0;

    for (int i = 2; i < strlen(token); i++) {
        if ((token[i] != '0') && (token[i] != '1'))
            return 0;
    }

    if (strlen(token) > 2)
        return 1;
    else
        return 0;
}

int isGuid(char token[]) {

    if (strlen(token) != 36)
        return 0;

    for (int i = 0; i < 8; i++) {
        if (!isxdigit(token[i]))
            return 0;
    }

    if (token[8] != '-')
        return 0;
    
    for (int i = 9; i < 13; i++) {
        if (!isxdigit(token[i]))
            return 0;
    }

    if (token[13] != '-')
        return 0;
    
    for (int i = 14; i < 18; i++) {
        if (!isxdigit(token[i]))
            return 0;
    }

    if (token[18] != '-')
        return 0;
    
    for (int i = 19; i < 23; i++) {
        if (!isxdigit(token[i]))
            return 0;
    }

    if (token[23] != '-')
        return 0;
    
    for (int i = 24; i < 36; i++) {
        if (!isxdigit(token[i]))
            return 0;
    }

    return 1;
}

int isPositiveFloatingPoint(char token[]) {

    int countDot = 0;

    if (token[0] == '.')
        return 0;

    if (token[strlen(token) - 1] == '.')
        return 0;

    for (int i = 0; i < strlen(token); i++) {
        if (!isdigit(token[i]) && token[i] != '.')
            return 0;
        if (token[i] == '.')
            countDot++;
    }

    if (countDot != 1)
        return 0;

    return 1;
}

int isNegativeFloatingPoint(char token[]) {

    int countDot = 0;

    if (token[0] != '-')
        return 0;

    if (token[1] == '.')
        return 0;
    
    if (token[strlen(token) - 1] == '.')
        return 0;

    for (int i = 1; i < strlen(token); i++) {
        if (!isdigit(token[i]) && token[i] != '.')
            return 0;
        if (token[i] == '.')
            countDot++;
    }

    if (countDot != 1)
        return 0;

    return 1;
}