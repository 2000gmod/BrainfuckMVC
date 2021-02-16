#include "compiler.h"

void checkSyntax(FILE* file){
    printf("Pass 1: Check syntax... ");
    int bracketCounter = 0;
    while(!feof(file)){
        char currChar = fgetc(file);
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