#include <iostream>
#include <memory>

#include "Subtask.hpp"
#include "Task.hpp"

int main() {

    std::cout << "*************** PART 1 (Subtask) ***************\n\n";

    const Subtask s0("Go shopping");
    Subtask s1("Vacuum", 5);
    Subtask s2("Do the dishes", 10, true);
    s1.mark_completed();

    s0.print();
    s1.print();
    s2.print();

    std::cout << std::endl << "s0: completed=" << s0.is_completed() << ", priority=" << s0.get_priority() << std::endl;

    std::cout << "\n*************** PART 2 (Task - no copy/move) ***************\n\n";

    Task t1("Finish C++ project");
    t1.add_subtask(Subtask("Write the documentation"));
    t1.add_subtask(Subtask("Run tests", 5, true));
    t1.add_subtask(Subtask("Refactor the code", 3, false));
    const Subtask s4 = Subtask("Write a Makefile", 99, false);
    t1.add_subtask(s4);
    t1.print();

    t1.complete_subtask(0);
    t1.complete_subtask(0);
    t1.complete_subtask(3);
    t1.print();

    std::cout << std::endl;

    Task t2("Study algebra");
    t2.add_subtask(Subtask("Linear combinations", 10));
    t2.add_subtask(Subtask("Matrix multiplication", 11, true));
    t2.print();

    t2.clear();
    t2.print();

    std::cout << "\n*************** PART 3 (Task - copy/move) ***************\n\n";

    Task t_copy1(t1);
    std::cout << "Task copy (constructor):" << std::endl;
    t_copy1.print();

    Task t_copy2;
    t_copy2 = t1;
    std::cout << "\nTask copy (assignment):" << std::endl;
    t_copy1.print();

    Task t_move1(std::move(t_copy1));
    std::cout << "\nTask moved (constructor):" << std::endl;
    t_move1.print();

    Task t_move2;
    t_move2 = std::move(t_copy2);
    std::cout << "\nTask moved (assignment):" << std::endl;
    t_move2.print();

    return 0;
}
