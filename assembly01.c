#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    printf("MOV [sp], 5\nMOV [sp+4], 10\nMOV [sp+8], 1\nMOV [sp+12], 2\nMOV r0, 0\nJMP L2\nL3 :\nMOV r1, 0\nJMP L4\nL5 :\nADD [sp+8], 1\nADD r1, 1\nL4 :\nCMP r1, [sp+4]\nJLE L5\nADD [sp+12], 1\nADD r0, 1\nL2 :\nCMP r0, [sp]\nJLE L3\nMOV r0, [sp]\nMOV r1, [sp+4]\nMOV r2, [sp+8]\nMOV r3, [sp+12]\n");

    return 0;
}
