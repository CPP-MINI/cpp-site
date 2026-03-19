#pragma once
#include "Subtask.hpp"

struct SubtaskNode {
    Subtask data;
    SubtaskNode* next;
    SubtaskNode(const Subtask& data) : data(data), next(nullptr) {}
};

class Task {

};
