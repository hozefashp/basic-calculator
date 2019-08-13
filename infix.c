#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <string.h>
#include <limits.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <ctype.h>
#include "stack.h"
#include "cstack.h"
/* Reads a line of input from the user, till \n
 * and stores it in the array arr and makes arr
 * a string, and returns no. of characters read
 */
int readline(char *arr, int n) {
	char ch;
	int i = 0;
	while((ch = getchar()) != '\n' && i < n)
		if ((ch == '(') || (ch == ')')) {
			arr[i++] = ' ';
			arr[i++] = ch;
			arr[i++] = ' ';
		}
		else {
			arr[i++] = ch;
		}
	arr[i] = '\0';
	return i;
}
/*getnext token function, where a token is a character followed by a space*/
#define	OPERAND		1
#define OPERATOR	2
#define	END		3
#define ERROR		4

int getnext(char *str, char *token) {
	char *p = str, *t = token;
	while (*p == ' ' || *p == '\t') 
		p++;
	while (*p && *p != ' ') {
		*token = *p;
		token++;
		p++;
	}
		
	*token = '\0';
	while ((*str++ = *p++))
		;
	if(t[0] == '\0')
		return 3; 			//END
	else if (isdigit(t[0]))
		return 1; 			//OPERAND
	else if ((t[0] == '-') && (isdigit(t[1])))
		return 1;			//OPERAND
	else if (t[0] == '+' || t[0] == '-' || t[0] == '*' || t[0] == '/' || t[0] == '(' || t[0] == ')' || t[0] == '%' || t[0] == '^' || t[0] == '<' || t[0] == '>' || t[0] == '!' || t[0] == 'S')
		return 2; 			//OPERATOR
	return 4;				//ERROR
}

char ctop(cstack *s) {
	char temp;
	if (!cisempty(s)) {
		temp = cpop(s);
		cpush(s, temp);
	}
	return temp;
}
/*precedence for operators*/
int precedence(char op) {
	if(op == '^')
		return 90;
	if(op == '%')
		return 70;
	if(op == '/')
		return 50;
	if(op == '*')
		return 40;
	if(op == '+' || op == '-')
		return 30;
	return 0;
}
Number calc(Number a, Number b, char op){
	switch(op) {
		case '+' :
			return addition (a,b);
		case '-' :
			return subtraction (a, b);
		case '/' :
			return division (a, b);
		case '*' :
			return multiplication (a, b);
		case '%' :
			return modulus (a, b);
		case '^' :
			return power (a, b);
		case '<' :
			return LeftShift (a, b);	
		case '>' :
			return RightShift (a, b);
		case '!' :
			return factorial (b);
		case 'S' :
			return Sine (b);
	}
}

Number infixval(char *infix) {
	stack s;
	cstack cs;
	Number x, y, result;
	initNumber(&x);
	initNumber(&y);
	Number a[100];
	initNumber(&result);
	int type,precurr, pretop, i, j = 0;
	char temp[1024], ch;
	init(&s);
	cinit(&cs);
	infix[strlen(infix)] = '\0';
	while (1) {
		type = getnext(infix, temp);
		if (type == OPERAND) {
			i = 0;
			initNumber(&a[j]);
			while (isdigit(temp[i]) || (temp[i] == '.') || (temp[i] == '-')) {
				append(&a[j], temp[i]);
				i++;
			}
			push(&s, a[j]);
			j++;
		}
		else if (type == OPERATOR) {
		/*Bracket Handling Begins*/
			if (temp[0] == '(')			
				cpush(&cs, temp[0]);
			else if (temp[0] == ')') {
				ch = cpop(&cs);
				while (ch != '(') {
					if (!isempty(&s)){
						x = pop(&s);
					}
					if (!isempty(&s))
						y = pop(&s);
					result = calc(y, x, ch);
					push(&s, result);
					ch = cpop(&cs);
				}
			}
			/*Bracket Handling Ends*/
			/*Precedence calculation and bracket calculation and pushes result on the stack*/
			else {
				precurr = precedence(ctop(&cs));
				pretop = precedence(temp[0]);
			while (!cisempty(&cs) && precurr >= pretop && ((ctop(&cs)) != '(')) {
				if (!isempty(&s))
					x = pop(&s);
				if (!isempty(&s))
					y = pop(&s);
				ch = cpop(&cs);
				result = calc(y, x, ch);
				push(&s, result);
			}
			cpush(&cs, temp[0]);
			}
		}
		else if (type == END)
			break;
		else if (type == ERROR) {
			fprintf(stderr, "Bad expression\n");
		}
	}
	/*Normal calculation*/
	while(!cisempty(&cs)) {
		x = pop(&s);
		if (!isempty(&s))
			y = pop(&s);
		ch = cpop(&cs);
		result = calc(y, x, ch);
		push(&s, result);
	}
	for (int k = 0; k <= j ;k++)
		destroyNumber(&a[k]);
	return result;
}

int main(int argc, char *argv[]) {
	char line[1024];
	int x;
	Number y;
	initNumber(&y);
	while ((x = readline(line, 1024))) {
		y = infixval(line);
		DeleteTailZeroes(&y);
		DeleteTailZeroes(&y);
		printNumber(y);
		destroyNumber(&y);
	}
	return 0;
}
