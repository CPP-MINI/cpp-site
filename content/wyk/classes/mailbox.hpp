#ifndef MAILBOX_HPP
#define MAILBOX_HPP

#include <vector>
#include <string>

class Mailbox
{
private:
    std::vector<std::string> messages;

public:
    void post(const std::string& message);
    std::string get();

    [[nodiscard]] std::size_t size() const { return messages.size(); }
    [[nodiscard]] bool empty() const { return messages.empty(); }
};

#endif