#ifndef PARSER_H
#define PARSER_H

#include "utils.h"
#include "codewriter.h"

#define MAX_LINE_LENGTH 100

void parse(CodeWriter *cw, FILE *inputFile);

void sanitize(char *str);

#endif // PARSER_H