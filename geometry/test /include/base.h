#ifndef BASE_H
#define BASE_H

using namespace std;

class Base {
   public:
    Base();

    void print();

   protected:
    virtual void name();
};

#endif