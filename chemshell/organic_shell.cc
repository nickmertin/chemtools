#include "organic_shell.h"
#include "root_shell.h"
#include "../organic/compound.h"

static organic::compound compound;

static size_t read_num(const std::vector<std::string> args, size_t index, std::string prompt) {
    size_t result;
    try {
        result = std::stoul(args[0]);
    }
    catch (...) {
        while (true)
            try {
                std::cout << "Invalid number!" << std::endl;
                std::cout << prompt;
                std::string line;
                std::getline(std::cin, line);
                result = std::stoul(line);
                break;
            }
        catch (...) {}
    }
    return result;
}

simple_shell_context organic_shell("organic", {
        {"formula", [] (const auto &args) {
            std::cout << compound.get_formula().str() << std::endl;
            return shell_context::success;
        }},
        {"name", [] (const auto &args) {
            std::cout << compound.get_iupac_name() << std::endl;
            return shell_context::success;
        }},
        {"chain", [] (const auto &args) {
            compound = organic::compound(read_num(args, 0, "New chain length: "));
            return shell_context::success;
        }}
}, &root_shell);
