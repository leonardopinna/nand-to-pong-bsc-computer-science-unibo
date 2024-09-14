#include "headers/Code.h"

const char *destCode(const char *value)
{
    if (strcmp(value, "") == 0)
    {
        return "000";
    }
    else if (strcmp(value, "M") == 0)
    {
        return "001";
    }
    else if (strcmp(value, "D") == 0)
    {
        return "010";
    }
    else if (strcmp(value, "MD") == 0)
    {
        return "011";
    }
    else if (strcmp(value, "A") == 0)
    {
        return "100";
    }
    else if (strcmp(value, "AM") == 0)
    {
        return "101";
    }
    else if (strcmp(value, "AD") == 0)
    {
        return "110";
    }
    else if (strcmp(value, "AMD") == 0)
    {
        return "111";
    }
    else
    {
        // Unknown dest value
        return "000";
    }
}

const char *compCode(const char *value)
{
    if (strcmp(value, "0") == 0)
    {
        return "0101010";
    }
    else if (strcmp(value, "1") == 0)
    {
        return "0111111";
    }
    else if (strcmp(value, "-1") == 0)
    {
        return "0111010";
    }
    else if (strcmp(value, "D") == 0)
    {
        return "0001100";
    }
    else if (strcmp(value, "A") == 0)
    {
        return "0110000";
    }
    else if (strcmp(value, "!D") == 0)
    {
        return "0001101";
    }
    else if (strcmp(value, "!A") == 0)
    {
        return "0110001";
    }
    else if (strcmp(value, "-D") == 0)
    {
        return "0001111";
    }
    else if (strcmp(value, "-A") == 0)
    {
        return "0110011";
    }
    else if (strcmp(value, "D+1") == 0)
    {
        return "0011111";
    }
    else if (strcmp(value, "A+1") == 0)
    {
        return "0110111";
    }
    else if (strcmp(value, "D-1") == 0)
    {
        return "0001110";
    }
    else if (strcmp(value, "A-1") == 0)
    {
        return "0110010";
    }
    else if (strcmp(value, "D+A") == 0)
    {
        return "0000010";
    }
    else if (strcmp(value, "D-A") == 0)
    {
        return "0010011";
    }
    else if (strcmp(value, "A-D") == 0)
    {
        return "0000111";
    }
    else if (strcmp(value, "D&A") == 0)
    {
        return "0000000";
    }
    else if (strcmp(value, "D|A") == 0)
    {
        return "0010101";
    }
    else if (strcmp(value, "M") == 0)
    {
        return "1110000";
    }
    else if (strcmp(value, "!M") == 0)
    {
        return "1110001";
    }
    else if (strcmp(value, "-M") == 0)
    {
        return "1110011";
    }
    else if (strcmp(value, "M+1") == 0)
    {
        return "1110111";
    }
    else if (strcmp(value, "M-1") == 0)
    {
        return "1110010";
    }
    else if (strcmp(value, "D+M") == 0)
    {
        return "1000010";
    }
    else if (strcmp(value, "D-M") == 0)
    {
        return "1010011";
    }
    else if (strcmp(value, "M-D") == 0)
    {
        return "1000111";
    }
    else if (strcmp(value, "D&M") == 0)
    {
        return "1000000";
    }
    else if (strcmp(value, "D|M") == 0)
    {
        return "1010101";
    }
    else
    {
        return "0000000";
    }
}

const char *jumpCode(const char *value)
{
    if (strcmp(value, "JGT") == 0)
    {
        return "001";
    }
    else if (strcmp(value, "JEQ") == 0)
    {
        return "010";
    }
    else if (strcmp(value, "JGE") == 0)
    {
        return "011";
    }
    else if (strcmp(value, "JLT") == 0)
    {
        return "100";
    }
    else if (strcmp(value, "JNE") == 0)
    {
        return "101";
    }
    else if (strcmp(value, "JLE") == 0)
    {
        return "110";
    }
    else if (strcmp(value, "JMP") == 0)
    {
        return "111";
    }
    else
    {
        // Unknown jump value
        return "000";
    }
}
