#include <stdio.h>

typedef enmum EyeColor{
	e1,e2,e3,e4
} ec;

int main(){
	ec a;
	for (int i = 0; i < 4; i++) {
		printf("%d\n", a[i]);
	}
}
