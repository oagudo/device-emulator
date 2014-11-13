#ifndef _LOGGER_H
#define _LOGGER_H

#ifdef WITH_LOG4CXX

#include "log4cxx/logger.h"
#define DEFINE_LOGGER(VAR, NAME) static log4cxx::LoggerPtr VAR = log4cxx::Logger::getLogger(NAME);
#define LOG_ERROR LOG4CXX_ERROR
#define LOG_WARN LOG4CXX_WARN
#define LOG_INFO LOG4CXX_INFO

#else

#include <iostream>
#define DEFINE_LOGGER(VAR, NAME) static const char *VAR = NAME;
#define LOG_ERROR(LOGGER, DATA) std::cerr << "E: <" << LOGGER << "> " << DATA << "\n";
#define LOG_WARN(LOGGER, DATA) std::cout << "W: <" << LOGGER << "> " << DATA << "\n";
#define LOG_INFO(LOGGER, DATA) std::cout << "I: <" << LOGGER << "> " << DATA << "\n";

#endif // WITH_LOG4CXX

#endif // LOGGER
