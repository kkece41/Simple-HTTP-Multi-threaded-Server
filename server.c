#include <stdio.h>
#include "request.h"
#include "io_helper.h"


char default_root[] = ".";  // Single dot (.)-->present directory. //double dot (..)-->parent directory


// ../wserver [-d basedir] [-p port] [-t threads] [-b buffers] [-s schedalg] 
// schedalg---> Scheduling Algorithm
int main(int argc, char *argv[])
{
    int c;
    char *root_dir = default_root;
    int port = 10000;

    log_info("Starting main(), going into loop");

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
        request_handle(conn_fd);
        close_or_die(conn_fd);
    }
    return 0;
}