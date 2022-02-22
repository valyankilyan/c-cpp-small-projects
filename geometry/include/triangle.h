#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "polygon.h"

class Triangle : public Polygon {
   public:
    using Polygon::Polygon;

    /**
     * @brief Returns true if triangle is done
     *
     * @return true
     * @return false
     */
    bool is_done();

   protected:
    /**
     * @brief Validates if operation went well
     *
     * @return true
     * @return false
     */
    virtual bool validate() override;
};

#endif