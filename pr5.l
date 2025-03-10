%{
#include <stdio.h>
// #include "y.tab.h"
%}

/* Regular Definitions */
DIGIT   [0-9]
ID      [a-zA-Z_][a-zA-Z0-9_]*
KEYWORD (int|char|void|return|long|float|struct)
OPERATOR [=+\-*/]
PUNCTUATION [;{}(),]
CONSTANT {DIGIT}+
STRING '([^']*)'
COMMENT \/\*([^*]|\*+[^*/])*\*+\/|\/\/.*

%%
{KEYWORD}       { printf("Keyword: %s\n", yytext); }
{ID}            { printf("Identifier: %s\n", yytext); }
{OPERATOR}      { printf("Operator: %s\n", yytext); }
{PUNCTUATION}   { printf("Punctuation: %s\n", yytext); }
{CONSTANT}      { printf("Constant: %s\n", yytext); }
{STRING}        { printf("String: %s\n", yytext); }
{COMMENT}       { /* Ignore comments */ }
[ \t\n]         { /* Ignore whitespace */ }
.               { printf("Lexical Error: %s\n", yytext); }
%%

int main() {
yylex();
return 0;
}

int yywrap() {
return 1;
}
