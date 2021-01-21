#pragma once

#include<set>
#include<string>
#include<vector>

/// Contains everything needed for the c body and header
struct CFile {
    std::set<std::string> casts_macro_invocations;
    std::vector<std::string> pretty_defines;
    std::set<std::string> header_includes;
    std::string declarations;
    std::string definitions;
};