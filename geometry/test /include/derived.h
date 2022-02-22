#ifndef DERIVED_H
#define DERIVED_H

#include "base.h"

class Derived : public Base {
   public:
    using Base::Base;

   protected:
    virtual void name() override;
};

#endif