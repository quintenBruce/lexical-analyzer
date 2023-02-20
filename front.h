#ifndef FRONT_H
#define FRONT_H

/* Character classes */
#define LETTER 0
#define DIGIT 1
#define UNKNOWN 99

/* Token codes */
#define INT_LIT 10
#define IDENT 11

#define ADD_OP 21
#define SUB_OP 22
#define MULT_OP 23
#define DIV_OP 24
#define LEFT_PAREN 25
#define RIGHT_PAREN 26


#define ASSIGN_OP 31
#define NEQUAL_OP 32
#define LEQUAL_OP 33
#define GEQUAL_OP 34
#define INC_OP 35
#define DEC_OP 36
#define KEY_READ 37
#define KEY_WRITE 38
#define KEY_WHILE 39

#define KEY_DO 40
#define KEY_OD 41

#define LESSER_OP 50
#define GREATER_OP 51
#define EQUAL_OP 52
#define SEMICOLON 53



int lex();

#endif
