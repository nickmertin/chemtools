#include "simple_shell_context.h"

static const simple_shell_context::command_map::value_type *find_command(const simple_shell_context::command_map &commands, const std::string &name) {
    simple_shell_context::command_map filter;
    std::copy_if(commands.cbegin(), commands.cend(), std::inserter(filter, filter.end()), [name] (const simple_shell_context::command_map::value_type &value) { return value.first.length() >= name.length() && value.first.substr(0, name.length()) == name; });
    return filter.size() == 1 ? &*filter.cbegin() : nullptr;
}

simple_shell_context::simple_shell_context(const std::string &name, const command_map &commands, shell_context *parent) noexcept : shell_context(parent), name(name), commands(commands) {
    this->commands["quit"] = [] (const auto &args) { return quit; };
    this->commands["help"] = [this] (const auto &args) {
        if (args.size()) {
            for (auto cmd : args) {
                auto match = find_command(this->commands, cmd);
                if (match)
                    std::cout << cmd << " -> " << match->first << std::endl;
                else
                    std::cout << "No match found for: " << cmd << std::endl;
            }
        }
        else {
            std::vector<std::string> names;
            std::transform(this->commands.cbegin(), this->commands.cend(), std::back_inserter(names), [](const auto &command) { return command.first; });
            std::sort(names.begin(), names.end());
            std::cout << "The following commands are available: " << std::endl;
            for (auto cmd : names)
                std::cout << cmd << std::endl;
        }
        return success;
    };
}

std::string simple_shell_context::getName() const noexcept {
    return name;
}

shell_context::result simple_shell_context::execute(std::string command, std::vector<std::string> args) noexcept {
    auto match = find_command(commands, command);
    return match ? match->second(args) : not_found;
}
