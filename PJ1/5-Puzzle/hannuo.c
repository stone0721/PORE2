#include <stdio.h>

void move(int x, char from, char to) {
    printf("%c%c", from, to);
}

void hanoi(int n, char a, char b, char c) {
    if (n == 1) {
    move(1, a, c);
    } 
    else {
    hanoi(n - 1, a, c, b);
    move(n, a, c);
    hanoi(n - 1, b, a, c);
}

}

int main() {
    int n = 5;
    hanoi(n, '0', '1', '2');
    printf("\n");
    return 0;
}