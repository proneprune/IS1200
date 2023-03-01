
#include <stdio.h>
#include <stdlib.h>

#define COLUMNS 6

int times_called = 0;



void print_number(float number_value){

  if(times_called % COLUMNS == 0){
    printf("\n");
  }
  printf("%10f ",number_value);
  times_called++;
}


void mean_sieves(int n){
    unsigned char *a = (unsigned char*)malloc(n);

    float total_value = 0;
    float mean_value = 0;
    float total_primes = 0;

    for(int i = 2; i < n; i++){
    a[i] = 1;
    }

    for(int i = 2; i < n; i++){
        if(a[i] == 1){
            for(int j = i*i; j <= n; j = j+i){
                a[j] = 0;
            }
        }
    }


    for(int i = 2; i < n; i++){
        if(a[i] == 1){
          total_value = total_value + i;
          total_primes++;
        }
    }
    mean_value = total_value/total_primes;
    print_number(mean_value);


    free(a);
}



int main(int argc, char *argv[]){
  if(argc == 2)
    mean_sieves(atoi(argv[1]));
  else
    printf("Please state an interger number.\n");
  return 0;
}