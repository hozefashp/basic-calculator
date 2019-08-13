/* The user of the stack, should call init()
 * before any calls to push(), pop();
 *
 */
#include "cstack.h"
#include <stdlib.h>
void cinit(cstack *s) {
	*s = NULL;
}
void cpush(cstack *s, char c) {
		cnode *temp1, *temp2;
		temp2 = *s;
		temp1 = (cnode*)malloc(sizeof(cnode));
		temp1 -> ch = c;
		temp1 -> cnext = NULL;
		if(*s == NULL){
			*s = temp1;
		}
		else{
			while (temp2 -> cnext != NULL)
				temp2 = temp2 -> cnext;
			temp2 -> cnext = temp1;
		}
}
/* The caller should check isempty() before calling
 * pop()
 */
char cpop(cstack *s) {
	cnode *temp1, *temp2;
	char c;
	int flag = 0;
	temp1 = *s;
	temp2 = temp1;
	while(temp1 -> cnext != NULL){
		temp2 = temp1;
		temp1 = temp1 -> cnext;
		flag = 1;
	}
	c = temp1 -> ch;
	if(flag == 0){
		*s = NULL;
		return c;
	}
	temp2 -> cnext = NULL;
	free(temp1);
	temp2 = NULL;
	return c;
}
int cisfull(cstack *s) {
	return 1;	
}
int cisempty(cstack *s){
	return *s == NULL;
}
