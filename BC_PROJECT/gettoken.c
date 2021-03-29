#include "list.h"
#include "gettoken.h"
#include<stdlib.h>
#include<stdio.h>
/*********************************token.c************************************/
enum states { SPC, DIG, OPR, STOP, ERR };
token *getnext(char *arr, int *reset) {
	static int currstate;
	int nextstate;
	static int i;
	static list *l;
	static int dec = 0;
	static int flag = 0;
	static int m = 0, num = 0, sign = 1;
	l = (list *)malloc(sizeof(list));
	init(l);
	if(m == 1) {
		append(l, num);
		m = 0;
	}	
	if(*reset == 1) {
		i = 0;
		currstate = SPC;
		*reset = 0;
	}
	token *t = (token *)malloc(sizeof(token));
	while(1) {
		switch(arr[i]) {
			case '0': case '1': case '2': case '3':
			case '4': case '5': case '6': case '7':
			case '8': case '9': case '.':
				nextstate = DIG;
				break;
			case '+': case '-': case '*': case '/':
			case '%': case '(': case ')': case '^':
			case '!': case '<': case '>': case '=':
			case 'S': case 'C': case 'T':
				nextstate = OPR;
				break;
			case '\0':
				nextstate = STOP;
				break;
			case ' ':
				nextstate = SPC;
				break;
			default:
				nextstate = ERR;
				break;
		}
		switch(currstate) {
			case SPC:
				if(nextstate == DIG) {
					if(arr[i] == '.') {
						flag = 1;
					}
					else {
						append(l,(arr[i] - '0'));
						if(flag == 1)
							dec++;
					}
				}			
				break;
			case DIG:
				if(nextstate == DIG) {
					if(arr[i] == '.') {
						flag = 1;
					}
					else {
						append(l, (arr[i] - '0'));
						if(flag == 1)
							dec++;
					}
				}
				else { 
					t->type = OPERAND;
					t->l = l;
					t->l->dec = dec;
					t->l->sign = sign;
					sign = 1; 
					dec = 0;
					flag = 0;
					currstate = nextstate;
					i++;
					return t;
				}
				break;
			case OPR:
				if(arr[i - 2] == '(') {
					if(arr[i - 1] == '-')
						sign = -1;
					else
						sign = 1;
				} 
				if(sign != -1) {
					t->type = OPERATOR;
					t->op = arr[i - 1];
				}		
				currstate = nextstate;
				if(arr[i - 1] == '/' && arr[i] == '*') {
					while(1) {
						i++;
						if(arr[i] == '*' && arr[i + 1] == '/') {
							break;
						}
					}
					nextstate = SPC;
					i = i + 1;
					break;
				}
				if(arr[i-1] == '<' && arr[i] == '=') {
					t->var = 'y';
				}
				if(arr[i - 1] == '>' && arr[i] == '=') {
					t->var = 'y';
				}
				if(arr[i - 1] == '=' && arr[i] == '=') {
					t->var = 'y';
				}
				if(arr[i - 1] == '=' && arr[i] == '!') {
					t->var = 'n';
				}		
				if(nextstate == DIG) { 
					if(arr[i] == '.') {
						flag = 1;
						dec = 0;
					}
					else {	
						m = 1;
						num = arr[i] - '0';
						if(flag == 1)
							dec++;
					}
				}
				i++;
				return t;
				break;
			case STOP:
				t->type = END;
				currstate = nextstate;
				i++;
				return t;
				break;
			case ERR:
				t->type = ERROR;
				currstate = nextstate;
				i++;
				return t;
				break;
		}
		currstate = nextstate;
		i++;
	}
}
