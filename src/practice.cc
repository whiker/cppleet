#include <iostream>
#include <vector>
#include <algorithm>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <chrono>

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

// 重载ostream的操作符"<<"
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

int functionStaticVarInitNum = 0;
std::mutex functionStaticVarInitNumMutex;

int functionStaticVar(int param) {
    static int var = [] (int param) -> int {
        // pthread_once
        int num;
        {
            std::lock_guard<std::mutex> guard(functionStaticVarInitNumMutex);
            num = ++functionStaticVarInitNum;
        }
        return num + param;
    }(param);
    return var;
}

void testfunctionStaticVarInitNumtaticVar() {
    std::mutex mtx;
    std::condition_variable cond;
    auto waitStart = std::chrono::high_resolution_clock::now();
    auto test = [&mtx, &cond, &waitStart] (int param) {
        {
            std::unique_lock<std::mutex> lock(mtx);
            cond.wait(lock);
        }
        auto waitEnd = std::chrono::high_resolution_clock::now();
        functionStaticVar(param);
        cout << param << "> wait: " << (waitEnd - waitStart).count() << endl;
    };

    const int ThreadNum = 4;
    std::thread* ths[ThreadNum];
    for (int i = 0; i < ThreadNum; ++i) {
        ths[i] = new std::thread(test, i + 1);
    }

    std::this_thread::sleep_for(std::chrono::seconds(2));
    cond.notify_all();

    for (int i = 0; i < ThreadNum; ++i) {
        ths[i]->join();
        delete ths[i];
    }
    cout << "init num: " << functionStaticVarInitNum << endl;
    cout << "var: " << functionStaticVar(0) << endl;
}

void test() {
    typedef void (*Func)();
    Func funcs[] = {
        sizeofType, printMemoryTest, compareAndSortVector,
        testfunctionStaticVarInitNumtaticVar
    };
    for (auto f: funcs) {
        f();
        cout << endl;
    }
}

}