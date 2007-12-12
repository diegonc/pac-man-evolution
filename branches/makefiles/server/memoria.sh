#!/bin/bash 

#Esto ejecuta el valgrind con todos estas cosas sobre el programa pasado por el primer parametro

exec valgrind --tool=memcheck --leak-check=yes --show-reachable=yes --num-callers=20 --track-fds=yes $1
