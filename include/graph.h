#ifndef __GRAPH_H__
#define __GRAPH_H__

// containers
#include <unordered_map>
#include <string>
#include <list>
#include <vector>

namespace graph_utils
{

using graph_t = std::unordered_map<std::string, std::list<std::string>>;
using parent_t = std::unordered_map<std::string, std::string>;
using path_t = std::vector<std::string>;

class graph final
{

public:
    graph () = default;

    explicit graph(const graph_t &graph);

    ~graph() = default;

public:
    void set_graph(const graph_t &graph) noexcept;

    graph_t get_graph() const noexcept;

    /*
     *  @brief
     */
    path_t bfs(std::string_view start, std::string_view end);

private:
    /*
     *  @brief This function is a helper function that backtrace start and end to find
     *  the final path
     *  @param relations This a map of nodes and their parent (each node only has one parent)
     *  @note inside "relations" map, node are key and its parent is the value
     *  @param start Start of the graph
     *  @param end End of the graph
     */
    path_t backtrace(const parent_t &relations, std::string_view start, std::string_view end);

private:
    graph_t _graph;
};

} // namespace graph_utils

#endif // __GRAPH_H__
