#include <iostream>
#include <vector>
#include <string>

class Mailbox
{
private:
    std::vector<std::string> messages;

public:
    void post(const std::string& message)
    {
        messages.push_back(message);
    }

    std::string get()
    {
        if (messages.empty())
        {
            return "";
        }

        std::string message = messages.front();
        messages.erase(messages.begin());
        return message;
    }

    [[nodiscard]] std::size_t size() const
    {
        return messages.size();
    }

    [[nodiscard]] bool empty() const
    {
        return messages.empty();
    }
};

int main()
{
    Mailbox box;

    box.post("Hello, my name is Adam. Nice to meet You");
    box.post("Hey, wanna buy some crypto?");
    box.post("I'm looking for a good deal. Call me");

    while (!box.empty())
    {
        std::string msg = box.get();
        std::cout << "Received message: \"" << msg << "\"\n";
    }

    return 0;
}