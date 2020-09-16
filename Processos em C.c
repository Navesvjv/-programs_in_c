#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int main(){
  
  int pid, status, val;
  
  pid = fork();
  if(pid != 0){
    printf("%d -> I'm your Father!\n", getppid());
  }else{
    int loop = 1;
    while(loop == 1){
       printf("Digite um valor entre 1 e 9: \n");
       scanf("%d", &val);
       if(val < 1 || val > 9){
          printf("Valor incorreto!\n");
       }else{
          loop = 0;
       }
    }   
    for(int i = 0; i < 10; i++){
       printf("Filho: %d ->> %d x %d = %d\n", getpid(), val, i, val*i);
    }
  }
  
  wait(&status);
  printf("Done!\n");
  
  return 0;
}
