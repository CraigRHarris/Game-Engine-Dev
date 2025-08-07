#include "Logger.h"
#include <fstream>
#include <iostream>
#include <string>

#include <chrono>
#include <format>

void Logger::Log(Logger::Category category, const std::string& buffer) // file pointer - Attempt to open file and append flag
{
    auto now = std::chrono::system_clock::now();

    std::string catString = GetCategoryString(category);

    std::string message = std::format("{:%F %T} [{}] {}\n", now, catString, buffer);
    std::cout << message;

    if (category < Category::Error) return;

    std::ofstream errorFile("error.log", std::ios::app);

    if (!errorFile.is_open())
        return;

    errorFile << message;
}

void Logger::Info(const std::string& buffer)
{
    Log(Category::Info, buffer);
}

void Logger::Error(const std::string& buffer)
{
    Log(Category::Error, buffer);
}

std::string Logger::GetCategoryString(Logger::Category cat)
{
    switch (cat)
    {
    case Category::Info:
        return "Info";
    case Category::Error:
        return "Error";
    case Category::Debug:
        return "Debug";
    case Category::Critical:
        return "Critical";
    }
    return std::string();
}