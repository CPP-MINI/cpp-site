int acc = 0;

void add(int* ptr) {
       acc += *ptr;
       delete ptr;
}

int main() {
    int a = 0;
    int* b = new int{3};
    add(&a);
    add(b);
    return 0;
}
