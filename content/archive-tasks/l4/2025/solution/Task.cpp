#include "Task.hpp"

#include <iostream>

Task::Task(const std::string& description) : description(description), head(nullptr) {}

void Task::clear() {
    while (head) {
        SubtaskNode* temp = head;
        head = head->next;
        delete temp;
    }
}

Task::~Task() {
    clear();
}

void Task::add_subtask(const Subtask& subtask) {
    SubtaskNode* new_node = new SubtaskNode(subtask);
    if (!head || subtask.get_priority() > head->data.get_priority()) {
        new_node->next = head;
        head = new_node;
        return;
    }

    SubtaskNode* current = head;
    while (current->next && subtask.get_priority() <= current->next->data.get_priority()) {
        current = current->next;
    }
    new_node->next = current->next;
    current->next = new_node;
}

void Task::complete_subtask(unsigned int index) {
    SubtaskNode* current = head;
    while (current && index--) {
        current = current->next;
    }
    if (current) {
        current->data.mark_completed();
    }
}

bool Task::is_completed() const {
    SubtaskNode* current = head;
    while (current) {
        if (!current->data.is_completed()) {
            return false;
        }
        current = current->next;
    }
    return true;
}

void Task::print() const {
    std::cout << "[" << (is_completed() ? 'x' : ' ') << "] " << description << std::endl;
    SubtaskNode* current = head;
    while (current) {
        std::cout << "    - ";
        current->data.print();
        current = current->next;
    }
}

void Task::copy_from(const Task& other) {
    description = other.description;
    head = nullptr;

    SubtaskNode* current = other.head;
    SubtaskNode** tail = &head;
    while (current) {
        *tail = new SubtaskNode(current->data);
        current = current->next;
        tail = &((*tail)->next);
    }
}

Task::Task(const Task& other) {
    copy_from(other);
}

Task& Task::operator=(const Task& other) {
    if (this != &other) {
        clear();
        copy_from(other);
    }
    return *this;
}

Task::Task(Task&& other) : description(std::move(other.description)), head(other.head) {
    other.head = nullptr;
}

Task& Task::operator=(Task&& other) {
    if (this != &other) {
        clear();
        description = std::move(other.description);
        head = other.head;
        other.head = nullptr;
    }
    return *this;
}
