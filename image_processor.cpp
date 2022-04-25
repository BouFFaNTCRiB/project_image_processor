#include "cmd_arg_parser.h"
#include "bitmap.h"
#include "base_filters.h"
#include "filter_factory.h"


int main(int argc, char* argv[]) {
    CmdLineParser parser;
    if(parser.Parse(argc, argv)) {
        Bitmap bitmap{};

        if (!bitmap.Load(parser.GetInputFileName().data())) {
            throw std::invalid_argument("invalid input file name");
        }

        FilterFactory factory;
        std::vector<FilterDescriptor> filters = parser.GetParsedFilters();
        for (const auto &filter: filters) {
            factory.CreateFilter(filter.filter_name)->Apply(bitmap.GetImage(), filter.filter_params);
        }


        if (!bitmap.CreateFile(bitmap.CreateFile(parser.GetOutputFileName()))) {
            throw std::invalid_argument("some cringe with output file");
        }
    }
    return 0;
}
