#ifndef __MYBCBIGNUM_H
#define __MYBCBIGNUM_H
#define PLUS 1
#define MINUS -1 
#define PI 3.1415926535
#include<math.h>
#include "list.h"
void copy(list *l1, list *l2);
int checkzero(list *l);
list *addnum(list *l1, list *l2);
list *subnum(list *l1, list *l2);
list *mulnum(list *l1, list *l2);
list *division(list *l1, list *l2);
list *modulus(list *l1, list *l2);
int compare(list *l1, list *l2);
list *power(list *l1, list *l2);
list *factorial(list *l1, list *l2);
double radian(list *l1);
list *sine(list *l);
list *cosine(list *l);
list *tangent(list *l);
#endif
