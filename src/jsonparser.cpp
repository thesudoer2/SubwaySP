#include <include/jsonparser.h>

// rapidjson header(s)
#include <rapidjson/document.h>

// exceptions
#include <stdexcept>

namespace json_utils
{

json_parser::json_parser(std::string_view json_string)
{
    set_json_string(json_string);
}

void json_parser::set_json_string(std::string_view json_string) noexcept
{
    if (!json_string.size())
        return;
    _json_string = json_string;
}

std::string json_parser::get_json_string() const noexcept
{
    return _json_string;
}

::graph_utils::graph_t json_parser::parse_json() const
{
    if (!_json_string.size())
        throw std::runtime_error("You should set json file path");

    graph_utils::graph_t result;

    rapidjson::Document doc;
    doc.Parse(_json_string.data());

    std::string_view station_name;
    for (auto it = doc.GetObject().begin(); it != doc.GetObject().end(); ++it)
    {
        station_name = it->name.GetString();
        result.insert({ station_name.data(), { } });

        if (it->value.IsObject())
        {
            for (const auto &inner_object : it->value.GetObject())
            {
                std::string_view inner_object_name = inner_object.name.GetString();
                if (inner_object_name == "relations")
                {
                    auto inner_array = inner_object.value.GetArray();
                    
                    // interating over objects inside the array
                    for (const auto& obj_inside_array : inner_array)
                        if (obj_inside_array.HasMember("name") && obj_inside_array["name"].IsString())
                            result[station_name.data()].push_back(obj_inside_array["name"].GetString());
                }
            }
        }
    }

    return result;
}

::graph_utils::graph_t json_parser::operator()() const
{
    return parse_json();
}

} // nmaepsace json_utils