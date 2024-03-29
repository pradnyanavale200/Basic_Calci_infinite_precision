#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include "list.h"
#include "function.h"
#include "stack.h"
#include<math.h>
void copy(list *l1, list *l2) {
	int dec, i, num, sign;
	init(l2);
	for(i = 0; i < l1->len; i++) {
		num = show(l1, i);
		append(l2, num);
	}
	dec = l1->dec;
	l2->dec = dec;
	sign = l1->sign;
	l2->sign = sign;
	return;
}
int checkzero(list *l) {
	int e, flag = 0;
	for(e = 0; e < l->len; e++) {
		if(show(l, e) != 0)
			flag = 1;
	}
	return flag;	
}
list *addnum(list *l1, list *l2) {
	list *result;
	int sign1, sign2;
	sign1 = l1->sign;
	sign2 = l2->sign;
	result = (list *)malloc(sizeof(list));
	init(result);
	if(dec(l1) > dec(l2)) {
		int i;
		int y = (dec(l1) - dec(l2));
		for(i = 0; i < y; i++) {
			append(l2, 0);
			l2->dec++;
		}
	}
	else if(dec(l2) > dec(l1)) {
		int i;
		int y = (dec(l2) - dec(l1));
		for(i = 0; i < y; i++) {
			append(l1, 0);
			l1->dec++;
		}
	}
	
	if(l1->sign != l2->sign) {
		if(l1->sign == -1) {
			l1->sign = 1;
			result = subnum(l2, l1);
			l1->sign = sign1;
			return result;
		}
		else if(l2->sign == -1) {
			l2->sign = 1;
			result = subnum(l1, l2);
			l2->sign = sign2;
			return result;
		}
	}
	else if(l1->sign == l2->sign) {
		if(l1->sign == -1)
			result->sign = -1;
		else
			result->sign = 1;
		int num = 0, i, j;
		i = length(l1);
		j = length(l2);
		int carry = 0;
		while(i != 0 || j != 0) {
			if(i == 0) {
				num = show(l2, j - 1) + carry;
				j--;
				carry = num / 10;
				num = num % 10;
				insert(result, 0, num);
			}
			else if(j == 0) {
				num = show(l1, i -1) + carry;
				i--;
				carry = num / 10;
				num = num % 10;
				insert(result, 0, num);
			}
			else {
				num = show(l1, i - 1) + show(l2, j - 1) + carry;
				i--;
				j--;
				carry = num / 10;
				num = num % 10;
				insert(result, 0 , num);
			}
		}
		result->dec = dec(l1);
		if(carry != 0)
			insert(result, 0, carry);
	}
	l1->sign = sign1;
	l2->sign = sign2;
	return result;
}

list *subnum(list *l1, list *l2) {
	int sign1, sign2;
	sign1 = l1->sign;
	sign2 = l2->sign;
	/*Make no of digits after decimal equal*/
	if(dec(l1) > dec(l2)) {
		int i;
		int y = (dec(l1) - dec(l2));
		for(i = 0; i < y; i++) {
			append(l2, 0);
			l2->dec++;
		}
	}
	else if(dec(l2) > dec(l1)) {
		int i;
		int y = (dec(l2) - dec(l1));
		for(i = 0; i < y; i++) {
			append(l1, 0);
			l1->dec++;
		}
	}
	int num;
	static int flag = 0;
	list *result;
	result = (list *)malloc(sizeof(list));
	init(result);
	if(l1->sign != l2->sign) {
		if(l2->sign == -1) {
			l2->sign = 1;
			result = addnum(l1, l2);
			result->sign = 1;
		}
		if(l1->sign == -1) {
			l1->sign = 1;
			result = addnum(l1, l2);
			result->sign = -1;
		}
	}
	else if(l1->sign == l2->sign) {
		if(l1->sign == -1) {
			l1->sign = 1;
			l2->sign = 1;
			result = subnum(l2, l1);
		}
		if(l1->sign == 1) {
			if(compare(l1, l2) >= 0) {
				if(flag != 1)
					result->sign = 1;
				else
					result->sign = -1;
				int b = 0;
				int m,n;
				m = length(l1) - 1;
				n = length(l2) - 1; 
				while(m != -1 || n != -1) {
					if(n == -1) {
						num = show(l1, m);
						m--;
						insert(result, 0, num);
					}
					else {
						int a = show(l1, m);
						m--;
						int c = show(l2, n);
						n--;
						if(a >= c) {
							num = a - c;
							insert(result, 0, num);
						}
						else {
							int d = 0;
							while(!(b = remov(l1, m))) {
								m--;
								d++;
							}
							m--;
							m++;
							insert(l1, m, b - 1);
							int i;
							for(i = 0; i < d; i++) {
								m++;
								insert(l1, m, 9);
							}
							num = 10 + a - c;
							insert(result, 0, num);
						}
					}
				}
			}
			else if(compare(l1, l2) < 0) {
				flag = 1;
				result = subnum(l2, l1);
				result->sign = -1;
			}
		}
	}
	result->dec = l1->dec;
	flag = 0;
	l1->sign = sign1;
	l2->sign = sign2;
	return result;
}   
list *mulnum(list *l1, list *l2) {
	list *result;
	result = (list *)malloc(sizeof(list));
	init(result);
	int tempsign, sign1, sign2;
	sign1 = l1->sign;
	sign2 = l2->sign;
	if(checkzero(l1) == 0)
		return l1;
	if(checkzero(l2) == 0)
		return l2;	
	if(l1->sign == l2->sign) {
		tempsign = 1;
		l1->sign = l2->sign = 1;
	}
	else {
		tempsign = -1;
		l1->sign = l2->sign = 1;
	}
	int x = length(l1) - length(l2);
	if(x < 0) {
		result = mulnum(l2, l1);
		return result;
	}
	else {
		int n = length(l2) - 1, j, i;
		int a = length(l2), b = length(l1);
		int arr[2 * b];
		for( i = 0; i < 2 * b; i++)
			arr[i] = 0;
		int num1 = 0, num2 = 0;
		int k = 2 * b - 1;
		for( i = 0; i < a; i++) {
			int m = length(l1) - 1;
			int carry1 = 0, carry2 = 0;
			for( j = k - i; j > b - 2; j--) {
				if(m != -1 && n != -1) {
					num1 = show(l1, m) * show(l2, n) + carry1;
					m--;
					carry1 = num1 / 10;
					num1 = num1 % 10;
					num2 = arr[j] + num1 + carry2;
					carry2 = num2 / 10;
					num2 = num2 % 10;
					arr[j] = num2;
				}
				else {
					break;
				}
			}
			arr[j] = carry1 + carry2 + arr[j];
			b--;
			n--;
		}
		j = 0;
		for( i = 2 * length(l1) - 1; i > b - 1 && i >= 0; i--) {
			insert(result, 0, arr[i]); j++;
		}
		result->dec = l1->dec + l2->dec;
		result->sign = tempsign;
		l1->sign = sign1;
		l2->sign = sign2;
		return result;
	}
}
list *division(list *l1, list *l2) {
	if(checkzero(l2) == 0) {
		printf("INVALID INPUT:cann't divide by zero");
		return NULL;
	}
	list *result;
	result = (list *)malloc(sizeof(list));
	list *temp;
	temp = (list *)malloc(sizeof(list));
	init(temp);
	init(result);
	int m, sign1, sign2;
	sign1 = l1->sign;
	sign2 = l2->sign;
	if(l1->sign == l2->sign) {
		result->sign = 1;
		l1->sign = l2->sign = 1;
	}
	else {
		result->sign = -1;
		l1->sign = l2->sign = 1;
	}
	int a, b;
	m = l1->dec - l2->dec;
	int i, j, k, num;
	a = l1->dec;
	b = l2->dec;
	l1->dec = l2->dec = 0;
	for(i = 0; i < length(l1); i++) {
		num = show(l1, i);
		append(temp, num);
		if(compare(temp, l2) < 0) {
			append(result, 0);
		}
		else {
			int d = 0;
			while(1) {
				temp = subnum(temp, l2);
				d++;
				if(compare(temp, l2) < 0)
					break;
					
			}
			append(result, d);
		}
	}
	j = 0; k = 0;
	while(j < 10) {
		append(temp, 0);
		int d = 0;
		while(compare(temp, l2) >= 0) {
			temp = subnum(temp, l2);
			d++;
		}
		if(d != 0) {
			append(result, d);
			k++;
		}
		j++;
	}
	result->dec = k + m;
	l1->dec = a;
	l2->dec = b;
	l1->sign = sign1;
	l2->sign = sign2;
	return result;
}
list *modulus(list *l1, list *l2) {
	if(checkzero(l2) == 0) {
		printf("INVALID INPUT:cann't divide by zero");
		return NULL;
	}
	list *result;
	result = (list *)malloc(sizeof(list));
	list *temp;
	temp = (list *)malloc(sizeof(list));
	init(temp);
	init(result);
	list *l3;
	l3 = (list *)malloc(sizeof(list));
	init(l3);
	copy(l2, l3);
	int m, sign1, sign2;
	sign1 = l1->sign;
	sign2 = l2->sign;
	if(l1->sign == l2->sign) {
		result->sign = 1;
		l1->sign = l2->sign = 1;
	}
	else {
		result->sign = -1;
		l1->sign = l2->sign = 1;
	}
	int a, b;
	m = length(l1);
	int i, j, num;
	a = dec(l1);
	b = dec(l2);
	if(dec(l1) != 0) {
		l1->len = l1->len - dec(l1);
	}
	if(l3->dec != 0) {
		i = dec(l3);
		for(j = 0; j < i; j++) {
			remov(l3, l3->len);
		}
	}
	for(i = 0; i < l1->len; i++) {
		num = show(l1, i);
		append(temp, num);
		if(compare(temp, l3) < 0) {
			append(result, 0);
		}
		else {
			int d = 0;
			while(1) {
				temp = subnum(temp, l3);
				d++;
				if(compare(temp, l3) < 0)
					break;
			}
			append(result, d);
		}
	}
	l1->len = m;
	l1->sign = sign1;
	l2->sign = sign2;
	l1->dec = a;
	l2->dec = b;
	return temp;
}
/*It does comparision of two list and make their dec and lenght eqaul */	
int compare(list *l1, list *l2) {
	if(l1->sign == 1 && l2->sign == -1)
		return 1;
	if(l2->sign == 1 && l1->sign == -1)
		return -1;
	/*Make no. of digits after decimal equal*/
	if(dec(l1) > dec(l2)) {
		int i;
		int y = (dec(l1) - dec(l2));
		for(i = 0; i < y; i++) {
			append(l2, 0);
			l2->dec++;
		}
	}
	else if(dec(l2) > dec(l1)) {
		int i;
		int y = (dec(l2) - dec(l1));
		for(i = 0; i < y; i++) {
			append(l1, 0);
			l1->dec++;
		}
	}
	int a = (length(l1) - length(l2));
	if(a > 0) {
		int i = 0;
		while(i < a) {
			insert(l2, 0, 0);
			i++;
		}
	}
	else if(a < 0) {
		int i = 0;
		a = -a;
		while(i < a) {
			insert(l1, 0, 0);
			i++;
		}
	}	
	int i;
	for(i = 1; i <= length(l1); i++) {
		if(show(l1, i - 1) > show(l2, i - 1))
			return 1;
		else if(show(l1, i - 1) < show(l2, i - 1))
			return -1;
	}
	return 0;
}

list *power(list *l1, list *l2) {
	list *result = (list *)malloc(sizeof(list));
	init(result);
	append(result, 1);
	list *c1 = (list *)malloc(sizeof(list));
	init(c1);
	append(c1, 1);
	list *l3 = (list *)malloc(sizeof(list));
	init(l3);
	list *c2 = (list *)malloc(sizeof(list));
	init(c2);
	list *c0 = (list *)malloc(sizeof(list));
	init(c0);
	int sign = l1->sign;
	append(c2, 2);
	append(c0, 0);
	copy(l2, l3);
	/*when multiplying power is positive*/
	if(l2->sign == 1) {
		while(checkzero(l3) != 0) {
			result = mulnum(result, l1);
			l3 = subnum(l3, c1);
		}
	}
	/*when multiplying power is negative*/
	else if(l2->sign == -1) {
		while(checkzero(l3) != 0) {
			result = division(result, l1);
			l3 = addnum(l3, c1);
		}
	}
	l1->sign = sign;
	/*to give sign to the result when it has -ve sign*/
	if(l1->sign == -1) {
		if(compare(modulus(l2, c2), c0) == 0)
			result->sign = 1;
		else
			result->sign = -1;
	}
	return result; 
	
} 
/*It gets the another list which contain 1 and finds the factorial*/
list *factorial(list *l1, list *l2) {
	list *result = (list *)malloc(sizeof(list));
	init(result);
	append(result, 1);
	while(compare(l1, l2) > 0) {
		result = mulnum(l1, result);
		l1 = subnum(l1, l2);
	}
	return result;		 
	
}
double radian(list *l1) {
	list *result;
	result = (list *)malloc(sizeof(list));
	list *temp;
	temp = (list *)malloc(sizeof(list));
	init(temp);
	init(result);
	list *l2;
	l2 = (list *)malloc(sizeof(list));
	init(temp);
	init(result);
	init(l2);
	append(l2, 3);
	append(l2, 6);
	append(l2, 0);
	double rad = 0;
	int flag = 1,i ,j, num, d;
	flag = l1->sign;
	for(i = 0; i < length(l1); i++) {
		num = show(l1, i);
		append(temp, num);
		if(compare(temp, l2) < 0) {
			append(result, 0);
		}
		else {
			d = 0;
			while(1) {
				temp = subnum(temp, l2);
				d++;
				if(compare(temp, l2) < 0)
					break;
			}
			append(result, d);
		}
	}
	list *std;
	std = (list *)malloc(sizeof(list));
	init(std);
	append(std, 1);
	append(std, 8);
	append(std, 0);
	if(compare(temp, std) <= 0) {
		j = 0;
		for(i = 0 - dec(temp); i < length(temp) - dec(temp); i++) {
			rad = rad + (double)show(temp, temp->len - j - 1) * pow(10, i);
			j++;
		}
		rad = (double)(rad / (180) * PI);
		if(flag == -1) 
			return (0 - rad);
	}
	else {
		temp = subnum(temp, std);
		j = 0;
		for(i = -dec(temp); i < length(temp) - dec(temp); i++) {
			rad = rad + show(temp, temp->len - j - 1) * pow(10, i);
			j++;
		}
		rad = (rad / 180) * PI;
		if(flag == 1) 
			return (0 - rad);
	}
	return rad; 
}
list *sine(list *l) {
	double rad = sin(radian(l));
	char s[50];
	double rem;
	int i = 0;
	list *result;
	result = (list *)malloc(sizeof(list));
	init(result);
	result->dec = 0;
	if(rad < 0 ) {
		result->sign = -1;
		rad = 0 - rad;
	}
	rem = rad;
	if(rad == 0) {
		append(result , 0);
		return result;
	}
	if(rem == 1) {
		append(result, 1);
		return result;
	}
	sprintf(s,"%f", rad);
	int num = strlen(s);
	int flag = 0, dec = 0;
	while(i < num) {
		if(flag == 1)
			dec++;
		if(s[i] == '.') {
			flag = 1;
		} 
		if(s[i] != '.')
			append(result, s[i] - '0');
		i++;
	}
	result->dec = dec;
	return result;
}
list *cosine(list *l) {
	double rad = cos(radian(l));
	double rem;
	char s[50];
	int i = 0;
	list *result;
	result = (list *)malloc(sizeof(list));
	init(result);
	result->dec = 0;
	if(rad < 0 ) {
		result->sign = -1;
		rad = 0 - rad;
	}
	rem = rad;
	if(rad == 0) {
		append(result , 0);
		return result;
	}
	if(rem == 1) {
		append(result, 1);
		return result;
	}
	sprintf(s,"%f", rad);
	int num = strlen(s);
	int flag = 0, dec = 0;
	while(i < num) {
		if(flag == 1)
			dec++;
		if(s[i] == '.') {
			flag = 1;
		} 
		if(s[i] != '.')
			append(result, s[i] - '0');
		i++;
	}
	result->dec = dec;
	return result;
}
list *tangent(list *l) {
	char s[50];
	double rad = tan(radian(l));
	double rem;
	int i = 0;
	list *result;
	result = (list *)malloc(sizeof(list));
	init(result);
	result->dec = 0;
	if(rad < 0 ) {
		result->sign = -1;
		rad = 0 - rad;
	}
	rem = rad;
	if(rad == 0) {
		append(result , 0);
		return result;
	}
	if(rem == 1) {
		append(result, 1);
		return result;
	}
	sprintf(s,"%f", rad);
	int num = strlen(s);
	int flag = 0, dec = 0;
	while(i < num) {
		if(flag == 1)
			dec++;
		if(s[i] == '.') {
			flag = 1;
		} 
		if(s[i] != '.')
			append(result, s[i] - '0');
		i++;
	}
	result->dec = dec;
	return result;
}
