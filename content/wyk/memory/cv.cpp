#include <string>

void set(int* ptr) {
    *ptr = 30;
}

void setref(int& i) {
    i = 40;
}

int main() {
    const int x = 10;
    const int* cpx = &x;
    // int* p = &x; //! porzucenie const
    // int* px = cpx; //! porzucenie const
    // *cpx = 10; //! zapis do const
    // set(cpx); //! porzucenie const przy przekazaniu parametru
    // setref(*cpx); //! porzucenie const przy przekazaniu parametru

    const int& crx = x;
    // int& rx = x; //! porzucenie const
    // setref(crx); //! porzucenie const przy przekazaniu parametru

    int y = 20;
    int* py = &y;
    set(py);
    const int* cpy = &y;
    // set(cpy); //!
    const int& cry = y;
    // setref(cry); //!

    const std::string str = "Hello";
    char c = str[3]; // odczyt ok!
    // str[3] = 'a'; //! modyfikacja obiektu const
    std::size_t s = str.size(); // ok! .size() nie modyfikuje
    // str.append(" world"); //! modyfikacja obiektu const
}