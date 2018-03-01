#include <algorithm>
#include <functional>
#include <iostream>
#include <map>
#include <unordered_map>
#include <vector>

#include <unistd.h> // getpid

#include "include/HashCode.hpp"
using namespace std;

struct Input {
    int n, m;

    Input(std::ifstream in) {
        in >> n;
        in >> m;
    }

    Input() { }
} input;


struct Output : BaseOutput {
    int x, y;

    Output() {
        x = rand() % 10000000;
        y = rand() % 10000000;
    }

    double Cost() {
        return x + y;
    }

    void Dump(ostream& out) {
        out << x << ' ' << y << '\n';
    }
};

int main(int argc, char** argv) {
    srand(time(0) + getpid());
    InitHashCode(argc, argv);
    input = Input(GetInputStream());

    vector<int> x = {10, 40, 30, 20};
    vector<int> y = {35, 25, 15, 45};

    Sort(x);
    Sort(y);
    auto p = Range(10);
    Debug(x, y, p);

    for (int i = 0; i < 10; i +=1 ) {
        Output o;
        Dump(o);
    }
}
