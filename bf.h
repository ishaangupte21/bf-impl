#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>

#ifndef BF_H
#define BF_H

char *getSource(const char *path);
void interpret(const char *source);

#endif