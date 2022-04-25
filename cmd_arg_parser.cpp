#include "cmd_arg_parser.h"
#include <iostream>
#include <ctype.h>

bool IsDigitString(std::string_view str) {
    return (std::all_of(str.begin(), str.end(), [](char i){return isdigit(i);}));
}

bool CmdLineParser::Parse(int argc, char* argv[]) {
    if (argc == 1) {
        std::cout << "image processor can apply some filters on your photos \n filters templates are:\n"
                     "-crop {num} {num}\n"
                     "-gs\n"
                     "-blur {num}\n"
                     "-neg\n"
                     "-sharp\n"
                     "-edge {num} \n"
                     "-distortion {num}\n"
                     << std::endl;
        return false;
    }

    if (argc != 0 && argc < MIN_PARAM_NUM) {
        throw std::invalid_argument("wrong argument count");
    }

    input_file_name_ = argv[INPUT_FILE_NAME_POS_];
    output_file_name_ = argv[OUTPUT_FILE_NAME_POS_];
    int i = 3;
    while (i < argc) {
        std::string_view cur = argv[i];
        if (cur == "-crop") {
            if (i + 2 < argc) {
                std::string_view param1 = argv[i + 1];
                std::string_view param2 = argv[i + 2];
                if (!IsDigitString(param1)) {
                    throw std::invalid_argument("wrong arguments to filter -crop: not int");
                }
                if (!IsDigitString(param2)) {
                    throw std::invalid_argument("wrong arguments to filter -crop: not int");
                }

                FilterDescriptor parsed_filter_data;
                parsed_filter_data.filter_name = "crop";
                parsed_filter_data.filter_params = {(std::size_t)std::stoi(param1.data()), (std::size_t)std::stoi(param2.data())};
                filters_.push_back(parsed_filter_data);
                i += 2;
            } else {
                throw std::invalid_argument("wrong arguments to filter -crop");
            }
        } else if (cur == "-blur") {
            if (i + 1 <= argc) {
                std::string_view param1 = argv[i + 1];
                if (!IsDigitString(param1)) {
                    throw std::invalid_argument("wrong arguments to filter -blur: not int");
                }

                FilterDescriptor parsed_filter_data;
                parsed_filter_data.filter_name = "blur";
                parsed_filter_data.filter_params = {(std::size_t)std::stoi(param1.data())};
                filters_.push_back(parsed_filter_data);
                i += 1;
            } else {
                throw std::invalid_argument("wrong arguments to filter -blur");
            }
        } else if (cur == "-neg") {
            FilterDescriptor parsed_filter_data;
            parsed_filter_data.filter_name = "neg";
            filters_.push_back(parsed_filter_data);
        } else if (cur == "-gs") {
            FilterDescriptor parsed_filter_data;
            parsed_filter_data.filter_name = "gs";
            filters_.push_back(parsed_filter_data);
        } else if (cur == "-sharp") {
            FilterDescriptor parsed_filter_data;
            parsed_filter_data.filter_name = "sharp";
            filters_.push_back(parsed_filter_data);
        } else if (cur == "-edge") {
            if (i + 1 <= argc) {
                std::string_view param1 = argv[i + 1];
                if (!IsDigitString(param1)) {
                    throw std::invalid_argument("wrong arguments to filter -edge: not int");
                }

                FilterDescriptor parsed_filter_data;
                parsed_filter_data.filter_name = "edge";
                parsed_filter_data.filter_params = {(std::size_t)std::stoi(param1.data())};
                filters_.push_back(parsed_filter_data);
                i += 1;
            } else {
                throw std::invalid_argument("wrong arguments to filter -edge");
            }
        }else if (cur == "-distortion") {
            if (i + 1 <= argc) {
                std::string_view param1 = argv[i + 1];
                if (!IsDigitString(param1)) {
                    throw std::invalid_argument("wrong arguments to filter -distortion: not int");
                }

                FilterDescriptor parsed_filter_data;
                parsed_filter_data.filter_name = "distortion";
                parsed_filter_data.filter_params = {(std::size_t)std::stoi(param1.data())};
                filters_.push_back(parsed_filter_data);
                i += 1;
            } else {
                throw std::invalid_argument("wrong arguments to filter -distortion");
            }
        } else {
            std::string error = "no matched filter: ";
            error += std::string(cur);
            throw std::invalid_argument(error);
        }
        ++i;
    }
    return true;
}

std::vector<FilterDescriptor> CmdLineParser::GetParsedFilters() const {
    return filters_;
}


