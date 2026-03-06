int* foo() {
     int x = 0;
     return &x;
}

int main() {
    int* ptr = foo();
    *ptr = 1;
    return 0;
}
