
#ifndef LS_MATH_VEC2_IMPL_H
#define LS_MATH_VEC2_IMPL_H

#include "lightsky/setup/Api.h" // LS_INLINE

namespace ls {
namespace math {

/*-------------------------------------
    Constructors
-------------------------------------*/
// Main Constructor
template <typename num_t>
constexpr LS_INLINE vec2_t<num_t>::vec2_t(num_t inX, num_t inY) :
    v{inX, inY}
{
}

/*
template <typename num_t>
constexpr LS_INLINE vec2_t<num_t>::vec2_t() :
    v{num_t(0), num_t(0)}
{
}
*/

template <typename num_t>
constexpr LS_INLINE vec2_t<num_t>::vec2_t(num_t n) :
    v{n, n}
{
}

/*
template <typename num_t>
constexpr LS_INLINE vec2_t<num_t>::vec2_t(const vec2_t<num_t>& v) :
    v{v.v[0], v.v[1]}
{
}

template <typename num_t>
constexpr LS_INLINE vec2_t<num_t>::vec2_t(vec2_t<num_t>&& v) :
    v{v.v[0], v.v[1]}
{
}
*/

/*-------------------------------------
    Conversions & Casting
-------------------------------------*/
template <typename num_t>
template <typename other_t>
constexpr LS_INLINE vec2_t<num_t>::operator vec2_t<other_t>() const {
    return vec2_t<other_t>{(other_t) v[0], (other_t) v[1]};
}

template <typename num_t>
constexpr LS_INLINE const num_t* vec2_t<num_t>::operator&() const {
    return v;
}

template <typename num_t>
inline LS_INLINE num_t* vec2_t<num_t>::operator&() {
    return v;
}

/*-------------------------------------
    Subscripting Operators
-------------------------------------*/
template <typename num_t>
template <typename index_t>
constexpr LS_INLINE num_t vec2_t<num_t>::operator[](index_t i) const {
    return v[i];
}

template <typename num_t>
template <typename index_t>
inline LS_INLINE num_t& vec2_t<num_t>::operator[](index_t i) {
    return v[i];
}

/*-------------------------------------
    Vector-Vector Math Operations
-------------------------------------*/
template <typename num_t> constexpr LS_INLINE
vec2_t<num_t> vec2_t<num_t>::operator+(const vec2_t<num_t>& input) const {
    return vec2_t<num_t>{
        v[0] + input.v[0],
        v[1] + input.v[1]
    };
}

template <typename num_t> constexpr LS_INLINE
vec2_t<num_t> vec2_t<num_t>::operator-(const vec2_t<num_t>& input) const {
    return vec2_t<num_t>{
        v[0] - input.v[0],
        v[1] - input.v[1]
    };
}

//for operations like "vectA = -vectB"

template <typename num_t> constexpr LS_INLINE
vec2_t<num_t> vec2_t<num_t>::operator-() const {
    return vec2_t<num_t>{-v[0], -v[1]};
}

template <typename num_t> constexpr LS_INLINE
vec2_t<num_t> vec2_t<num_t>::operator*(const vec2_t<num_t>& input) const {
    return vec2_t<num_t>{
        v[0] * input.v[0],
        v[1] * input.v[1]
    };
}

template <typename num_t> constexpr LS_INLINE
vec2_t<num_t> vec2_t<num_t>::operator/(const vec2_t<num_t>& input) const {
    return vec2_t<num_t>{
        v[0] / input.v[0],
        v[1] / input.v[1]
    };
}

template <typename num_t> inline LS_INLINE
vec2_t<num_t>& vec2_t<num_t>::operator+=(const vec2_t<num_t>& input) {
    v[0] += input.v[0];
    v[1] += input.v[1];
    return *this;
}

/*
template <typename num_t> inline LS_INLINE
vec2_t<num_t>& vec2_t<num_t>::operator=(const vec2_t<num_t>& input) {
    v[0] = input.v[0];
    v[1] = input.v[1];
    return *this;
}

template <typename num_t> inline LS_INLINE
vec2_t<num_t>& vec2_t<num_t>::operator=(vec2_t<num_t>&& input) {
    v[0] = input.v[0];
    v[1] = input.v[1];
    return *this;
}
*/

template <typename num_t> inline LS_INLINE
vec2_t<num_t>& vec2_t<num_t>::operator-=(const vec2_t<num_t>& input) {
    v[0] -= input.v[0];
    v[1] -= input.v[1];
    return *this;
}

template <typename num_t> inline LS_INLINE
vec2_t<num_t>& vec2_t<num_t>::operator*=(const vec2_t<num_t>& input) {
    v[0] *= input.v[0];
    v[1] *= input.v[1];
    return *this;
}

template <typename num_t> inline LS_INLINE
vec2_t<num_t>& vec2_t<num_t>::operator/=(const vec2_t<num_t>& input) {
    v[0] /= input.v[0];
    v[1] /= input.v[1];
    return *this;
}

// prefix operations

template <typename num_t> inline LS_INLINE
vec2_t<num_t>& vec2_t<num_t>::operator++() {
    ++v[0];
    ++v[1];
    return *this;
}

template <typename num_t> inline LS_INLINE
vec2_t<num_t>& vec2_t<num_t>::operator--() {
    --v[0];
    --v[1];
    return *this;
}
//postfix operations

template <typename num_t> inline LS_INLINE
vec2_t<num_t> vec2_t<num_t>::operator++(int) {
    return vec2_t<num_t>{
        ++v[0],
        ++v[1]
    };
}

template <typename num_t> inline LS_INLINE
vec2_t<num_t> vec2_t<num_t>::operator--(int) {
    return vec2_t<num_t>{
        --v[0],
        --v[1]
    };
}

//comparisons

template <typename num_t> constexpr LS_INLINE
bool vec2_t<num_t>::operator==(const vec2_t<num_t>& compare) const {
    return
    v[0] == compare.v[0] &&
        v[1] == compare.v[1];
}

template <typename num_t> constexpr LS_INLINE
bool vec2_t<num_t>::operator!=(const vec2_t<num_t>& compare) const {
    return
    v[0] != compare.v[0] ||
        v[1] != compare.v[1];
}

template <typename num_t> constexpr LS_INLINE
bool vec2_t<num_t>::operator<(const vec2_t<num_t>& compare) const {
    return
    v[0] < compare.v[0] &&
        v[1] < compare.v[1];
}

template <typename num_t> constexpr LS_INLINE
bool vec2_t<num_t>::operator>(const vec2_t<num_t>& compare) const {
    return
    v[0] > compare.v[0] &&
        v[1] > compare.v[1];
}

template <typename num_t> constexpr LS_INLINE
bool vec2_t<num_t>::operator<=(const vec2_t<num_t>& compare) const {
    return
    v[0] <= compare.v[0] &&
        v[1] <= compare.v[1];
}

template <typename num_t> constexpr LS_INLINE
bool vec2_t<num_t>::operator>=(const vec2_t<num_t>& compare) const {
    return
    v[0] >= compare.v[0] &&
        v[1] >= compare.v[1];
}

/*-------------------------------------
    Vector-Scalar Math Operations
-------------------------------------*/
template <typename num_t> constexpr LS_INLINE
vec2_t<num_t> vec2_t<num_t>::operator-(num_t input) const {
    return vec2_t<num_t>{
        (num_t)(v[0] - input),
        (num_t)(v[1] - input)
    };
}

template <typename num_t> constexpr LS_INLINE
vec2_t<num_t> vec2_t<num_t>::operator*(num_t input) const {
    return vec2_t<num_t>{
        (num_t)(v[0] * input),
        (num_t)(v[1] * input)
    };
}

template <typename num_t> constexpr LS_INLINE
vec2_t<num_t> vec2_t<num_t>::operator/(num_t input) const {
    return vec2_t<num_t>{
        (num_t)(v[0] / input),
        (num_t)(v[1] / input)
    };
}

template <typename num_t> inline LS_INLINE
vec2_t<num_t> vec2_t<num_t>::operator=(num_t input) {
    v[0] = input;
    v[1] = input;
    return *this;
}

template <typename num_t> constexpr LS_INLINE
vec2_t<num_t> vec2_t<num_t>::operator+(num_t input) const {
    return vec2_t<num_t>{
        (num_t)(v[0] + input),
        (num_t)(v[1] + input)
    };
}

template <typename num_t> inline LS_INLINE
vec2_t<num_t>& vec2_t<num_t>::operator+=(num_t input) {
    v[0] += input;
    v[1] += input;
    return *this;
}

template <typename num_t> inline LS_INLINE
vec2_t<num_t>& vec2_t<num_t>::operator-=(num_t input) {
    v[0] -= input;
    v[1] -= input;
    return *this;
}

template <typename num_t> inline LS_INLINE
vec2_t<num_t>& vec2_t<num_t>::operator*=(num_t input) {
    v[0] *= input;
    v[1] *= input;
    return *this;
}

template <typename num_t> inline LS_INLINE
vec2_t<num_t>& vec2_t<num_t>::operator/=(num_t input) {
    v[0] /= input;
    v[1] /= input;
    return *this;
}

/*-------------------------------------
    Non-Member Vector-Scalar operations
-------------------------------------*/
template <typename num_t> constexpr LS_INLINE
vec2_t<num_t> operator+(num_t n, const vec2_t<num_t>& v) {
    return v + n;
}

template <typename num_t> constexpr LS_INLINE
vec2_t<num_t> operator-(num_t n, const vec2_t<num_t>& v) {
    return v - n;
}

template <typename num_t> constexpr LS_INLINE
vec2_t<num_t> operator*(num_t n, const vec2_t<num_t>& v) {
    return v * n;
}

} // end math namespace
} // end ls namespace

#endif /* LS_MATH_VEC2_IMPL_H */
