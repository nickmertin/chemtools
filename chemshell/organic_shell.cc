#include "organic_shell.h"
#include "root_shell.h"
#include "../organic/compound.h"
#include "../utils/functional.h"
#include "../utils/io.h"
#include "../organic/branch.h"
#include "../organic/halogen.h"
#include "../organic/hydroxyl.h"
#include "../organic/phenyl.h"
#include "../organic/chain.h"

static organic::compound *compound;

template<class T>
static T read(const std::vector<std::string> args, size_t index, std::string prompt, std::function<T(const std::string &)> parser) {
    try {
        if (index >= args.size())
            throw 0;
        return parser(args[index]);
    }
    catch (...) {
        while (true)
            try {
                std::cout << "Invalid input!" << std::endl;
                std::cout << prompt;
                std::string line;
                std::getline(std::cin, line);
                return parser(line);
            }
        catch (...) {}
    }
}

simple_shell_context organic_shell("organic", {
        {"formula", [] (const auto &args) {
            if (!compound) {
                std::cout << "No compound has been loaded!" << std::endl;
                return shell_context::failure;
            }
            std::cout << compound->get_formula().str() << std::endl;
            return shell_context::success;
        }},
        {"name", [] (const auto &args) {
            if (!compound) {
                std::cout << "No compound has been loaded!" << std::endl;
                return shell_context::failure;
            }
            std::cout << compound->get_iupac_name() << std::endl;
            return shell_context::success;
        }},
        {"chain", [] (const auto &args) {
            try {
                compound = new organic::chain(read<size_t>(args, 0, "New chain length: ", utils::parse<size_t>));
                return shell_context::success;
            }
            catch (utils::exception e) {
                std::cout << e << std::endl;
                return shell_context::failure;
            }
        }},
        {"bond", [] (const auto &args) {
            if (!compound) {
                std::cout << "No compound has been loaded!" << std::endl;
                return shell_context::failure;
            }
            try {
                auto index = read<size_t>(args, 0, "Carbon index: ", utils::parse<size_t>);
                auto bond = read(args, 1, "Bond count: ", utils::cast_result<utils::ranged_numeric<int, 1, 3>, long, const std::string &>(utils::parse<long>));
                compound->set_bond_type(index, bond);
                return shell_context::success;
            }
            catch (utils::exception e) {
                std::cout << e << std::endl;
                return shell_context::failure;
            }
        }},
        {"list-groups", [] (const auto &args) {
            if (!compound) {
                std::cout << "No compound has been loaded!" << std::endl;
                return shell_context::failure;
            }
            try {
                auto index = read<size_t>(args, 0, "Carbon index: ", utils::parse<size_t>);
                if (!index || index-- > compound->size()) {
                    std::cout << "Out of range!" << std::endl;
                    return shell_context::failure;
                }
                for (const auto &d : (*compound)[index].groups)
                    std::cout << d->get_name() << " (" << d->get_formula().str() << ")" << std::endl;
                return shell_context::success;
            }
            catch (utils::exception e) {
                std::cout << e << std::endl;
                return shell_context::failure;
            }
        }},
        {"remove-group", [] (const auto &args) {
            if (!compound) {
                std::cout << "No compound has been loaded!" << std::endl;
                return shell_context::failure;
            }
            try {
                auto index = read<size_t>(args, 0, "Carbon index: ", utils::parse<size_t>);
                auto group = read<size_t>(args, 1, "Group index: ", utils::parse<size_t>);
                compound->remove_group(index, group);
                return shell_context::success;
            }
            catch (utils::exception e) {
                std::cout << e << std::endl;
                return shell_context::failure;
            }
        }},
        {"branch", [] (const auto &args) {
            if (!compound) {
                std::cout << "No compound has been loaded!" << std::endl;
                return shell_context::failure;
            }
            try {
                auto index = read<size_t>(args, 0, "Carbon index: ", utils::parse<size_t>);
                auto length = read<size_t>(args, 1, "Length: ", utils::cast_result<utils::ranged_numeric<int, 1, 10>, long, const std::string &>(utils::parse<long>));
                compound->add_group(index, [length] () { return new organic::branch(length); });
                return shell_context::success;
            }
            catch (utils::exception e) {
                std::cout << e << std::endl;
                return shell_context::failure;
            }
        }},
        {"halogen", [] (const auto &args) {
            if (!compound) {
                std::cout << "No compound has been loaded!" << std::endl;
                return shell_context::failure;
            }
            try {
                auto index = read<size_t>(args, 0, "Carbon index: ", utils::parse<size_t>);
                auto type = read<organic::halogen::type>(args, 1, "Element: ", organic::halogen::get_parser());
                compound->add_group(index, [type] () { return new organic::halogen(type); });
                return shell_context::success;
            }
            catch (utils::exception e) {
                std::cout << e << std::endl;
                return shell_context::failure;
            }
        }},
        {"hydroxyl", [] (const auto &args) {
            if (!compound) {
                std::cout << "No compound has been loaded!" << std::endl;
                return shell_context::failure;
            }
            try {
                auto index = read<size_t>(args, 0, "Carbon index: ", utils::parse<size_t>);
                compound->add_group(index, [] () { return new organic::hydroxyl(); });
                return shell_context::success;
            }
            catch (utils::exception e) {
                std::cout << e << std::endl;
                return shell_context::failure;
            }
        }},
        {"phenyl", [] (const auto &args) {
            if (!compound) {
                std::cout << "No compound has been loaded!" << std::endl;
                return shell_context::failure;
            }
            try {
                auto index = read<size_t>(args, 0, "Carbon index: ", utils::parse<size_t>);
                compound->add_group(index, [] () { return new organic::phenyl(); });
                return shell_context::success;
            }
            catch (utils::exception e) {
                std::cout << e << std::endl;
                return shell_context::failure;
            }
        }}
}, &root_shell);
