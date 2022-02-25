#ifndef MEMBER_H
#define MEMBER_H

class Member {
   public:
    /**
     * @brief Construct a new Member object
     *
     */
    Member();

    /**
     * @brief Construct a new Member object from k and pow
     *
     * @param k coefficient
     * @param pow power
     */
    Member(long double k, int pow);

    int pow;
    long double k;
};

#endif