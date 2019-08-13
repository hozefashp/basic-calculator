/* The user of the stack, should call init()
 * before any calls to push(), pop();
 *
 */
#include "stack.h"
#include <stdlib.h>
void init(stack *s) {
	*s = NULL;
}
void push(stack *s, Number num) {
		nnode *temp1, *temp2;
		temp2 = *s;
		temp1 = (nnode*)malloc(sizeof(nnode));
		temp1 -> val = num;
		temp1 -> next = NULL;
		if(*s == NULL){
			*s = temp1;
		}
		else{
			while (temp2 -> next != NULL)
				temp2 = temp2 -> next;
			temp2 -> next = temp1;
		}
}
/* The caller should check isempty() before calling
 * pop()
 */
Number pop(stack *s) {
	nnode *temp1, *temp2;
	Number num;
	initNumber(&num);
	int flag = 0;
	temp1 = *s;
	temp2 = temp1;
	while(temp1 -> next != NULL){
		temp2 = temp1;
		temp1 = temp1 -> next;
		flag = 1;
	}
	num = temp1 -> val;
	if(flag == 0){
		*s = NULL;
		return num;
	}
	temp2 -> next = NULL;
	free (temp1);
	temp2 = NULL;
	return num;
}
int isfull(stack *s) {
	return 1;	
}
int isempty(stack *s){
	return *s == NULL;
}
