%{
#include <stdio.h>
#include <stdlib.h>

int valid = 1; // To keep track of whether the string is valid

// Function prototypes
int validate_S();
int validate_L();
int validate_L_();

%}

S   (\ L \) | a
L   S L_
L_  , S L_ | \0

%%
\(    { if (!validate_L()) valid = 0; }
\)    { if (yymore()) valid = 0; }
a     { if (yymore()) valid = 0; }
,     { if (!validate_S()) valid = 0; }
.     { valid = 0; } /* Any other character is invalid */
\n    { /* End of input */ return 0; }
%%

int validate_S() {
    if (input() == '(') {
        return validate_L() && (input() == ')');
    }
    return input() == 'a';
}

int validate_L() {
    return validate_S() && validate_L_();
}

int validate_L_() {
    if (input() == ',') {
        return validate_S() && validate_L_();
    }
    unput(',');
    return 1; // \0 (epsilon) case
}

int yywrap() {
    return 1;
}

int main() {
    yylex();
    if (valid) {
        printf("Valid string\n");
    } else {
        printf("Invalid string\n");
    }
    return 0;
}
