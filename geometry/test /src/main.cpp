#include "../include/base.h"
#include "../include/derived.h"

using namespace std;

int main() {
    Base base;
    Derived derived;
    base.print();
    derived.print();
}