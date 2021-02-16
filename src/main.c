#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "compiler.h"

int main(){
    FILE* inFile = fopen("./examples/helloworld.bf", "r");

    checkSyntax(inFile);
    return 1;
}