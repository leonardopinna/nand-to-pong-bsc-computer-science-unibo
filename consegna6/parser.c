#include "headers/parser.h"

void parse(CodeWriter *cw, FILE *inputFile)
{
    char line[MAX_LINE_LENGTH];

    // bootstrap
    writeInit(cw);

    // read lines and parse
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

        // Skip empty lines
        if (line[0] == '\n' || line[0] == '\r')
        {
            // Skip empty lines
            continue;
        }

        // manage tabs at start of the lines
        while (line[0] == '\t')
        {
            line[0] = line[1];
        }

        // Parse the line
        char *command = NULL;
        char *segment = NULL;
        char *index = NULL;

        command = strtok(line, " ");

        if (command != NULL)
        {
            segment = strtok(NULL, " ");
            if (segment != NULL)
            {
                index = strtok(NULL, " ");
            }
        }

        // sanitize strings
        sanitize(command);
        sanitize(segment);
        sanitize(index);

        // activate codeWriter depending on the command
        // push and pop operations
        if (strcmp(command, "push") == 0)
        {
            writePush(cw, segment, atoi(index));
        }
        else if (strcmp(command, "pop") == 0)
        {
            writePop(cw, segment, atoi(index));
        }
        // label, goto, if-goto
        else if (strcmp(command, "label") == 0)
        {
            writeLabel(cw, segment);
        }
        else if (strcmp(command, "goto") == 0)
        {
            writeGoto(cw, segment);
        }
        else if (strcmp(command, "if-goto") == 0)
        {
            writeIf(cw, segment);
        }
        // call, function, return
        else if (strcmp(command, "call") == 0)
        {
            writeCall(cw, segment, atoi(index));
        }
        else if (strcmp(command, "function") == 0)
        {
            writeFunction(cw, segment, atoi(index));
        }
        else if (strcmp(command, "return") == 0)
        {
            writeReturn(cw);
        }
        // arithmetic commands
        else
        {
            writeArithmetic(cw, command);
        }
    }
}

// removes all characters before and after the input string
void sanitize(char *str)
{
    bool found = false;
    if (str == NULL)
        return;

    size_t len = strlen(str);
    size_t newLen = 0;

    for (size_t i = 0; i < len; i++)
    {
        if (str[i] == ' ' || str[i] == '\t' || str[i] == '\n' || str[i] == '\r')
        {
            if (!found)
            {
                // Skip initial whitespace or tab characters
                continue;
            }
            else
                // First stopping char found after begin of string
                break;
        }
        else
        {
            // string begins
            found = true;
        }

        // Copy the non-whitespace character to the new string
        str[newLen++] = str[i];
    }

    // End the new string
    str[newLen] = '\0';
}
