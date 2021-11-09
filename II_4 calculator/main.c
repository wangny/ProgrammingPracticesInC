#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

/*
Something like Python

>> y = 2
>> z = 2
>> x = 3*y + 4/(2*z)

*/


/*
the only type: integer
everything is an expression
  statement   := END | expr END
  expr            := add_expr   expr_tail
  expr_tail       := LTGT   add_expr   expr_tail | NIL
  add_expr        := term   add_expr_tail
  add_expr_tail   := ADDSUB   term     add_expr_tail | NIL
  term        := factor term_tail
  term_tail := MULDIV factor term_tail | NIL
  factor      := INT | ADDSUB INT | ADDSUB ID | ID ASSIGN expr | ID | LPAREN expr RPAREN
*/

#ifndef __LEX__
#define __LEX__
#define MAXLEN 256
typedef enum {UNKNOWN, END, INT, ID, ADDSUB, MULDIV, ASSIGN,
LPAREN, RPAREN, LTGT} TokenSet;
char lexeme[MAXLEN];

extern int match (TokenSet token);
extern void advance(void);
#endif // __LEX__

static TokenSet getToken(void);
static TokenSet lookahead = UNKNOWN;

TokenSet getToken(void)
{
    int i;
    char c;

    while ( (c = fgetc(stdin)) == ' ' || c== '\t' );  // deal with space

    if (isdigit(c)) {
        lexeme[0] = c;
        c = fgetc(stdin);
        i = 1;
        while (isdigit(c) && i<MAXLEN) {
            lexeme[i] = c;
            ++i;
            c = fgetc(stdin);
        }
        ungetc(c, stdin);
        lexeme[i] = '\0';
        return INT;
    } else if (c == '+' || c == '-') {
        lexeme[0] = c;
        lexeme[1] = '\0';
        return ADDSUB;
    } else if (c == '*' || c == '/'|| c=='%') {
        lexeme[0] = c;
        lexeme[1] = '\0';
        return MULDIV;
    }   else if (c == '>' || c == '<') {
        lexeme[0] = c;
        lexeme[1] = '\0';
        return LTGT;
    } else if (c == '\n') {
        lexeme[0] = '\0';
        return END;
    } else if (c == '=') {
        strcpy(lexeme, "=");
        return ASSIGN;
    } else if (c == '(') {
        strcpy(lexeme, "(");
        return LPAREN;
    } else if (c == ')') {
        strcpy(lexeme, ")");
        return RPAREN;
    } else if (isalpha(c) || c == '_') {
        lexeme[0] = c;
        c = fgetc(stdin);
        i = 1;
        while (isalpha(c) || isdigit(c) || c == '_') {
            lexeme[i] = c;
            ++i;
            c = fgetc(stdin);
        }
        ungetc(c, stdin);
        lexeme[i] = '\0';
        return ID;
    } else {
        return UNKNOWN;
    }
}

void advance(void)
{
    lookahead = getToken();
}

int match(TokenSet token)
{
    if (lookahead == UNKNOWN) advance();
    return token == lookahead;
}



#define TBLSIZE 65535
typedef struct {
    char name[MAXLEN];
    int val;
} Symbol;
Symbol table[TBLSIZE];
int sbcount = 0;

void statement(void);
int expr(void);
int add_expr(void);
int term(void);
int factor(void);
int getval(void);
int setval(char*, int);

typedef enum {MISPAREN, NOTNUMID, NOTFOUND, RUNOUT} ErrorType;
void error(ErrorType errorNum);


int getval(void)
{
    int i, retval, found;

    if (match(INT)) {
        retval = atoi(lexeme);
    } else if (match(ID)) {
        i = 0; found = 0; retval = 0;
        while (i<sbcount && !found) {
            if (strcmp(lexeme, table[i].name)==0) {
                retval = table[i].val;
                found = 1;
                break;
            } else {
                i++;
            }
        }
        if (!found) {
            if (sbcount < TBLSIZE) {
                strcpy(table[sbcount].name, lexeme);
                table[sbcount].val = 0;
                sbcount++;
            } else {
                error(RUNOUT);
            }
        }
    }
    return retval;
}

int setval(char *str, int val)
{
    int i, retval;
    i = 0;
    while (i<sbcount) {
        if (strcmp(str, table[i].name)==0) {
            table[i].val = val;
            retval = val;
            break;
        } else {
            i++;
        }
    }
    return retval;
}

int expr(void)
{
    int retval;

    retval = add_expr();
    while (match(LTGT)) {
        if (strcmp(lexeme, ">")==0) {
            advance();
            if(retval > add_expr()){
                retval=1;
            }else {
                retval=0;
            }
        } else if (strcmp(lexeme, "<")==0) {
            advance();
            if(retval < add_expr()){
                retval=1;
            }else {
                retval=0;
            }
        } else {
            // Nil
        }
    }


    return retval;
}

int add_expr(void)
{
    int retval;

    retval = term();
    while (match(ADDSUB)) {
        if (strcmp(lexeme, "+")==0) {
            advance();
            retval += term();
        } else if (strcmp(lexeme, "-")==0) {
            advance();
            retval -= term();
        } else {
            // Nil
        }
    }


    return retval;
}

int term(void)
{
    int retval;
    retval = factor();
    while (match(MULDIV)) {
        if (strcmp(lexeme, "*")==0) {
            advance();
            retval *= factor();
        } else if (strcmp(lexeme, "/")==0) {
            advance();
            retval /= factor();
        } else if (strcmp(lexeme, "%")==0) {
            advance();
            retval %= factor();
        } else {
            //Nil
        }
    }
    return retval;
}

int factor(void)
{
    int retval = 0;
    char tmpstr[MAXLEN];

    if (match(INT)) {
        retval = getval();
        advance();
    } else if (match(ID)) {
        retval = getval();
        strcpy(tmpstr, lexeme);
        advance();
        if (match(ASSIGN)) {
            advance();
            retval = expr();
            retval = setval(tmpstr, retval);
        }
    } else if (match(ADDSUB)) {
        strcpy(tmpstr, lexeme);
        advance();
        if (match(ID) || match(INT)) {
            retval = getval();
            if (strcmp(tmpstr, "-")==0) {
                retval = -retval;
            }
            advance();
        } else {
            error(NOTNUMID);
        }
    }else if (match(LPAREN)) {
        advance();
        retval = expr();
        if (match(RPAREN)) {
            advance();
        } else {
            error(MISPAREN);
        }
    } else {
        error(NOTNUMID);
    }
    return retval;
}

void error(ErrorType errorNum)
{
    switch (errorNum) {
    case MISPAREN:
        fprintf(stderr, "Mismatched parenthesis\n");
        break;
    case NOTNUMID:
        fprintf(stderr, "Number or identifier expected\n");
        break;
    case NOTFOUND:
        fprintf(stderr, "%s not defined\n", lexeme);
        break;
    case RUNOUT:
        fprintf(stderr, "Out of memory\n");
    }
    exit(0);
}

void statement(void)
{
    int retval;

    if (match(END)) {
        advance();
    } else {
        retval = expr();
        if (match(END)) {
            printf("%d\n", retval);
            advance();
        }
    }
}

int main()
{
    while (1) {
        statement();
    }
    return 0;
}
