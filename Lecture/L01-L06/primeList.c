#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void main() {
	int N;

	printf("Enter an upper bound: ");
	scanf("%d", &N);

	//Make storage for flags
	int *isPrime = (int*) malloc(N * sizeof(int));

	//Initialize, i.e. set everything "true"
	for (int i = 0; i < N; i++) isPrime[i] = 1;

	int sqrtN = (int) sqrt(N);

	for (int i = 2; i < sqrtN; i++) {
		if (isPrime[i]) { //If i is prime
			for (int j = i * i; j < N; j+=i) {
				isPrime[j] = 0; //Not prime
			}
		}
	}

	//Count the number of primes we found
	int cnt = 0;
	for (int i = 0; i < N; i++) {
		if (isPrime[i]) {
			cnt++;
		}
	}

	//Make a list of them
	int *primes = (int*) malloc(cnt * sizeof(int));

	//Loop once more and build the list
	cnt = 0;
	for (int i = 0; i < N; i++) {
		if (isPrime[i]) {
			primes[cnt++] = i;
		}
	}

	//Print out what find
	for (int i = 0; i < cnt; i++) printf("The %d-th prime is %d\n", i, primes[i]);

	//cleanup
	free(isPrime);
	free(primes);
}
