#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "compiler.h"

int main(){
    FILE* inFile = fopen("./examples/helloworld.bf", "r");
    FILE* outFile = fopen("./examples/helloworld.vx", "w");

    checkSyntax(inFile);
    compile(inFile, outFile);
    
    fclose(inFile);
    fclose(outFile);
    return 1;
}