#include<stdio.h>
#include<unistd.h>
#include<pthread.h>
#include<semaphore.h>
#include<stdlib.h>
sem_t l;
int rrp[20];//to store resourse required by each process
void* (*f[20])(void *);//function pointer array to store functions of each process 
int P;//no of resourses
int Q;//no of processes
int check=0;//to check allocated resourses
int count=0;//to count process no.
void* fun(void* i)//function body
{
  count++;//to increase running process no
   check+=(int)i;//to add the total resource required
  while(check>20);//to check the total resourses
  sem_wait(&l);//semaphore waiting
  printf("Process %d is Executecd\n",count);
  sleep(10);
  sem_post(&l);//unlock semaphore
  check-=(int)i;//descrease resorses required
}
int main()
{
 int flag1=1;//User Input.
 while(flag1)
 {
 printf("Enter no of Resourses.\n");
 scanf("%d",&P);
 printf("Enter no Processes.\n");
 scanf("%d",&Q);
 if(P<=0||Q<=0||Q>=20)
 {
 printf("Enetr valid values.\n Try Again.");
 }
 else
 flag1=0;
 }
 int sum=0;
 for(int i=0;i<Q;i++)
 {
   printf("Enetr the No. of Resourses. For process %d\n",i+1);
   scanf("%d",&rrp[i]);
   }
 int flag=0;
 for(int i=0;i<Q;i++)//checking of resourses required.
  {
   if(rrp[i]<=0||rrp[i]>=P)
   {
   printf("Process %d requires invalid no of Resourses. \n",i+1);
   flag=1;
   }
   else
   sum+=rrp[i];
  }
 if(flag==1)
  return 0;
 if(sum>P+Q)
  {
    printf("Maximum Resourses needed is greater than P+Q.\n");
    return 0;
    }
 sem_init(&l,0,P);//initializing resourses
 pthread_t t[20];
 for(int i=0;i<Q;i++)
 f[i]=fun;//initializing each process funtion
 for(int i=0;i<Q;i++)
 pthread_create(&t[i],NULL,f[i],(void*)rrp[i]);//creating threads
 for(int i=0;i<Q;i++)//joining threads
 pthread_join(t[i],NULL);
 return 0;
}
