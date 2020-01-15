
namespace ls
{
namespace math
{

/*-----------------------------------------------------------------------------
    Fixed-Point Class Methods
-----------------------------------------------------------------------------*/
/*
 *  Constructor
 */
/*
template<typename fixed_base_t, unsigned num_frac_digits>
constexpr LS_INLINE
fixed_t<fixed_base_t, num_frac_digits>::fixed_t() :
    number{}
{
}
*/



/*
 *  Copy Constructor
 *
 */
/*
template<typename fixed_base_t, unsigned num_frac_digits>
constexpr LS_INLINE
fixed_t<fixed_base_t, num_frac_digits>::fixed_t(const fixed_t& f) :
    number{f.number}
{
}
*/



/*
 *  Move Constructor
 */
/*
template<typename fixed_base_t, unsigned num_frac_digits>
constexpr LS_INLINE
fixed_t<fixed_base_t, num_frac_digits>::fixed_t(fixed_t&& f) :
    number{f.number}
{
}
*/



/*
 *  Numeric Constructor
 */
template<typename fixed_base_t, unsigned num_frac_digits>
template<typename numeric_t>
constexpr LS_INLINE
fixed_t<fixed_base_t, num_frac_digits>::fixed_t(numeric_t f) :
    number{(fixed_base_t)(setup::IsFloat<numeric_t>::value ? (f * (numeric_t)(1ull << num_frac_digits)) : f)}
{
}



/*
 *  Pre-Increment operator
 */
template<typename fixed_base_t, unsigned num_frac_digits>
inline LS_INLINE
fixed_t <fixed_base_t, num_frac_digits>& fixed_t<fixed_base_t, num_frac_digits>::operator++()
{
    number += (fixed_base_t)(1ull << num_frac_digits);
    return *this;
}



/*
 *  Pre-Decrement operator
 */
template<typename fixed_base_t, unsigned num_frac_digits>
inline LS_INLINE
fixed_t <fixed_base_t, num_frac_digits>& fixed_t<fixed_base_t, num_frac_digits>::operator--()
{
    number -= (fixed_base_t)(1ull << num_frac_digits);
    return *this;
}



/*
 *  Post-Increment operator
 */
template<typename fixed_base_t, unsigned num_frac_digits>
inline LS_INLINE
fixed_t <fixed_base_t, num_frac_digits> fixed_t<fixed_base_t, num_frac_digits>::operator++(int)
{
    const fixed_t ret{number};
    number += (fixed_base_t)(1ull << num_frac_digits);
    return ret;
}



/*
 *  Post-Decrement operator
 */
template<typename fixed_base_t, unsigned num_frac_digits>
inline LS_INLINE
fixed_t <fixed_base_t, num_frac_digits> fixed_t<fixed_base_t, num_frac_digits>::operator--(int)
{
    const fixed_t ret{number};
    number -= (fixed_base_t)(1ull << num_frac_digits);
    return ret;
}



/*
 *  Arithmetic "not" operator.
 */
template<typename fixed_base_t, unsigned num_frac_digits>
constexpr LS_INLINE
bool fixed_t<fixed_base_t, num_frac_digits>::operator!() const
{
    return !number;
}



/*
 *  Equivalence operator
 */
template<typename fixed_base_t, unsigned num_frac_digits>
constexpr LS_INLINE
bool fixed_t<fixed_base_t, num_frac_digits>::operator==(const fixed_t& f) const
{
    return number == f.number;
}



/*
 *  Non-Equivalence operator
 */
template<typename fixed_base_t, unsigned num_frac_digits>
constexpr LS_INLINE
bool fixed_t<fixed_base_t, num_frac_digits>::operator!=(const fixed_t& f) const
{
    return number != f.number;
}



/*
 *  Greater than or equal to operator.
 */
template<typename fixed_base_t, unsigned num_frac_digits>
constexpr LS_INLINE
bool fixed_t<fixed_base_t, num_frac_digits>::operator>=(const fixed_t& f) const
{
    return number >= f.number;
}



/*
 *  Less than or equal to operator.
 */
template<typename fixed_base_t, unsigned num_frac_digits>
constexpr LS_INLINE
bool fixed_t<fixed_base_t, num_frac_digits>::operator<=(const fixed_t& f) const
{
    return number <= f.number;
}



/*
 *  Greater than operator.
 */
template<typename fixed_base_t, unsigned num_frac_digits>
constexpr LS_INLINE
bool fixed_t<fixed_base_t, num_frac_digits>::operator>(const fixed_t& f) const
{
    return number > f.number;
}



/*
 *  Less than operator.
 */
template<typename fixed_base_t, unsigned num_frac_digits>
constexpr LS_INLINE
bool fixed_t<fixed_base_t, num_frac_digits>::operator<(const fixed_t& f) const
{
    return number < f.number;
}



/*
 *  Addition operator
 */
template<typename fixed_base_t, unsigned num_frac_digits>
constexpr LS_INLINE
fixed_t <fixed_base_t, num_frac_digits> fixed_t<fixed_base_t, num_frac_digits>::operator+(const fixed_t& f) const
{
    return fixed_t{number + f.number};
}



/*
 *  Subtraction operator
 */
template<typename fixed_base_t, unsigned num_frac_digits>
constexpr LS_INLINE
fixed_t <fixed_base_t, num_frac_digits> fixed_t<fixed_base_t, num_frac_digits>::operator-(const fixed_t& f) const
{
    return fixed_t{number - f.number};
}



/*
 *  Negation operator
 */
template<typename fixed_base_t, unsigned num_frac_digits>
constexpr LS_INLINE
fixed_t <fixed_base_t, num_frac_digits> fixed_t<fixed_base_t, num_frac_digits>::operator-() const
{
    return fixed_t{-number};
}



/*
 *  Multiplication operator
 */
template<typename fixed_base_t, unsigned num_frac_digits>
constexpr LS_INLINE
fixed_t <fixed_base_t, num_frac_digits> fixed_t<fixed_base_t, num_frac_digits>::operator*(const fixed_t& f) const
{
    // Since 64-bit multiplication will run out of precision, we have two
    // methods of multiplying. The first will drop a bit from each number to
    // ensure the result will have enough precision. The second method will
    // simply make use of all available bits in a 64-bit number, then remove
    // any excess bits.

    #if 0
    return (sizeof(fixed_base_t) > sizeof(int32_t))
        ? fixed_t{((number >> (num_frac_digits >> 1)) * (f.number >> (num_frac_digits >> 1))) >> (fixed_base_t)ls::math::IsSigned<fixed_base_t>::value}
        : fixed_t{(fixed_base_t)(((int64_t)number * (int64_t)f.number) / (1ll << num_frac_digits))};
    #else
    return fixed_t{(fixed_base_t)(
        (((number >> num_frac_digits) * (f.number >> num_frac_digits)) << num_frac_digits) + // integer multiply
        (((number & fraction_mask)    * (f.number & fraction_mask))    >> num_frac_digits) + // fraction multiply
        (((number >> num_frac_digits) * (f.number & fraction_mask)) + ((number & fraction_mask) * (f.number >> num_frac_digits))) // mixed multiply
    )};
    #endif
}



/*
 *  Division operator
 */
template<typename fixed_base_t, unsigned num_frac_digits>
constexpr LS_INLINE
fixed_t<fixed_base_t, num_frac_digits> fixed_t<fixed_base_t, num_frac_digits>::operator/(const fixed_t& f) const
{
    //return fixed_t{(fixed_base_t)(((int64_t)number << (int64_t)num_frac_digits) / (int64_t)f.number)};
    return this->operator*(fixed_t<fixed_base_t, num_frac_digits>{(fixed_base_t)(((0x8000000000000000ull >> (63ull-num_frac_digits)) << num_frac_digits) / (uint64_t)f.number)});
}



/*
 *  Modulus operator
 */
template<typename fixed_base_t, unsigned num_frac_digits>
constexpr LS_INLINE
fixed_t <fixed_base_t, num_frac_digits> fixed_t<fixed_base_t, num_frac_digits>::operator%(const fixed_t& f) const
{
    return fixed_t{number % f.number};
}



/*
 *  Logical AND operator
 */
template<typename fixed_base_t, unsigned num_frac_digits>
constexpr LS_INLINE
fixed_t <fixed_base_t, num_frac_digits> fixed_t<fixed_base_t, num_frac_digits>::operator&(const fixed_t& f) const
{
    return fixed_t{number & f.number};
}



/*
 *  Logical OR operator
 */
template<typename fixed_base_t, unsigned num_frac_digits>
constexpr LS_INLINE
fixed_t <fixed_base_t, num_frac_digits> fixed_t<fixed_base_t, num_frac_digits>::operator|(const fixed_t& f) const
{
    return fixed_t{number | f.number};
}



/*
 *  Logical XOR operator
 */
template<typename fixed_base_t, unsigned num_frac_digits>
constexpr LS_INLINE
fixed_t <fixed_base_t, num_frac_digits> fixed_t<fixed_base_t, num_frac_digits>::operator^(const fixed_t& f) const
{
    return fixed_t{number ^ f.number};
}



/*
 *  Logical NOT operator
 */
template<typename fixed_base_t, unsigned num_frac_digits>
constexpr LS_INLINE
fixed_t <fixed_base_t, num_frac_digits> fixed_t<fixed_base_t, num_frac_digits>::operator~() const
{
    return fixed_t{~number};
}



/*
 *  Shift-Right operator
 */
template<typename fixed_base_t, unsigned num_frac_digits>
constexpr LS_INLINE
fixed_t <fixed_base_t, num_frac_digits> fixed_t<fixed_base_t, num_frac_digits>::operator>>(int n) const
{
    return fixed_t{number >> n};
}



/*
 *  Shift-Left operator
 */
template<typename fixed_base_t, unsigned num_frac_digits>
constexpr LS_INLINE
fixed_t <fixed_base_t, num_frac_digits> fixed_t<fixed_base_t, num_frac_digits>::operator<<(int n) const
{
    return fixed_t{number << n};
}



/*
 *  Copy-Assignment operator
 */
/*
template <typename fixed_base_t, unsigned num_frac_digits> inline LS_INLINE
fixed_t<fixed_base_t, num_frac_digits>& fixed_t<fixed_base_t, num_frac_digits>::operator=(const fixed_t& f) {
    number = f.number;
    return *this;
}
*/



/*
 *  Move-Assignment operator
 */
/*
template <typename fixed_base_t, unsigned num_frac_digits> inline LS_INLINE
fixed_t<fixed_base_t, num_frac_digits>& fixed_t<fixed_base_t, num_frac_digits>::operator=(fixed_t&& f) {
    number = f.number;
    return *this;
}
*/



/*
 *  Addition-Assignment operator
 */
template<typename fixed_base_t, unsigned num_frac_digits>
inline LS_INLINE
fixed_t <fixed_base_t, num_frac_digits>& fixed_t<fixed_base_t, num_frac_digits>::operator+=(const fixed_t& f)
{
    number += f.number;
    return *this;
}



/*
 *  Subtraction-Assignment operator
 */
template<typename fixed_base_t, unsigned num_frac_digits>
inline LS_INLINE
fixed_t <fixed_base_t, num_frac_digits>& fixed_t<fixed_base_t, num_frac_digits>::operator-=(const fixed_t& f)
{
    number -= f.number;
    return *this;
}



/*
 *  Multiplication-Assignment operator
 */
template<typename fixed_base_t, unsigned num_frac_digits>
inline LS_INLINE
fixed_t <fixed_base_t, num_frac_digits>& fixed_t<fixed_base_t, num_frac_digits>::operator*=(const fixed_t& f)
{
    return *this = this->operator*(f);
}



/*
 *  Division-Assignment operator
 */
template<typename fixed_base_t, unsigned num_frac_digits>
inline LS_INLINE
fixed_t <fixed_base_t, num_frac_digits>& fixed_t<fixed_base_t, num_frac_digits>::operator/=(const fixed_t& f)
{
    return *this = this->operator/(f);
}



/*
 *  Modulo-Assignment operator
 */
template<typename fixed_base_t, unsigned num_frac_digits>
inline LS_INLINE
fixed_t <fixed_base_t, num_frac_digits>& fixed_t<fixed_base_t, num_frac_digits>::operator%=(const fixed_t& f)
{
    number %= f.number;
    return *this;
}



/*
 *  Logical AND-Assignment operator
 */
template<typename fixed_base_t, unsigned num_frac_digits>
inline LS_INLINE
fixed_t <fixed_base_t, num_frac_digits>& fixed_t<fixed_base_t, num_frac_digits>::operator&=(const fixed_t& f)
{
    number &= f.number;
    return *this;
}



/*
 *  Logical OR-Assignment operator
 */
template<typename fixed_base_t, unsigned num_frac_digits>
inline LS_INLINE
fixed_t <fixed_base_t, num_frac_digits>& fixed_t<fixed_base_t, num_frac_digits>::operator|=(const fixed_t& f)
{
    number |= f.number;
    return *this;
}



/*
 *  Logical XOR-Assignment operator
 */
template<typename fixed_base_t, unsigned num_frac_digits>
inline LS_INLINE
fixed_t <fixed_base_t, num_frac_digits>& fixed_t<fixed_base_t, num_frac_digits>::operator^=(const fixed_t& f)
{
    number ^= f.number;
    return *this;
}



/*
 *  Shift-Right and Assign operator
 */
template<typename fixed_base_t, unsigned num_frac_digits>
inline LS_INLINE
fixed_t <fixed_base_t, num_frac_digits>& fixed_t<fixed_base_t, num_frac_digits>::operator>>=(int n)
{
    number >>= n;
    return *this;
}



/*
 *  Shift-Left and Assign operator
 */
template<typename fixed_base_t, unsigned num_frac_digits>
inline LS_INLINE
fixed_t <fixed_base_t, num_frac_digits>& fixed_t<fixed_base_t, num_frac_digits>::operator<<=(int n)
{
    number <<= n;
    return *this;
}



/*
 *  Single-Precision floating-point cast.
 */
template<typename fixed_base_t, unsigned num_frac_digits>
constexpr LS_INLINE
fixed_t<fixed_base_t, num_frac_digits>::operator float() const
{
    return ls::math::float_cast<float>(*this);
}



/*
 *  Double-Precision floating-point cast.
 */
template<typename fixed_base_t, unsigned num_frac_digits>
constexpr LS_INLINE
fixed_t<fixed_base_t, num_frac_digits>::operator double() const
{
    return ls::math::float_cast<double>(*this);
}



/*
 *  Numeric cast.
 */
template<typename fixed_base_t, unsigned num_frac_digits>
constexpr LS_INLINE
fixed_t<fixed_base_t, num_frac_digits>::operator fixed_base_t() const
{
    return ls::math::integer_cast<fixed_base_t>(*this);
}



#if 0
/*
 *  Integral Assignment.
 */
template<typename fixed_base_t, unsigned num_frac_digits>
template<typename numeric_t>
inline LS_INLINE
fixed_t <fixed_base_t, num_frac_digits>& fixed_t<fixed_base_t, num_frac_digits>::operator=(typename ls::utils::EnableIf<ls::math::IsIntegral<numeric_t>::value, numeric_t>::type f)
{
    return *this = fixed_t{f};
}



/*
 *  Single-Precision floating-point Assignment.
 */
template<typename fixed_base_t, unsigned num_frac_digits>
template<typename numeric_t>
inline LS_INLINE
fixed_t <fixed_base_t, num_frac_digits>& fixed_t<fixed_base_t, num_frac_digits>::operator=(numeric_t f)
{
    return *this = fixed_t{f};
}
#endif



/*-----------------------------------------------------------------------------
    Fixed-Point Utility Functions
-----------------------------------------------------------------------------*/
} //end math namespace

/*-------------------------------------
    Cast to Fixed-Point Representation
-------------------------------------*/
template <class fixed_type, typename numeric_t>
constexpr math::fixed_t<typename fixed_type::base_type, fixed_type::fraction_digits> math::fixed_cast(const typename setup::EnableIf<setup::IsFloat<numeric_t>::value, numeric_t>::type n)
{
    //return fixed_t<typename fixed_type::base_type, fixed_type::fraction_digits>{n};
    return math::fixed_t<typename fixed_type::base_type, fixed_type::fraction_digits>{n};
}



/*-------------------------------------
    Cast to Fixed-Point Representation
-------------------------------------*/
template <class fixed_type, typename numeric_t>
constexpr math::fixed_t<typename fixed_type::base_type, fixed_type::fraction_digits> math::fixed_cast(const numeric_t n)
{
    return setup::IsFloat<numeric_t>::value
        ? math::fixed_t<typename fixed_type::base_type, fixed_type::fraction_digits>{n}
        : math::fixed_t<typename fixed_type::base_type, fixed_type::fraction_digits>{(typename fixed_type::base_type)((unsigned long long)n << fixed_type::fraction_digits)};
}



/*-------------------------------------
    Cast to Integer
-------------------------------------*/
template <typename integral_type, typename fixed_type>
constexpr integral_type math::integer_cast(const fixed_type f)
{
    return (integral_type)((unsigned long long)f.number >> fixed_type::fraction_digits);
}



/*-------------------------------------
    Cast to Float
-------------------------------------*/
template <typename float_type, class fixed_type>
constexpr float_type math::float_cast(const fixed_type f)
{
    return (float_type)f.number / (float_type)(1ull << fixed_type::fraction_digits);
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
    return (num.number >= 0) ? num : math::fixed_t<fixed_base_t, num_frac_digits>{fixed_impl::abs_shift<fixed_base_t>(num.number)};
}



/*-------------------------------------
    rcp
-------------------------------------*/
template<typename fixed_base_t, unsigned num_frac_digits>
constexpr LS_INLINE math::fixed_t<fixed_base_t, num_frac_digits> math::rcp(const math::fixed_t<fixed_base_t, num_frac_digits>& num) noexcept
{
    return (num.number != 0)
    ? (math::fixed_t<fixed_base_t, num_frac_digits>{(fixed_base_t)(0x8000000000000000ull >> (63ull-num_frac_digits))} / num) : math::fixed_t<fixed_base_t, num_frac_digits>{(fixed_base_t)0ull};
}



/*-------------------------------------
    sign
-------------------------------------*/
template<typename fixed_base_t, unsigned num_frac_digits>
constexpr LS_INLINE int math::sign_mask(const math::fixed_t<fixed_base_t, num_frac_digits>& x) noexcept
{
    return setup::IsSigned<fixed_base_t>::value
        ? (int)(x.number >> (((sizeof(fixed_base_t) * CHAR_BIT) - 1)) & 0x01)
        : 0;
}



/*-------------------------------------
    floor
-------------------------------------*/
template<typename fixed_base_t, unsigned num_frac_digits>
constexpr LS_INLINE math::fixed_t<fixed_base_t, num_frac_digits> math::floor(const math::fixed_t<fixed_base_t, num_frac_digits>& x) noexcept
{
    return math::fixed_t<fixed_base_t, num_frac_digits>{x.number & math::fixed_t<fixed_base_t, num_frac_digits>::integer_mask};
}



/*-------------------------------------
    floor
-------------------------------------*/
template<typename fixed_base_t, unsigned num_frac_digits>
constexpr LS_INLINE math::fixed_t<fixed_base_t, num_frac_digits> math::ceil(const math::fixed_t<fixed_base_t, num_frac_digits>& x) noexcept
{
    return math::floor<fixed_base_t, num_frac_digits>(math::fixed_t<fixed_base_t, num_frac_digits>{x.number + (fixed_base_t)(0x01ull << num_frac_digits)});
}



/*-------------------------------------
    round
-------------------------------------*/
template<typename fixed_base_t, unsigned num_frac_digits>
inline LS_INLINE math::fixed_t<fixed_base_t, num_frac_digits> math::round(const math::fixed_t<fixed_base_t, num_frac_digits>& x) noexcept
{
    constexpr fixed_base_t pointFive = (fixed_base_t)(0x05ull * (1ull << (num_frac_digits-1ull)));
    constexpr fixed_base_t one = (fixed_base_t)(1ull << num_frac_digits);
    const fixed_base_t standard = x.number + pointFive;
    const fixed_base_t rounded = x.number + one;

    return ((standard >> num_frac_digits) <= (rounded >> num_frac_digits))
    ? math::floor<fixed_base_t, num_frac_digits>(x)
    : math::ceil<fixed_base_t, num_frac_digits>(x);
}



/*-------------------------------------
    fmod_1
-------------------------------------*/
template<typename fixed_base_t, unsigned num_frac_digits>
constexpr LS_INLINE math::fixed_t<fixed_base_t, num_frac_digits> math::fmod_1(const math::fixed_t<fixed_base_t, num_frac_digits>& x) noexcept
{
    return math::fixed_t<fixed_base_t, num_frac_digits>{
        (x.number - (x.number & math::fixed_t<fixed_base_t, num_frac_digits>::integer_mask)) - ((fixed_base_t)(x.number < 0) << num_frac_digits)
    };
}



/*-------------------------------------
    sin
-------------------------------------*/
template<typename fixed_base_t, unsigned num_frac_digits>
inline LS_INLINE const math::fixed_t<fixed_base_t, num_frac_digits> math::sin(const math::fixed_t<fixed_base_t, num_frac_digits>& x) noexcept
{
    const math::fixed_t<fixed_base_t, num_frac_digits>&& x2 = x*x;
    const math::fixed_t<fixed_base_t, num_frac_digits>&& x3 = x2*x;
    const math::fixed_t<fixed_base_t, num_frac_digits>&& x5 = x2*x3;
    const math::fixed_t<fixed_base_t, num_frac_digits>&& x7 = x2*x5;
    const math::fixed_t<fixed_base_t, num_frac_digits>&& x9 = x2*x7;

    return x
           - (x3 * fixed_t<fixed_base_t, num_frac_digits>{1.f / 6.f})
           + (x5 * fixed_t<fixed_base_t, num_frac_digits>{1.f / 120.f})
           - (x7 * fixed_t<fixed_base_t, num_frac_digits>{1.f / 5040.f})
           + (x9 * fixed_t<fixed_base_t, num_frac_digits>{1.f / 362880.f});
}



/*-------------------------------------
    cos
-------------------------------------*/
template<typename fixed_base_t, unsigned num_frac_digits>
inline LS_INLINE const math::fixed_t<fixed_base_t, num_frac_digits> math::cos(const math::fixed_t<fixed_base_t, num_frac_digits>& x) noexcept
{
    const math::fixed_t<fixed_base_t, num_frac_digits>&& x2 = x*x;
    const math::fixed_t<fixed_base_t, num_frac_digits>&& x4 = x2*x2;
    const math::fixed_t<fixed_base_t, num_frac_digits>&& x6 = x2*x4;
    const math::fixed_t<fixed_base_t, num_frac_digits>&& x8 = x2*x6;

    return math::fixed_cast<math::fixed_t<fixed_base_t, num_frac_digits>>(1ull)
           - (x2 * fixed_t<fixed_base_t, num_frac_digits>{1.f / 2.f})
           + (x4 * fixed_t<fixed_base_t, num_frac_digits>{1.f / 24.f})
           - (x6 * fixed_t<fixed_base_t, num_frac_digits>{1.f / 720.f})
           + (x8 * fixed_t<fixed_base_t, num_frac_digits>{1.f / 40320.f});
}



/*-------------------------------------
    tan
-------------------------------------*/
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



} //end ls namespace
