#ifndef DERIVED_H
#define DERIVED_H

#include "base.h"

class Derived : public Base {
   protected:
    using Base::Base;

    virtual void name() override;
};

#endif