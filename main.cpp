#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <pthread.h>
#include <sstream>
#define PERMS S_IWUSR|S_IRUSR

using namespace std;


stringstream ss;
const int ITERATION = 20;
const int BUFFSIZE = 4;
const int NUM_THREADS = 10;
pthread_mutex_t mut = PTHREAD_MUTEX_INITIALIZER;

int shmid= shmget(IPC_PRIVATE, BUFFSIZE*sizeof(char), PERMS);
//char shmBUF = new float[BUFFSIZE];
float *shmBUF = (float *)shmat(shmid, 0, SHM_RND);
void *process_one( void *);

int main(){
    pthread_t threads[NUM_THREADS];

    //shmid = shmget(IPC_PRIVATE, BUFFSIZE*sizeof(char), EPERM);
    //shmBUF = (char *)shmat(shmid, 0, SHM_RND);

    for (int j = 0; j< BUFFSIZE;j++){
        //char *temp = shmBUF;
        shmBUF[j]= 3;
    }


    for( int i = 0; i < NUM_THREADS; i++ ) {
        cout << "main() : creating thread, " << i << endl;
        int rc = pthread_create(&threads[i], NULL, process_one,(void *)i);
        pthread_join(threads[i], NULL);

        if (rc) {
            cout << "Error:unable to create thread," << rc << endl;
            exit(-1);
        }
    }

    shmdt(shmBUF);
    pthread_mutex_destroy(&mut);
    exit(0);
} // main

void *process_one( void *i) {

    //srand(time(NULL));
    for(int k=0; k<ITERATION; k++){
        float beta = (float)rand()/RAND_MAX - 0.5;
        cout<<"Beta: "<<beta<<endl;
        int ind = rand()%BUFFSIZE;
        pthread_mutex_lock (&mut);
        //char *temp_point = shmBUF;
        float temp = shmBUF[ind];
        cout<<"Before adding into "<< ind <<": "<<shmBUF[ind]<<endl;
        shmBUF[ind] = temp + beta;
        cout<<"temp + beta: "<<temp + beta<<endl;
        cout<<"After adding: "<<shmBUF[ind]<<endl;
        cout<<"Process "<<i<<" result at variable "<< ind<<": "<<shmBUF[ind]<<endl;
				cout<<endl;
				pthread_mutex_unlock (&mut);
    }
    pthread_exit(NULL);
} // parent_proc
