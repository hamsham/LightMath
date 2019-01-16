
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
template<typename fixed_base_t, unsigned num_frac_digits>
constexpr LS_INLINE
fixed_t<fixed_base_t, num_frac_digits>::fixed_t() :
    number{}
{
}



/*
 *  Copy Constructor
 *
 */
template<typename fixed_base_t, unsigned num_frac_digits>
constexpr LS_INLINE
fixed_t<fixed_base_t, num_frac_digits>::fixed_t(const fixed_t& f) :
    number{f.number}
{
}



/*
 *  Move Constructor
 */
template<typename fixed_base_t, unsigned num_frac_digits>
constexpr LS_INLINE
fixed_t<fixed_base_t, num_frac_digits>::fixed_t(fixed_t&& f) :
    number{f.number}
{
}



/*
 *  Numeric Constructor
 */
template<typename fixed_base_t, unsigned num_frac_digits>
template<typename numeric_t>
constexpr LS_INLINE
fixed_t<fixed_base_t, num_frac_digits>::fixed_t(numeric_t f) :
    number{(fixed_base_t)(ls::math::IsFloat<numeric_t>::value ? (f * (numeric_t)(1ull << num_frac_digits)) : f)}
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
    return sizeof(fixed_base_t) > sizeof(int32_t)
        ? fixed_t{((number >> (num_frac_digits >> 1)) * (f.number >> (num_frac_digits >> 1))) >> (fixed_base_t)ls::math::IsSigned<fixed_base_t>::value}
        : fixed_t{(fixed_base_t)(((int64_t)number * (int64_t)f.number) / (1ll << num_frac_digits))};
}



/*
 *  Division operator
 */
template<typename fixed_base_t, unsigned num_frac_digits>
constexpr LS_INLINE
fixed_t <fixed_base_t, num_frac_digits> fixed_t<fixed_base_t, num_frac_digits>::operator/(const fixed_t& f) const
{
    return fixed_t{(fixed_base_t)(((int64_t)number << (int64_t)num_frac_digits) / (int64_t)f.number)};
    //return fixed_t{(number / f.number) + (fixed_base_t)(((number % f.number) << 1) >= f.number)};
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
    if (sizeof(fixed_base_t) > sizeof(int32_t))
    {
        number = ((number >> (num_frac_digits >> 1)) * (f.number >> (num_frac_digits >> 1))) >> (fixed_base_t)ls::math::IsSigned<fixed_base_t>::value;
    }
    else
    {
        number = (fixed_base_t)(((int64_t)number * (int64_t)f.number) / (1ll << num_frac_digits));
    }
    return *this;
}



/*
 *  Division-Assignment operator
 */
template<typename fixed_base_t, unsigned num_frac_digits>
inline LS_INLINE
fixed_t <fixed_base_t, num_frac_digits>& fixed_t<fixed_base_t, num_frac_digits>::operator/=(const fixed_t& f)
{
    number = (fixed_base_t)(((int64_t)number << num_frac_digits) / (int64_t)f.number);
    return *this;
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



#if 0
/*
 *  Single-Precision floating-point cast.
 */
template<typename fixed_base_t, unsigned num_frac_digits>
constexpr LS_INLINE
fixed_t<fixed_base_t, num_frac_digits>::operator float() const
{
    return (float)number / (float)(1ull << num_frac_digits);
}



/*
 *  Double-Precision floating-point cast.
 */
template<typename fixed_base_t, unsigned num_frac_digits>
constexpr LS_INLINE
fixed_t<fixed_base_t, num_frac_digits>::operator double() const
{
    return (double)number / (double)(1ull << num_frac_digits);
}



/*
 *  Numeric cast.
 */
template<typename fixed_base_t, unsigned num_frac_digits>
constexpr LS_INLINE
fixed_t<fixed_base_t, num_frac_digits>::operator fixed_base_t() const
{
    return (fixed_base_t)((unsigned long long)number >> num_frac_digits);
}



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
/*-------------------------------------
    Cast to Fixed-Point Representation
-------------------------------------*/
template <class fixed_type, typename numeric_t>
constexpr ls::math::fixed_t<typename fixed_type::base_type, fixed_type::fraction_digits> fixed_cast(const typename ls::utils::EnableIf<ls::math::IsFloat<numeric_t>::value, numeric_t>::type n)
{
    //return fixed_t<typename fixed_type::base_type, fixed_type::fraction_digits>{n};
    return ls::math::fixed_t<typename fixed_type::base_type, fixed_type::fraction_digits>{n};
}



/*-------------------------------------
    Cast to Fixed-Point Representation
-------------------------------------*/
template <class fixed_type, typename numeric_t>
constexpr ls::math::fixed_t<typename fixed_type::base_type, fixed_type::fraction_digits> fixed_cast(const numeric_t n)
{
    return ls::math::IsFloat<numeric_t>::value
        ? ls::math::fixed_t<typename fixed_type::base_type, fixed_type::fraction_digits>{n}
        : ls::math::fixed_t<typename fixed_type::base_type, fixed_type::fraction_digits>{(typename fixed_type::base_type)((unsigned long long)n << fixed_type::fraction_digits)};
}



/*-------------------------------------
    Cast to Integer
-------------------------------------*/
template <typename integral_type, typename fixed_type>
constexpr integral_type integer_cast(const fixed_type f)
{
    return (integral_type)((unsigned long long)f.number >> fixed_type::fraction_digits);
}



/*-------------------------------------
    Cast to Float
-------------------------------------*/
template <typename float_type, class fixed_type>
constexpr float_type float_cast(const fixed_type f)
{
    return (float_type)f.number / (float_type)(1ull << fixed_type::fraction_digits);
}



/*-------------------------------------
    rcp
-------------------------------------*/
template<typename fixed_base_t, unsigned num_frac_digits>
constexpr LS_INLINE fixed_t<fixed_base_t, num_frac_digits> rcp(const fixed_t<fixed_base_t, num_frac_digits>& num) noexcept
{
    return num.number
        ? (fixed_t<fixed_base_t, num_frac_digits>{(fixed_base_t)(1ull << num_frac_digits)} / num)
        : fixed_t<fixed_base_t, num_frac_digits>{0x7FFFFFFFFFFFFFFF};
}



/*-------------------------------------
    sign_bit
-------------------------------------*/
template<typename fixed_base_t, unsigned num_frac_digits>
constexpr LS_INLINE int sign_bit(const fixed_t<fixed_base_t, num_frac_digits>& x) noexcept
{
    return IsSigned<fixed_base_t>::value
        ? (int)(x.number >> (((sizeof(fixed_base_t) * CHAR_BIT) - 1)) & 0x01)
        : 0;
}



/*-------------------------------------
    floor
-------------------------------------*/
template<typename fixed_base_t, unsigned num_frac_digits>
constexpr LS_INLINE fixed_t<fixed_base_t, num_frac_digits> floor(const fixed_t<fixed_base_t, num_frac_digits>& x) noexcept
{
    return fixed_t<fixed_base_t, num_frac_digits>{x.number & (fixed_base_t)(~0ull << num_frac_digits)};
}



/*-------------------------------------
    floor
-------------------------------------*/
template<typename fixed_base_t, unsigned num_frac_digits>
constexpr LS_INLINE fixed_t<fixed_base_t, num_frac_digits> ceil(const fixed_t<fixed_base_t, num_frac_digits>& x) noexcept
{
    return floor<fixed_base_t, num_frac_digits>(fixed_t<fixed_base_t, num_frac_digits>{x.number + (fixed_base_t)(0x01ull << num_frac_digits)});
}



/*-------------------------------------
    round
-------------------------------------*/
template<typename fixed_base_t, unsigned num_frac_digits>
inline LS_INLINE fixed_t<fixed_base_t, num_frac_digits> round(const fixed_t<fixed_base_t, num_frac_digits>& x) noexcept
{
    constexpr fixed_base_t pointFive = (fixed_base_t)(0x05ull * (1ull << (num_frac_digits-1ull)));
    constexpr fixed_base_t one = (fixed_base_t)(1ull << num_frac_digits);
    const fixed_base_t standard = x.number + pointFive;
    const fixed_base_t rounded = x.number + one;

    return ((standard >> num_frac_digits) <= (rounded >> num_frac_digits))
    ? floor<fixed_base_t, num_frac_digits>(x)
    : ceil<fixed_base_t, num_frac_digits>(x);
}



} //end math namespace
} //end ls namespace
