#include <stdio.h>

typedef enum EyeColor{
	e1,e2,e3,e4
} ec;

int main(){
	ec a;
	a = e2;
	for (int i = 0; i < 4; i++) {
		printf("%d\n", a);
	}
}
