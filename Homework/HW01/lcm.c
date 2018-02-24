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
	printf("The least common multiple of %d and %d is %d.\n", a, b, a * b / findGCD(a, b));
}

/**
	return The gcd found.
*/
int findGCD(int a, int b) {
	if (b == 0) return a;
	else return findGCD(b, a % b);
}