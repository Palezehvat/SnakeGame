#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/basic_file_sink.h>
#include <filesystem>
#include "logger.h"

namespace nLogger {

    std::shared_ptr<spdlog::logger> nLogger::Logger::logger = nullptr;
    
    void Logger::init() {
        std::filesystem::create_directories("logs");
        auto consoleSink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
        auto fileSink = std::make_shared<spdlog::sinks::basic_file_sink_mt>("logs/snake.log", true);
    
        consoleSink->set_pattern("[%T] [%^%l%$] %v");
        fileSink->set_pattern("[%Y-%m-%d %T] [%l] %v");
    
        logger = std::make_shared<spdlog::logger>("snake", spdlog::sinks_init_list{consoleSink,
                                                                                   fileSink});
        spdlog::register_logger(logger);
        logger->set_level(spdlog::level::debug);
        logger->flush_on(spdlog::level::info);
    }
    
    std::shared_ptr<spdlog::logger>& Logger::getLogger() {
        if (!logger) {
            auto nullSink = std::make_shared<spdlog::sinks::null_sink_mt>();
            logger = std::make_shared<spdlog::logger>("null_logger", nullSink);
        }
        return logger;
    }

}
