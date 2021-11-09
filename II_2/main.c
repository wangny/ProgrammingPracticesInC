#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum code {
    MOV,
    ADD
};

enum op_type {
    REG,
    CONST
};

typedef struct INST {

    enum code opcode;
    enum op_type op1;
    int operand1_value;
    enum op_type op2;
    int operand2_value;
    struct INST* next;

} INST;

INST* readInput(){

    char opc[10], op1[10], op2[10];
    int ns=0, c;
    INST *head=0, *curr=0;
    ns = scanf("%s %s %d ", opc, op1, &c);

    while(ns > 0) {

        if (head == 0){
            head = (INST*) malloc(sizeof(INST));
            curr = head;
            curr->next = 0;
        } else {
            curr->next = (INST*) malloc(sizeof(INST));
            curr = curr->next;
            curr->next = 0;
        }

        if (strcmp(opc, "MOV")==0)
            curr->opcode = MOV;
        else if (strcmp(opc, "ADD")==0)
            curr->opcode = ADD;

        curr->op1 = REG;
        curr->operand1_value = op1[1]-'0';

        if (ns == 2){
            scanf("%s ", op2);
            curr->op2 = REG;
            curr->operand2_value = op2[1] -'0';
        } else if (ns == 3) {
            curr->op2 = CONST;
            curr->operand2_value = c;
        }

        ns = scanf("%s %s %d ", opc, op1, &c);
    }
    return head;
}

int main(void)
{
    INST *a ;
    int r[4]={0};

    a = readInput();

    while(a!=0){
        if(a->opcode==0){
            if(a->op2==0){
                r[a->operand1_value]=r[a->operand2_value];
            }else if(a->op2==1){
                r[a->operand1_value]=a->operand2_value;
            }
        }else if(a->opcode==1){
            if(a->op2==0){
                r[a->operand1_value]=r[a->operand1_value]+r[a->operand2_value];
            }else if(a->op2==1){
                r[a->operand1_value]=r[a->operand1_value]+a->operand2_value;
            }
        }
        a = a->next;
    }

    printf("%4d%4d%4d%4d\n",r[0],r[1],r[2],r[3]);
}
