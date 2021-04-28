#pragma once

#include <string>

inline std::string to_pascal_case(const std::string& s) {
    std::string result;

    bool brk = true;
    bool waslower = true;
    int wasupper = 0;
    for (auto c_ : s) {
        auto c = c_;
        if (waslower && isupper(c)) {
            brk = true;
        }
        if (wasupper > 1 && islower(c) && c != '_') {
            result.back() = toupper(result.back());
            wasupper = 0;
        }
        if (brk) {
            c = toupper(c);
            brk = false;
        } else {
            c = tolower(c);
        }
        if (c == '_') {
            brk = true;
            wasupper = 0;
            continue;
        }
        result.push_back(c);

        waslower = islower(c_);
        if (isupper(c_)) {
            wasupper++;
        }
    }

    return result;
}

inline std::string to_snake_case(const std::string& s) {
    std::string result;

    bool brk = false;
    bool waslower = false;
    int wasupper = 0;
    char lastc = '\0';
    for (auto c : s) {
        if (lastc == '\0') {
            lastc = c;
            continue;
        }

        if (lastc == '_') {
            result.push_back(lastc);
            wasupper = 0;
        } else {
            if (isupper(c) && islower(lastc)) {
                result.push_back(tolower(lastc));
                result.push_back('_');
                wasupper = 0;
            } else if (wasupper > 1 && islower(c)) {
                result.push_back('_');
                result.push_back(tolower(lastc));
                wasupper = 0;
            } else {
                result.push_back(tolower(lastc));
            }
        }

        if (isupper(c)) {
            wasupper++;
        }

        lastc = c;
    }
    result.push_back(tolower(lastc));

    return result;
}

inline std::string to_capital_case(const std::string& s) {
    std::string result;

    bool brk = false;
    bool waslower = false;
    int wasupper = 0;
    char lastc = '\0';
    for (auto c : s) {
        if (lastc == '\0') {
            lastc = c;
            continue;
        }

        if (lastc == '_') {
            result.push_back(lastc);
            wasupper = 0;
        } else {
            if (isupper(c) && islower(lastc)) {
                result.push_back(toupper(lastc));
                result.push_back('_');
                wasupper = 0;
            } else if (wasupper > 1 && islower(c)) {
                result.push_back('_');
                result.push_back(toupper(lastc));
                wasupper = 0;
            } else {
                result.push_back(toupper(lastc));
            }
        }

        if (isupper(c)) {
            wasupper++;
        }

        lastc = c;
    }
    result.push_back(toupper(lastc));

    return result;
}
