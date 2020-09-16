
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

float var_g = 0.0;

void delay(){
   for(unsigned int j = 0; j < 5000000; j++);
}

void* funcao_t(void *arg){
   int* val = (int*)arg;
   int nt = (*val), divbyzero = 0;
   float res = 0.0;
   char op, str;

   printf("Inicio da thread %d\n", nt);
   for(int i = 0; i < 10; i++){
      
      if(nt == 0){
         op = '+';
         str = 'A';
         res = var_g + i;
      }else if(nt == 1){
         op = '-';
         str = 'S';
         res = var_g - i;
      }else if(nt == 2){
         op = '*';
         str = 'M';
         res = var_g * i;
      }else if(nt == 3){
         if(i != 0){
            op = '/';
            str = 'D';
            res = var_g / i;
         }else{
            op = '/';
            str = 'D';
            res = 0;
            divbyzero = 1;
         }
      }
      if(divbyzero == 1){
          printf("Thread: %d -->> [%c] => %.0f %c %d = Division by zero\n", nt, str, var_g, op, i);
          divbyzero = 0;
      }else{
         printf("Thread: %d -->> [%c] => %.0f %c %d = %.2f\n", nt, str, var_g, op, i, res);   
      }
      
      delay();
   }
   printf("Fim da thread %d\n", nt);
   return NULL;
}

int main(){
   pthread_t t[4];
   int t_args[4];
   
   int x = 1;
   while(x == 1){
      printf("Digite um valor entre 1 e 9: \n");
      scanf("%f", &var_g);
      if(var_g < 1.0 || var_g > 9.0){
         printf("Valor incorreto!\n");
      }else{
         x = 0;
      }
   }
   
   for(int i = 0; i < 4; i++){
      t_args[i] = i;
      pthread_create(&(t[i]), NULL, funcao_t, &(t_args[i]));
      
   }
   
   // Espera as threads terminarem
   for(int i = 0; i < 4; i++){
      pthread_join(t[i], NULL);
   }
   
   printf("Done!\n");
   return 0;
}