cmake_minimum_required(VERSION 3.9)
project(Collatz C)

set(CMAKE_C_STANDARD 99)

add_executable(Collatz Collatz-Producer.c Collatz-Consumer.c)