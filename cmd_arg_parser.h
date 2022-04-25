#pragma once

#include <string_view>
#include <vector>
#include <exception>
#include <stdexcept>
#include <string>

struct FilterDescriptor {
    std::string_view filter_name;
    std::vector<std::size_t> filter_params;
};

class CmdLineParser {
private:
    static const int MIN_PARAM_NUM = 3;
    static const int INPUT_FILE_NAME_POS_ = 1;
    static const int OUTPUT_FILE_NAME_POS_ = 2;

public:
    bool Parse(int argc, char* argv[]);
    std::string_view GetInputFileName() const { return input_file_name_; }
    std::string_view GetOutputFileName() const { return output_file_name_; }
    std::vector<FilterDescriptor> GetParsedFilters() const;

private:
    std::string_view input_file_name_;
    std::string_view output_file_name_;
    std::vector<FilterDescriptor>filters_;
};
