#include <iostream>
#include <variant>
#include <vector>
#include <map>
#include <memory>
#include <string>

struct BencodeValue;
using List = std::vector<std::unique_ptr<BencodeValue>>;
using Dictionary = std::map<std::string, std::unique_ptr<BencodeValue>>;

struct BencodeValue {
    std::variant<int64_t, std::string, List, Dictionary> value;
};

// 1. Helper helper trick to combine lambdas into a visitor
template<class... Ts> struct overloaded : Ts... { using Ts::operator()...; };
template<class... Ts> overloaded(Ts...) -> overloaded<Ts...>;

// 2. Recursive print function
void printBencode(const BencodeValue& bencode) {
    std::visit(overloaded{
        // Handle integers
        [](int64_t val) { 
            std::cout << "i" << val << "e"; 
        },
        // Handle strings
        [](const std::string& val) { 
            std::cout << val.length() << ":" << val; 
        },
        // Handle lists recursively
        [](const List& list) {
            std::cout << "l";
            for (const auto& item : list) {
                if (item) printBencode(*item); // Recursive call
            }
            std::cout << "e";
        },
        // Handle dictionaries recursively
        [](const Dictionary& dict) {
            std::cout << "d";
            for (const auto& [key, item] : dict) {
                // Keys in bencode are always strings
                std::cout << key.length() << ":" << key; 
                if (item) printBencode(*item); // Recursive call
            }
            std::cout << "e";
        }
    }, bencode.value);
}
