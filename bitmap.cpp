#include "bitmap.h"
#include <fstream>

bool Bitmap::Load(std::string_view file_name) {
    std::fstream file;
    file.open(file_name.data(), std::ios_base::in | std::ios_base::binary);
    if (!file.is_open()) {
        return false;
    }
    Load(file);
    return true;
}

bool Bitmap::Load(std::istream& stream) {
    stream.read(reinterpret_cast<char*> (&bmp_header_), sizeof(bmp_header_));
    stream.read(reinterpret_cast<char*> (&dib_header_), sizeof(dib_header_));
    if (dib_header_.dib_header_size != 40) {
        throw std::invalid_argument("Incorrect DIB header size");
    }
    if (bmp_header_.signature != BMP_FORMAT) {
        throw std::invalid_argument("Unrecognized file format");
    }
    image_.SetHeight(dib_header_.height);
    image_.SetWidth(dib_header_.width);
    image_.GetPixels().resize(dib_header_.height, std::vector<Pixel>(dib_header_.width));
    const int padding = ((4 - (dib_header_.width * 3) % 4) % 4);
    for (std::size_t i = 0; i < dib_header_.height; ++i) {
        for (std::size_t j = 0; j < dib_header_.width; ++j) {
            Pixel cur_pixel;
            stream.read(reinterpret_cast<char*> (&cur_pixel.b), 1);
            stream.read(reinterpret_cast<char*> (&cur_pixel.g), 1);
            stream.read(reinterpret_cast<char*> (&cur_pixel.r), 1);
            image_.SetPixel(cur_pixel,i, j);
        }
        stream.ignore(padding);
    }
    return true;
}

std::ofstream& Bitmap::CreateFile(std::string_view file_name) const {
    static std::ofstream file;
    file.open(file_name.data(), std::ios_base::out | std::ios_base::binary);
    return file;
}

bool Bitmap::CreateFile(std::ofstream& stream) {
    dib_header_.width = image_.GetWidth();
    dib_header_.height = image_.GetHeight();
    const std::size_t bufferfour = 4;
    const int padding = ((bufferfour - (dib_header_.width * 3) % bufferfour) % bufferfour);
    stream.write(reinterpret_cast<char*> (&bmp_header_), sizeof(bmp_header_));
    stream.write(reinterpret_cast<char*> (&dib_header_), sizeof(dib_header_));
    for (std::size_t i = 0; i < dib_header_.height; ++i) {
        for (std::size_t j = 0; j < dib_header_.width; ++j) {
            unsigned char r = image_.GetPixel(i, j).r;
            unsigned char g = image_.GetPixel(i, j).g;
            unsigned char b = image_.GetPixel(i, j).b;
            unsigned char color[] = {b, g, r};
            stream.write(reinterpret_cast<char*>(color), 3);
        }
        unsigned char bmp_pad[3] = {0, 0, 0};
        stream.write(reinterpret_cast<char*>(bmp_pad), padding);
    }
    return true;
}

Image& Bitmap::GetImage() {
    return image_;
}
