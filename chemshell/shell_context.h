#ifndef CHEMTOOLS_SHELL_CONTEXT_H
#define CHEMTOOLS_SHELL_CONTEXT_H


#include <string>
#include <vector>
#include <iostream>

class shell_context {
private:
    shell_context *parent;

public:
    enum result {
        success,
        failure,
        not_found,
        quit
    };

protected:
    virtual result execute(std::string command, std::vector<std::string> args) noexcept = 0;

public:
    explicit shell_context(shell_context *parent = nullptr) noexcept;

    virtual std::string getName() const noexcept = 0;
    std::string getFullName() const noexcept;
    void run(std::vector<std::string> args = {}) noexcept;
};


#endif //CHEMTOOLS_SHELL_CONTEXT_H
