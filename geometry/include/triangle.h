#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "polygon.h"

class Triangle : public Polygon {
   public:
    Triangle();

    Triangle(Line* l);

    /**
     * @brief Returns true if triangle is done
     *
     * @return true
     * @return false
     */
    virtual bool is_done() override;

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