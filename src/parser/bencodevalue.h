#pragma once

#include <vector>
#include <memory>
#include <variant>
#include <map>

struct BencodeValue;

struct InfoPos{
    std::streampos start;
    std::streampos end;
};

using List = std::vector<std::unique_ptr<BencodeValue>>;

using Dictionary = std::map<std::string, std::unique_ptr<BencodeValue>>;

struct BencodeValue
{
    std::variant<
        int64_t,
        std::string,
        List,
        Dictionary>
        value;
};