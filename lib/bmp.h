#include <cstdint>
#include "vector.h"
#include <fstream>


class BMP {
public:
    BMP(uint32_t width, uint32_t height, vector<vector<int>>& field);
    ~BMP();
    void MakeFile(const std::string& path);
    uint32_t WhatColor(uint32_t amogus);
private:
    uint32_t width;
    uint32_t height;
    vector<vector<int>> field;
    uint8_t header[14];
    uint8_t info[40];
    uint32_t colors[16] = {
            0x00fadbc8,
            0x003caa3c,
            0x00f4c430,
            0x009966cc,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000,
            0x00000000
    };
};
