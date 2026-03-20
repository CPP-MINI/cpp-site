#pragma once

#include <string>

class Subtask {
private:
    std::string description;
    unsigned int priority;
    bool completed;

public:
    Subtask(const std::string& description, unsigned int priority = 0, bool completed = false);
    bool is_completed() const;
    void mark_completed();
    unsigned int get_priority() const;
    void print() const;
};
