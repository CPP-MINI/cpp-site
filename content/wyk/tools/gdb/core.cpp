#include <string>
#include <memory>
#include <iostream>

struct Node
{
    std::string text;
    std::unique_ptr<Node> next;

    Node(std::string text, std::unique_ptr<Node> next) : text{text}, next{std::move(next)}
    {
    }
};

using UNode = std::unique_ptr<Node>;

UNode prepend(UNode head, std::string text)
{
    return std::make_unique<Node>(text, std::move(head));
}

UNode append(UNode head, std::string text)
{
    if (!head) return std::make_unique<Node>(text, nullptr);
    Node* h = head.get();
    while (h->next)
    {
        h = h->next.get();
    }
    h->next = std::make_unique<Node>(text, nullptr);
    return head;
}

UNode make_list(int argc, char* argv[])
{
    std::unique_ptr<Node> head = nullptr;
    for (int i = argc - 1; i > 0; --i)
    {
        head = prepend(std::move(head), argv[i]);
    }
    return head;
}

UNode load_from_stdin()
{
    std::string line;
    std::unique_ptr<Node> head;
    while (std::cin >> line)
    {
        if (line == ".") break;
        head = append(std::move(head), line);
    }
    return head;
}

Node* find(Node* head, std::string text)
{
    while (head->text != text)
    {
        head = head->next.get();
    }
    return head;
}

void print(Node* head)
{
    while (head)
    {
        std::cout << head->text << " ";
        head = head->next.get();
    }
    std::cout << std::endl;
}

int main(int argc, char* argv[])
{
    std::unique_ptr<Node> head;
    if (argc > 1)
        head = make_list(argc, argv);
    else
        head = load_from_stdin();
    print(head.get());
    Node* n = find(head.get(), "hello");
    n->text = "hey";
    print(head.get());
    return 0;
}
