#pragma once

#include <cstdint>
#include <iostream>
#include "image.h"

const uint16_t BMP_FORMAT = 0x4d42;

class Bitmap {

public:
    struct BMPHeader {
        uint16_t signature;
        uint32_t file_size;
        uint32_t cringe;
        uint32_t bitarray_offset;
    } __attribute__((__packed__));

    struct DIBHeader {
        uint32_t dib_header_size;
        uint32_t width;
        uint32_t height;
        uint64_t cringe;
        uint32_t raw_bitmap_data_size;
        uint64_t cringe2;
        uint64_t cringe3;
    } __attribute__((__packed__));

private:
    BMPHeader bmp_header_;
    DIBHeader dib_header_;
    Image image_;

public:
    bool Load(std::istream& stream);

    bool Load(std::string_view file_name);

    std::ofstream& CreateFile(std::string_view file_name) const;

    bool CreateFile(std::ofstream& stream);

    Image& GetImage();
};
