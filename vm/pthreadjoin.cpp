#include <pthread.h>
#include <unistd.h>
#include <stdio.h>
struct args{
  char name[10];
  int exit_code;
};

void * thread_run(void *arg){
  struct args* a = (struct args*)arg;
  printf("%s run, id:%p\n", a->name, (pthread_self())); // use arg to get the params;
  if(a->exit_code % 2){
    sleep(a->exit_code); // make the thread sleep some second;
    printf("im thread %d, here sleep %d second!\n", a->exit_code, a->exit_code);
  }
  pthread_exit((void*)(&(a->exit_code)));
}

int main(){
  pthread_t tid[10];  //thread_ids
  struct args a[10];  //thread_function's args
  void *ec;           //exit code
  int i;
  for(i = 0; i < 10; ++i){
    a[i].name[0] = '\0';
    sprintf(a[i].name, "thread_%d", i);
    a[i].exit_code = i;
    if(pthread_create(&tid[i], NULL, thread_run, (void *)(&a[i]))){ //call pthread_create to create a thread use arg[i]
      printf("error");
      return 0;
    }
  }
  for(i = 0; i < 10; ++i){
    pthread_join(tid[i], &ec);//wait for thread tid[i] stop;
    printf("[%p] %s exit code is:%d\n", tid[i], a[i].name, (*(int*)ec));
  }
  return 0;
}
