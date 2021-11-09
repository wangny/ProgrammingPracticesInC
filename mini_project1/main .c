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
  expr        := term expr_tail
  expr_tail   := ADDSUB term expr_tail | NIL
  term        := factor term_tail
  term_tail := MULDIV factor term_tail | NIL
  factor      := INT | ADDSUB INT | ADDSUB ID | ID ASSIGN expr | ID | LPAREN expr RPAREN
*/

#ifndef __LEX__
#define __LEX__
#define MAXLEN 256
typedef enum {UNKNOWN, END, INT, ID, ADDSUB, MULDIV, ASSIGN,
LPAREN, RPAREN, EXIT} TokenSet;
char lexeme[MAXLEN];

extern int match (TokenSet token);
extern void advance(void);
#endif // __LEX__

static TokenSet getToken(void);
static TokenSet lookahead = UNKNOWN;

typedef enum {MISPAREN, NOTNUMID, NOTFOUND, RUNOUT} ErrorType;

int dontusei=0;

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
    } else if (c == '*' || c == '/') {
        lexeme[0] = c;
        lexeme[1] = '\0';
        return MULDIV;
    } else if (c == '\n') {
        lexeme[0] = '\0';
        return END;
    }else if (c == EOF) {
        lexeme[0] = '\0';
        return EXIT;
    }else if (c == '=') {
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
        dontusei++;
        if(dontusei>1) error(MISPAREN);
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


#define TBLSIZE 4
typedef struct symbol{
    char name[2];
    int val;
} Symbol;
Symbol table[TBLSIZE];
int sbcount = -1;
int ask=-1;

int mem[64];
int memnum=0;
int change=-1;

void statement(void);
int expr(void);
int term(int);
int factor(void);
int getval(void);
//int setval(char*, int);


void error(ErrorType errorNum);


int getval(void)
{
    int i;
    int retval;
    char tmpstr[MAXLEN];

    if (match(INT)) {
        retval=atoi(lexeme);
    } else if (match(ID)) {
        i = 0;
        while (i<3) {
            if (strcmp(lexeme, table[i].name) == 0) {
                retval=i;

                break;
            } else {
                i++;
            }
        }
        /*if (!found) {
            if (sbcount < TBLSIZE) {
                strcpy(table[sbcount].name, lexeme);
                table[sbcount].val = 0;
                sbcount++;
            } else {
                error(RUNOUT);
            }
        }*/
    }

    return retval;
}

/*int setval(char *str, int val)
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
}*/

int expr(void)
{
    int retval;
    int tmp;

    retval = term(-1);

    while (match(ADDSUB)) {
        if (strcmp(lexeme, "+")==0) {
            advance();
            tmp = term(retval);
            printf("ADD r%d, r%d\n",retval,tmp);
            //retval += tmp;

        } else if (strcmp(lexeme, "-")==0) {
            advance();
            tmp = term(retval);
            printf("SUB r%d, r%d\n",retval,tmp);
            //retval -= tmp;
        } else {
            // Nil
        }
    }

    return retval;
}

int term(int last)
{
    int retval;
    int tmp,tmp2,yes=0;
    retval = factor();

    while (match(MULDIV)) {

        if(last>=0){
            tmp2=last;
            printf("MOV [%d], r%d\n",memnum*4,tmp2);
            printf("MOV r%d, r%d\n",tmp2,retval);
            yes=1;
        }else if(yes!=1&& last>=0){tmp2=retval;}

        if (strcmp(lexeme, "*")==0) {
            advance();
            tmp = factor();
            printf("MUL r%d, r%d\n", tmp2,tmp);
        } else if (strcmp(lexeme, "/")==0) {
            advance();
            tmp = factor();
            printf("DIV r%d, r%d\n", tmp2,tmp);

        } else {
            // Nil
        }


        last=-1;
    }

    if(yes==1){
            printf("MOV r%d, r%d\n",tmp,tmp2);
            retval=tmp;
            printf("MOV r%d, [%d]\n",tmp2,memnum*4);
            yes=0;
    }

    return retval;
}

int factor(void)
{
    int retval = 0;

    char tmpstr[MAXLEN];

    if (match(INT)) {
        retval = getval();
        if(sbcount>=0){
            printf("MOV r%d, %d\n",sbcount,retval);
            retval=sbcount;
            sbcount=-1;
        }else if(sbcount==-1){
            printf("MOV r3, %d\n",retval);
            retval=3;
        }
        advance();
    } else if (match(ID)) {
        retval = getval();
        strcpy(tmpstr, lexeme);
        advance();
        if (match(ASSIGN)) {
            sbcount=retval;
            ask=sbcount;
            advance();
            if (match(ADDSUB)) {   ///ÅÜ¸¹
            strcpy(tmpstr, lexeme);
            advance();
            if (match(INT)) {
                retval = getval();
                if (strcmp(tmpstr, "-")==0) {
                    if(sbcount>=0){
                        printf("MOV r%d, -%d\n",sbcount,retval);
//                        retval=sbcount;
//                        sbcount=-1;
                    }
                }
                retval=sbcount;
                sbcount=-1;
                advance();
            }
            else if(match(ID)){
                retval = getval();
                printf("MOV r3, -1\n");
                printf("MUL r%d, r3\n",retval);
                printf("MOV r%d, r%d\n",sbcount, retval);
                retval = sbcount;
                sbcount=-1;
                advance();
            }
            else {
                error(NOTNUMID);
            }
        }
        }else if(sbcount>=0){
            printf("MOV r%d, r%d\n",sbcount,retval);
            retval=sbcount;
            sbcount=-1;
        }

    }else if (match(LPAREN)) {
        if(sbcount==-1){
            printf("MOV [%d], r%d\n",memnum*4,ask);
            sbcount=ask;
            change=memnum;
            memnum++;
        }
        advance();
        retval = expr();
        if (match(RPAREN)) {
            if(change>=0){
                printf("MOV r%d, r%d\n",3,ask);
                printf("MOV r%d, [%d]\n",ask,change*4);
                change=-1;
                retval=3;
            }
            advance();
        } else {
            error(MISPAREN);
        }
    }else if (match(ADDSUB)) {   ///ÅÜ¸¹
            strcpy(tmpstr, lexeme);
            advance();
            if (match(INT)) {
                retval = getval();
                if (strcmp(tmpstr, "-")==0) {
                    if(sbcount>=0){
                        printf("MOV r%d, -%d\n",sbcount,retval);
                        retval=sbcount;
                        sbcount=-1;
                    }
                }
                advance();
            } else {
                error(NOTNUMID);
            }
        }
    else {
        error(NOTNUMID);
    }

    return retval;
}

void error(ErrorType errorNum)
{
    /*switch (errorNum) {
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
    }*/
    printf("EXIT 1\n");
    exit(0);
}

void statement(void)
{
    int retval;

    if(match(EXIT)){
        printf("EXIT 0\n");
        exit(0);
        return;
    }

    if (match(END)) {
        advance();
    } else {
        retval = expr();
        if (match(END)) {
            advance();
        }
    }
}

int main()
{
    int i;
    for(i=0;i<TBLSIZE;i++){
        table[i].val=0;
        printf("MOV r%d, 0\n",i);
    }
    table[0].name[0]='x';
    table[1].name[0]='y';
    table[2].name[0]='z';

    while (1) {
        statement();
    }
    //printf("EXIT 0\n");
    return 0;
}

