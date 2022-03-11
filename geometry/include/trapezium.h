#ifndef TRAPEZIUM_H
#define TRAPEZIUM_H

#include "polygon.h"
#include "segment.h"

#define POINT_COUNT 4

class Trapezium : public Polygon {
   public:
    /**
     * @brief Construct a new Trapezium object
     *
     */
    Trapezium();

    /**
     * @brief Construct a new Trapezium object from two Segments
     *
     * @param a
     * @param b
     */
    Trapezium(Segment a, Segment b);

    /**
     * @brief Construct a new Trapezium object from first 4 Points of line
     *
     * @param line
     */
    Trapezium(Line *line);

   protected:
    /**
     * @brief true if it's done
     *
     * @return true
     * @return false
     */
    virtual bool is_done() override;

    /**
     * @brief true if it's validated
     *
     * @return true
     * @return false
     */
    virtual bool validate() override;
};

#endif