#include <iostream>
#include <limits>
#include <memory>
#include <vector>

struct Node
{
    int value;
    std::unique_ptr<Node> next;

    Node(int value, std::unique_ptr<Node> next) : value{value}, next{std::move(next)}
    {
    }
};

class SortedLinkedList
{
    std::unique_ptr<Node> head;

public:
    SortedLinkedList() : head(nullptr)
    {
    }

    void print()
    {
        Node* n = head.get();
        while (n)
        {
            std::cout << n->value << " ";
            n = n->next.get();
        }
        std::cout << std::endl;
    }

    void insert(int value)
    {
        std::unique_ptr<Node>* n = &head;
        while (*n && (*n)->value < value)
        {
            n = &(*n)->next;
        }
        *n = std::make_unique<Node>(value, std::move(*n));
    }

    void remove(int value)
    {
        std::unique_ptr<Node>* n = &head;
        while (*n)
        {
            if ((*n)->value == value)
                *n = std::move((*n)->next);
            else
                n = &(*n)->next;
        }
    }
};

void fill(SortedLinkedList& list, const std::vector<int>& v)
{
    for (std::size_t i = 0; i < v.size(); ++i)
    {
        list.insert(v[i]);
    }
}

int main(int argc, char** argv)
{
    SortedLinkedList list;

    if (argc == 1)
    {
        std::vector<int> values = {1, 2, 0, 3, -1, 2};
        std::cout << "Filling list with dummy data ..." << std::endl;
        fill(list, values);
    }
    else
    {
        std::cout << "Reading list from argv[]" << std::endl;
        std::vector<int> values;
        for (int i = 1; i < argc; ++i) values.push_back(std::stoi(argv[i]));
        fill(list, values);
    }

    list.print();
    list.remove(2);
    list.print();
    return 0;
}
