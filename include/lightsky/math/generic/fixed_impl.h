
#ifndef LS_MATH_FIXED_IMPL_H
#define LS_MATH_FIXED_IMPL_H

#include "lightsky/math/scalar_utils.h"

namespace ls
{
namespace math
{

/*-----------------------------------------------------------------------------
    Fixed-Point Class Methods
-----------------------------------------------------------------------------*/
/*
 *  Destructor
 */
/*
template<typename fixed_base_t, unsigned num_frac_digits>
inline LS_INLINE fixed_t<fixed_base_t, num_frac_digits>::~fixed_t() noexcept
{
}
*/



/*
 *  Constructor (integral)
 */
/*
template<typename fixed_base_t, unsigned num_frac_digits>
constexpr LS_INLINE fixed_t<fixed_base_t, num_frac_digits>::fixed_t() noexcept :
    number{0}
{}
*/



/*
 *  Constructor (integral)
 */
template<typename fixed_base_t, unsigned num_frac_digits>
constexpr LS_INLINE fixed_t<fixed_base_t, num_frac_digits>::fixed_t(float n) noexcept :
    number{(fixed_base_t)(n * (float)(1ull << num_frac_digits))}
{}



/*
 *  Constructor (integral)
 */
template<typename fixed_base_t, unsigned num_frac_digits>
constexpr LS_INLINE fixed_t<fixed_base_t, num_frac_digits>::fixed_t(double n) noexcept :
    number{(fixed_base_t)(n * (double)(1ull << num_frac_digits))}
{}



/*
 *  Constructor (integral)
 */
template<typename fixed_base_t, unsigned num_frac_digits>
constexpr LS_INLINE fixed_t<fixed_base_t, num_frac_digits>::fixed_t(fixed_base_t n, bool useRawBits) noexcept :
    number{useRawBits
        ? n
        : (fixed_base_t)((unsigned long long)n << (unsigned long long)num_frac_digits)
    }
{}



/*
 *  Copy Constructor
 *
 */
/*
template<typename fixed_base_t, unsigned num_frac_digits>
constexpr LS_INLINE fixed_t<fixed_base_t, num_frac_digits>::fixed_t(const fixed_t& f) noexcept :
    number{f.number}
{}
*/



/*
 *  Move Constructor
 */
/*
template<typename fixed_base_t, unsigned num_frac_digits>
constexpr LS_INLINE fixed_t<fixed_base_t, num_frac_digits>::fixed_t(fixed_t&& f) noexcept :
    number{f.number}
{}
*/



/*
 *  Copy-Assignment operator
 */
/*
template <typename fixed_base_t, unsigned num_frac_digits>
inline LS_INLINE fixed_t<fixed_base_t, num_frac_digits>& fixed_t<fixed_base_t, num_frac_digits>::operator=(const fixed_t& f) noexcept
{
    number = f.number;
    return *this;
}
*/



/*
 *  Move-Assignment operator
 */
/*
template <typename fixed_base_t, unsigned num_frac_digits>
inline LS_INLINE fixed_t<fixed_base_t, num_frac_digits>& fixed_t<fixed_base_t, num_frac_digits>::operator=(fixed_t&& f) noexcept
{
    number = f.number;
    return *this;
}
*/



/*
 *  Pre-Increment operator
 */
template<typename fixed_base_t, unsigned num_frac_digits>
inline LS_INLINE fixed_t<fixed_base_t, num_frac_digits>& fixed_t<fixed_base_t, num_frac_digits>::operator++() noexcept
{
    number += (fixed_base_t)(1ull << num_frac_digits);
    return *this;
}



/*
 *  Pre-Decrement operator
 */
template<typename fixed_base_t, unsigned num_frac_digits>
inline LS_INLINE fixed_t<fixed_base_t, num_frac_digits>& fixed_t<fixed_base_t, num_frac_digits>::operator--() noexcept
{
    number -= (fixed_base_t)(1ull << num_frac_digits);
    return *this;
}



/*
 *  Post-Increment operator
 */
template<typename fixed_base_t, unsigned num_frac_digits>
inline LS_INLINE fixed_t<fixed_base_t, num_frac_digits> fixed_t<fixed_base_t, num_frac_digits>::operator++(int) noexcept
{
    const fixed_t ret{number};
    number += (fixed_base_t)(1ull << num_frac_digits);
    return ret;
}



/*
 *  Post-Decrement operator
 */
template<typename fixed_base_t, unsigned num_frac_digits>
inline LS_INLINE fixed_t<fixed_base_t, num_frac_digits> fixed_t<fixed_base_t, num_frac_digits>::operator--(int) noexcept
{
    const fixed_t ret{number};
    number -= (fixed_base_t)(1ull << num_frac_digits);
    return ret;
}



/*
 *  Arithmetic "not" operator.
 */
template<typename fixed_base_t, unsigned num_frac_digits>
constexpr LS_INLINE bool fixed_t<fixed_base_t, num_frac_digits>::operator!() const noexcept
{
    return !number;
}



/*
 *  Equivalence operator
 */
template<typename fixed_base_t, unsigned num_frac_digits>
constexpr LS_INLINE bool fixed_t<fixed_base_t, num_frac_digits>::operator==(const fixed_t& f) const noexcept
{
    return number == f.number;
}



/*
 *  Non-Equivalence operator
 */
template<typename fixed_base_t, unsigned num_frac_digits>
constexpr LS_INLINE bool fixed_t<fixed_base_t, num_frac_digits>::operator!=(const fixed_t& f) const noexcept
{
    return number != f.number;
}



/*
 *  Greater than or equal to operator.
 */
template<typename fixed_base_t, unsigned num_frac_digits>
constexpr LS_INLINE bool fixed_t<fixed_base_t, num_frac_digits>::operator>=(const fixed_t& f) const noexcept
{
    return number >= f.number;
}



/*
 *  Less than or equal to operator.
 */
template<typename fixed_base_t, unsigned num_frac_digits>
constexpr LS_INLINE bool fixed_t<fixed_base_t, num_frac_digits>::operator<=(const fixed_t& f) const noexcept
{
    return number <= f.number;
}



/*
 *  Greater than operator.
 */
template<typename fixed_base_t, unsigned num_frac_digits>
constexpr LS_INLINE bool fixed_t<fixed_base_t, num_frac_digits>::operator>(const fixed_t& f) const noexcept
{
    return number > f.number;
}



/*
 *  Less than operator.
 */
template<typename fixed_base_t, unsigned num_frac_digits>
constexpr LS_INLINE bool fixed_t<fixed_base_t, num_frac_digits>::operator<(const fixed_t& f) const noexcept
{
    return number < f.number;
}



/*
 *  Addition operator
 */
template<typename fixed_base_t, unsigned num_frac_digits>
constexpr LS_INLINE fixed_t<fixed_base_t, num_frac_digits> fixed_t<fixed_base_t, num_frac_digits>::operator+(const fixed_t& f) const noexcept
{
    return fixed_t{number + f.number, true};
}



/*
 *  Subtraction operator
 */
template<typename fixed_base_t, unsigned num_frac_digits>
constexpr LS_INLINE fixed_t<fixed_base_t, num_frac_digits> fixed_t<fixed_base_t, num_frac_digits>::operator-(const fixed_t& f) const noexcept
{
    return fixed_t{number - f.number, true};
}



/*
 *  Negation operator
 */
template<typename fixed_base_t, unsigned num_frac_digits>
constexpr LS_INLINE fixed_t<fixed_base_t, num_frac_digits> fixed_t<fixed_base_t, num_frac_digits>::operator-() const noexcept
{
    return fixed_t{(~number + fixed_base_t{1}), true};
}



/*
 *  Multiplication operator
 */
template<typename fixed_base_t, unsigned num_frac_digits>
constexpr LS_INLINE fixed_t<fixed_base_t, num_frac_digits> fixed_t<fixed_base_t, num_frac_digits>::operator*(const fixed_t& f) const noexcept
{
    return fixed_t{
        (ls::setup::IsUnsigned<fixed_base_t>::value
            ? (fixed_base_t)(((uint64_t)number * (uint64_t)f.number) >> ((uint64_t)num_frac_digits))
            : (fixed_base_t)(((int64_t)number * (int64_t)f.number) / (1ll << (int64_t)num_frac_digits))),
        true
    };
}



/*
 *  Division operator
 */
template<typename fixed_base_t, unsigned num_frac_digits>
constexpr LS_INLINE fixed_t<fixed_base_t, num_frac_digits> fixed_t<fixed_base_t, num_frac_digits>::operator/(const fixed_t& f) const noexcept
{
    return fixed_t{
        (ls::setup::IsUnsigned<fixed_base_t>::value
            ? (fixed_base_t)(((uint64_t)number * (1ull << (uint64_t)num_frac_digits) / (uint64_t)f.number))
            : (fixed_base_t)(((int64_t)number * (1ll << (int64_t)num_frac_digits) / (int64_t)f.number))),
        true
    };
}



/*
 *  Modulus operator
 */
template<typename fixed_base_t, unsigned num_frac_digits>
constexpr LS_INLINE fixed_t<fixed_base_t, num_frac_digits> fixed_t<fixed_base_t, num_frac_digits>::operator%(const fixed_t& f) const noexcept
{
    return fixed_t{number % f.number, true};
}



/*
 *  Logical AND operator
 */
template<typename fixed_base_t, unsigned num_frac_digits>
constexpr LS_INLINE fixed_t<fixed_base_t, num_frac_digits> fixed_t<fixed_base_t, num_frac_digits>::operator&(const fixed_t& f) const noexcept
{
    return fixed_t{number & f.number, true};
}



/*
 *  Logical OR operator
 */
template<typename fixed_base_t, unsigned num_frac_digits>
constexpr LS_INLINE fixed_t<fixed_base_t, num_frac_digits> fixed_t<fixed_base_t, num_frac_digits>::operator|(const fixed_t& f) const noexcept
{
    return fixed_t{number | f.number, true};
}



/*
 *  Logical XOR operator
 */
template<typename fixed_base_t, unsigned num_frac_digits>
constexpr LS_INLINE fixed_t<fixed_base_t, num_frac_digits> fixed_t<fixed_base_t, num_frac_digits>::operator^(const fixed_t& f) const noexcept
{
    return fixed_t{number ^ f.number, true};
}



/*
 *  Logical NOT operator
 */
template<typename fixed_base_t, unsigned num_frac_digits>
constexpr LS_INLINE fixed_t<fixed_base_t, num_frac_digits> fixed_t<fixed_base_t, num_frac_digits>::operator~() const noexcept
{
    return fixed_t{~number, true};
}



/*
 *  Shift-Right operator
 */
template<typename fixed_base_t, unsigned num_frac_digits>
template <typename integral_type>
constexpr LS_INLINE fixed_t<fixed_base_t, num_frac_digits> fixed_t<fixed_base_t, num_frac_digits>::operator>>(typename setup::EnableIf<setup::IsIntegral<integral_type>::value, integral_type>::type n) const noexcept
{
    return fixed_t{number >> (fixed_base_t)n, true};
}



/*
 *  Shift-Left operator
 */
template<typename fixed_base_t, unsigned num_frac_digits>
template <typename integral_type>
constexpr LS_INLINE fixed_t<fixed_base_t, num_frac_digits> fixed_t<fixed_base_t, num_frac_digits>::operator<<(typename setup::EnableIf<setup::IsIntegral<integral_type>::value, integral_type>::type n) const noexcept
{
    return fixed_t{number << (fixed_base_t)n, true};
}



/*
 *  Addition-Assignment operator
 */
template<typename fixed_base_t, unsigned num_frac_digits>
inline LS_INLINE fixed_t<fixed_base_t, num_frac_digits>& fixed_t<fixed_base_t, num_frac_digits>::operator+=(const fixed_t& f) noexcept
{
    number += f.number;
    return *this;
}



/*
 *  Subtraction-Assignment operator
 */
template<typename fixed_base_t, unsigned num_frac_digits>
inline LS_INLINE fixed_t<fixed_base_t, num_frac_digits>& fixed_t<fixed_base_t, num_frac_digits>::operator-=(const fixed_t& f) noexcept
{
    number -= f.number;
    return *this;
}



/*
 *  Multiplication-Assignment operator
 */
template<typename fixed_base_t, unsigned num_frac_digits>
inline LS_INLINE fixed_t<fixed_base_t, num_frac_digits>& fixed_t<fixed_base_t, num_frac_digits>::operator*=(const fixed_t& f) noexcept
{
    number = ls::setup::IsUnsigned<fixed_base_t>::value
        ? (fixed_base_t)(((uint64_t)number * (uint64_t)f.number) >> ((uint64_t)num_frac_digits))
        : (fixed_base_t)(((int64_t)number * (int64_t)f.number) / (1ll << (int64_t)num_frac_digits));
    return *this;
}



/*
 *  Division-Assignment operator
 */
template<typename fixed_base_t, unsigned num_frac_digits>
inline LS_INLINE fixed_t<fixed_base_t, num_frac_digits>& fixed_t<fixed_base_t, num_frac_digits>::operator/=(const fixed_t& f) noexcept
{
    number = ls::setup::IsUnsigned<fixed_base_t>::value
        ? (fixed_base_t)(((uint64_t)number * (1ull << (uint64_t)num_frac_digits) / (uint64_t)f.number))
        : (fixed_base_t)(((int64_t)number * (1ll << (int64_t)num_frac_digits) / (int64_t)f.number));
    return *this;
}



/*
 *  Modulo-Assignment operator
 */
template<typename fixed_base_t, unsigned num_frac_digits>
inline LS_INLINE fixed_t<fixed_base_t, num_frac_digits>& fixed_t<fixed_base_t, num_frac_digits>::operator%=(const fixed_t& f) noexcept
{
    number %= f.number;
    return *this;
}



/*
 *  Logical AND-Assignment operator
 */
template<typename fixed_base_t, unsigned num_frac_digits>
inline LS_INLINE fixed_t<fixed_base_t, num_frac_digits>& fixed_t<fixed_base_t, num_frac_digits>::operator&=(const fixed_t& f) noexcept
{
    number &= f.number;
    return *this;
}



/*
 *  Logical OR-Assignment operator
 */
template<typename fixed_base_t, unsigned num_frac_digits>
inline LS_INLINE fixed_t<fixed_base_t, num_frac_digits>& fixed_t<fixed_base_t, num_frac_digits>::operator|=(const fixed_t& f) noexcept
{
    number |= f.number;
    return *this;
}



/*
 *  Logical XOR-Assignment operator
 */
template<typename fixed_base_t, unsigned num_frac_digits>
inline LS_INLINE fixed_t<fixed_base_t, num_frac_digits>& fixed_t<fixed_base_t, num_frac_digits>::operator^=(const fixed_t& f) noexcept
{
    number ^= f.number;
    return *this;
}



/*
 *  Shift-Right and Assign operator
 */
template<typename fixed_base_t, unsigned num_frac_digits>
template <typename integral_type>
inline LS_INLINE fixed_t<fixed_base_t, num_frac_digits>& fixed_t<fixed_base_t, num_frac_digits>::operator>>=(typename setup::EnableIf<setup::IsIntegral<integral_type>::value, integral_type>::type n) noexcept
{
    number >>= (fixed_base_t)n;
    return *this;
}



/*
 *  Shift-Left and Assign operator
 */
template<typename fixed_base_t, unsigned num_frac_digits>
template <typename integral_type>
inline LS_INLINE fixed_t<fixed_base_t, num_frac_digits>& fixed_t<fixed_base_t, num_frac_digits>::operator<<=(typename setup::EnableIf<setup::IsIntegral<integral_type>::value, integral_type>::type n) noexcept
{
    number <<= (fixed_base_t)n;
    return *this;
}



/*
 *  Single-Precision floating-point cast.
 */
template<typename fixed_base_t, unsigned num_frac_digits>
constexpr LS_INLINE fixed_t<fixed_base_t, num_frac_digits>::operator float() const noexcept
{
    return ls::math::float_cast<float>(*this);
}



/*
 *  Double-Precision floating-point cast.
 */
template<typename fixed_base_t, unsigned num_frac_digits>
constexpr LS_INLINE fixed_t<fixed_base_t, num_frac_digits>::operator double() const noexcept
{
    return ls::math::float_cast<double>(*this);
}



/*
 *  Numeric cast.
 */
template<typename fixed_base_t, unsigned num_frac_digits>
constexpr LS_INLINE fixed_t<fixed_base_t, num_frac_digits>::operator fixed_base_t() const noexcept
{
    return ls::math::integer_cast<fixed_base_t>(*this);
}



/*-----------------------------------------------------------------------------
    Fixed-Point Utility Functions
-----------------------------------------------------------------------------*/
} //end math namespace

/*-------------------------------------
    Float to Fixed-Point Representation
-------------------------------------*/
template <class fixed_type, typename numeric_t>
constexpr math::fixed_t<typename fixed_type::base_type, fixed_type::fraction_digits> math::fixed_cast(
    const typename setup::EnableIf<setup::IsFloat<numeric_t>::value, numeric_t>::type& n
) noexcept
{
    return math::fixed_t<typename fixed_type::base_type, fixed_type::fraction_digits>{n};
}



/*-------------------------------------
    Int to Fixed-Point Representation
-------------------------------------*/
template <class fixed_type, typename numeric_t>
constexpr math::fixed_t<typename fixed_type::base_type, fixed_type::fraction_digits> math::fixed_cast(
    const typename setup::EnableIf<setup::IsIntegral<numeric_t>::value, numeric_t>::type& n
) noexcept
{
    return math::fixed_t<typename fixed_type::base_type, fixed_type::fraction_digits>{n, false};
}



/*-------------------------------------
    Fixed to Fixed-Point Representation
-------------------------------------*/
namespace math
{
namespace impl
{

template <unsigned fixed_shifts, unsigned other_shifts>
constexpr unsigned long long _fixed_shift_factor(typename ls::setup::EnableIf<(fixed_shifts >= other_shifts), unsigned>::type n) noexcept
{
    return n << (unsigned long long)(fixed_shifts - other_shifts);
}

template <unsigned fixed_shifts, unsigned other_shifts>
constexpr unsigned long long _fixed_shift_factor(typename ls::setup::EnableIf<(fixed_shifts < other_shifts), unsigned>::type n) noexcept
{
    return n << (unsigned long long)(other_shifts - fixed_shifts);
}

} // end impl namespace
} // end math namespace

template <class fixed_type, typename other_fixed_type>
constexpr math::fixed_t<typename fixed_type::base_type, fixed_type::fraction_digits> math::fixed_cast(
    const math::fixed_t<typename other_fixed_type::base_type, other_fixed_type::fraction_digits>& n
) noexcept
{
    return math::fixed_t<typename fixed_type::base_type, fixed_type::fraction_digits>{
        (typename fixed_type::base_type)((fixed_type::fraction_digits >= (typename fixed_type::base_type)other_fixed_type::fraction_digits)
            ? (typename fixed_type::base_type)((unsigned long long)n.number * impl::_fixed_shift_factor<fixed_type::fraction_digits, other_fixed_type::fraction_digits>(1))
            : (typename fixed_type::base_type)((unsigned long long)n.number / impl::_fixed_shift_factor<fixed_type::fraction_digits, other_fixed_type::fraction_digits>(1))
        ),
        true
    };
}



/*-------------------------------------
    Cast to Integer
-------------------------------------*/
template <typename integral_type, typename fixed_type>
constexpr integral_type math::integer_cast(const fixed_type& f)
{
    return (integral_type)(f.number >> fixed_type::fraction_digits);
}



/*-------------------------------------
    Cast to Float
-------------------------------------*/
template <typename float_type, class fixed_type>
constexpr float_type math::float_cast(const fixed_type& f)
{
    return (float_type)f.number / (float_type)(1ull << (unsigned long long)fixed_type::fraction_digits);
}



/*-------------------------------------
    abs
-------------------------------------*/
namespace fixed_impl
{
    template <typename data_t>
    constexpr LS_INLINE data_t abs_mask(data_t x, data_t mask) noexcept
    {
        return (x^mask) - mask;
    }

    template <typename data_t>
    constexpr LS_INLINE data_t abs_shift(data_t x) noexcept
    {
        return setup::IsUnsigned<data_t>::value ? x : fixed_impl::abs_mask<data_t>(x, x >> ((sizeof(data_t)*CHAR_BIT)-(data_t)1));
    }
}

template<typename fixed_base_t, unsigned num_frac_digits>
constexpr LS_INLINE math::fixed_t<fixed_base_t, num_frac_digits> math::abs(const math::fixed_t<fixed_base_t, num_frac_digits>& num) noexcept
{
    return (num.number >= 0)
        ? num
        : math::fixed_t<fixed_base_t, num_frac_digits>{fixed_impl::abs_shift<fixed_base_t>(num.number), true};
}



/*-------------------------------------
    rcp
-------------------------------------*/
template<typename fixed_base_t, unsigned num_frac_digits>
constexpr LS_INLINE math::fixed_t<fixed_base_t, num_frac_digits> math::rcp(const math::fixed_t<fixed_base_t, num_frac_digits>& num) noexcept
{
    return (num.number != 0)
        ? (math::fixed_cast<math::fixed_t<fixed_base_t, num_frac_digits>, fixed_base_t>(1) / num)
        : math::fixed_t<fixed_base_t, num_frac_digits>{~(fixed_base_t)0, true};
}



/*-------------------------------------
    sign
-------------------------------------*/
template<typename fixed_base_t, unsigned num_frac_digits>
constexpr LS_INLINE int math::sign_mask(const math::fixed_t<fixed_base_t, num_frac_digits>& x) noexcept
{
    return setup::IsSigned<fixed_base_t>::value ? (int)(x.number < 0) : 0;
}



/*-------------------------------------
    floor
-------------------------------------*/
template<typename fixed_base_t, unsigned num_frac_digits>
constexpr LS_INLINE math::fixed_t<fixed_base_t, num_frac_digits> math::floor(const math::fixed_t<fixed_base_t, num_frac_digits>& x) noexcept
{
    return math::fixed_t<fixed_base_t, num_frac_digits>{x.number & math::fixed_t<fixed_base_t, num_frac_digits>::integer_mask, true};
}



/*-------------------------------------
    floor
-------------------------------------*/
template<typename fixed_base_t, unsigned num_frac_digits>
constexpr LS_INLINE math::fixed_t<fixed_base_t, num_frac_digits> math::ceil(const math::fixed_t<fixed_base_t, num_frac_digits>& x) noexcept
{
    return math::floor<fixed_base_t, num_frac_digits>(math::fixed_t<fixed_base_t, num_frac_digits>{x.number + (fixed_base_t)(0x01ull * (1ull << (num_frac_digits-1ull))), true});
}



/*-------------------------------------
    round
-------------------------------------*/
template<typename fixed_base_t, unsigned num_frac_digits>
inline LS_INLINE math::fixed_t<fixed_base_t, num_frac_digits> math::round(const math::fixed_t<fixed_base_t, num_frac_digits>& x) noexcept
{
    constexpr math::fixed_t<fixed_base_t, num_frac_digits> pointFive{(fixed_base_t)(0x01ull * (1ull << (num_frac_digits - 1ull))), true};

    const math::fixed_t<fixed_base_t, num_frac_digits>&& lo = math::floor<fixed_base_t, num_frac_digits>(x);
    const math::fixed_t<fixed_base_t, num_frac_digits>&& hi = math::floor<fixed_base_t, num_frac_digits>(x + pointFive);

    return lo == hi ? lo : hi;
}



/*-------------------------------------
    fmod_1
-------------------------------------*/
template<typename fixed_base_t, unsigned num_frac_digits>
constexpr LS_INLINE math::fixed_t<fixed_base_t, num_frac_digits> math::fmod_1(const math::fixed_t<fixed_base_t, num_frac_digits>& x) noexcept
{
    return math::fixed_t<fixed_base_t, num_frac_digits>{
        (x.number - (x.number & math::fixed_t<fixed_base_t, num_frac_digits>::integer_mask)) - ((fixed_base_t)(x.number < 0) << num_frac_digits),
        true
    };
}



/*-------------------------------------
    fract
-------------------------------------*/
template<typename fixed_base_t, unsigned num_frac_digits>
constexpr LS_INLINE math::fixed_t<fixed_base_t, num_frac_digits> math::fract(const math::fixed_t<fixed_base_t, num_frac_digits>& n) noexcept
{
    return math::fixed_t<fixed_base_t, num_frac_digits>{n.number & math::fixed_t<fixed_base_t, num_frac_digits>::fraction_mask, true};
}



/*-------------------------------------
    sin
-------------------------------------*/
template<typename fixed_base_t, unsigned num_frac_digits>
inline LS_INLINE const math::fixed_t<fixed_base_t, num_frac_digits> math::sin(const math::fixed_t<fixed_base_t, num_frac_digits>& x) noexcept
{
    typedef ls::math::fixed_t<fixed_base_t, num_frac_digits> FixedType;
    return ls::math::impl::sincos_impl<FixedType>(ls::math::fmod_1<FixedType>(x / FixedType{LS_TWO_PI}), FixedType{1.0}, FixedType{0.5});
}



/*-------------------------------------
    cos
-------------------------------------*/
template<typename fixed_base_t, unsigned num_frac_digits>
inline LS_INLINE const math::fixed_t<fixed_base_t, num_frac_digits> math::cos(const math::fixed_t<fixed_base_t, num_frac_digits>& x) noexcept
{
    typedef ls::math::fixed_t<fixed_base_t, num_frac_digits> FixedType;
    return ls::math::impl::sincos_impl<FixedType>(ls::math::fmod_1<FixedType>(x / FixedType{LS_TWO_PI}), FixedType{0.5}, FixedType{0.25});
}



/*-------------------------------------
    tan
-------------------------------------*/
/*
template<typename fixed_base_t, unsigned num_frac_digits>
inline LS_INLINE const math::fixed_t<fixed_base_t, num_frac_digits> math::tan(const math::fixed_t<fixed_base_t, num_frac_digits>& x) noexcept
{
    const math::fixed_t<fixed_base_t, num_frac_digits>&& x2 = x*x;
    const math::fixed_t<fixed_base_t, num_frac_digits>&& x3 = x2*x;
    const math::fixed_t<fixed_base_t, num_frac_digits>&& x5 = x2*x3;
    const math::fixed_t<fixed_base_t, num_frac_digits>&& x7 = x2*x5;
    const math::fixed_t<fixed_base_t, num_frac_digits>&& x9 = x2*x7;

    return x
           + (x3 * math::fixed_t<fixed_base_t, num_frac_digits>{1.f / 3.f})
           + (x5 * math::fixed_t<fixed_base_t, num_frac_digits>{2.f / 15.f})
           + (x7 * math::fixed_t<fixed_base_t, num_frac_digits>{17.f / 315.f})
           + (x9 * math::fixed_t<fixed_base_t, num_frac_digits>{62.f / 2835.f});
}
*/



} //end ls namespace

#endif /* LS_MATH_FIXED_IMPL_H */
