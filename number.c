#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "number.h"
void initNumber(Number *a){
	a -> head = a -> tail = NULL;
	a -> sign = 0;
}
void append(Number *a, char c){
	if (isdigit(c) || c == '.'|| c == '-') {
		if (c == '-') {
			a -> sign = 1;
			return;
		} 
		int len;
		node *x, *tmp;
		len = length(*a);
	
		x = (node *)malloc(sizeof(node));
		x -> ch = c;
		if(len == 0) {
			a -> head = a -> tail = x;
			x -> prev = x -> next = NULL;
			return;
		}
		tmp = a -> tail;
	
		tmp -> next = x;
		x -> next = NULL;
		x -> prev = tmp;
	
		a -> tail = x;
	}
}

void appendAtHead(Number *a, char c){
	if (isdigit(c) || c == '.') { 
		int len;
		node *x, *tmp;
		len = length(*a);
	
		x = (node *)malloc(sizeof(node));
		x -> ch = c;
		if(len == 0) {
			a -> head = a -> tail = x;
			x -> prev = x -> next = NULL;
			return;
		}
		tmp = a -> head;
	
		tmp -> prev = x;
		x -> prev = NULL;
		x -> next = tmp;
	
		a -> head = x;
	}
}

void insert(Number *a, char ch, int pos){
	node *x, *tmp;
	x = (node *)malloc(sizeof(node));
	x -> ch = ch;
	
	tmp = a -> tail;
	for(int i = 0; i < pos; i++)
		tmp = tmp -> prev;

	tmp -> next -> prev = x;
	x -> next = tmp -> next;
	tmp -> next = x;
	x -> prev = tmp;
}

void appendZeroes(Number *a, Number *b) {
	int len1, len2;
	len1 = decimalLength(*a);
	len2 = decimalLength(*b);
	if (len1 != len2) {
		if (len1 > len2) {
			if (len2 == 0) {
				append(b, '.');
			}
			for (int i = 0; i < (len1 - len2); i++) {
				append(b, 0 + '0');
			}
		}
		else if (len1 < len2) {
			if (len1 == 0) {
				append(a, '.');
			}
			for (int i = 0; i < (len2 - len1); i++) {
				append(a, 0 + '0');
			}
		}
	}
}

void newNumber (Number *a, char *str);
void newNumber (Number *a, char *str) {
	char *p = str;
	while (isdigit(*p) || (*p == '.') || (*p == '-')) {
		append(a, *p);
		p++;
	}
}

Number addition(Number a, Number b) {
	Number c;
	initNumber(&c);
	if ((a.sign == b.sign) && (a.sign == 1))
		c.sign = 1;
	else if (a.sign != b.sign){
		if (a.sign == 1) {
			a.sign = 0;
			if (compare(a, b) > 0) 
				c = subtraction(a, b);
			else
				c = subtraction(b, a);
			a.sign = 1;
		}
		else if (b.sign == 1) {
			b.sign = 0;
			c = subtraction(a, b);
			b.sign = 1;
		}
		if (compare(a, b) > 0) {
			if (a.sign == 1) 
				c.sign = 1;
		}
		return c;
	}
	int d, num1, num2 = 0;
	char e;
	node *tmp1, *tmp2;
	appendZeroes(&a, &b);
	tmp1 = a.tail;
	tmp2 = b.tail;
	while(1) {
		if (tmp1 && tmp2) {
			if (tmp1 -> ch == '.'){
				appendAtHead(&c, '.');
				tmp1 = tmp1 -> prev;
				tmp2 = tmp2 -> prev;
			}
		}
		if (!tmp1 && tmp2) {
			appendAtHead(&a, '0');
			tmp1 = a.head;
		}
		if (tmp1 && !tmp2) {
			appendAtHead(&b, '0');
			tmp2 = b.head;
		}
		else if (!tmp1 && !tmp2 && num2) {
			appendAtHead(&c, num2 + '0');
			break;
		}
		else if ((!tmp1) && (!tmp2) && (num2 == 0))
			break;
		d = (((tmp1 -> ch) - '0') + ((tmp2 -> ch) - '0') + num2);
		if (d > 9) {
			num1 = d % 10;
			num2 = (d - num1) / 10;
			e = num1 + '0';
		}
		else {
			num2 = 0;
			e = d + '0';
		}
		appendAtHead(&c, e);
		tmp1 = tmp1 -> prev;
		tmp2 = tmp2 -> prev;	
	}
	return c;
}


Number subtraction(Number a, Number b){
	Number c;
	initNumber(&c);
	if (a.sign != b.sign){
		if (a.sign == 1) {
			a.sign = 0;
			c = addition(a, b);
			a.sign = 1;
		}
		else if (b.sign == 1) {
			b.sign = 0;
			c = addition(a, b);
			b.sign = 1;
		}
		if (a.sign == 1) 
			c.sign = 1;
		return c;
	}
	int d, f, g, j = 0;
	char e;
	node *tmp1, *tmp2;
	appendZeroes(&a, &b);
	if (compare(a, b) == -1 ) {
		tmp1 = b.tail;
		tmp2 = a.tail;
		c.sign = 1;
	}
	else if (compare(a, b) == 1 ) {
		tmp1 = a.tail;
		tmp2 = b.tail;
	}
	else if (compare(a, b) == 0 ){
		append(&c, '0');
		return c;
	}
	if (a.sign == b.sign){
		if (compare(a, b) > 0) {
			if (a.sign == 1) 
				c.sign = 1;
		}
		else if (compare(a, b) < 0) {
			if (a.sign == 1) 
				c.sign = 0;
		}
	}
	while(tmp1 && tmp2) {
		if (tmp1 && tmp2) {
			if (tmp1 -> ch == '.'){
				appendAtHead(&c, '.');
				tmp1 = tmp1 -> prev;
				tmp2 = tmp2 -> prev;
			}
		}
		if (tmp1 && !tmp2) {
          		tmp2 = (node *)malloc(sizeof(node));
            		tmp2 -> ch = '0';
		}
		f = (tmp1 -> ch) - '0';
		g = (tmp2 -> ch) - '0';
		if (f <= g) {
			f += 10;
			d = f - g - j;
			j = 1;
			if (d == 10) {
				d = 0;
				j = 0;
			}
		}
		else {
			d = f - g -j;
			j = 0;
		}
		e = d + '0';
		appendAtHead(&c, e);
		tmp1 = tmp1 -> prev;
		tmp2 = tmp2 -> prev;	
	}
	DeleteHeadZeroes(&c);
	return c;

}

Number multiplication (Number a, Number b) {
	Number c;
	initNumber(&c);
	if (a.sign != b.sign)
		c.sign = 1;
	node *tmp1, *tmp2, *tmp3, *tmp4;
	int i, j, d, num1, num2 = 0, k, len1 = decimalLength(a), len2 = decimalLength(b);
	tmp1 = a.tail;
	tmp2 = b.tail;
	char e;
	if (tmp2) {
		if (tmp2 -> ch == '.')
			tmp2 = tmp2 -> prev;
		}
	j = (tmp2 -> ch) - '0';
	while(tmp1 || num2){
		if (tmp1) {
			if (tmp1 -> ch == '.')
				tmp1 = tmp1->prev;
		}		
		if (!tmp1){
			e = num2 + '0';
			appendAtHead(&c, e);
			break;
		}
		i = (tmp1 -> ch) - '0';
		d = (i * j) + num2;
		if (d > 9) {
			num1 = d % 10;
			num2 = (d - num1) / 10;
			e = num1 + '0';
		}
		else {
			num2 = 0;
			e = d + '0';
		}
		appendAtHead(&c, e);
		tmp1 = tmp1 -> prev;
	}
	tmp4 = c.tail -> prev;
	tmp3 = c.tail -> prev;
	while ((tmp2 = tmp2 -> prev)) {
		tmp1 = a.tail;
		if (tmp2) {
			if (tmp2 -> ch == '.')
				tmp2 = tmp2 -> prev;
		}
		j = (tmp2 -> ch) - '0';
		num2 = 0;
		tmp3 = tmp4; 
		while (1) {
			if (tmp1) {
				if (tmp1 -> ch == '.')
					tmp1 = tmp1 -> prev;
			}
			if ((!tmp3 || !tmp4) && !tmp1 && !num2) {
				break;
			}
			if (!tmp3 && !tmp1 && num2) {
				appendAtHead(&c, num2 + '0');
				break;
			}
			if (!tmp3) {
				appendAtHead(&c, '0');
				tmp3 = c.head;
				if (!tmp4)
				   tmp4 = c.head;
			}
			i = (tmp1 -> ch) - '0';
			k = (tmp3 -> ch) - '0';
			d = k + (i * j) + num2;
			if (d > 9) {
				num1 = d % 10;
				tmp3 -> ch = num1 + '0';
				num2 = (d - num1) / 10;
			}
			else {
				num2 = 0;
				tmp3 -> ch = d + '0';
			}
			tmp3 = tmp3 -> prev;
			tmp1 = tmp1 -> prev;
		}
		tmp4 = tmp4 -> prev;
		
	}
	if (len1 || len2) {
		insert(&c, '.', (len1 + len2));
	}
	DeleteHeadZeroes(&c);
	DeleteTailZeroes(&c);
	return c;
}


Number division(Number a, Number b) {
	Number tmp1, tmp2, result;
	initNumber(&tmp1);
	initNumber(&tmp2);
	initNumber(&result);
	newNumber(&tmp2, "0");
	if (compare(tmp2, b) == 0) {
		printf("Zero Division Error\n");
		destroyNumber(&tmp1);
		destroyNumber(&tmp2);
		return result;
	}
	if (a.sign != b.sign)
		result.sign = 1;
	int flag = 0;
	if (b.sign == 1) {
		b.sign = 0;
		flag = 1;
	}
	int d = 0, j = 0;
   	char Number;
   	tens(&a, &b);
   	node *x;
	x = a.head;
	for (int i = 0; i < length(a); i++) {
		Number = (x -> ch);
		x = x -> next;
		append(&tmp1, Number);
		if (compare(tmp1, b) < 0){
			append(&result, '0');
			}
		else {
			d = 0;
			while(1) {
				tmp1 = subtraction(tmp1,b);
				d++;
				if (compare(tmp1, b) < 0){
					break;
				}
            		}
			append(&result, d + '0');
		}
	}
	if (compare(result,tmp2) != 0)
		DeleteHeadZeroes(&result);
	if (compare(tmp1, tmp2) != 0) {
		append(&result, '.');
		while (j < 10) {
			append(&tmp1, '0');
			d = 0;
			while(compare(tmp1, b) >= 0) {
				tmp1 = subtraction(tmp1,b);
				d++;
			}
			append(&result, d + '0');
			j++;
		}
	}
	DeleteHeadZeroes(&result);
	DeleteTailZeroes(&result);
	destroyNumber(&tmp1);
	destroyNumber(&tmp2);
	if (flag == 1)
		b.sign = 1;
	return result;
}

Number modulus(Number a, Number b) {
	Number tmp1, tmp2;
	initNumber(&tmp1);
	initNumber(&tmp2);
	newNumber(&tmp2, "0");
	if (compare(tmp2, b) == 0) {
		printf("Zero Division Error\n");
		destroyNumber(&tmp2);
		return tmp1;
	}
	int len1 = decimalLength(a), len2 = decimalLength(b);
	tens(&a, &b);
	node *x;
	x = a.head;
   	char Number;
	for (int i = 0; i < length(a); i++) {
		Number = (x -> ch);
		x = x -> next;
		append(&tmp1, Number);
		if (compare(tmp1, b) < 0)
			;
		else {
			while(1) {
				tmp1 = subtraction(tmp1,b);
				if (compare(tmp1, b) < 0){
					break;
            			}
			}
		}
	}
	if (len1 || len2) {
		if (len1 >=len2)
			insert(&tmp1, '.', len1);
		else
			insert(&tmp1, '.', len2);
	}
	return tmp1;
}

Number power(Number a, Number b) {
	Number i, j ,k;
   	initNumber(&i);
   	initNumber(&j);
   	initNumber(&k);
   	newNumber(&i, "0");
   	newNumber(&j, "1");
   	newNumber(&k, "1");
   	for( ; (compare(i, b) == -1); i = addition(i,j)) {
   		k = multiplication(k, a);
   	}
   	destroyNumber(&i);
   	destroyNumber(&j);
   	return k;
}

Number LeftShift(Number a, Number b) {
	Number tmp;
	initNumber(&tmp);
	newNumber(&tmp, "2");
	return multiplication(a, power(tmp, b));
}

Number RightShift(Number a, Number b) {
	Number tmp;
	initNumber(&tmp);
	newNumber(&tmp, "2");
	return division(a, power(tmp, b));
}

Number factorial (Number a) {
	Number i, j, result;
	initNumber(&i);
   	initNumber(&j);
   	initNumber(&result);
   	newNumber(&i, "1");
   	newNumber(&j, "1");
   	newNumber(&result, "1");
	for( ; ((compare(i, a) == -1) || compare(i, a) == 0); i = addition(i,j)) {
   		result = multiplication(result, i);
   	}
   	destroyNumber(&i);
   	destroyNumber(&j);
   	return result;
}
void DegreeToRadian(Number *a);
void DegreeToRadian(Number *a) {
	Number pi, d;
	initNumber(&pi);
	initNumber(&d);
	newNumber(&pi, "3.1415926536");
	newNumber(&d, "180");
	*a = multiplication(division(*a, d), pi);
	destroyNumber(&pi);
	destroyNumber(&d);
}
/* Calculates Sine when input is in Degrees */
/* Gives Wrong Answer for some inputs*/
Number Sine (Number a) {
	DegreeToRadian(&a);
	Number i, sum, t, tmp1, p, zero, one, two;
	initNumber(&i);
	initNumber(&sum);
	initNumber(&t);
	initNumber(&tmp1);
	initNumber(&p);
	initNumber(&zero);
	initNumber(&one);
	initNumber(&two);
	newNumber(&i, "2");
	sum = a;
	t = a;
	newNumber(&tmp1, "0.00001");
	newNumber(&zero, "0");
	newNumber(&one, "1");
	newNumber(&two, "2");
	while (compare(t, tmp1) == 1) {
		p = multiplication(subtraction(multiplication(two, i), one), subtraction(multiplication(two, i), two));
		t = division(multiplication(t, multiplication(a, a)), p);
		if (compare(modulus(i, two), zero) == 0)
			sum = subtraction(sum, t);
		else
			sum = addition(sum, t);
		i = addition(i, one);
	}
	destroyNumber(&i);
	destroyNumber(&t);
	destroyNumber(&tmp1);
	destroyNumber(&p);
	destroyNumber(&zero);
	destroyNumber(&one);
	destroyNumber(&two);
	return sum;
}

void DeleteHeadZeroes(Number *a) {
    node *x, *tmp;
    x = a -> head;
    while ((x -> ch == '0') && (x -> next) && (x -> next -> ch != '.')){
        tmp = x;
        x = x -> next;
        a -> head = x;
        x -> prev = NULL;
        free(tmp);
    }
}

void DeleteTailZeroes(Number *a) {
	int len = decimalLength(*a);
	if (len) {
    		node *x, *tmp;
    		x = a -> tail;
    		while (((x -> ch == '0') || (x -> ch == '.')) && (x -> prev)){
    			tmp = x;
			x = x -> prev;
			a -> tail = x;
			x -> next = NULL;
			if (tmp -> ch == '.')
				break;
			free(tmp);
   		}
  	}
}

void tens(Number *a, Number *b) {
	Number t;
	initNumber(&t);
	append(&t, '1');
	int len1 = decimalLength(*a), len2 = decimalLength(*b), k = len1;
	if (len1 > len2) {
		k = (len1 - len2);
		if (len2)
			k += len2;
   		for (int i = 0; i < k; i++) {
   			append(&t, '0');
   		}
   		*a = multiplication(*a, t);
   		*b = multiplication(*b, t);
   	}
   	else if (len1 < len2) {
   		k = (len2 - len1);
		if (len1)
			k += len1;
   		for (int i = 0; i < k; i++) {
   			append(&t, '0');
   		}
   		*a = multiplication(*a, t);
   		*b = multiplication(*b, t);
   	}
   	else {
   		for (int i = 0; i < k; i++) {
   			append(&t, '0');
   		}
   		*a = multiplication(*a, t);
   		*b = multiplication(*b, t);
   	}
}


int compare(Number a, Number b) {
	int len1, len2, len3, len4, p, q;
	len1 = decimalLength(a);
	len2 = decimalLength(b);
	len3 = length(a);
	len4 = length(b);
	p = (len3-len1) - (len4-len2);
	q = (len3-len1);
	if (p > 0) {
        	for (int i = 0; i < p; i++) {
		        appendAtHead(&b, '0');
        	}
        	q = (len3-len1);
	}
	else if (p < 0) {
        	p = -p;
        	for (int i = 0; i < p; i++) {
        		appendAtHead(&a, '0');
        	}
        	q = (len4 - len2);
	}
	else if ((p == 0) && (len1 || len2)) {
		if (len2 > len1) {
			for (int i = 0; i < (len2 - len1); i++) {
				append(&a, '0');
			}
		}
		else if (len2 < len1) {
			for (int i = 0; i < (len1 - len2); i++) {
				append(&a, '0');
			}
		}
		if (len3 > len4)
			q = len3;
		else
			q = len4;
	}
    	node *x, *y;
    	x = a.head;
    	y = b.head;
    	for (int i = 0; i < q; i++) {
    		if ((x -> ch == '.') && (x -> next))
    			x = x -> next;
    		if ((y -> ch == '.') && (y -> next))
    			y = y -> next;
        	if (((x -> ch) - '0') > ((y -> ch) - '0'))
        	    	return 1;
        	else if (((x -> ch) - '0') < ((y -> ch) - '0'))
        	    	return -1;
        	else if ((((x -> ch) - '0') == ((y -> ch) - '0')) && (x -> next) && (y -> next)) {
        	    	x = x -> next;
        	    	y = y -> next;
        	}
    	}
    	return 0;
}
void printNumber(Number a){
	node *tmp;
	tmp = a.head;
	if(!tmp) {
		return;
	}
	if (a.sign == 1)
		printf("-");
	do {
		printf("%c", tmp -> ch);
		tmp = tmp -> next;
	}while(tmp != NULL);
	printf("\n");
}

void destroyNumber(Number *a) {
	if (a -> head == NULL)
		return;
	else {
		node *tmp;
		int i, len = length(*a);
		for (i = 0; i < len; i++) {
			tmp = a -> head;
			if (len == 1) {
				a-> head = NULL;
				free(tmp);
			}
			else {
				a -> head = tmp -> next;
				a -> head -> prev = NULL;
				free(tmp);
				len--;
			}
		}
	}
}

int decimalLength (Number a) {
	int len = 0;
	node *tmp, *tmp1;
	tmp = tmp1 = a.tail;
	if (!tmp)
		return 0;
	while(tmp1) {
		if (tmp1->ch == '.') {
			break;
		}
		tmp1 = tmp1->prev;
	}
	if (tmp1) {
		if (tmp1->ch == '.') {
			do {
				tmp = tmp -> prev;
				len++;
			}while (tmp->ch != '.');
		}
	}
	return len;
	
}

int length (Number a) {
	int len = 0;
	node *tmp;
	tmp = a.head;
	if (!tmp)
		return 0;
	do {
		if (tmp -> ch == '.')
			len--;
		tmp = tmp -> next;
		len++;
	}while (tmp != NULL);
	return len;
}
