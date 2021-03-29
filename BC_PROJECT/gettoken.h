#include "list.h"
#define OPERAND 10 
#define OPERATOR 20
#define	END 40
#define ERROR 50
typedef struct token {
	char op;
	//int dec;
	int type; /* type takes values OPERAND/OPERATOR/END/*/	
	list *l;
	//int flag;
	char var;
}token;
token *getnext(char *, int *);
