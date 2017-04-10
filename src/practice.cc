#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

namespace Practice {

inline const char* boolToStr(bool b) {
    return b ? "true" : "false";
}

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

class Foo {
    friend ostream& operator << (ostream& out, const Foo &foo);

public:
    static bool equal(const Foo &f1, const Foo &f2) {
        return f1.foo == f2.foo;
    }

    static bool compare(const Foo &f1, const Foo &f2) {
        return f1.foo < f2.foo;
    }

public:
    Foo(int v): foo(v) {}

private:
    int foo;
};

ostream& operator << (ostream& out, const Foo &foo) {
    out << foo.foo;
    return out;
}

void compareAndSortVector() {
    vector<int> vec{3, 1, 2};
    Foo arr[] = {3, 1, 2};
    cout << boolToStr(equal(vec.begin(), vec.end(), arr, Foo::equal)) << endl;

    sort(vec.begin(), vec.end(), Foo::compare);
    cout << "{ ";
    for (const Foo &foo : vec) {
        cout << foo << " ";
    }
    cout << "}" << endl;
}

void test() {
    typedef void (*Func)();
    Func funcs[] = {sizeofType, printMemoryTest, compareAndSortVector};
    for (auto f: funcs) {
        f();
        cout << endl;
    }
}

}