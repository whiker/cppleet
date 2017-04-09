#include <iostream>

using namespace std;

namespace Practice {

void sizeofType() {
    cout << "sizeof type" << endl;
    cout << " unsigned: " << sizeof(unsigned) << endl;
    cout << "     long: " << sizeof(long) << endl;
    cout << "long long: " << sizeof(long long) << endl;
}

void printMemory(const void *src, int size) {
    static char charMap[] = "0123456789ABCDEF\n";
    cout << "MEM:";
    const unsigned char *p = (const unsigned char *) src;
    if (p && size > 0) {
        for (; size > 0; --size, ++p) {
            cout << ' ' << charMap[(*p & 0xF0) >> 4] << charMap[*p & 0x0F];
        }
    }
    cout << endl;
}

void printMemoryTest() {
    int i = 8 + (7 << 4) + (10 << 8) + (9 << 12) + (12 << 16) + (11 << 20);
    printMemory(&i, sizeof(i));
}

void test() {
    typedef void (*Func)();
    Func funcs[] = {sizeofType, printMemoryTest};
    for (auto f: funcs) {
        f();
        cout << endl;
    }
}

}