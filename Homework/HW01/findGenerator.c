#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void main() {
	int n;
	int prime = 1;

	printf("Enter a prime number: ");
	scanf("%d", &n);
	
	if (n == 1) prime = 0;
	else {
		for (int i = 2; i <= n / 2; i++) {
			if (n % i == 0) prime = 0;
		}
	}

	if (prime != 1) printf("%d is not prime. You have to enter a prime number\n", n);
	else {
		for (int i = 2; i < n; i ++) {
			int g = 1;
			for (int j = 1; j < n - 2; j++) {
				if ((int) pow(i, j) % n == 1) g = 0;
			}
			if (g == 1) printf("%d is a generator of Z_%d.\n", i, n);
		}
	}
}