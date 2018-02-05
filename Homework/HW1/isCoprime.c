#include <stdio.h>

int findGCD(int a, int b);

void main() {
	int a, b;
	
	printf("Enter the first number: ");
	scanf("%d", &a);
	printf("Enter the second number: ");
	scanf("%d", &b);
	if (a < b) {
		int temp;
		temp = a;
		a = b;
		b = temp;
	}
	if (findGCD(a, b) == 1) printf("%d and %d are coprime.\n", a, b);
	else printf("%d and %d are not coprime.\n", a, b);
}

/**
	return The gcd found.
*/
int findGCD(int a, int b) {
	if (b == 0) return a;
	else return findGCD(b, a % b);
}