#include "base_filters.h"
#include <cstdint>
#include <cmath>
#include <ctime>



void CropFilter::Apply(Image &image, std::vector<std::size_t> params) const {
    size_t a = params[0];
    size_t b = params[1];
    image.SetWidth(std::min(a, image.GetWidth()));
    image.SetHeight(std::min(b, image.GetWidth()));
    for (std::size_t i = 0; i < image.GetHeight(); ++i) {
        image.GetPixels().resize(image.GetWidth());
    }
    image.GetPixels().resize(image.GetHeight());
}

void GrayScaleFilter::Apply(Image &image, std::vector<std::size_t> params) const {
    for (std::size_t i = 0; i < image.GetHeight(); ++i) {
        for (std::size_t j = 0; j < image.GetWidth(); ++j) {
            Pixel cur_pixel = image.GetPixel(i, j);
            unsigned char r = cur_pixel.r, g = cur_pixel.g, b = cur_pixel.b;
            cur_pixel.r = static_cast<unsigned char>(0.299 * static_cast<double>(r) + 0.587 * static_cast<double>(g) +
                                                     0.144 * static_cast<double>(b));
            cur_pixel.g = static_cast<unsigned char>(0.299 * static_cast<double>(r) + 0.587 * static_cast<double>(g) +
                                                     0.144 * static_cast<double>(b));
            cur_pixel.b = static_cast<unsigned char>(0.299 * static_cast<double>(r) + 0.587 * static_cast<double>(g) +
                                                     0.144 * static_cast<double>(b));
            image.SetPixel(cur_pixel, i, j);
        }
    }
}

void NegativeFilter::Apply(Image &image, std::vector<std::size_t> params) const {
    for (std::size_t i = 0; i < image.GetHeight(); ++i) {
        for (std::size_t j = 0; j < image.GetWidth(); ++j) {
            Pixel cur_pixel = image.GetPixel(i, j);
            unsigned char r = 255 - cur_pixel.r, g = 255 - cur_pixel.g, b = 255 - cur_pixel.b;
            cur_pixel.r = r;
            cur_pixel.g = g;
            cur_pixel.b = b;
            image.SetPixel(cur_pixel, i, j);
        }
    }
}

void SharpFilter::Apply(Image &image, std::vector<std::size_t> params) const {
    Image copy_image = image;
    for (std::int32_t i = 0; i < image.GetHeight(); ++i) {
        for (std::int32_t j = 0; j < image.GetWidth(); ++j) {
             Pixel cur_pixel;
             cur_pixel.r = (std::min(255, std::max(0, (
                    - (copy_image.GetPixels()[i][std::max(j - 1, 0)].r)
                    - (copy_image.GetPixels()[std::max(i - 1, 0)][j].r)
                    + (5 * copy_image.GetPixels()[i][j].r)
                    - (copy_image.GetPixels()[std::min(i + 1, static_cast<int32_t>(image.GetHeight()) - 1)][j].r)
                    - (copy_image.GetPixels()[i][std::min(j + 1, static_cast<int32_t>(image.GetWidth()) - 1)].r)))));
            cur_pixel.g = (std::min(255, std::max(0, (
                    - (copy_image.GetPixels()[i][std::max(j - 1, 0)].g)
                    - (copy_image.GetPixels()[std::max(i - 1, 0)][j].g)
                    + (5 * copy_image.GetPixels()[i][j].g)
                      - (copy_image.GetPixels()[std::min(i + 1, static_cast<int32_t>(image.GetHeight()) - 1)][j].g)
                      - (copy_image.GetPixels()[i][std::min(j + 1, static_cast<int32_t>(image.GetWidth()) - 1)].g)))));
            cur_pixel.b = (std::min(255, std::max(0, (
                    - (copy_image.GetPixels()[i][std::max(j - 1, 0)].b)
                    - (copy_image.GetPixels()[std::max(i - 1, 0)][j].b)
                    + (5 * copy_image.GetPixels()[i][j].b)
                    - (copy_image.GetPixels()[std::min(i + 1, static_cast<int32_t>(image.GetHeight()) - 1)][j].b)
                    - (copy_image.GetPixels()[i][std::min(j + 1, static_cast<int32_t>(image.GetWidth()) - 1)].b)))));

            image.SetPixel(cur_pixel, i, j);
        }
    }
}

double BlurFilter::GaussFunction(int32_t x, int32_t y, int sigma) const {
    return pow(M_E, -(pow(x, 2) + pow(y, 2)) / (2 * pow(sigma, 2))) / (2 * M_PI * pow(sigma, 2));
}

void BlurFilter::Apply(Image &image, std::vector<std::size_t> params) const {
    int sigma = params[0];
    int kernel_size = 3 * sigma;
    std::vector<std::vector<double>> kernel_matrix;

    double whole_sum = 0;
    for (int32_t x = -kernel_size; x <= kernel_size; ++x) {
        std::vector<double> tmp;
        for (int32_t y = -kernel_size; y <= kernel_size; ++y) {
            double gauss_func = GaussFunction(x, y, sigma);
            whole_sum += gauss_func;
            tmp.push_back(gauss_func);
        }
        kernel_matrix.push_back(tmp);
    }

    for (int32_t x = -kernel_size; x < kernel_size; ++x) {
        for (int32_t y = kernel_size; y < kernel_size; ++y) {
            kernel_matrix[x + kernel_size][y + kernel_size] /= whole_sum;
        }
    }

    int32_t edge = kernel_matrix.size() / 2;
    std::vector<std::vector<Pixel>> copy_pixels = image.GetPixelsCopy();
    for (size_t i = 0; i < image.GetHeight(); ++i) {
        for (size_t j = 0; j < image.GetWidth(); ++j) {
            double r = 0;
            double g = 0;
            double b = 0;
            for (int32_t delta_x = -edge; delta_x <= edge; ++delta_x) {
                for (int32_t delta_y = -edge; delta_y <= edge; ++delta_y) {
                    int32_t x = j + delta_x;
                    int32_t y = i + delta_y;
                    x = std::min(std::max(x, 0), static_cast<int32_t>(image.GetHeight()) - 1);
                    y = std::min(std::max(y, 0), static_cast<int32_t>(image.GetWidth()) - 1);
                    r += copy_pixels[y][x].r * kernel_matrix[delta_y + edge][delta_x + edge];
                    g += copy_pixels[y][x].g * kernel_matrix[delta_y + edge][delta_x + edge];
                    b += copy_pixels[y][x].b * kernel_matrix[delta_y + edge][delta_x + edge];
                }
            }

            Pixel new_pixel;

            new_pixel.r = std::min(255.0, std::max(0.0, r));
            new_pixel.g = std::min(255.0, std::max(0.0, g));
            new_pixel.b = std::min(255.0, std::max(0.0, b));

            image.SetPixel(new_pixel, i,j);
        }
    }
}

void EdgeFilter::Apply(Image &image, std::vector<std::size_t> params) const {
    Image copy_image = image;
    for (std::int32_t i = 0; i < image.GetHeight(); ++i) {
        for (std::int32_t j = 0; j < image.GetWidth(); ++j) {
            Pixel cur_pixel;
            cur_pixel.r = (std::min(255, std::max(0, (
                    - (copy_image.GetPixels()[i][std::max(j - 1, 0)].r)
                    - (copy_image.GetPixels()[std::max(i - 1, 0)][j].r)
                    + (4 * copy_image.GetPixels()[i][j].r)
                    - (copy_image.GetPixels()[std::min(i + 1, static_cast<int32_t>(image.GetHeight()) - 1)][j].r)
                    - (copy_image.GetPixels()[i][std::min(j + 1, static_cast<int32_t>(image.GetWidth()) - 1)].r)))));
            cur_pixel.g = (std::min(255, std::max(0, (
                    - (copy_image.GetPixels()[i][std::max(j - 1, 0)].g)
                    - (copy_image.GetPixels()[std::max(i - 1, 0)][j].g)
                    + (4 * copy_image.GetPixels()[i][j].g)
                    - (copy_image.GetPixels()[std::min(i + 1, static_cast<int32_t>(image.GetHeight()) - 1)][j].g)
                    - (copy_image.GetPixels()[i][std::min(j + 1, static_cast<int32_t>(image.GetWidth()) - 1)].g)))));
            cur_pixel.b = (std::min(255, std::max(0, (
                    - (copy_image.GetPixels()[i][std::max(j - 1, 0)].b)
                    - (copy_image.GetPixels()[std::max(i - 1, 0)][j].b)
                    + (4 * copy_image.GetPixels()[i][j].b)
                    - (copy_image.GetPixels()[std::min(i + 1, static_cast<int32_t>(image.GetHeight()) - 1)][j].b)
                    - (copy_image.GetPixels()[i][std::min(j + 1, static_cast<int32_t>(image.GetWidth()) - 1)].b)))));

            image.SetPixel(cur_pixel, i, j);
        }
    }
    GrayScaleFilter filter;
    filter.Apply(image, {});
    for (std::int32_t i = 0; i < image.GetHeight(); ++i) {
        for (std::int32_t j = 0; j < image.GetWidth(); ++j) {
            if (image.GetPixels()[i][j].r > params[0]) {
                image.GetPixels()[i][j].r = 255;
                image.GetPixels()[i][j].g = 255;
                image.GetPixels()[i][j].b = 255;
            } else {
                image.GetPixels()[i][j].r = 0;
                image.GetPixels()[i][j].g = 0;
                image.GetPixels()[i][j].b = 0;
            }
        }
    }
}

void DistortionFilter::Apply(Image &image, std::vector<std::size_t> params) const {
    std::srand(std::time(nullptr));
    int param = params[0];
    std::vector<std::vector<Pixel>> copy_pixels = image.GetPixelsCopy();
    for (std::int32_t i = 0; i < image.GetHeight(); ++i) {
        for (std::int32_t j = 0; j < image.GetWidth(); ++j) {
            int r, g, b;
            size_t x = std::max(0, std::min(i + param - rand() % param, int(image.GetHeight() - 1)));
            size_t y = std::max(0, std::min(j + param - rand() % param, int(image.GetWidth() - 1)));
            r = copy_pixels[x][y].r;
            g = copy_pixels[x][y].g;
            b = copy_pixels[x][y].b;
            Pixel new_pixel;
            new_pixel.r = r;
            new_pixel.g = g;
            new_pixel.b = b;
            image.SetPixel(new_pixel, i, j);
        }
    }
}
