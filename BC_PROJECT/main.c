#include "stack.h"
#include "list.h"
#include "infix.h"
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define COUNT 1024
int main(int argc, char *argv[]) {
	int arg = 0;
	if(argc == 2 && strcmp(argv[1], "-h") == 0) {
		printf("MODE:- HELP\n");
		printf("My-bc 1.1.0\n");
		printf("Copyright 2018 --->Pradnya Navale\n");
		printf("This is free software with ABSOLUTELY NO WARRANTY.\n");
		printf("\nUsage: project [option]\n");
		printf("\t-h\t--help\t\tprint this help and exit\n");
		printf("\t-v\t--version\tprints information about version of this software\n");
		printf("\t-q\t--quiet\t\tdon't print initial banner\n");
		printf("\t-i\t--integers\tprints answers in integer format only\n");
		printf("\t-f\t--friendly\tmakes ouput user friendly\n\n");
		printf("(-expr)\tThe result is the negation of the expression.\n");
		printf(" expr+expr\n");
		printf("\tThe result of the expression is the sum of the two expressions.\n");
		printf(" expr-expr\n");
		printf("\tThe result of the expression is the difference of the two expressions.\n\n");
		printf(" expr*expr\n");
		printf("\tThe result of the expression is the sum of the two expressions.\n\n");
		printf(" expr/expr\n");
		printf("\tThe result of the expression is the quotient of the two  expressions.\n\n");
		printf(" expr%%expr\n");
		printf("\tThe result of the expression is the \"remainder\n\n");
		printf(" expr^expr\n");
		printf("\tThe result of the expression is the value of the first raised to the second\n\n");
		printf("expr!\n");
		printf("\tThe result of the expression is the factorial of given input value\n");
		printf(" (expr)\n");
		printf("\tThis  alters  the standard precedence to force the evaluation of\n");
		printf("\tthe expression.\n");
		printf(" /*...*/\n");
		printf("\tThis can be used for putting comments\n");
		printf("\tRelational expressions are a special kind  of  expression  that  always\n");
		printf("\tevaluate to 0 or 1, 0 if the relation is false and 1 if the relation is\n");
		printf("\ttrue.\n");
		printf(" expr1<expr2\n");
		printf("\tThe result is 1 if expr1 is strictly less than expr2.\n");
		printf(" expr1>expr2\n");
		printf("\tThe result is 1 if expr1 is strictly grater than expr2.\n");
		printf(" expr1<=expr2\n");
		printf("\tThe result is 1 if expr1 is less than or equal to expr2.\n");
		printf(" expr1==expr2\n");
		printf("\t The result is 1 if expr1 is strictly equal to expr2.\n");
		printf(" expr1>=expr2\n");
		printf("\tThe result is 1 if expr1 is greater than or equal to expr2.\n");
		printf(" S(x)\n");
		printf("\tThe sine of x, x is in degrees.\n");
		printf(" C(x)\n");
		printf("\tThe cosine of x, x is in degrees.\n");
		printf(" T(x)\n");
		printf("\tThe tangent of x, x is in degrees.\n");
		exit(0);		
	}
	else if(argc == 2 && strcmp(argv[1], "-i") == 0) {
		arg = 2;
		printf("MODE:- INTEGER\n");
		printf("My-bc 1.1.0\n");
		printf("Copyright 2018 --->Pradnya Navale\n");
		printf("This is free software with ABSOLUTELY NO WARRANTY.\n");
	}
	else if(argc == 2 && strcmp(argv[1], "-v") == 0) {
		arg = 1;
		printf("MODE:- VERSION\n");
		printf("My-bc 1.1.0\n");
		printf("Copyright 2018 --->Pradnya Navale\n");
		printf("This is free software with ABSOLUTELY NO WARRANTY.\n");
		exit(0);
	}
	else if(argc == 2 && strcmp(argv[1], "-q") == 0) {
		printf("MODE:- QUIET\n");
		arg = 4;
	}
	else if(argc == 2 && strcmp(argv[1], "-f") == 0) {
		arg = 5;
		printf("MODE:- FRIENDLY\n");
		printf("My-bc 1.1.0\n");
		printf("Copyright 2018 --->Pradnya Navale\n");
		printf("This is free software with ABSOLUTELY NO WARRANTY.\n");
	}
	else if(argc == 1) {
		arg = 0;
		printf("My-bc 1.1.0\n");
		printf("Copyright 2018 --->Pradnya Navale\n");
		printf("This is free software with ABSOLUTELY NO WARRANTY.\n");
	}
	else {
		printf("USAGE: ./project [option] \n");
		printf("USAGE for help : ./project -h\n");
		exit(0);
	}
	char str[COUNT];	
	int x;
	list *ans;
	ans = (list *)malloc(sizeof(list));
	init(ans);
	while((x = readline(str, COUNT))) {
		ans = infix(str);
		if(ans == NULL) {
			fprintf(stderr, "Erorr in expression\n");
		}  
		else {
			if(arg != 5) {
				printf("answer = ");
				traverse(ans, arg);
			}
			else 
				traverse(ans, arg);
			printf("\n");
		}
	}
	return 0;
}
