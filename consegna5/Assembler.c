#include "headers/Assembler.h"

// Parse the A-instruction and put the binary code in the binaryCode string
void parseAInstruction(char *instruction, char *binaryCode, SymbolTable *table)
{
    char *symbol = strtok(instruction + 1, " \t\n\r");
    int address;

    // Check if the symbol is numeric
    if (isdigit(symbol[0]))
    {
        // Convert numeric address to binary
        address = atoi(symbol);
    }
    else
    // The symbol is not numeric, so it is an alphabetic symbol
    {
        // if the symbol is found in the table, return the value of the symbol
        if (contains(table, symbol))
        {
            address = getAddress(table, symbol);
        }
        // if the symbol is not found, add the symbol to the table and return its RAM address
        else
        {
            addEntry(table, symbol, table->nextRAMAddress);
            address = table->nextRAMAddress;
            table->nextRAMAddress++;
        }
    }

    // A-instruction: leftmost digit is 0;
    binaryCode[0] = '0';

    // convert the decimal address in binary for positions 1 to 15
    for (int i = 15; i >= 1; --i)
    {
        binaryCode[i] = '0' + (address & 1);
        address >>= 1;
    }

    // Null-terminate the string
    binaryCode[16] = '\0';
}

// Parse the binaryCode string associated to the input C-instruction
void parseCInstruction(char *instruction, char *binaryCode)
{
    char dest[4], comp[8], jump[4];

    // if the '=' sign is not found, it is a comp;jump instruction
    if (strstr(instruction, "=") == NULL)
    {
        sscanf(instruction, "%[^;];%s", comp, jump);
        strcpy(dest, "");
    }
    else
    {
        int itemsMatched = sscanf(instruction, "%[^=]=%[^;];%s", dest, comp, jump);

        // if the ';' sign is not found, it is a dest=comp instruction
        if (itemsMatched < 3)
        {
            strcpy(jump, "");
        }
    }

    // Translate comp, dest and jump fields
    char compBits[8];
    strcpy(compBits, compCode(comp));

    char destBits[4];
    strcpy(destBits, destCode(dest));

    char jumpBits[4];
    strcpy(jumpBits, jumpCode(jump));

    // Concatenate the binary code fields
    sprintf(binaryCode, "111%s%s%s", compBits, destBits, jumpBits);
}

void parseAndTranslate(SymbolTable *table, FILE *inputFile, FILE *outputFile)
{
    char line[MAX_LINE_LENGTH];

    // First pass: build symbol table
    while (fgets(line, MAX_LINE_LENGTH, inputFile) != NULL)
    {
        // Find the position of "//" in the line
        char *commentPosition = strstr(line, "//");

        // Skip lines starting with "//"
        if (strncmp(line, "//", 2) == 0)
        {
            continue;
        }

        // If "//" is found, replace newline characters after the comment position with spaces
        if (commentPosition != NULL)
        {
            for (char *ptr = commentPosition; *ptr != '\0' && *ptr != '\n'; ++ptr)
            {
                *ptr = ' ';
            }
        }

        // Remove comments and whitespace
        strtok(line, " \t\n\r");

        // Skip empty line
        if (line[0] == '\n' || line[0] == '\r' || line[0] == '\t')
        {
            // Skip empty lines and label definitions
            continue;
        }

        if (line[0] == '(')
        {
            // Label definition
            char *symbol = strtok(line + 1, ")");
            // if (!contains(&assembler->symbolTable, symbol))
            addEntry(table, symbol, table->nextROMAddress);
        }
        else
        {
            table->nextROMAddress = table->nextROMAddress + 1;
        }
    }

    // Reset file pointer to the beginning of file
    fseek(inputFile, 0, SEEK_SET);

    // Second pass: translate and write to output file
    while (fgets(line, MAX_LINE_LENGTH, inputFile) != NULL)
    {
        // Skip empty lines
        if (line[0] == '\n' || line[0] == '\r')
            continue;

        // Skip label definition
        if (line[0] == '(')
            continue;

        // Skip lines starting with "//"
        if (strncmp(line, "//", 2) == 0)
            continue;

        // Remove comments and whitespace
        char *token = strtok(line, " \t\n\r");

        // Parse binary code string
        char binaryCode[17];

        if (token[0] == '@')
        {
            // A-instruction
            parseAInstruction(token, binaryCode, table);
        }
        else
        {
            // C-instruction
            parseCInstruction(token, binaryCode);
        }

        // Write binary string to output file
        fprintf(outputFile, "%s\n", binaryCode);
    }
}