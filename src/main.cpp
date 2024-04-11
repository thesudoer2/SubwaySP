// local header(s)
#include <include/jsonparser.h>

// stream in/out
#include <iostream>

static const char* program_name;
extern const char* stations_json;

void usage(FILE* fd)
{
    fputs("Usage:\n", fd);
    fprintf(fd, "\t%s <start_station> <end_station>\n", program_name);
}

auto main(int argc, char* argv[]) -> int
{
    program_name = argv[0];

    if (argc != 3)
    {
        std::cerr << "invalid number of arguments!\n";
        usage(stderr);
        exit(EXIT_FAILURE);
    }

    // taking start_station and end_station stations from command-line arguments
    std::string_view start_station { argv[1] }, end_station { argv[2] };

    try
    {
        graph_utils::graph gp(json_utils::json_parser{stations_json}());
        auto result = gp.bfs(start_station, end_station);
        
        for (size_t i { }; i < result.size(); ++i)
        {
            std::cout << result[i];
            if (i == (result.size() - 1))
                break;
            std::cout << " -> ";
        }
        std::cout << '\n';
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }

    return 0;
}
