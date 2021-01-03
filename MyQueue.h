#ifndef MYQUEUE_H
#define MYQUEUE_H

struct node
{
    int *conn_fd;
    struct node* next;
};

typedef struct node Node;

void Enqueue(int* conn_fd);
int* Dequeue();



#endif