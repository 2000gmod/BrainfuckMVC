#include "compiler.h"

void checkSyntax(FILE* fileIn){
    printf("Pass 1: Check syntax... ");
    int bracketCounter = 0;
    while(!feof(fileIn)){
        char currChar = fgetc(fileIn);
        switch (currChar){
            case '[':
                bracketCounter++;
                break;
            case ']':
                bracketCounter--;
                break;
        }
    }
    if(bracketCounter != 0){
        printf("Syntax error!\n");
        exit(0);
    }
    else{
        printf("Done.\n");
        fseek(fileIn, 0, SEEK_SET);
        return;
    }
}


void compile(FILE* fileIn, FILE* fileOut){
    printf("Pass 2: Compiling... ");
    unsigned short currentAddress = 0;
    unsigned short pointerContent = 0xC000;

    //SET A000 TO C0, B001 TO 01
    char initArray[8] = {0x01, 0xA0, 0x00, 0xC0, 0x01, 0xB0, 0x01, 0x01};

    for(int k = 0; k < 8; k++){
        fputc(initArray[k], fileOut);
        currentAddress++;
    }
    char currentChar = 0;

    while(currentChar != EOF){
        currentChar = fgetc(fileIn);
        switch(currentChar){
            case '+':{
                //                       DIR + 11  dPTR          MOV   DIR+12    dPTR + 1      ADD     PTR       B000
                char insArray[15] = {0x02, 0xFF, 0xFF, 0xA0, 0x00, 0x02, 0xFF, 0xFF, 0xA0, 0x01, 0x05, 0xFF, 0xFF, 0xB0, 0x01};
                insArray[1] = getNthByte(currentAddress + 11, 1);
                insArray[2] = getNthByte(currentAddress + 11, 0);
                insArray[6] = getNthByte(currentAddress + 12, 1);
                insArray[7] = getNthByte(currentAddress + 12, 0);
                insArray[11] = getNthByte(pointerContent, 1);
                insArray[12] = getNthByte(pointerContent, 0);

                for(int k = 0; k < 15; k++){
                    //printf("%x\n", currentAddress);
                    fputc(insArray[k], fileOut);
                    currentAddress++;
                }
                //exit(0);
                break;
            }
            case '-':{
                //                       DIR + 11  dPTR          MOV   DIR+12    dPTR + 1      SUB     PTR       B000
                char insArray[15] = {0x02, 0xFF, 0xFF, 0xA0, 0x00, 0x02, 0xFF, 0xFF, 0xA0, 0x01, 0x06, 0xFF, 0xFF, 0xB0, 0x01};
                insArray[1] = getNthByte(currentAddress + 11, 1);
                insArray[2] = getNthByte(currentAddress + 11, 0);
                insArray[6] = getNthByte(currentAddress + 12, 1);
                insArray[7] = getNthByte(currentAddress + 12, 0);
                insArray[11] = getNthByte(pointerContent, 1);
                insArray[12] = getNthByte(pointerContent, 0);

                for(int k = 0; k < 15; k++){
                    fputc(insArray[k], fileOut);
                    currentAddress++;
                }
                break;
            }
            case '>':{
                //                 ADDC        dPTR        B000
                char insArray[6] = {0x13, 0x02, 0xA0, 0x00, 0xB0, 0x00};
                pointerContent++;
                for(int k = 0; k < 6; k++){
                    fputc(insArray[k], fileOut);
                    currentAddress++;
                }
                break;
            }
            case '<':{
                //                 SUBC        dPTR        B000
                char insArray[6] = {0x14, 0x02, 0xA0, 0x00, 0xB0, 0x00};
                pointerContent--;
                for(int k = 0; k < 6; k++){
                    fputc(insArray[k], fileOut);
                    currentAddress++;
                }
                break;
            }

            case '[':{
                int currentFileLoc = ftell(fileIn);
                char insArray[5] = {0x0D, 0xFF, 0xFF, 0xA0, 0x00};
                short matchingPairLoc = (short) getAddressOfMatchingClosing(currentAddress, fileIn, currentFileLoc) + bfBrackets;
                insArray[1] = getNthByte(matchingPairLoc, 1);
                insArray[2] = getNthByte(matchingPairLoc, 0);

                for(int k = 0; k < 5; k++){
                    fputc(insArray[k], fileIn);
                    currentAddress++;
                }
                break;
            }
            case ']':{
                int currentFileLoc = ftell(fileIn);
                char insArray[5] = {0x04, 0xFF, 0xFF, 0xA0, 0x00};
                short matchingPairLoc = (short) getAddressOfMatchingOpening(currentAddress, fileIn, currentFileLoc) + bfBrackets;
                insArray[1] = getNthByte(matchingPairLoc, 1);
                insArray[2] = getNthByte(matchingPairLoc, 0);

                for(int k = 0; k < 5; k++){
                    fputc(insArray[k], fileIn);
                    currentAddress++;
                }
                break;
            }

            default: {
                break;
            }
        }
    }
    printf("Done.\n");
    return;
}

char getNthByte(int input, int n){
    return (char)(input >> (n * 8)) & 0xFF;
}

int getAddressOfMatchingClosing(int currentAddress, FILE* fileIn, int currentFilePointer){
    int bracketCount = 1;
    char currentChar = 0;
    int addressOffset = 0;

    while (bracketCount != 0 && !feof(fileIn)){
        currentChar = fgetc(fileIn);

        switch(currentChar){
            case '[':
                bracketCount++;
                addressOffset += bfBrackets;
                break;
            case ']':
                bracketCount--;
                addressOffset += bfBrackets;
                break;
            case '+':
                addressOffset += bfAddSub;
                break;
            case '-':
                addressOffset += bfAddSub;
                break;
            case '>':
                addressOffset += bfPointerMove;
                break;
            case '<':
                addressOffset += bfPointerMove;
                break;
            case '.':
                addressOffset += bfPrint;
                break;
            case ',':
                addressOffset += bfPrint;
                break;
        }
    }
    fseek(fileIn, currentFilePointer, SEEK_SET);
    return currentAddress + addressOffset;
}

int getAddressOfMatchingOpening(int currentAddress, FILE* fileIn, int currentFilePointer){
    int bracketCount = 1;
    char currentChar = 0;
    int addressOffset = 0;
    int counter = currentFilePointer;

    while (bracketCount > 0 && !feof(fileIn)){
        counter--;
        currentChar = fgetc(fileIn);
        fseek(fileIn, counter, SEEK_CUR);

        switch(currentChar){
            case '[':
                bracketCount--;
                addressOffset -= bfBrackets;
                break;
            case ']':
                bracketCount++;
                addressOffset -= bfBrackets;
                break;
            case '+':
                addressOffset -= bfAddSub;
                break;
            case '-':
                addressOffset -= bfAddSub;
                break;
            case '>':
                addressOffset -= bfPointerMove;
                break;
            case '<':
                addressOffset -= bfPointerMove;
                break;
            case '.':
                addressOffset -= bfPrint;
                break;
            case ',':
                addressOffset -= bfPrint;
                break;
        }
    }
    fseek(fileIn, currentFilePointer, SEEK_SET);
    return currentAddress + addressOffset;
}