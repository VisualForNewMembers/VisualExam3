#include <stdio.h>
int main()
{
	long sum = 1, n;
	scanf_s("%d", &n);
	for (int i = 1; i <= n; i++)
		sum *= i;
	printf("%l", sum);
}