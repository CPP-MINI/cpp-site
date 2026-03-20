#pragma once
#include "Subtask.hpp"

struct SubtaskNode {
    Subtask data;
    SubtaskNode* next;
    SubtaskNode(const Subtask& data) : data(data), next(nullptr) {}
};

class Task {
private:
    std::string description;
    SubtaskNode* head;

    void copy_from(const Task& other);

public:
    Task(const std::string& description = "");
    ~Task();

    bool is_completed() const;
    void complete_subtask(unsigned int index);
    void add_subtask(const Subtask& subtask);
    void clear();
    void print() const;

    Task(const Task& other);
    Task& operator=(const Task& other);
    Task(Task&& other);
    Task& operator=(Task&& other);
};
