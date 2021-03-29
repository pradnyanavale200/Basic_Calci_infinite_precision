#ifndef __MYBCINFIX_H
#define __MYBCINFIX_H
#include "stack.h"
#include "list.h"
#include "function.h"
int precedence(char op);
int readline(char *arr, int len);
list *infix(char *str);
#endif
