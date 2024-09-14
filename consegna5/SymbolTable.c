#include "headers/SymbolTable.h"

void initSymbolTable(SymbolTable *table)
{
    // Add predefined symbols
    addEntry(table, "SP", 0);
    addEntry(table, "LCL", 1);
    addEntry(table, "ARG", 2);
    addEntry(table, "THIS", 3);
    addEntry(table, "THAT", 4);

    for (int i = 0; i <= 15; ++i)
    {
        char symbol[MAX_SYMBOL_LENGTH];
        sprintf(symbol, "R%d", i);
        addEntry(table, symbol, i);
    }

    addEntry(table, "SCREEN", 16384);
    addEntry(table, "KBD", 24576);

    // init RAM and ROM addresses
    table->nextRAMAddress = 16;
    table->nextROMAddress = 0;
}

void addEntry(SymbolTable *table, const char *symbol, int address)
{
    if (table == NULL)
    {
        fprintf(stderr, "Error: Table is null.\n");
        exit(EXIT_FAILURE);
    }

    // Create the new entry
    SymbolEntry *newEntry = (SymbolEntry *)malloc(sizeof(SymbolEntry));

    strncpy(newEntry->symbol, symbol, sizeof(newEntry->symbol) - 1);
    newEntry->symbol[sizeof(newEntry->symbol) - 1] = '\0';
    newEntry->address = address;
    newEntry->next = NULL;

    // Insert new entry in the symbol table
    if (table->symbolList == NULL)
    {
        table->symbolList = newEntry;
    }
    else
    {
        SymbolEntry *tmp = table->symbolList;
        while (tmp->next != NULL)
        {
            tmp = tmp->next;
        }
        tmp->next = newEntry;
    }
}

bool contains(SymbolTable *table, const char *symbol)
{
    if (table == NULL)
    {
        fprintf(stderr, "Error: Table is null.\n");
        exit(EXIT_FAILURE);
    }
    SymbolEntry *tmp = table->symbolList;
    while (tmp != NULL)
    {
        if (strcmp(tmp->symbol, symbol) == 0)
        {
            return true;
        }
        tmp = tmp->next;
    }

    return false;
}

int getAddress(SymbolTable *table, const char *symbol)
{
    if (table == NULL)
    {
        fprintf(stderr, "Error: Table is null.\n");
        exit(EXIT_FAILURE);
    }
    SymbolEntry *tmp = table->symbolList;
    while (tmp != NULL)
    {
        if (strcmp(tmp->symbol, symbol) == 0)
        {
            return tmp->address;
        }
        tmp = tmp->next;
    }

    fprintf(stderr, "Symbol %s not found.", symbol);
    exit(EXIT_FAILURE);
}
