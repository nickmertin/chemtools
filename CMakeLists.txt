cmake_minimum_required(VERSION 3.9)
project(chemtools)

set(CMAKE_CXX_STANDARD 17)

set(SRC_UTILS utils/ranged_numeric.h utils/string_utils.h utils/var_array.h utils/exception.h utils/functional.h utils/io.h utils/map_parser.h)

add_library(base STATIC ${SRC_UTILS} base/base.cc base/base.h base/formula.cc base/formula.h base/table.cc base/table.h base/table.inc)
add_library(organic STATIC ${SRC_UTILS} organic/compound.cc organic/compound.h organic/group.cc organic/group.h organic/branch.cc organic/branch.h organic/organic.cc organic/organic.h organic/halogen.cc organic/halogen.h organic/hydroxyl.cc organic/hydroxyl.h organic/phenyl.cc organic/phenyl.h organic/chain.cc organic/chain.h organic/benzene.cc organic/benzene.h)
add_executable(chemshell ${SRC_UTILS} chemshell/main.cc chemshell/shell_context.cc chemshell/shell_context.h chemshell/simple_shell_context.cc chemshell/simple_shell_context.h chemshell/root_shell.cc chemshell/root_shell.h chemshell/organic_shell.cc chemshell/organic_shell.h)
target_link_libraries(organic base)
target_link_libraries(chemshell base organic)
