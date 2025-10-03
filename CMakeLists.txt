cmake_minimum_required(VERSION 3.20)
project(PROJECT)
find_package(SDL2 REQUIRED)
# 手动设置 SDL2_ttf 的头文件和库文件路径
set(SDL2_TTF_INCLUDE_DIRS "/usr/include/SDL2")
set(SDL2_TTF_LIBRARIES "/usr/lib/x86_64-linux-gnu/libSDL2_ttf.so")


#添加文件目录
include_directories(./include ./src  ${SDL2_INCLUDE_DIRS})

 #生成对应名称
add_executable( yestodo  ./src/main.cpp ./src/map.cpp ./src/character.cpp ./src/window.cpp)
target_link_libraries(yestodo ${SDL2_LIBRARIES} ${SDL2_TTF_LIBRARIES})
#cmake -B build
#cmake --build build -j
#./build/yestodo