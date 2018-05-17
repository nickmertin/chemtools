#include "organic_shell.h"
#include "root_shell.h"
#include "../organic/compound.h"
#include "../utils/functional.h"
#include "../utils/io.h"

static organic::compound compound;

template<class T>
static T read_num(const std::vector<std::string> args, size_t index, std::string prompt, std::function<T(const std::string &)> parser) {
    T result;
    try {
        result = parser(args[index]);
    }
    catch (...) {
        while (true)
            try {
                std::cout << "Invalid number!" << std::endl;
                std::cout << prompt;
                std::string line;
                std::getline(std::cin, line);
                result = parser(line);
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
            try {
                compound = organic::compound(read_num<size_t>(args, 0, "New chain length: ", utils::parse<size_t>));
                return shell_context::success;
            }
            catch (utils::exception e) {
                std::cout << e << std::endl;
                return shell_context::failure;
            }
        }},
        {"bond", [] (const auto &args) {
            try {
                auto index = read_num<size_t>(args, 0, "Carbon index: ", utils::parse<size_t>);
                auto bond = read_num(args, 1, "Bond count: ", utils::cast_result<utils::ranged_numeric<int, 1, 3>, long, const std::string &>(utils::parse<long>));
                compound.set_bond_type(index, bond);
                return shell_context::success;
            }
            catch (utils::exception e) {
                std::cout << e << std::endl;
                return shell_context::failure;
            }
        }}
}, &root_shell);
