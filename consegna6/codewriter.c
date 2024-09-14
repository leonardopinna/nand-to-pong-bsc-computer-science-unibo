#include "headers/codewriter.h"

void setOutputFile(CodeWriter *cw, FILE *outputFile)
{
    cw->outputFile = outputFile;
};

void setFileName(CodeWriter *cw, char *fileName)
{
    strncpy(cw->outputFileName, fileName, MAX_OUTPUTFILE_LENGTH - 1);
}

void writeInit(CodeWriter *cw)
{
    fprintf(cw->outputFile, "@256\n");
    fprintf(cw->outputFile, "D=A\n");
    fprintf(cw->outputFile, "@SP\n");
    fprintf(cw->outputFile, "M=D\n");
};

void writeArithmetic(CodeWriter *cw, char *command)
{
    // math commands
    if (strcmp(command, "add") == 0)
    {
        fprintf(cw->outputFile, "@SP\n");
        fprintf(cw->outputFile, "M=M-1\n");
        fprintf(cw->outputFile, "A=M\n");
        fprintf(cw->outputFile, "D=M\n");
        fprintf(cw->outputFile, "A=A-1\n");
        fprintf(cw->outputFile, "M=D+M\n");
    }
    else if (strcmp(command, "sub") == 0)
    {
        fprintf(cw->outputFile, "@SP\n");
        fprintf(cw->outputFile, "M=M-1\n");
        fprintf(cw->outputFile, "A=M\n");
        fprintf(cw->outputFile, "D=M\n");
        fprintf(cw->outputFile, "A=A-1\n");
        fprintf(cw->outputFile, "M=M-D\n");
    }
    else if (strcmp(command, "neg") == 0)
    {
        fprintf(cw->outputFile, "@SP\n");
        fprintf(cw->outputFile, "A=M-1\n");
        fprintf(cw->outputFile, "M=-M\n");
    }

    // comparison commands
    else if (strcmp(command, "eq") == 0)
    {
        fprintf(cw->outputFile, "@SP\n");
        fprintf(cw->outputFile, "M = M - 1\n");
        fprintf(cw->outputFile, "A = M\n");
        fprintf(cw->outputFile, "D = M\n");
        fprintf(cw->outputFile, "A = A - 1\n");
        fprintf(cw->outputFile, "D = D - M\n");
        fprintf(cw->outputFile, "@TRUE_EQ_%d\n", cw->labelCounter);
        fprintf(cw->outputFile, "D;JEQ\n");
        fprintf(cw->outputFile, "@SP\n");
        fprintf(cw->outputFile, "A = M - 1\n");
        fprintf(cw->outputFile, "M = 0\n");
        fprintf(cw->outputFile, "@CONTINUE_EQ_%d\n", cw->labelCounter);
        fprintf(cw->outputFile, "0;JMP\n");
        fprintf(cw->outputFile, "(TRUE_EQ_%d)\n", cw->labelCounter);
        fprintf(cw->outputFile, "@SP\n");
        fprintf(cw->outputFile, "A = M - 1\n");
        fprintf(cw->outputFile, "M = -1\n");
        fprintf(cw->outputFile, "(CONTINUE_EQ_%d)\n", cw->labelCounter);
        cw->labelCounter++;
    }
    else if (strcmp(command, "gt") == 0)
    {
        fprintf(cw->outputFile, "@SP\n");
        fprintf(cw->outputFile, "M = M - 1\n");
        fprintf(cw->outputFile, "A = M\n");
        fprintf(cw->outputFile, "D = M\n");
        fprintf(cw->outputFile, "A = A - 1\n");
        fprintf(cw->outputFile, "D = M - D\n");
        fprintf(cw->outputFile, "@TRUE_GT_%d\n", cw->labelCounter);
        fprintf(cw->outputFile, "D;JGT\n");
        fprintf(cw->outputFile, "@SP\n");
        fprintf(cw->outputFile, "A = M - 1\n");
        fprintf(cw->outputFile, "M = 0\n");
        fprintf(cw->outputFile, "@CONTINUE_GT_%d\n", cw->labelCounter);
        fprintf(cw->outputFile, "0;JMP\n");
        fprintf(cw->outputFile, "(TRUE_GT_%d)\n", cw->labelCounter);
        fprintf(cw->outputFile, "@SP\n");
        fprintf(cw->outputFile, "A = M - 1\n");
        fprintf(cw->outputFile, "M = -1\n");
        fprintf(cw->outputFile, "(CONTINUE_GT_%d)\n", cw->labelCounter);
        cw->labelCounter++;
    }
    else if (strcmp(command, "lt") == 0)
    {
        fprintf(cw->outputFile, "@SP\n");
        fprintf(cw->outputFile, "M = M - 1\n");
        fprintf(cw->outputFile, "A = M\n");
        fprintf(cw->outputFile, "D = M\n");
        fprintf(cw->outputFile, "A = A - 1\n");
        fprintf(cw->outputFile, "D = M - D\n");
        fprintf(cw->outputFile, "@TRUE_LT_%d\n", cw->labelCounter);
        fprintf(cw->outputFile, "D;JLT\n");
        fprintf(cw->outputFile, "@SP\n");
        fprintf(cw->outputFile, "A = M - 1\n");
        fprintf(cw->outputFile, "M = 0\n");
        fprintf(cw->outputFile, "@CONTINUE_LT_%d\n", cw->labelCounter);
        fprintf(cw->outputFile, "0;JMP\n");
        fprintf(cw->outputFile, "(TRUE_LT_%d)\n", cw->labelCounter);
        fprintf(cw->outputFile, "@SP\n");
        fprintf(cw->outputFile, "A = M - 1\n");
        fprintf(cw->outputFile, "M = -1\n");
        fprintf(cw->outputFile, "(CONTINUE_LT_%d)\n", cw->labelCounter);
        cw->labelCounter++;
    }

    // logic commands
    else if (strcmp(command, "and") == 0)
    {
        fprintf(cw->outputFile, "@SP\n");
        fprintf(cw->outputFile, "M = M - 1\n");
        fprintf(cw->outputFile, "A = M\n");
        fprintf(cw->outputFile, "D = M\n");
        fprintf(cw->outputFile, "A = A - 1\n");
        fprintf(cw->outputFile, "M = D & M\n");
    }
    else if (strcmp(command, "or") == 0)
    {
        fprintf(cw->outputFile, "@SP\n");
        fprintf(cw->outputFile, "M = M - 1\n");
        fprintf(cw->outputFile, "A = M\n");
        fprintf(cw->outputFile, "D = M\n");
        fprintf(cw->outputFile, "A = A - 1\n");
        fprintf(cw->outputFile, "M = D | M\n");
    }
    else if (strcmp(command, "not") == 0)
    {
        fprintf(cw->outputFile, "@SP\n");
        fprintf(cw->outputFile, "A = M - 1\n");
        fprintf(cw->outputFile, "M = !M\n");
    }
    else
    {
        // Command not found or invalid
        printf("Unsupported VM command: %s\n", command);
    }
};

void writePush(CodeWriter *cw, char *segment, int index)
{
    if (strcmp(segment, "local") == 0 || strcmp(segment, "argument") == 0)
    {
        char *cmd = strcmp(segment, "local") == 0 ? "LCL" : "ARG";

        fprintf(cw->outputFile, "@%d\n", index);
        fprintf(cw->outputFile, "D=A\n");
        fprintf(cw->outputFile, "@%s\n", cmd);
        fprintf(cw->outputFile, "A=D+M\n");
        fprintf(cw->outputFile, "D=M\n");
        fprintf(cw->outputFile, "@SP\n");
        fprintf(cw->outputFile, "A=M\n");
        fprintf(cw->outputFile, "M=D\n");
        fprintf(cw->outputFile, "@SP\n");
        fprintf(cw->outputFile, "M=M+1\n");
    }
    else if (strcmp(segment, "static") == 0)
    {
        fprintf(cw->outputFile, "@%s.%d\n", segment, index);
        fprintf(cw->outputFile, "D=M\n");
        fprintf(cw->outputFile, "@SP\n");
        fprintf(cw->outputFile, "A=M\n");
        fprintf(cw->outputFile, "M=D\n");
        fprintf(cw->outputFile, "@SP\n");
        fprintf(cw->outputFile, "M=M+1\n");
    }
    else if (strcmp(segment, "constant") == 0)
    {
        fprintf(cw->outputFile, "@%d\n", index);
        fprintf(cw->outputFile, "D=A\n");
        fprintf(cw->outputFile, "@SP\n");
        fprintf(cw->outputFile, "A=M\n");
        fprintf(cw->outputFile, "M=D\n");
        fprintf(cw->outputFile, "@SP\n");
        fprintf(cw->outputFile, "M=M+1\n");
    }
    else
    {
        // THIS, THAT, POINTER, TEMP segments not managed in this VM version
        printf("Unsupported VM command: push %s\n", segment);
    }
};
void writePop(CodeWriter *cw, char *segment, int index)
{
    if ((strcmp(segment, "local") == 0) || (strcmp(segment, "argument") == 0))
    {
        char *cmd = (strcmp(segment, "local") == 0) ? "LCL" : "ARG";

        fprintf(cw->outputFile, "@%d\n", index);
        fprintf(cw->outputFile, "D=A\n");
        fprintf(cw->outputFile, "@%s\n", cmd);
        fprintf(cw->outputFile, "D=D+M\n");
        fprintf(cw->outputFile, "@R13\n");
        fprintf(cw->outputFile, "M=D\n");
        fprintf(cw->outputFile, "@SP\n");
        fprintf(cw->outputFile, "M=M-1\n");
        fprintf(cw->outputFile, "A=M\n");
        fprintf(cw->outputFile, "D=M\n");
        fprintf(cw->outputFile, "@R13\n");
        fprintf(cw->outputFile, "A=M\n");
        fprintf(cw->outputFile, "M=D\n");
    }

    else if (strcmp(segment, "static") == 0)
    {
        // STATIC - POP
        fprintf(cw->outputFile, "@%s.%d\n", segment, index);
        fprintf(cw->outputFile, "D=A\n");
        fprintf(cw->outputFile, "@R13\n");
        fprintf(cw->outputFile, "M=D\n");
        fprintf(cw->outputFile, "@SP\n");
        fprintf(cw->outputFile, "M=M-1\n");
        fprintf(cw->outputFile, "A=M\n");
        fprintf(cw->outputFile, "D=M\n");
        fprintf(cw->outputFile, "@R13\n");
        fprintf(cw->outputFile, "A=M\n");
        fprintf(cw->outputFile, "M=D\n");
    }
    else
    {
        // THIS, THAT, POINTER, TEMP segments not managed in this VM version
        printf("Unsupported VM command: pop %s\n", segment);
    }
};

void writeLabel(CodeWriter *cw, char *label)
{
    fprintf(cw->outputFile, "(%s:%s)\n", cw->fName, label);
};

void writeGoto(CodeWriter *cw, char *label)
{
    fprintf(cw->outputFile, "@%s:%s\n", cw->fName, label);
    fprintf(cw->outputFile, "0;JMP\n");
};

void writeIf(CodeWriter *cw, char *label)
{
    fprintf(cw->outputFile, "@SP\n");
    fprintf(cw->outputFile, "M = M - 1\n");
    fprintf(cw->outputFile, "A = M\n");
    fprintf(cw->outputFile, "D = M\n");
    fprintf(cw->outputFile, "@%s:%s\n", cw->fName, label);
    fprintf(cw->outputFile, "D;JNE\n");
};

void writeCall(CodeWriter *cw, char *functionName, int numArgs)
{
    // push return-address
    fprintf(cw->outputFile, "@%s_RETURN_%d\n", functionName, cw->returnCounter);
    fprintf(cw->outputFile, "D=A\n");
    fprintf(cw->outputFile, "@SP\n");
    fprintf(cw->outputFile, "A=M\n");
    fprintf(cw->outputFile, "M=D\n");
    fprintf(cw->outputFile, "@SP\n");
    fprintf(cw->outputFile, "M=M+1\n");

    // push LCL
    fprintf(cw->outputFile, "@LCL\n");
    fprintf(cw->outputFile, "D=M\n");
    fprintf(cw->outputFile, "@SP\n");
    fprintf(cw->outputFile, "A=M\n");
    fprintf(cw->outputFile, "M=D\n");
    fprintf(cw->outputFile, "@SP\n");
    fprintf(cw->outputFile, "M=M+1\n");

    // push ARG
    fprintf(cw->outputFile, "@ARG\n");
    fprintf(cw->outputFile, "D=M\n");
    fprintf(cw->outputFile, "@SP\n");
    fprintf(cw->outputFile, "A=M\n");
    fprintf(cw->outputFile, "M=D\n");
    fprintf(cw->outputFile, "@SP\n");
    fprintf(cw->outputFile, "M=M+1\n");

    // push THIS
    fprintf(cw->outputFile, "@THIS\n");
    fprintf(cw->outputFile, "D=M\n");
    fprintf(cw->outputFile, "@SP\n");
    fprintf(cw->outputFile, "A=M\n");
    fprintf(cw->outputFile, "M=D\n");
    fprintf(cw->outputFile, "@SP\n");
    fprintf(cw->outputFile, "M=M+1\n");

    // push THAT
    fprintf(cw->outputFile, "@THAT\n");
    fprintf(cw->outputFile, "D=M\n");
    fprintf(cw->outputFile, "@SP\n");
    fprintf(cw->outputFile, "A=M\n");
    fprintf(cw->outputFile, "M=D\n");
    fprintf(cw->outputFile, "@SP\n");
    fprintf(cw->outputFile, "M=M+1\n");

    // ARG = SP - n - 5
    fprintf(cw->outputFile, "D=M\n");
    fprintf(cw->outputFile, "@%d\n", numArgs);
    fprintf(cw->outputFile, "D=D-A\n");
    fprintf(cw->outputFile, "@5\n");
    fprintf(cw->outputFile, "D=D-A\n");
    fprintf(cw->outputFile, "@ARG\n");
    fprintf(cw->outputFile, "M=D\n");

    // LCL = SP
    fprintf(cw->outputFile, "@SP\n");
    fprintf(cw->outputFile, "D=M\n");
    fprintf(cw->outputFile, "@LCL\n");
    fprintf(cw->outputFile, "M=D\n");

    // goto f
    fprintf(cw->outputFile, "@%s\n", functionName);
    fprintf(cw->outputFile, "0;JMP\n");

    // (return-address)
    fprintf(cw->outputFile, "(%s_RETURN_%d)\n", functionName, cw->returnCounter);

    cw->returnCounter++;
};

void writeReturn(CodeWriter *cw)
{
    // FRAME (R14) = LCL
    fprintf(cw->outputFile, "@LCL\n");
    fprintf(cw->outputFile, "D=M\n");
    fprintf(cw->outputFile, "@R14\n");
    fprintf(cw->outputFile, "M=D\n");

    // RETURN (R15) = * (FRAME - 5)
    fprintf(cw->outputFile, "@R14\n");
    fprintf(cw->outputFile, "D=M\n");
    fprintf(cw->outputFile, "@5\n");
    fprintf(cw->outputFile, "A=D-A\n");
    fprintf(cw->outputFile, "D=M\n");
    fprintf(cw->outputFile, "@R15\n");
    fprintf(cw->outputFile, "M=D\n");

    // *ARG = pop()
    fprintf(cw->outputFile, "@0\n");
    fprintf(cw->outputFile, "D=A\n");
    fprintf(cw->outputFile, "@ARG\n");
    fprintf(cw->outputFile, "D=D+M\n");
    fprintf(cw->outputFile, "@R13\n");
    fprintf(cw->outputFile, "M=D\n");
    fprintf(cw->outputFile, "@SP\n");
    fprintf(cw->outputFile, "M=M-1\n");
    fprintf(cw->outputFile, "A=M\n");
    fprintf(cw->outputFile, "D=M\n");
    fprintf(cw->outputFile, "@R13\n");
    fprintf(cw->outputFile, "A=M\n");
    fprintf(cw->outputFile, "M=D\n");

    // SP = ARG + 1
    fprintf(cw->outputFile, "@ARG\n");
    fprintf(cw->outputFile, "D=M\n");
    fprintf(cw->outputFile, "@1\n");
    fprintf(cw->outputFile, "D=D+A\n");
    fprintf(cw->outputFile, "@SP\n");
    fprintf(cw->outputFile, "M=D\n");

    // THAT = * (FRAME - 1)
    fprintf(cw->outputFile, "@R14\n");
    fprintf(cw->outputFile, "D=M\n");
    fprintf(cw->outputFile, "@1\n");
    fprintf(cw->outputFile, "A=D-A\n");
    fprintf(cw->outputFile, "D=M\n");
    fprintf(cw->outputFile, "@THAT\n");
    fprintf(cw->outputFile, "M=D\n");

    // THIS = * (FRAME - 2)
    fprintf(cw->outputFile, "@R14\n");
    fprintf(cw->outputFile, "D=M\n");
    fprintf(cw->outputFile, "@2\n");
    fprintf(cw->outputFile, "A=D-A\n");
    fprintf(cw->outputFile, "D=M\n");
    fprintf(cw->outputFile, "@THIS\n");
    fprintf(cw->outputFile, "M=D\n");

    // ARG = * (FRAME - 3)
    fprintf(cw->outputFile, "@R14\n");
    fprintf(cw->outputFile, "D=M\n");
    fprintf(cw->outputFile, "@3\n");
    fprintf(cw->outputFile, "A=D-A\n");
    fprintf(cw->outputFile, "D=M\n");
    fprintf(cw->outputFile, "@ARG\n");
    fprintf(cw->outputFile, "M=D\n");

    // LCL = * (FRAME - 4)
    fprintf(cw->outputFile, "@R14\n");
    fprintf(cw->outputFile, "D=M\n");
    fprintf(cw->outputFile, "@4\n");
    fprintf(cw->outputFile, "A=D-A\n");
    fprintf(cw->outputFile, "D=M\n");
    fprintf(cw->outputFile, "@LCL\n");
    fprintf(cw->outputFile, "M=D\n");

    // goto RETURN
    fprintf(cw->outputFile, "@R15\n");
    fprintf(cw->outputFile, "A=M\n");
    fprintf(cw->outputFile, "0;JMP\n");
};

void writeFunction(CodeWriter *cw, char *functionName, int numLocals)
{
    // (f)
    fprintf(cw->outputFile, "(%s)\n", functionName);
    strcpy(cw->fName, functionName);

    // repeat k times: PUSH 0
    while (numLocals > 0)
    {
        fprintf(cw->outputFile, "@0\n");
        fprintf(cw->outputFile, "D=A\n");
        fprintf(cw->outputFile, "@SP\n");
        fprintf(cw->outputFile, "A=D+M\n");
        fprintf(cw->outputFile, "D=M\n");
        fprintf(cw->outputFile, "@SP\n");
        fprintf(cw->outputFile, "A=M\n");
        fprintf(cw->outputFile, "M=D\n");
        fprintf(cw->outputFile, "@SP\n");
        fprintf(cw->outputFile, "M=M+1\n");
        numLocals--;
    }
};
