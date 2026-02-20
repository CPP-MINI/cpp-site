#include "mailbox.hpp"

void Mailbox::post(const std::string& message)
{
    messages.push_back(message);
}

std::string Mailbox::get()
{
    if (messages.empty())
    {
        return "";
    }

    std::string message = messages.front();
    messages.erase(messages.begin());
    return message;
}
