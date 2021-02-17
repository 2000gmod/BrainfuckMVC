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
        return;
    }
}


void compile(FILE* fileIn, FILE* fileOut){
    printf("Pass 2: Compiling...");
    unsigned short currentAddress = 0;
    unsigned short pointerContent = 0xC000;

    //SET A000 TO C0, B001 TO 01
    char initArray[8] = {0x01, 0xA0, 0x00, 0xC0, 0x01, 0xB0, 0x01, 0x01};

    for(int k = 0; k < 8; k++){
        fputc(initArray[k], fileOut);
        currentAddress++;
    }
    while(!feof(fileIn)){
        switch(fgetc(fileIn)){

        }
    }
    return;
}

char getNthByte(int input, int n){
    return (char)(input >> (n * 8)) & 0xFF;
}