#include "Subtask.hpp"

#include <iostream>

Subtask::Subtask(const std::string& description, unsigned int priority, bool completed)
    : description(description), priority(priority), completed(completed) {}

void Subtask::mark_completed() {
    completed = true;
}

unsigned int Subtask::get_priority() const {
    return priority;
}

void Subtask::print() const {
    std::cout << "[" << (completed ? 'x' : ' ') << "] " << "P: " << priority << ", " << description << std::endl;
}

bool Subtask::is_completed() const {
    return completed;
}
