#ifndef ASSEMBLER_H
#define ASSEMBLER_H

#include "SymbolTable.h"
#include "Code.h"

#define MAX_LINE_LENGTH 100

typedef struct Assembler
{
    SymbolTable symbolTable;
} Assembler;

// Parse the A-instruction and put the binary code in the binaryCode string
void parseAInstruction(char *instruction, char *binaryCode, SymbolTable *table);

// Parse the binaryCode string associated to the input C-instruction
void parseCInstruction(char *instruction, char *binaryCode);

// Function to parse and translate the input assembly file
void parseAndTranslate(SymbolTable *table, FILE *inputFile, FILE *outputFile);

#endif // ASSEMBLER_H