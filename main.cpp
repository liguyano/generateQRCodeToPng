#define STB_IMAGE_WRITE_IMPLEMENTATION  // 这行需要在包含 stb_image_write.h 之前
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
static void printQr(const uint8_t qrcode[]) {
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
    writePng(matrix,"b.png",3);
}
void writePng(const std::vector<std::vector<int>>& matrix, const char *filename,int sca) {
    int size = matrix.size();
    int scale = sca*sca;  // 每个点放大为4个像素
    int scaledSize = size * scale;

    // 创建放大后的图像数据
    std::vector<unsigned char> image(scaledSize * scaledSize * 3, 255);  // 初始化全白背景

    for (int y = 0; y < size; y++) {
        for (int x = 0; x < size; x++) {
            if (matrix[y][x] == 1) {  // 如果是黑色像素
                for (int sy = 0; sy < scale; sy++) {
                    for (int sx = 0; sx < scale; sx++) {
                        int scaledY = y * scale + sy;
                        int scaledX = x * scale + sx;
                        image[(scaledY * scaledSize + scaledX) * 3] = 0;  // R
                        image[(scaledY * scaledSize + scaledX) * 3 + 1] = 0;  // G
                        image[(scaledY * scaledSize + scaledX) * 3 + 2] = 0;  // B
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
static void doBasicDemo(void) {
    const char *text = "http://121.36.15.48:8080/tango/";                // User-supplied text
    enum qrcodegen_Ecc errCorLvl = qrcodegen_Ecc_LOW;  // Error correction level

    // Make and print the QR Code symbol
    uint8_t qrcode[qrcodegen_BUFFER_LEN_MAX];
    uint8_t tempBuffer[qrcodegen_BUFFER_LEN_MAX];
    bool ok = qrcodegen_encodeText(text, tempBuffer, qrcode, errCorLvl,
                                   qrcodegen_VERSION_MIN, qrcodegen_VERSION_MAX, qrcodegen_Mask_AUTO, true);
    if (ok)
        printQr(qrcode);

}

int main() {
    doBasicDemo();
    return 0;
}