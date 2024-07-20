
#ifndef LS_MATH_QUAT_H
#define LS_MATH_QUAT_H

#include "lightsky/math/fixed.h"

namespace ls {
namespace math {

struct half;



/**
 *  @brief Quaternion Structure
 *
 *  Recommended for use with non-integral types
 *
 *  @note
 *  Indexing is as follows:
 *      0 = X
 *      1 = Y
 *      2 = Z
 *      3 = W   (real component)
 */
template <typename num_t>
struct alignas(sizeof(num_t)) quat_t
{
    // data
    num_t q[4];

    ~quat_t() = default;

    constexpr quat_t() = default;
    constexpr quat_t(num_t inX, num_t inY, num_t inZ, num_t inW);
    constexpr quat_t(num_t xyz, num_t w);

    quat_t(const quat_t<num_t>&) = default;
    quat_t(quat_t<num_t>&&) = default;

    // Conversions & Casting
    template <typename other_t>
    inline explicit operator quat_t<other_t>() const;

    constexpr const num_t* operator&() const;
    inline num_t* operator&();

    // Subscripting Operators
    template <typename index_t>
    constexpr num_t operator[](index_t i) const;

    template <typename index_t>
    inline num_t& operator[](index_t i);

    //quaternion-quaternion operators
    quat_t& operator++(); //prefix operators
    quat_t& operator--();
    quat_t operator++(int); //postfix operators
    quat_t operator--(int);
    constexpr quat_t operator-() const;
    constexpr quat_t operator+(const quat_t<num_t>& input) const;
    constexpr quat_t operator-(const quat_t<num_t>& input) const;
    constexpr quat_t operator*(const quat_t<num_t>& input) const;
    quat_t& operator=(const quat_t<num_t>&) = default;
    quat_t& operator=(quat_t<num_t>&&) = default;
    quat_t& operator+=(const quat_t<num_t>& input);
    quat_t& operator-=(const quat_t<num_t>& input);
    quat_t& operator*=(const quat_t<num_t>& input);
    constexpr bool operator==(const quat_t<num_t>& input) const;
    constexpr bool operator!=(const quat_t<num_t>& input) const;

    //quaternion-scalar operators
    constexpr quat_t operator+(num_t) const;
    constexpr quat_t operator-(num_t) const;
    constexpr quat_t operator*(num_t) const;
    constexpr quat_t operator/(num_t) const;
    quat_t& operator=(num_t);
    quat_t& operator+=(num_t);
    quat_t& operator-=(num_t);
    quat_t& operator*=(num_t);
    quat_t& operator/=(num_t);
};

/*-------------------------------------
    Non-Member Quaternion-Scalar operations
-------------------------------------*/
template <typename num_t> constexpr
quat_t<num_t> operator+(num_t n, const quat_t<num_t>& q);

template <typename num_t> constexpr
quat_t<num_t> operator-(num_t n, const quat_t<num_t>& q);

template <typename num_t> constexpr
quat_t<num_t> operator*(num_t n, const quat_t<num_t>& q);

/*-------------------------------------
    Quaternion Template Specializations
-------------------------------------*/
typedef quat_t<half>     quath;
typedef quat_t<float>    quatf;
typedef quat_t<double>   quatd;
typedef quat_t<int>      quati;
typedef quat_t<unsigned> quatu;
typedef quat_t<medp_t>   quatx;

typedef quat_t<float> quat;

} //end math namespace
} //end ls namespace

#include "lightsky/math/generic/quat_impl.h"

#endif /* LS_MATH_QUAT_H */
