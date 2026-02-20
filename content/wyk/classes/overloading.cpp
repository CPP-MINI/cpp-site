#include <iostream>
#include <ostream>
#include <string>
#include <vector>

enum class Severity
{
    DEBUG,
    INFO,
    WARNING,
    ERROR,
};

std::string severity_to_string(Severity severity)
{
    switch (severity)
    {
        case Severity::DEBUG:
            return "DEBUG";
        case Severity::INFO:
            return "INFO";
        case Severity::WARNING:
            return "WARNING";
        case Severity::ERROR:
            return "ERROR";
    }
}

struct Log
{
    Severity severity;
    std::string text;
};

class Logger
{
    std::vector<Log> logs;

public:
    void write(const Log& msg)
    {
        logs.push_back(msg);
        print(msg);
    }

    void write(const std::string& msg)
    {
        Log l{.severity = Severity::INFO, msg};
        write(l);
    }

    void write(const char* msg)
    {
        Log l{.severity = Severity::INFO, msg};
        write(l);
    }

    void write(const Log& msg) const
    {
        print(msg);
    }

    void write(const std::string& msg) const
    {
        Log l{.severity = Severity::INFO, msg};
        write(l);
    }

    void write(const std::string& msg, Severity sev = Severity::INFO) const
    {
        Log l{.severity = sev, msg};
        write(l);
    }

    void write(const char* msg) const
    {
        Log l{.severity = Severity::INFO, msg};
        write(l);
    }

private:
    void print(const Log& msg) const
    {
        std::cout << severity_to_string(msg.severity) << ": " << msg.text << std::endl;
    }
};

int main()
{
    Logger logger;
    logger.write("Hello, World!");
    logger.write({.severity = Severity::ERROR, "Something went wrong"});
}
