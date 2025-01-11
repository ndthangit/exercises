clude <stdio.h>
#include <stdlib.h>
#define INCREMENT(x) ++x
int main()
{
	char *ptr = "DHBK-HN";
	int x = 10;
	printf("%s  ", INCREMENT(ptr + 1));
	printf("%d", INCREMENT(1 + x));
	return 0;
}