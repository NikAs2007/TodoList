cmake_minimum_required(VERSION 3.10)
project(TodoList)

#if(NOT CMAKE_BUILD_TYPE) #Задаем принудительную релиз сборку
set(CMAKE_BUILD_TYPE Release)
#endif()

add_executable(TodoList AppForTasks.cpp TodoList.cpp)

target_include_directories(TodoList PUBLIC .)