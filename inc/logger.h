#pragma once
#include <memory>
#include <spdlog/spdlog.h>

namespace Log {
class Logger {
private:
    static std::shared_ptr<spdlog::logger> logger;
public:
    static void init();
    static std::shared_ptr<spdlog::logger>& getLogger();
};
}