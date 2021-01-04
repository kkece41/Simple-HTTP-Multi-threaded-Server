# Simple-HTTP-Multi-threaded-Server
A Simple server, that can handle multiple clients.

We created a master thread (Producer), then it created an thread pool with THREAD_POOL_SIZE number of threads (Consumer). Master thread is responsible for accepting new http connections over the network and placing the descriptor for this connection into a queue. Consumers, take the  descriptor from the queue, and then calls the handleconnection function.

1) We can use simple python script to open browser to access a server. For this, use the client.py code, and enable the corresponding code in the bash script.

2) You can use the client.c, to create a client binary and run it with bash script. 
