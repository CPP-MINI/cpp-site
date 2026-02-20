void add(int* acc, int* ptr) {
       *ptr = 0;
       delete ptr;
}

int main() {
    int acc = 0;
    int* ptr = new int{3};
    add(&acc, ptr);
    add(&acc, ptr);
    return 0;
}
