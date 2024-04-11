#ifndef __JSON_PARSER_H__
#define __JSON_PARSER_H__

// local headers
#include <include/graph.h>

namespace json_utils
{

class json_parser final
{
public:
    json_parser() = default;
    ~json_parser() = default;

    explicit json_parser(std::string_view json_string);

public:
    void set_json_string(std::string_view json_string) noexcept;
    std::string get_json_string() const noexcept;

    ::graph_utils::graph_t parse_json() const;

public:
    ::graph_utils::graph_t operator()() const;

private:
    std::string _json_string;
};

} // namespace json_utils

#endif // __JSON_PARSER_H__