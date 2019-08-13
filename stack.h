#include <stdio.h>
#include "number.h"
typedef struct nnode{
	Number val;
	struct nnode *next;
	}nnode;
typedef nnode *stack;
void init(stack *s);
void push(stack *s, Number num);
Number pop(stack *s);
int isempty(stack *s);
int isfull(stack *s);
