cmake_minimum_required(VERSION 3.28)
project(QrcodetTest)

set(CMAKE_CXX_STANDARD 11)

add_executable(QrcodetTest main.cpp qrcodegen.c
        stb-master/stb_vorbis.c
        GenerateQrCode.cpp
        GenerateQrCode.h)
add_library(qrCodeGenerater   qrcodegen.c
        stb-master/stb_vorbis.c
        GenerateQrCode.cpp
        GenerateQrCode.h

)
