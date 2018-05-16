#include <algorithm>
#include <deque>
#include "shell_context.h"
#include "../utils/string_utils.h"

shell_context::shell_context(shell_context *parent) noexcept : parent(parent) {}

std::string shell_context::getFullName() const noexcept {
    return parent ? parent->getFullName() + "/" + getName() : getName();
}

void shell_context::run(std::vector<std::string> args) noexcept {
    result _result;
    while (true) {
        std::cout << getFullName() << '>';
        std::cout.flush();
        std::string cmd;
        std::getline(std::cin, cmd);
        std::vector<std::string> parts(utils::split(cmd, ' '));
        std::vector<std::string> tmp;
        std::copy_if(parts.cbegin(), parts.cend(), std::back_inserter(tmp), [] (const std::string &s) { return !s.empty(); });
        parts.clear();
        std::copy(tmp.cbegin() + 1, tmp.cend(), std::back_inserter(parts));
        cmd = tmp.front();
        _result = execute(cmd, parts);
        switch (_result) {
            case failure:
                std::cout << getName() << ": " << cmd << ": failure" << std::endl;
                break;
            case not_found:
                std::cout << getName() << ": " << cmd << ": not found" << std::endl;
                break;
            case quit:
                return;
        }
    }
}
