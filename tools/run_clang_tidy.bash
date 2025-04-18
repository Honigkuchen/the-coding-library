#!/usr/bin/env bash
clang-tidy-20 --header-filter=.* --extra-arg="--std=gnu++20" --extra-arg="-Iinclude/" -p=build include/coding_library/coding_library.hpp
# clang-tidy-20 -p=build include/coding_library/coding_library.hpp