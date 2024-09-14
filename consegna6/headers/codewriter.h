#ifndef CODEWRITER_H
#define CODEWRITER_H

#include "utils.h"

#define MAX_OUTPUTFILE_LENGTH 100
#define MAX_FUNCTION_NAME_LENGTH 100

typedef struct CodeWriter
{
    FILE *outputFile;
    char outputFileName[MAX_OUTPUTFILE_LENGTH];
    int labelCounter;
    int returnCounter;
    char fName[MAX_FUNCTION_NAME_LENGTH];
} CodeWriter;

void setOutputFile(CodeWriter *cw, FILE *outputFile);
void setFileName(CodeWriter *cw, char *fileName);
void writeInit(CodeWriter *cw);
void writeArithmetic(CodeWriter *cw, char *command);
void writePush(CodeWriter *cw, char *segment, int index);
void writePop(CodeWriter *cw, char *segment, int index);
void writeLabel(CodeWriter *cw, char *label);
void writeGoto(CodeWriter *cw, char *label);
void writeIf(CodeWriter *cw, char *label);
void writeCall(CodeWriter *cw, char *functionName, int numArgs);
void writeReturn(CodeWriter *cw);
void writeFunction(CodeWriter *cw, char *functionName, int numLocals);

#endif // CODEWRITER_H