#!/bin/bash 

#Esto ejecuta el valgrind con todos estas cosas sobre el programa pasado por el primer parametro

echo $2

exec valgrind --tool=memcheck --leak-check=yes --show-reachable=yes --num-callers=20 --track-fds=yes --log-file-exactly=valgrind $1 "$2"
