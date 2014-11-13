#ifndef _LOGGER_H
#define _LOGGER_H

#include <iostream>

#ifdef WITH_LOG4CXX

#include <log4cxx/xml/domconfigurator.h>
#include <log4cxx/logger.h>
#include <log4cxx/helpers/pool.h>
#include <log4cxx/basicconfigurator.h>
#include <log4cxx/fileappender.h>
#include <log4cxx/simplelayout.h>

#define DEFINE_LOGGER(VAR, NAME) static log4cxx::LoggerPtr VAR = log4cxx::Logger::getLogger(NAME);
#define LOG_ERROR LOG4CXX_ERROR
#define LOG_WARN LOG4CXX_WARN
#define LOG_INFO LOG4CXX_INFO

#else

#define DEFINE_LOGGER(VAR, NAME)
#define LOG_ERROR(LOGGER, DATA) 
#define LOG_WARN(LOGGER, DATA) 
#define LOG_INFO(LOGGER, DATA) 

#endif // WITH_LOG4CXX

namespace device_emulator {

    /*!
      \class Represents the logger facility of the library
    */
    class Logger {

    public:

        static void Init()
        {
#ifdef WITH_LOG4CXX
            log4cxx::FileAppender * fileAppender = new
                log4cxx::FileAppender(log4cxx::LayoutPtr(new log4cxx::SimpleLayout()),
                                      "device_emulator.log", false);
            log4cxx::helpers::Pool p;
            fileAppender->activateOptions(p);
            log4cxx::BasicConfigurator::configure(log4cxx::AppenderPtr(fileAppender));
            log4cxx::Logger::getRootLogger()->setLevel(log4cxx::Level::getDebug());
#endif
        }

        static void Configure(const std::string &fileName) {
            try {
#ifdef WITH_LOG4CXX
                log4cxx::xml::DOMConfigurator::configure(fileName);
#else
                // Do nothing
#endif
            } catch (std::exception &e) {
                std::cerr << "Error when configuring logging " << e.what() << std::endl;
            }
        }
    };

} // namespace

#endif // LOGGER
