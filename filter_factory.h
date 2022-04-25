#pragma once

#include "cmd_arg_parser.h"
#include "base_filters.h"

class FilterFactory {
public:
    BaseFilter* CreateFilter(const std::string_view filter_name) const;
};
