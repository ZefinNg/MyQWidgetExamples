#ifndef LOGGER_H
#define LOGGER_H

#include "spdlog.h"
#include "async.h"
#include "sinks/daily_file_sink.h"
#include "stopwatch.h"
#include "sinks/stdout_color_sinks.h"
#include "sinks/callback_sink.h"

class Logger
{
public:
    static Logger* getInstance();
    ~Logger();

private:
    Logger();

    void init_spdlog();
};

#endif // LOGGER_H
