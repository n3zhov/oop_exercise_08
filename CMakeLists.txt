cmake_minimum_required(VERSION 3.17)
project(oop_exercise_08)

set(CMAKE_CXX_STANDARD 17)

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

add_executable(oop_exercise_08 main.cpp trapeze.hpp rhomb.hpp pentagon.hpp figure.hpp factory.hpp pub_sub.hpp)
target_link_libraries(oop_exercise_08 PRIVATE Threads::Threads)