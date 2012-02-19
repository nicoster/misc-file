 #include <pthread.h>
 #include <stdio.h>
 #include <unistd.h>
 #include <sys/errno.h>
 
 void printids(const char* s){
   pid_t pid;
   pthread_t tid;
 
   pid = getpid();
   tid = pthread_self();
   printf("%s   pid:%d tid:%p\n", s, pid, tid);
 }
 
 
 void* pthread_run(void *arg){
   printids("new thread");
   return ((void *)0);
 }
 int main(){
 
   pthread_t tid;
   if(pthread_create(&tid, NULL, pthread_run, NULL)){
     printf("error");
     return 0;
   }
	printf("ESRCH:%d, EINVAL:%d, EINTR:%d\n", ESRCH, EINVAL, EINTR);
	int rc = pthread_kill(tid, 0);
	printf("kill:%d\n", rc);
   sleep(1);
	rc = pthread_kill(tid, 0);
	printf("kill:%d\n", rc);
   printids("main thread");
   return 0;
 }
