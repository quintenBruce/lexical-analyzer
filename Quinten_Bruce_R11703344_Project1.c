/*
*    Name: Quinten Bruce
*    R#: R11703344
*    Project: CS3361 Project #1
*
*    Description: a lexical analyzer system for a predifined grammar
*/

#include <stdio.h>
#include <ctype.h>
#include <string.h>

/* Character Classes */
#define LETTER "LETTER"
#define DIGIT "DIGIT"
#define UNKNOWN "UNKNOWN"

/* Token Codes */
#define INT_LIT "INT_LIT"
#define IDENT "IDENT"
#define ADD_OP "ADD_OP"
#define SUB_OP "SUB_OP"
#define MULT_OP "MULT_OP"
#define DIV_OP "DIV_OP"
#define LEFT_PAREN "LEFT_PAREN"
#define RIGHT_PAREN "RIGHT_PAREN"
#define ASSIGN_OP "ASSIGN_OP"
#define NEQUAL_OP "NEQUAL_OP"
#define LEQUAL_OP "LEQUAL_OP"
#define GEQUAL_OP "GEQUAL_OP"
#define INC_OP "INC_OP"
#define DEC_OP "DEC_OP"
#define KEY_READ "KEY_READ"
#define KEY_WRITE "KEY_WRITE"
#define KEY_WHILE "KEY_WHILE"
#define KEY_DO "KEY_DO"
#define KEY_OD "KEY_OD"
#define LESSER_OP "LESSER_OP"
#define GREATER_OP "GREATER_OP"
#define EQUAL_OP "EQUAL_OP"
#define SEMICOLON "SEMICOLON"

/* Global Variable */
int *nextToken;

/* Local Variables */
static int charClass;
static char lexeme[100];
static char nextChar;
static int lexLen;
static FILE *in_fp;

/* Function Declarations */
static void addChar(); // append char to lexeme
static void getChar();
static void getNonBlank();
int lex();


/******************************************************/


/* main driver */
int main(int argc, char *argv[])
{
    printf("DCooke Analyzer :: R11703344\n");
    //if ((in_fp = fopen("front.in", "r")) == NULL) //for debugging local input files
    if ((in_fp = fopen(argv[1], "r")) == NULL) 
        printf("ERROR - cannot open front.in \n");
    else
    {
        getChar();
        do
        {
            lex();
        } while (nextToken != EOF);
    }
    return 0;
}


/* lookupDoubleCharOp - a function to lookup double character operators and return the token */
static int lookupDoubleCharOp(char a, char b)
{
    char op[2];
    op[0] = a;
    op[1] = b;

    if ((strncmp("!=", op, 2) == 0))
        return NEQUAL_OP;
    else if ((strncmp("<=", op, 2) == 0))
        return LEQUAL_OP;
    else if ((strncmp(">=", op, 2) == 0))
        return GEQUAL_OP;
    else if ((strncmp("++", op, 2) == 0))
        return INC_OP;
    else if ((strncmp(":=", op, 2) == 0))
        return ASSIGN_OP;
    else if ((strncmp("--", op, 2) == 0))
        return DEC_OP;
    return UNKNOWN;
}
// postcodition: function will return the matching token code or 
// the UNKOWN token code if no mathing token is found



/* lookup - a function to lookup operators and parentheses and return the token */
static void lookup()
{
    char ch = lexeme[0];
    if (isalpha(ch) && lexLen == 1)
    {
        nextToken = LETTER;
        return;
    }

    if (lexLen == 1)
    {
        switch (ch)
        {
        case '(':
            nextToken = LEFT_PAREN;
            break;
        case ')':
            nextToken = RIGHT_PAREN;
            break;
        case '+':
            nextToken = ADD_OP;
            break;
        case '-':
            nextToken = SUB_OP;
            break;
        case '*':
            nextToken = MULT_OP;
            break;
        case '/':
            nextToken = DIV_OP;
            break;
        case '<':
            nextToken = LESSER_OP;
            break;
        case '>':
            nextToken = GREATER_OP;
            break;
        case '=':
            nextToken = EQUAL_OP;
            break;
        case ';':
            nextToken = SEMICOLON;
            break;
        default:
            nextToken = UNKNOWN;
            break;
        }
    }
    else
    {
        if ((strncmp("!=", lexeme, lexLen) == 0) && (strcmp("!=", lexeme) == 0))
            nextToken = NEQUAL_OP;
        else if ((strncmp("<=", lexeme, lexLen) == 0) && (strcmp("<=", lexeme) == 0))
            nextToken = LEQUAL_OP;
        else if ((strncmp(">=", lexeme, lexLen) == 0) && (strcmp(">=", lexeme) == 0))
            nextToken = GEQUAL_OP;
        else if ((strncmp("++", lexeme, lexLen) == 0) && (strcmp("++", lexeme) == 0))
            nextToken = INC_OP;
        else if ((strncmp("--", lexeme, lexLen) == 0) && (strcmp("--", lexeme) == 0))
            nextToken = DEC_OP;
        else if ((strncmp("read", lexeme, lexLen) == 0) && (strcmp("read", lexeme) == 0))
            nextToken = KEY_READ;
        else if ((strncmp("write", lexeme, lexLen) == 0) && (strcmp("write", lexeme) == 0))
            nextToken = KEY_WRITE;
        else if ((strncmp("do", lexeme, lexLen) == 0) && (strcmp("do", lexeme) == 0))
            nextToken = KEY_DO;
        else if ((strncmp("while", lexeme, lexLen) == 0) && (strcmp("while", lexeme) == 0))
            nextToken = KEY_WHILE;
        else if ((strncmp("od", lexeme, lexLen) == 0) && (strcmp("od", lexeme) == 0))
            nextToken = KEY_OD;
        else if ((strncmp(":=", lexeme, lexLen) == 0) && (strcmp(":=", lexeme) == 0))
            nextToken = ASSIGN_OP;
        else
            nextToken = UNKNOWN;
    }
}
// postcodition: nextToken will be assigned to matching token code or 
// the UNKOWN token code if no mathing token is found



/* addChar - a function to add nextChar to lexeme */
static void addChar()
{
    if (lexLen <= 98)
    {
        lexeme[lexLen++] = nextChar;
        lexeme[lexLen] = 0;
    }
    else
        printf("Error - lexeme is too long \n");
}
// postcondition: nextChar will be appended to lexeme. 
// null character (0) will be set at approppriate position.



/* getChar - a function to get the next character of input and determine its character class */
static void getChar()
{
    if ((nextChar = getc(in_fp)) != EOF)
    {
        if (isalpha(nextChar)) // checks if char is a-z or A-Z
            charClass = LETTER;
        else if (isdigit(nextChar)) // checks if 0-9
            charClass = DIGIT;
        else
            charClass = UNKNOWN;
    }
    else
        charClass = EOF;
}
// postcodition: nextChar will be assigned to next character in file stream.
// charClass will be appropriately assigned a token code



/* getNonBlank - a function to call getChar until it returns a non-whitespace character */
static void getNonBlank()
{
    while (isspace(nextChar))
        getChar();
}



/* lex - a lexical analyzer */
int lex()
{
    lexLen = 0; // 'reset' lexeme array
    getNonBlank();
    addChar();

    /*** Parse Identifiers ***/
    if (charClass == LETTER)
    {
        getChar();
        while (charClass == LETTER)
        {
            addChar();
            getChar();
        }

        if (charClass == DIGIT) // invalid identifier...must be UNKNOWN
        { 
            while (charClass == DIGIT || charClass == LETTER)
            {
                addChar();
                getChar();
            }

            nextToken = UNKNOWN;
        }
        else
        {
            lookup();
            if (nextToken == UNKNOWN || nextToken == LETTER)
                nextToken = IDENT;
        }
    }

    /*** Parse Integer Literals ***/
    else if (charClass == DIGIT)
    {
        getChar();
        while (charClass == DIGIT)
        {
            addChar(); 
            getChar();
        }

        if (charClass == LETTER) // invalid digit.... must be UNKNOWN
        { 
            while (charClass == DIGIT || charClass == LETTER)
            {
                addChar();
                getChar();
            }
            nextToken = UNKNOWN;
        } else
            nextToken = INT_LIT; 
    }

    /*** Parse Parentheses and Operators ***/
    else if (charClass == UNKNOWN)
    {
        lookup();

        char a = nextChar;
        getChar();

        if (charClass == UNKNOWN && !isspace(nextChar)) // next character is not a space, letter, or number. 
        {
            char b = nextChar;
            int charPairTokenCode = lookupDoubleCharOp(a, b); 
            if (charPairTokenCode != UNKNOWN) // double char lexeme is a recognized token.
            {
                nextToken = charPairTokenCode;
                addChar();
                getChar();
            }
        } else // double char is not a recognized token. 
            lookup();
    }

    /*** EOF ***/
    else if (charClass == EOF)
    {
        nextToken = EOF;
        return -1; 
    }

    printf("%s    %s\n", lexeme, nextToken);
    return nextToken;
}
// postcondtion: function will print out the next lexeme and corrosponding token name and 
// will return the token name.