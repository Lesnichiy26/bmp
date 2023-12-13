#include "bmp.h"

uint32_t BMP::WhatColor(uint32_t amogus) {
    if (amogus > 3) {
        return 4;
    }
    return amogus;
}


BMP::BMP(uint32_t width, uint32_t height, vector<vector<int>>& field) :
        width(width),
        height(height),
        field(field){}

BMP::~BMP() = default;

void BMP::MakeFile(const std::string& path) {

    std::ofstream bmp;
    bmp.open(path, std::ios::out | std::ios::binary);
    if (!bmp.is_open()) {
        std::cerr << "NO";
        exit(EXIT_FAILURE);
    }

    int row = width / 2 + width % 2;
    int padding = (4 - (row % 4)) % 4;

    const int COLORSSIZE = sizeof(colors);
    const int HEADERSIZE = sizeof(header);
    const int INFOSIZE = sizeof(info);
    const int OFFSET = COLORSSIZE + HEADERSIZE + INFOSIZE;
    const int TOTAL = (row + padding) * height;
    const int IMAGESIZE = COLORSSIZE + HEADERSIZE + INFOSIZE + TOTAL;

    // type
    header[0] = 'B';
    header[1] = 'M';
    // HEADERSIZE
    header[2] = HEADERSIZE;
    header[3] = HEADERSIZE >> 8;
    header[4] = HEADERSIZE >> 16;
    header[5] = HEADERSIZE >> 24;
    // reserv0
    header[6] = 0;
    header[7] = 0;
    // reserv1
    header[8] = 0;
    header[9] = 0;
    // offset
    header[10] = OFFSET;
    header[11] = OFFSET >> 8;
    header[12] = OFFSET >> 16;
    header[13] = OFFSET >> 24;
    // INFOSIZE
    info[0] = INFOSIZE;
    info[1] = INFOSIZE >> 8;
    info[2] = INFOSIZE >> 16;
    info[3] = INFOSIZE >> 24;
    // width
    info[4] = width;
    info[5] = width >> 8;
    info[6] = width >> 16;
    info[7] = width >> 24;
    // height
    info[8] = height;
    info[9] = height >> 8;
    info[10] = height >> 16;
    info[11] = height >> 24;
    // planes
    info[12] = 1;
    info[13] = 0;
    // bits per pixel
    info[14] = 4;
    info[15] = 0;
    // compression
    info[16] = 0;
    info[17] = 0;
    info[18] = 0;
    info[19] = 0;
    // image size
    info[20] = IMAGESIZE;
    info[21] = IMAGESIZE >> 8;
    info[22] = IMAGESIZE >> 16;
    info[23] = IMAGESIZE >> 24;
    // x pixels per meter
    info[24] = 0;
    info[25] = 0;
    info[26] = 0;
    info[27] = 0;
    // y pixels per meter
    info[28] = 0;
    info[29] = 0;
    info[30] = 0;
    info[31] = 0;
    // total colors
    info[32] = 16;
    info[33] = 0;
    info[34] = 0;
    info[35] = 0;
    // important colors
    info[36] = 5;
    info[37] = 0;
    info[38] = 0;
    info[39] = 0;

    bmp.write(reinterpret_cast<char *>(header), HEADERSIZE);
    bmp.write(reinterpret_cast<char *>(info), INFOSIZE);
    bmp.write(reinterpret_cast<char *>(colors), COLORSSIZE);

    uint8_t *pixels = new uint8_t[TOTAL];
    uint8_t *pixel = pixels;

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x += 2) {
            int current1 = field[y][x];
            int current2 = 0;
            if (x + 1 < width) {
                current2 = field[y][x + 1];
            }
            uint32_t color1 = WhatColor(current1);
            uint32_t color2 = WhatColor(current2);
            *pixel = static_cast<uint8_t>((color1 << 4) | color2);
            pixel++;
        }
        pixel += padding;
    }

    bmp.write(reinterpret_cast<char *>(pixels), TOTAL);
    
    delete[] pixels;
}