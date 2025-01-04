//
// Created by kurum on 2024/10/26.
//

#include "GenerateQrCode.h"
//#define STB_IMAGE_WRITE_IMPLEMENTATION  // 这行需要在包含 stb_image_write.h 之前
#include "stb-master/stb_image_write.h"            // 确保这个文件已经被包含在项目中

#include <vector>
#include <iostream>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "qrcodegen.h"
void writePng(const std::vector<std::vector<int>>& matrix, const char *filename,int sca);
static void printQr(const uint8_t qrcode[],std::string fileName,int sca=2) {
    int size = qrcodegen_getSize(qrcode);
    int border = 4;
    std::vector<std::vector<int>> matrix;
    for (int y = -border; y < size + border; y++) {
        std::vector<int> line;
        for (int x = -border; x < size + border; x++) {
            // fputs((qrcodegen_getModule(qrcode, x, y) ? "##" : "  "), stdout);

            line.push_back((qrcodegen_getModule(qrcode, x, y) ? 1 : 0));
            //  line.push_back((qrcodegen_getModule(qrcode, x, y) ? 1 : 0));



        }
        // printf_s("line size :%d \n",line.size());
        //fputs("\n", stdout);
        matrix.push_back(line);


    }
    // fputs("\n", stdout);
    writePng(matrix,fileName.c_str(),sca);
}
void writePng(const std::vector<std::vector<int>>& matrix, const char *filename, int fixedSize = 200) {
    int size = matrix.size();
    int border = 4;
    // Calculate the scale factor based on the fixed output size and the QR code's size with borders.
    int qrSizeWithBorder = size + border * 2;
    double scaleFactor = (double)fixedSize / qrSizeWithBorder;
    int scaledSize = fixedSize;

    // 创建放大后的图像数据
    std::vector<unsigned char> image(scaledSize * scaledSize * 3, 255);  // 初始化全白背景

    for (int y = 0; y < size; y++) {
        for (int x = 0; x < size; x++) {
            if (matrix[y][x] == 1) {  // 如果是黑色像素
                // Scale each module to fit into the fixed size image.
                for (double sy = 0; sy < scaleFactor; sy++) {
                    for (double sx = 0; sx < scaleFactor; sx++) {
                        // Add the border offset in the scaled coordinates.
                        int scaledY = (y + border) * scaleFactor + sy;
                        int scaledX = (x + border) * scaleFactor + sx;
                        // Make sure we are within bounds.
                        if (scaledY < scaledSize && scaledX < scaledSize) {
                            image[(int)(scaledY * scaledSize + scaledX) * 3] = 0;  // R
                            image[(int)(scaledY * scaledSize + scaledX) * 3 + 1] = 0;  // G
                            image[(int)(scaledY * scaledSize + scaledX) * 3 + 2] = 0;  // B
                        }
                    }
                }
            }
        }
    }

    // 写入PNG文件
    if (!stbi_write_png(filename, scaledSize, scaledSize, 3, image.data(), 0)) {
        std::cerr << "Failed to write PNG file." << std::endl;
    } else {
        std::cout << "PNG file written successfully: " << filename << std::endl;
    }
}

std::string generateQrCode(std::string textPara,std::string outPath,int sca)
{
    const char *text =textPara.c_str();
    enum qrcodegen_Ecc errCorLvl = qrcodegen_Ecc_LOW;  // Error correction level

    // Make and print the QR Code symbol
    uint8_t qrcode[qrcodegen_BUFFER_LEN_MAX];
    uint8_t tempBuffer[qrcodegen_BUFFER_LEN_MAX];
    bool ok = qrcodegen_encodeText(text, tempBuffer, qrcode, errCorLvl,
                                   qrcodegen_VERSION_MIN, qrcodegen_VERSION_MAX, qrcodegen_Mask_AUTO, true);
    if (ok)
    {
        printQr(qrcode,outPath,sca);
        return outPath;
    }

    else
    {
        printf_s("too big\n");
        return "failed";
    }


}
