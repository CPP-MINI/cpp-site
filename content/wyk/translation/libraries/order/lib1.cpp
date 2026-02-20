#include "lib1.hpp"
#include "lib2.hpp"

namespace lib1 {
void foo() {
    lib2::foo();
}
}
