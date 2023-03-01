/*
 print-prime.c
 By David Broman.
 Last modified: 2015-09-15
 This file is in the public domain.
*/


#include <stdio.h>
#include <stdlib.h>

#define COLUMNS 6

int times_called = 0;

void print_number(int number_value){

  if(times_called % COLUMNS == 0){
    printf("\n");
  }
  printf("%10d ",number_value);
  times_called++;
}

int is_prime(int n){
  for(int i = 2; i< n; i++){
    if(n % i == 0){
    return 0;
    }
  }
  return 1;
}


void print_primes(int n){
  // Should print out all prime numbers less than 'n'
  // with the following formatting. Note that
  // the number of columns is stated in the define
  // COLUMNS
for(int i = 2; i < n; i++){
  if(is_prime(i) == 1){
    print_number(i);
  }

}


}

// 'argc' contains the number of program arguments, and
// 'argv' is an array of char pointers, where each
// char pointer points to a null-terminated string.
int main(int argc, char *argv[]){
  if(argc == 2)
    print_primes(atoi(argv[1]));
  else
    printf("Please state an interger number.\n");
  return 0;
}

 
