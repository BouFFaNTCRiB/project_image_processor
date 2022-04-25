#pragma once

#include "image.h"
#include <vector>
#include <string_view>

class BaseFilter {
public:
    virtual void Apply(Image &image, std::vector<std::size_t> params) const = 0;
    virtual ~BaseFilter() = default;
};

class CropFilter : public BaseFilter {
public:
    void Apply(Image &image, std::vector<std::size_t> params) const override;
};

class GrayScaleFilter : public BaseFilter {
public:
    void Apply(Image &image, std::vector<std::size_t> params) const override;
};

class NegativeFilter : public BaseFilter {
public:
    void Apply(Image &image, std::vector<std::size_t> params) const override;
};

class SharpFilter : public BaseFilter {
public:
    void Apply(Image &image, std::vector<std::size_t> params) const override;
};

class EdgeFilter : public BaseFilter {
public:
    void Apply(Image &image, std::vector<std::size_t> params) const override;
};

class BlurFilter : public BaseFilter {
public:
    void Apply(Image &image, std::vector<std::size_t> params) const override;
    double GaussFunction(int32_t x, int32_t y, int sigma) const;
};

class DistortionFilter : public BaseFilter {
public:
    void Apply(Image &image, std::vector<std::size_t> params) const override;

};
