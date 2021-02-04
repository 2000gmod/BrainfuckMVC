/*

INITIALIZE WITH:

    POINTER ADDRESS (dPTR): A000
    POINTER CONTENT (PTR): 00 00

    ON B000:
        00
        01


INSTRUCTION TRANSLATION:

+:
    DIR - 10: MOV [DIR + 1] [dPTR]
    DIR - 5 : MOV [DIR + 2] [dPTR + 1]
    DIR: ADD [PTR] [0B01]

-:
    DIR - 10: MOV [DIR + 1] [dPTR]
    DIR - 5 : MOV [DIR + 2] [dPTR + 1]
    DIR: SUB [PTR] [0B01]


>:
    DIR: ADDC 2 [dPTR] [0B00]

<:
    DIR: SUBC 2 [dPTR] [0B00]

*/