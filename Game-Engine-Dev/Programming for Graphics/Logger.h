#pragma once
#include <string>

class Logger
{
public:

	enum class Category {
		Info,
		Debug,
		Error,
		Critical
	};

	/**
	* Finding the category for logger. Then output a message that is put into the logger.
	* @param category The category to log.
	* @param buffer using the buffer for logging.
	*/
	static void Log(Logger::Category category, const std::string& buffer);
	
	static void Info(const std::string& buffer);
	static void Error(const std::string& buffer);

private:
	static std::string GetCategoryString(Logger::Category cat);

};

