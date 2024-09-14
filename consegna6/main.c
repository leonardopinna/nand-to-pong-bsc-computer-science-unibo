#include "headers/utils.h"
#include "headers/parser.h"
#include "headers/codewriter.h"

int endsWith(char *str, char *suffix);
void processFile(CodeWriter *cw, char *filePath);

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        fprintf(stderr, "ERROR:\nUsage: <filepath>/VMtranslator inputFile.vm or <filepath>/VMtranslator directoryName\n");
        exit(EXIT_FAILURE);
    }

    char *inputPath = argv[1];
    DIR *dir = opendir(inputPath);

    CodeWriter cw = {
        .outputFile = NULL,
        .outputFileName = {'\0'},
        .labelCounter = 0,
        .returnCounter = 0,
        .fName = {"main"}};

    // Check if it's a directory
    if (dir)
    {
        // It's a directory: process all vm files
        struct dirent *entry;
        while ((entry = readdir(dir)) != NULL)
        {
            if (entry->d_type == DT_REG && endsWith(entry->d_name, ".vm"))
            {
                // File with .vm extension in the directory
                char fullPath[1000];

                sprintf(fullPath, "%s/%s", inputPath, entry->d_name);
                // Process the VM file
                processFile(&cw, fullPath);
            }
        }
        closedir(dir);
    }
    else
    {
        // Process the VM file
        processFile(&cw, inputPath);
    }

    return 0;
}

// Helper function to check if a string ends with a specific suffix
int endsWith(char *str, char *suffix)
{
    if (!str || !suffix)
        return 0;

    size_t lenStr = strlen(str);
    size_t lenSuffix = strlen(suffix);

    if (lenStr < lenSuffix)
        return 0;

    return strcmp(str + lenStr - lenSuffix, suffix) == 0;
}

void processFile(CodeWriter *cw, char *filePath)
{
    // Open input and output files
    FILE *inputFile = fopen(filePath, "r");
    if (inputFile == NULL)
    {
        perror("Error opening input file");
        exit(EXIT_FAILURE);
    }

    setFileName(cw, filePath);
    // Replace the extension ".vm" with ".asm"
    char *dotVM = strrchr(cw->outputFileName, '.');
    if (dotVM != NULL && strcmp(dotVM, ".vm") == 0)
    {
        strcpy(dotVM, ".asm");
    }
    else
    {
        perror("Input file has to be with extension '.vm'");
        free(cw->outputFileName);
        fclose(inputFile);
        exit(EXIT_FAILURE);
    }

    FILE *outputFile = fopen(cw->outputFileName, "w");
    if (!inputFile || !outputFile)
    {
        perror("Error opening files");
        exit(EXIT_FAILURE);
    }

    setOutputFile(cw, outputFile);

    parse(cw, inputFile);
    fclose(inputFile);
    fclose(outputFile);
}
