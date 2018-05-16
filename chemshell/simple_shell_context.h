#ifndef CHEMTOOLS_SIMPLE_SHELL_CONTEXT_H
#define CHEMTOOLS_SIMPLE_SHELL_CONTEXT_H


#include <functional>
#include <map>
#include "shell_context.h"

class simple_shell_context final : public shell_context {
public:
    typedef std::map<std::string, std::function<shell_context::result(std::vector<std::string>)>> command_map;

private:
    std::string name;
    command_map commands;

public:
    explicit simple_shell_context(const std::string &name, const command_map &commands, shell_context *parent = nullptr) noexcept;

    std::string getName() const noexcept override;

protected:
    result execute(std::string command, std::vector<std::string> args) noexcept override;
};


#endif //CHEMTOOLS_SIMPLE_SHELL_CONTEXT_H
