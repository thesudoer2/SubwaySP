#include <include/graph.h>

// containers
#include <set>
#include <queue>

// exceptions
#include <stdexcept>

namespace graph_utils
{

graph::graph(const graph_t& graph)
{
    set_graph(graph);
}

void graph::set_graph(const graph_t &graph) noexcept
{
    if (!graph.size())
        return;
    _graph = graph;
}

graph_t graph::get_graph() const noexcept
{
    return _graph;
}

path_t graph::bfs(std::string_view start, std::string_view end)
{
    if (!_graph.size())
        throw std::runtime_error("You should fill the graph first");

    std::queue<std::string> queue;
    std::set<std::string> visited_nodes;
    parent_t parents;

    queue.push(start.data());
    while (!queue.empty())
    {
        std::string &current_node = queue.front();
        if (current_node == end)
            return backtrace(parents, start, end);

        // if current_node doesn't exist in visited_nodes
        if (visited_nodes.find(current_node) == visited_nodes.end())
        {
            for (const auto& neighbor : _graph.at(current_node))
            {
                if (visited_nodes.find(neighbor) == visited_nodes.end())
                {
                    queue.push(neighbor);
                    parents.insert({neighbor, current_node});
                }
            }

            // add current_node to visited_nodes to avoid revisiting it (to prevent from loops)
            visited_nodes.insert(current_node);

        }
        // poping current_node from the queue
        queue.pop();
    }

    return { };
}

path_t graph::backtrace(const parent_t &relations, std::string_view start, std::string_view end)
{
    path_t final_path;

    std::string node = end.data();
    final_path.push_back(node);
    for (std::string_view parent = relations.at(node); parent != start; node = parent, parent = relations.at(node))
        final_path.push_back(parent.data());

    final_path.push_back(start.data());
    
    // reverse the path and then return it (to be from start to end not reverse)
    return {final_path.rbegin(), final_path.rend()};
}

} // namespace graph_utils