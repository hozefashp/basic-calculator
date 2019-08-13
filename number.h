typedef struct node {
	char ch;
	struct node *prev, *next;
}node;

typedef struct Number{
	int sign;
	node *head, *tail;
}Number;

void initNumber(Number *a);
void append(Number *a, char c);
void appendAtHead(Number *a, char c);
void insert(Number *a, char ch, int pos);
void appendZeroes(Number *a, Number *b);
Number addition(Number a, Number b);
Number subtraction(Number a, Number b);
Number multiplication(Number a, Number b);
Number division(Number a, Number b);
Number modulus(Number a, Number b);
Number power(Number a, Number b);
Number LeftShift(Number a, Number b);
Number RightShift(Number a, Number b);
Number factorial (Number a);
Number Sine (Number a);
void DeleteHeadZeroes (Number *a);
void DeleteTailZeroes (Number *a);
void tens(Number *a, Number *b);
int compare(Number a, Number b);
void printNumber(Number a);
void destroyNumber(Number *a);
int decimalLength (Number a);
int length(Number a);
