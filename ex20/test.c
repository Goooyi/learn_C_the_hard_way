#include <stdio.h>

typedef int (*fp) (int a, int b);

int add2(int a, int b){
	return a+b;}


int main()
{
	fp fpp = add2;
	printf("function pointer is %p, and function string s %s, int is %d\n", fpp, fpp, fpp);
	printf("function pointer is %p, and function string s %s, int is %d\n", add2, add2, add2);
}
