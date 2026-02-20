int main() {
    int* ptr = new int{3};
    *ptr = 0;
    delete ptr;
    *ptr = 1;
    return 0;
}
