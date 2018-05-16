#include "root_shell.h"
#include "organic_shell.h"

simple_shell_context root_shell("chemshell", {
        {"organic", [] (const auto &args) {
            organic_shell.run();
            return shell_context::success;
        }}
});
