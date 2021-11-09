/**
Introduction to Programing, 2015 spring
Mini-project output parser

Author : Jacky Chen
Version: 1.0
**/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/**
print error message.
because it uses some special variable, use it carefully.
**/
#define error(fmt, ...) \
printf("**********************************\n"); \
printf("ERROR at '%s'\n => ", input); \
printf(fmt, __VA_ARGS__); \
printf("**********************************\n");

enum code {MOV, ADD, SUB, MUL, DIV, EXIT};
enum op_type {REG, CONST, ADDR};

typedef struct INST
{
	enum code opcode;

	enum op_type op1_type;
	int op1_value;

	enum op_type op2_type;
	int op2_value;

} INST;

void print(INST *i)
{
    switch(i->opcode){
        case MOV:  printf("MOV  |"); break;
        case ADD:  printf("ADD  |"); break;
        case SUB:  printf("SUB  |"); break;
        case MUL:  printf("MUL  |"); break;
        case DIV:  printf("DIV  |"); break;
        case EXIT: printf("EXIT |"); break;
    }

    switch(i->op1_type){
        case REG:   printf(" REG  : %-4d |", i->op1_value); break;
        case CONST: printf(" CONST: %-4d |", i->op1_value); break;
        case ADDR:  printf(" ADDR : %-4d |", i->op1_value); break;
    }

    if(i->opcode!=EXIT){
        switch(i->op2_type){
            case REG:   printf(" REG  : %-4d |\n", i->op2_value); break;
            case CONST: printf(" CONST: %-4d |\n", i->op2_value); break;
            case ADDR:  printf(" ADDR : %-4d |\n", i->op2_value); break;
        }
    }else{
        printf("             |\n");
    }
}

/// check the op is register or not
int readREG(char *op, enum op_type *op_t, int *op_v )
{
    if( strlen(op)>=2 && op[0]=='r' ){
        if( op[1]>='0' && op[1]<='3' ){
            *op_t = REG;
            *op_v = op[1]-'0';
            return 1;
        }
        return -1;
    }
    return 0;
}

/// check the op is constant or not
int readCONST(char *op, enum op_type *op_t, int *op_v)
{
    int i;
    for( i=0; i<strlen(op) && isdigit(op[i]); i++ );
    if( i==strlen(op) ){
        *op_t = CONST;
        *op_v = atoi(op);
        return 1;
    }
    return 0;
}

int readADDR(char *op, enum op_type *op_t, int *op_v)
{
    int i;

    if( op[0]=='[' && op[strlen(op)-1]==']')
    {
        for( i=1; i<strlen(op)-1 && isdigit(op[i]); i++ );

        if( i==strlen(op)-1 )
        {
            if( atoi(op+1)%4==0 ){
                *op_t = ADDR;
                *op_v = atoi(op+1);
                return 1;
            }
            return -2;
        }
        return  -1;
    }
    return 0;
}

int readOP(char *input, char *op, enum op_type *op_t, int *op_v)
{
    /// check op type and read its value,
    /// if success return 1, else return 0

    switch( readREG(op, op_t, op_v) ){
    case -1: /// REGISTER out of range
        error("register out of range: '%s'\n", op);
        return 0;
    case 1:  /// op is a REGISTER
        return 1;
    case 0:  /// op is not a REGISTER
        break;
    }

    switch( readADDR(op, op_t, op_v) ){
    case -1: /// ADDRESS out of range
        error("address out of range: '%s'\n", op);
        return 0;
    case -2: /// ADDRESS out of range
        error("address must be multiple of 4 : '%s'\n", op);
        return 0;
    case 1:  /// op is a ADDRESS
        return 1;
    case 0:  /// op is not a ADDRESS
        break;
    }

    switch( readCONST(op, op_t, op_v) ){
    case 0:  /// op is not a CONSTANT
        break;
    case 1:  /// op is a CONSTANT
        return 1;
    }
    return 0;
}

/**
read input from stdin.

return:
 1 : success
 2 : illegal instruction
-1 : input EOF
**/
int readInst(INST **inst)
{
    char *tok=" ", *chr;
    enum code opcode;
    enum op_type op1_t, op2_t;
    int op1_v, op2_v;

	char input[32]="", decode[32]="", *op;

	if( fgets(input, 31, stdin)==NULL ){
        return -1;
	}else{
	    /// replace newline to EOF, if newline exist
	    if( input[strlen(input)-1]=='\n')
            input[strlen(input)-1]='\0';

	    strcpy(decode, input);

        /// remove ',', if it exist
        chr = strchr(decode, ',');
        if( chr!=NULL )
        while( *chr!='\0' ){
            *chr = *(chr+1);
            chr++;
        }
        op = strtok(decode, tok);
	}

    /// read opcode
         if (strcmp(op, "MOV" )==0) opcode = MOV;
    else if (strcmp(op, "ADD" )==0) opcode = ADD;
    else if (strcmp(op, "SUB" )==0) opcode = SUB;
    else if (strcmp(op, "MUL" )==0) opcode = MUL;
    else if (strcmp(op, "DIV" )==0) opcode = DIV;
    else if (strcmp(op, "EXIT")==0) opcode = EXIT;
    else {
        error("un-define opcode: '%s'\n", op);
        return 2;
    }

    /// read op1
    op = strtok(NULL, tok);
    if( !readOP(input, op, &op1_t, &op1_v) ){
        return 2;
    }

    /// read op2 except EXIT
    if( opcode != EXIT ){
        op = strtok(NULL, tok);
        if( !readOP(input, op, &op2_t, &op2_v) ){
            return 2;
        }
    }else{
        op2_t = CONST;
        op2_v = 0;
    }

    /// According to opcode, check op1 and op2
    switch( opcode )
    {
        case MOV:
            if( op1_t==ADDR && op2_t!=REG ){
                error("%s\n", "At MOV, when op1 is ADDR, op2 is only REG");
                return 2;
            }
            break;

        case ADD:
            if( op1_t!=REG ){ error("%s\n", "op1 of ADD is only REG"); return 2;}
            if( op2_t!=REG ){ error("%s\n", "op2 of ADD is only REG"); return 2;}
            break;

        case SUB:
            if( op1_t!=REG ){ error("%s\n", "op1 of SUB is only REG"); return 2;}
            if( op2_t!=REG ){ error("%s\n", "op2 of SUB is only REG"); return 2;}
            break;

        case MUL:
            if( op1_t!=REG ){ error("%s\n", "op1 of MUL is only REG"); return 2;}
            if( op2_t!=REG ){ error("%s\n", "op2 of MUL is only REG"); return 2;}
            break;

        case DIV:
            if( op1_t!=REG ){ error("%s\n", "op1 of DIV is only REG"); return 2;}
            if( op2_t!=REG ){ error("%s\n", "op2 of DIV is only REG"); return 2;}
            break;

        case EXIT:
            if( op1_t!=CONST && (op1_v==1 || op1_v==0) ){
                error("%s\n", "op1 of EXIT is constant 1 or 0");
                return 2;
            }
    }

    (*inst) = (INST*)malloc(sizeof(INST));
    (*inst)->opcode = opcode;
    (*inst)->op1_type  = op1_t;
    (*inst)->op2_type  = op2_t;
    (*inst)->op1_value = op1_v;
    (*inst)->op2_value = op2_v;

//    print(*inst);

    return 1;
}

int main()
{
    freopen("./input.txt", "r",  stdin);
    freopen("./ouput.txt", "w", stdout);

    /**
    inst    : the current instruction
    reg     : the registers (0~3)
    mem     : the memory space (0~63)
    state   : the state of while
                =0, exit normal
                =1, read instruction correct
                =2, read instruction correct but format error
                <0, input EOF, exit
    **/

	INST *inst;
	int reg[4], i, state;
    int mem[64];
    state=1;

	while(state>0)
	{
        if( (state=readInst(&inst)) != 1 ){
            continue;
        }

        print(inst);

		switch(inst->opcode)
		{
			case MOV:
				if(inst->op1_type==REG){
                    switch(inst->op2_type){
                    case REG:   reg[inst->op1_value]=reg[inst->op2_value];  break;
                    case CONST: reg[inst->op1_value]=    inst->op2_value;   break;
                    case ADDR:  reg[inst->op1_value]=mem[inst->op2_value/4];break;
                    }
				}else{
                    mem[inst->op1_value/4]=reg[inst->op2_value];
				}
				break;

			case ADD:
                reg[inst->op1_value]+=reg[inst->op2_value];
				break;

            case SUB:
                reg[inst->op1_value]-=reg[inst->op2_value];
				break;

			case MUL:
                reg[inst->op1_value]*=reg[inst->op2_value];
				break;

            case DIV:
                if( reg[inst->op2_value]==0 ){
                    printf("**********************************\n");
                    printf("ERROR divisor is not equal to 0\n");
                    printf("**********************************\n");
                }else{
                    reg[inst->op1_value]/=reg[inst->op2_value];
                }
				break;

            case EXIT:
                printf("----------------------------------\n");
                if( inst->op1_value==0 )
                    printf("exit normally\n");
                else
                    printf("the expression cannot be evaluated\n");
                state=0;
                break;
		}
		free(inst);
	}

	if(state!=0){
        printf("**********************************\n");
        printf("ERROR ending without EXIT\n");
        printf("**********************************\n");
	}

    printf("\n");
	for(i=0; i<3; i++)
	{
		printf("r[%d] = %d\n", i, reg[i]);
	}

	return 0;
}
