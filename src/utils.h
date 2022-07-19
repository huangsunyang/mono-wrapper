#pragma once

#include <iostream>
#include <string>
#include <windows.h>


#define EXPORT __declspec(dllexport)

#define ASSERT_NOT_NULL(ptr)                                             \
    do                                                                   \
    {                                                                    \
        if (ptr == nullptr)                                              \
        {                                                                \
            std::cout << "!!ERROR: " << #ptr << " is null" << std::endl; \
            return 0;                                                    \
        }                                                                \
    } while (0)

#define CHECK_EXC(exc)                                                    \
    do                                                                    \
    {                                                                     \
        if (exc != nullptr)                                               \
        {                                                                 \
            std::cout << "!!ERROR: " << PyNet_ExceptionToString(exc) << std::endl; \
            return 0;                                                     \
        }                                                                 \
    } while (0)


class Region {
public:
    static int level;
    std::string name;

    Region (std::string name) {
        this->name = name;
        std::cout << std::endl;
        std::cout << GetIdent() << "++++++++ " << name << " start +++++++++" << std::endl;
        level += 1;
    }

    ~Region() {
        level -= 1;
        std::cout << GetIdent() << "======== " << name << " end =========" << std::endl;
    }

    static std::string GetIdent() {return std::string(level * 4, ' ');}
};

std::string getCurrentDir();
