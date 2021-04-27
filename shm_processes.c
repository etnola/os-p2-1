#include  <stdio.h>
#include  <stdlib.h>
#include  <sys/types.h>
#include  <sys/ipc.h>
#include  <sys/shm.h>
#include <unistd.h>
#include <sys/wait.h>

void  ClientProcess(int []);


void deposit(int* bankAccount);


void withdraw(int* bankAccount);


int  main(int  argc, char *argv[])
{
     int    ShmID;
     int    *ShmPTR;
     pid_t  pid;
     int    status;
     int fd ,i , nloop=5,zero=0,*counter_ptr;
     sem_t *mutex; 
  
  fd = open("log.txt",O_RDWR|O_CREAT,S_IRWXU);
  write(fd,&zero,sizeof(int));
  counter_ptr = mmap(NULL,sizeof(int),PROT_READ |PROT_WRITE,MAP_SHARED,fd,0);
  close(fd);

 if ((mutex = sem_open("examplesaaaebbmaphore", O_CREAT, 0644, 1)) == SEM_FAILED) {
    perror("semaphore initilization");
    exit(1);
  }
  
    pid = fork();
    if (pid > 0) {
        for (i = 0; i>-1; i++){
            sleep(rand()%6);
            printf("Dear Old Dad: Attempting to Check Balance\n");\
            sem_wait(mutex);
            int rnum = rand()%101;
            if (rnum % 2 == 0){
              if (*counter_ptr<100){
                depositMoney(counter_ptr);
              } else {
                printf("Dear old Dad: Thinks Student has enough Cash ($%d)\n", *counter_ptr);
              }
            }else{
              printf("Dear Old Dad: Last Checking Balance = $%d\n", *counter_ptr);
            }
            sem_post(mutex);              
        }
        
        exit(1);
    }
    else if (pid == 0) {
        for (i = 0; i>-1; i++){
            sleep(rand()%6);
            printf("Poor Student: Attempting to Check Balance\n");  
            sem_wait(mutex);
            int rnum = rand();
            if (rnum%2 == 0){
              withdrawMoney(counter_ptr);
            }else{
              printf("Poor Student: Last Checking Balance = $%d\n", *counter_ptr);
            }
            sem_post(mutex);
            
        }
        printf("   Client is about to exit\n");
        exit(0);
    }

    wait(&status);
    printf("Server has detected the completion of its child...\n");
    printf("Server has detached its shared memory...\n");
    printf("Server has removed its shared memory...\n");
    printf("Server exits...\n");
    exit(0);
}


void depositMoney(int* bankAccount){
  int bal= *bankAccount;
  int amount = rand() % 101;
  if (amount%2 == 0){
    bal+= amount;
    printf("Dear old Dad: Deposits $%d / Balance = $%d\n", amount, bal);
    *bankAccount= bal;
  }
  else{
    printf("Dear old Dad: Doesn't have any money to give\n");
  }
}

void withdrawMoney(int* bankAccount){
  int bal = *bankAccount;
  int need = rand() % 51;
  printf("Poor Student needs $%d\n", need);
  if (need <= bal){
    bal-=need;
    printf("Poor Student: Withdraws $%d / Balance = $%d\n", need, bal);
    *bankAccount = bal;
  }else{
    ("Poor Student: Not Enough Cash ($%d)\n", bal);
  }

void  ClientProcess(int []);