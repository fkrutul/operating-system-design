#include <stdio.h>

    int main() {

    int i;
	int numOfTerms; 
	int baseCase1 = 0;
	int baseCase2 = 1;
	int fib;

    printf("How many terms? : ");
    scanf("%d", &numOfTerms);
    printf("Sequence up to entered term: ");

    for (i = 1; i <= numOfTerms; i++) {
        printf("%d, ", baseCase1);
        fib = baseCase1 + baseCase2;
        baseCase1 = baseCase2;
        baseCase2 = fib;
        }
        
	printf("Completed\n");
        return 0;
    }
