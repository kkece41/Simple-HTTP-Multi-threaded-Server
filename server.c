#include <stdio.h>
#include "request.h"
#include "io_helper.h"
#include "MyQueue.h"

#define THREAD_POOL_SIZE 25

pthread_t thread_pool[THREAD_POOL_SIZE];

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void* get_conn_fd(void *arg)
{
    while(1)
    {
        pthread_mutex_lock(&mutex);
        int *conn_fd = Dequeue();
        pthread_mutex_unlock(&mutex);
        if(conn_fd != NULL)
        {
            request_handle(conn_fd);
        }
    }
}

char default_root[] = ".";  // Single dot (.)-->present directory. //double dot (..)-->parent directory


// ../wserver [-d basedir] [-p port] [-t threads] [-b buffers] [-s schedalg] 
// schedalg---> Scheduling Algorithm
int main(int argc, char *argv[])
{
    log_info("Starting main()");
    int c;
    char *root_dir = default_root;
    int port = 10000;
    
    for(int i=0; i<THREAD_POOL_SIZE; i++)
    {
        pthread_create(&thread_pool[i], NULL, get_conn_fd, NULL);
    }

    log_info("Created a thread pool");

    while ((c = getopt(argc, argv, "d:p:")) != -1)
        switch (c)
        {
        case 'd':
            root_dir = optarg; //optarg-->Argument of options. Here it contains root directory string
            log_info("Getting root directory");
            break;

        case 'p':
            port = atoi(optarg);  //atoi-->converts string to integer
            log_info("Getting port number");

            break;

        default:
            fprintf(stderr, "usage: wserver [-d basedir] [-p port]\n");
            exit(1);
        }

    // change directory
    chdir_or_die(root_dir);
    log_info("Changed root directory");


    // now, get to work
    int listen_fd = open_listen_fd_or_die(port);
    while (1)
    {
        struct sockaddr_in client_addr;
        int client_len = sizeof(client_addr);
        int conn_fd = accept_or_die(listen_fd, (sockaddr_t *)&client_addr, (socklen_t *)&client_len);
        //request_handle((void*)&conn_fd);  // Enable for sequential execution of clients, without threads
        
        int* pclient = malloc(sizeof(int));
        *pclient = conn_fd;

        pthread_mutex_lock(&mutex);  // Synchronising the access of queeue.
        Enqueue(pclient);
        pthread_mutex_unlock(&mutex);

      
        //pthread_t ptr;
        //pthread_create(&ptr, NULL, request_handle,(void*)&conn_fd); // Creating a thread for every new connection

        //close_or_die(conn_fd);
    }
    return 0;
}