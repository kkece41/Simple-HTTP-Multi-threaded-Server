#include <stdlib.h>
#include "MyQueue.h"

Node *front = NULL;
Node *tail = NULL;

void Enqueue(int *conn_fd)
{
    Node *newnode = malloc(sizeof(Node));
    newnode->conn_fd = conn_fd;
    newnode->next = NULL;

    if (tail == NULL)
    {
        front = newnode;
    }

    else
    {
        tail->next = newnode;
    }

    tail = newnode;
}

int *Dequeue()
{
    if (front == NULL)
        return NULL;

    else
    {
        //int* con_res = malloc(sizeof(int));
        int *con_res = front->conn_fd;
        Node *temp = front;
        front = front->next;

        if (front == NULL)
        {
            tail = NULL;
        }
        free(temp);

        return con_res;
    }
}