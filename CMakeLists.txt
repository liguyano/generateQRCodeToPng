cmake_minimum_required(VERSION 3.28)
project(QrcodetTest)

set(CMAKE_CXX_STANDARD 17)

add_executable(QrcodetTest main.cpp qrcodegen.c
        stb-master/stb_vorbis.c)
