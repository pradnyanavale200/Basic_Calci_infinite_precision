#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include "stack.h"
#include "list.h"
void push(stack *s, list *l) {
	s->l[s->i]= l;
	(s->i)++;
}
/* the caller should check that the stack is not empty before calling pop()*/
list *pop(stack *s) {
	list *t = (list *)malloc(sizeof(list)); 
	t = s->l[s->i - 1];
	(s->i)--;
	return t;
}
int empty(stack *s) {
	return s->i == 0;
}
int full(stack *s) {
	return s->i == MAX;
}
/* It is mandatory to call init() on a stack before calling push, pop or any other function on the stack*/
void sinit(stack *s) {
	s->i = 0;
}
/*******************************stack1.c**************************************/
void push1(stack1 *s, list *l) {
	s->l[s->i]= l;
	(s->i)++;
}
/* the caller should check that the stack is not empty before calling pop()*/
list *pop1(stack1 *s) {
	list *t = (list *)malloc(sizeof(list)); 
	t = s->l[s->i - 1];
	(s->i)--;
	return t;
}
int empty1(stack1 *s) {
	return s->i == 0;
}
int full1(stack1 *s) {
	return s->i == MAX;
}
/* It is mandatory to call init() on a stack before calling push, pop or any other function on the stack*/
void sinit1(stack1 *s) {
	s->i = 0;
}
/**********************************cstack.c**************************************/
void cpush(cstack *s, char num) {
	s->a[s->i]= num;
	(s->i)++;
}
/* the caller should check that the cstack is not empty before calling pop()*/
char cpop(cstack *s) {
	char t = s->a[s->i - 1];
	(s->i)--;
	return t;
}
int cempty(cstack *s) {
	return s->i == 0;
}
int cfull(cstack *s) {
	return s->i == MAX;
}
/* It is mandatory to call init() on a cstack before calling push, pop or any other function on the cstack*/
void cinit(cstack *s) {
	s->i = 0;
}

