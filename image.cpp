#include "image.h"


Image::Image() = default;

Pixel Image::GetPixel(std::size_t x, std::size_t y) const{
    return pixels_[x][y];
}

void Image::SetPixel(const Pixel& pixel, std::size_t x, std::size_t y) {
    pixels_[x][y].r = pixel.r;
    pixels_[x][y].g = pixel.g;
    pixels_[x][y].b = pixel.b;
}

std::size_t Image::GetWidth() {
    return width_;
}

std::size_t Image::GetHeight() {
    return height_;
}

std::vector<std::vector<Pixel>> Image::GetPixelsCopy() {
    return pixels_;
}

std::vector<std::vector<Pixel>>& Image::GetPixels() {
    return pixels_;
}

void Image::SetHeight(std::size_t height) {
    height_ = height;
}

void Image::SetWidth(std::size_t width) {
    width_ = width;
}

void Image::ResizeImage(size_t height, size_t width) {
    pixels_.resize(height, std::vector<Pixel>(width));
}
