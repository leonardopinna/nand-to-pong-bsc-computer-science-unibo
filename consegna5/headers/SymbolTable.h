#ifndef SYMBOL_TABLE_H
#define SYMBOL_TABLE_H

#include "Utils.h"

// Define the maximum number of entries in the symbol table
#define MAX_SYMBOL_LENGTH 100

// Structure to represent a symbol entry
typedef struct SymbolEntry
{
    char symbol[MAX_SYMBOL_LENGTH];
    int address;
    struct SymbolEntry *next;
} SymbolEntry;

// Structure to represent the symbol table
typedef struct SymbolTable
{
    struct SymbolEntry *symbolList;
    int nextRAMAddress;
    int nextROMAddress;
} SymbolTable;

// Function to initialize a new symbol table
void initSymbolTable(SymbolTable *table);

// Function to add a new entry to the symbol table
void addEntry(SymbolTable *table, const char *symbol, int address);

// Function to check if the symbol table contains a given symbol
bool contains(SymbolTable *table, const char *symbol);

// Function to get the address associated with a symbol
int getAddress(SymbolTable *table, const char *symbol);

#endif // SYMBOL_TABLE_H