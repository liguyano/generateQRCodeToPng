#define STB_IMAGE_WRITE_IMPLEMENTATION  // 这行需要在包含 stb_image_write.h 之前
#include "stb-master/stb_image_write.h"            // 确保这个文件已经被包含在项目中

#include <vector>
#include <iostream>
#include <stdio.h>
#include "GenerateQrCode.h"

int main() {
    generateQrCode("http://www.baidu.com","./a.png",134);
    return 0;
}