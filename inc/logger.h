/**
 * @file logger.h
 * @brief Логирование различных этапов программы
 */

#ifndef LOGGER_H
#define LOGGER_H

#include <memory>
#include <spdlog/spdlog.h>
#include <spdlog/sinks/null_sink.h>

/**
 * @namespace nLogger
 * @brief Содержит в себе класс Logger
 */
namespace nLogger {

/**
 * @class Logger
 * @brief Ответственен за логирование программы
 * Включает в себя:
 * - работу с файлом для логов
 * - работу с консолью для логов
 * - поддерживает разные уровни сообщений
 */
class Logger {

public:
    /**
     * @brief Инициализация устройства логирования
     * 
     * Включает в себя:
     * - работу с файлом для логов
     * - работу с консолью для логов
     * - поддерживает разные уровни сообщений
     */
    static void init();
    /// Получение устройства логирования
    static std::shared_ptr<spdlog::logger>& getLogger();

private:
    static std::shared_ptr<spdlog::logger> logger;

};

};

#endif