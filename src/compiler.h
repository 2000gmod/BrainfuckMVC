/*

INITIALIZE WITH:

    POINTER ADDRESS (dPTR): A000
    POINTER CONTENT (PTR): C0 00

    ON B000:
        00
        01


INSTRUCTION TRANSLATION:

+:
    DIR: MOV [DIR + 11] [dPTR]
    DIR + 5 : MOV [DIR + 12] [dPTR + 1]
    DIR + 10: ADD [PTR] [0B01]

-:
    DIR: MOV [DIR + 11] [dPTR]
    DIR + 5 : MOV [DIR + 12] [dPTR + 1]
    DIR + 10: SUB [PTR] [0B01]


>:
    DIR: ADDC 2 [dPTR] [0B00]

<:
    DIR: SUBC 2 [dPTR] [0B00]

[:
    L11: JMZ [L12] [dPTR]

]:
    L12: JNT [L11] [dPTR]

.: 
    DIR: MOV [DIR + 11] [dPTR]
    DIR + 5 : MOV [DIR + 12] [dPTR + 1]
    DIR + 10: PRINT [PTR]
*/

#ifndef COMPILER_H
#define COMPILER_H

#include <stdio.h>
#include <stdlib.h>

void checkSyntax(FILE* file);

#endif