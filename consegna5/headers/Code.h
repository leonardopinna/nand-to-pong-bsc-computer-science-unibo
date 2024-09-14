#ifndef CODE_H
#define CODE_H

#include "Utils.h"

// Returns the binary code for the dest value.
const char *destCode(const char *value);

// Returns the binary code for the comp value.
const char *compCode(const char *value);

// Returns the binary code for the jump value.
const char *jumpCode(const char *value);

#endif // CODE_H