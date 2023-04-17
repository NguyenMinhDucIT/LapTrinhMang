#include <stdio.h>
#include <string.h>

int main(){
	char a[256] = "a";
	char b[256] = "b";

	printf("%s", a);
	char c[256] = strcat(a, b);
	printf("%s", c);
}

