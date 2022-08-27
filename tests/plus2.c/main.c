/* SPDX-License-Identifier: MIT */
// gcc -shared -O2 -o plus2.dll  main.c -fPIC

int sum(const int x, const int y) {
    return x + y;
}

// gcc -O2 -o main.exe  main.c
// ./main.exe
int main() {
    int x = 1, y = 2, z = -1;
    z = sum(x, y);

    return !(3 == z);
}
