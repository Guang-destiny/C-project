cmake_minimum_required(VERSION 3.20)
 #我的文件名是WEEK1
 project(PROJECT)
 #添加文件目录
include_directories(./include ./src)
 #生成对应名称的文件
add_executable( yestodo  ./src/main.cpp ./src/map.cpp ./src/character.cpp)