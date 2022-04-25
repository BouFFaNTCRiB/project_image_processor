#include "filter_factory.h"

BaseFilter* FilterFactory::CreateFilter(const std::string_view filter_name) const {
    if (filter_name == "crop") {
        return new CropFilter;
    } else if (filter_name == "blur") {
        return new BlurFilter;
    } else if (filter_name == "gs") {
        return new GrayScaleFilter;
    } else if (filter_name == "neg") {
        return new NegativeFilter;
    } else if (filter_name == "sharp") {
        return new SharpFilter;
    } else if (filter_name == "edge") {
        return new EdgeFilter;
    } else if (filter_name == "distortion") {
        return new DistortionFilter;
    }
    return nullptr;
}
