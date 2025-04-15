#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/basic_file_sink.h>
#include <filesystem>
#include "logger.h"

using namespace Log;

std::shared_ptr<spdlog::logger> Log::Logger::logger = nullptr;

void Logger::init() {
    std::filesystem::create_directories("logs");
    auto console_sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
    auto file_sink = std::make_shared<spdlog::sinks::basic_file_sink_mt>("logs/snake.log", true);

    console_sink->set_pattern("[%T] [%^%l%$] %v");
    file_sink->set_pattern("[%Y-%m-%d %T] [%l] %v");

    logger = std::make_shared<spdlog::logger>("snake", spdlog::sinks_init_list{console_sink, file_sink});
    spdlog::register_logger(logger);
    logger->set_level(spdlog::level::debug);
    logger->flush_on(spdlog::level::info);
}

std::shared_ptr<spdlog::logger>& Logger::getLogger() {
    return logger;
}