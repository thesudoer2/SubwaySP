// local header(s)
#include <include/jsonparser.h>

// stream in/out
#include <iostream>
#include <fstream>

auto main(int argc, char* argv[]) -> int
{
    if (argc != 3)
    {
        std::cerr << "invalid number of arguments\n";
        return 1;
    }

    // taking source and destination stations from command-line arguments
    std::string_view source { argv[1] }, destination { argv[2] };

    std::ifstream file("res/stations.json", std::ios::in);
    if (!file)
    {
        perror("Couldn't open the file");
        exit(EXIT_FAILURE);
    }

    try
    {
        std::string file_content { std::istreambuf_iterator<char>(file), std::istreambuf_iterator<char>() };

        graph_utils::graph gp(json_utils::json_parser{file_content}());

        auto result = gp.bfs(source, destination);
        
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
