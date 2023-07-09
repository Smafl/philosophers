cmake_minimum_required(VERSION 3.25)
project(philo C)

set(CMAKE_C_STANDARD 99)

add_executable(philo philo.c init.c parse_input.c utils.c)
