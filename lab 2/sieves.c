
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

///jämför med sieves-heap för att få rätt kod
void print_sieves(int n){
    unsigned char *a = (unsigned char*)malloc(n);

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
            print_number(i);
        }
    }
    free(a);
}


int main(int argc, char *argv[]){
  if(argc == 2)
    print_sieves(atoi(argv[1]));
  else
    printf("Please state an interger number.\n");
  return 0;
}