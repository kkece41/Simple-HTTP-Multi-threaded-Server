#!/bin/bash

#Use this loop to open 10 browser terminals, without client.c code
# In this case, web browser is the client.
#for N in {1..10}
#do
#    python client.py &
#done


#This loop runs client binary 10 times, so it kind a mimics 10 clients accessing a server.
for N in {1..10}
do
    ./client CEWiT-Latitude-3400 2014 /kk.html
done