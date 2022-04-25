#include <vector>
#pragma once

struct Pixel
{
    unsigned char r,g,b;
};

class Image
{
private:
    std::size_t width_, height_;
    std::vector<std::vector<Pixel>> pixels_;
public:
    Image();
    Pixel GetPixel(std::size_t x, std::size_t y) const;
    void SetPixel(const Pixel& pixel, std::size_t x, std::size_t y);
    void ResizeImage(size_t height, size_t width);
    std::size_t GetWidth();
    std::size_t GetHeight();
    std::vector<std::vector<Pixel>> GetPixelsCopy();
    std::vector<std::vector<Pixel>>& GetPixels();
    void SetHeight(std::size_t height);
    void SetWidth(std::size_t width);
};
