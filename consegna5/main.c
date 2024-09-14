#include "headers/Utils.h"
#include "headers/Assembler.h"

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        fprintf(stderr, "Usage: %s input.asm\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    // Open input and output files
    FILE *inputFile = fopen(argv[1], "r");
    FILE *outputFile = fopen("output.hack", "w");

    if (!inputFile || !outputFile)
    {
        perror("Error opening files");
        exit(EXIT_FAILURE);
    }

    // Initialize symbol table
    Assembler *assembler = malloc(sizeof(Assembler));

    initSymbolTable(&assembler->symbolTable);

    // Call parseAndTranslate with the initialized symbol table
    parseAndTranslate(&assembler->symbolTable, inputFile, outputFile);

    fclose(inputFile);
    fclose(outputFile);

    return 0;
}
