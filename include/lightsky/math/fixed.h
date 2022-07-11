
#ifndef LS_MATH_FIXED_H
#define LS_MATH_FIXED_H

#include <climits> // CHAR_BIT
#include <limits> // std::numeric_limits
#include <cstdint> // fixed-width types

#include "lightsky/setup/Api.h"
#include "lightsky/setup/Macros.h"
#include "lightsky/setup/Types.h"

namespace ls {
namespace math {



/**----------------------------------------------------------------------------
 *  @brief Fixed-Point number Class.
 *  Utilizes the bits provided by a type from a "fixed_base_t" in order to
 *  store integral values that represent a fixed-precision number.
 *
 *  In it's current state, it's prone to overflows.
-----------------------------------------------------------------------------*/
template <typename fixed_base_t, unsigned num_frac_digits>
class fixed_t final
{
    static_assert(num_frac_digits < (sizeof (fixed_base_t)) * CHAR_BIT, "Fixed-Point object has too much precision.");
    static_assert(num_frac_digits != 0, "Fixed-Point object has no precision.");

  public:
    typedef fixed_base_t base_type;

    enum : fixed_base_t
    {
        fraction_digits = (fixed_base_t)num_frac_digits,
        fraction_mask   = (fixed_base_t)~(~0ull << (unsigned long long)num_frac_digits),
        integer_mask    = (fixed_base_t)(~0ull << (unsigned long long)num_frac_digits)
    };

    /**
     *  @brief number
     *  The singular piece of data contained within this class which
     *  represents a fractional decimal number using fixed-point
     *  arithmetic.
     */
    fixed_base_t number;

    /**
     *  @brief Destructor
     *
     *  Defaulted in order to allow a fixed-precision type to be used in
     *  constexpr expressions.
     */
    ~fixed_t() noexcept = default;

    /**
     *  @brief Constructor
     */
    constexpr fixed_t() noexcept = default;

    /**
     *  @brief Constructor
     *
     *  This constructor attempts to create a fixed-point value from a
     *  floating-point value.
     *
     *  Floating-point values will provide a fractional and decimal component.
     *
     *  @param n
     *  A single-precision floating-point number.
     */
    explicit constexpr fixed_t(float n) noexcept;

    /**
     *  @brief Constructor
     *
     *  This constructor attempts to create a fixed-point value from a
     *  floating-point value.
     *
     *  Floating-point values will provide a fractional and decimal component.
     *
     *  @param n
     *  A double-precision floating-point number.
     */
    explicit constexpr fixed_t(double n) noexcept;

    /**
     *  @brief Constructor
     *
     *  This constructor attempts to create a fixed-point value from an
     *  integral value.
     *
     *  @param n
     *  An integral number.
     *
     *  @param useRawBits
     *  If TRUE, the constructor will use the raw bits of n to construct the
     *  internal fixed-point number. If FALSE, the input integral will be
     *  converted to fixed-point representation (potentially truncating leading
     *  bits) to construct internal data.
     */
    explicit constexpr fixed_t(fixed_base_t n, bool useRawBits = false) noexcept;

    /**
     *  @brief Copy Constructor
     *
     *  Copies all data from the input parameter into *this.
     *
     *  @param f
     *  A constant reference to another fixed-point number with the same
     *  precision and bit-count.
     *
     */
    constexpr fixed_t(const fixed_t& f) noexcept = default;

    /**
     *  @brief Move Constructor
     *
     *  Moves data from the input parameter into *this.
     *
     *  @param f
     *  A fixed-point number of the same type as *this.
     */
    constexpr fixed_t(fixed_t&& f) noexcept = default;

    inline fixed_t& operator=(const fixed_t& f) noexcept = default;
    inline fixed_t& operator=(fixed_t&& f) noexcept = default;

    inline fixed_t& operator++() noexcept;
    inline fixed_t& operator--() noexcept;
    inline fixed_t operator++(int) noexcept;
    inline fixed_t operator--(int) noexcept;

    constexpr bool operator!() const noexcept;
    constexpr bool operator==(const fixed_t& f) const noexcept;
    constexpr bool operator!=(const fixed_t& f) const noexcept;
    constexpr bool operator>=(const fixed_t& f) const noexcept;
    constexpr bool operator<=(const fixed_t& f) const noexcept;
    constexpr bool operator>(const fixed_t& f) const noexcept;
    constexpr bool operator<(const fixed_t& f) const noexcept;

    constexpr fixed_t operator+(const fixed_t& f) const noexcept;
    constexpr fixed_t operator-(const fixed_t& f) const noexcept;
    constexpr fixed_t operator-() const noexcept;
    constexpr fixed_t operator*(const fixed_t& f) const noexcept;
    constexpr fixed_t operator/(const fixed_t& f) const noexcept;
    constexpr fixed_t operator%(const fixed_t& f) const noexcept;

    constexpr fixed_t operator&(const fixed_t& f) const noexcept;
    constexpr fixed_t operator|(const fixed_t& f) const noexcept;
    constexpr fixed_t operator ^ (const fixed_t& f) const noexcept;
    constexpr fixed_t operator~() const noexcept;

    template <typename integral_type>
    constexpr fixed_t operator>>(typename setup::EnableIf<setup::IsIntegral<integral_type>::value, integral_type>::type n) const noexcept;

    template <typename integral_type>
    constexpr fixed_t operator<<(typename setup::EnableIf<setup::IsIntegral<integral_type>::value, integral_type>::type n) const noexcept;

    inline fixed_t& operator+=(const fixed_t& f) noexcept;
    inline fixed_t& operator-=(const fixed_t& f) noexcept;
    inline fixed_t& operator*=(const fixed_t& f) noexcept;
    inline fixed_t& operator/=(const fixed_t& f) noexcept;
    inline fixed_t& operator%=(const fixed_t& f) noexcept;

    inline fixed_t& operator&=(const fixed_t& f) noexcept;
    inline fixed_t& operator|=(const fixed_t& f) noexcept;
    inline fixed_t& operator^=(const fixed_t& f) noexcept;

    template <typename integral_type>
    inline fixed_t& operator>>=(typename setup::EnableIf<setup::IsIntegral<integral_type>::value, integral_type>::type n) noexcept;

    template <typename integral_type>
    inline fixed_t& operator<<=(typename setup::EnableIf<setup::IsIntegral<integral_type>::value, integral_type>::type n) noexcept;

    explicit constexpr operator float() const noexcept;
    explicit constexpr operator double() const noexcept;
    constexpr operator fixed_base_t() const noexcept;
};



/*-------------------------------------
    Fixed-Point Template Specializations
-------------------------------------*/
LS_DECLARE_CLASS_TYPE(lowp_t, fixed_t, int32_t, 8); // 23.8 (-1 for the sign)
LS_DECLARE_CLASS_TYPE(medp_t, fixed_t, int32_t, 12); // 19.12
LS_DECLARE_CLASS_TYPE(highp_t, fixed_t, int32_t, 16); // 15.16

LS_DECLARE_CLASS_TYPE(long_lowp_t, fixed_t, int64_t, 16); // 47.16
LS_DECLARE_CLASS_TYPE(long_medp_t, fixed_t, int64_t, 20); // 43.20
LS_DECLARE_CLASS_TYPE(long_highp_t, fixed_t, int64_t, 24); // 39.24

LS_DECLARE_CLASS_TYPE(ulowp_t, fixed_t, uint32_t, 8); // 24.8
LS_DECLARE_CLASS_TYPE(umedp_t, fixed_t, uint32_t, 12); // 20.12
LS_DECLARE_CLASS_TYPE(uhighp_t, fixed_t, uint32_t, 16); // 16.16

LS_DECLARE_CLASS_TYPE(ulong_lowp_t, fixed_t, uint64_t, 16); // 48.16
LS_DECLARE_CLASS_TYPE(ulong_medp_t, fixed_t, uint64_t, 20); // 44.20
LS_DECLARE_CLASS_TYPE(ulong_highp_t, fixed_t, uint64_t, 24); // 40.24



/*-----------------------------------------------------------------------------
    Fixed-Point Utility Functions
-----------------------------------------------------------------------------*/
/*-------------------------------------
    Cast to Fixed-Point Representation
-------------------------------------*/
template <class fixed_type, typename numeric_t>
constexpr fixed_t<typename fixed_type::base_type, fixed_type::fraction_digits> fixed_cast(
    const typename setup::EnableIf<setup::IsFloat<numeric_t>::value, numeric_t>::type& n
) noexcept;

template <class fixed_type, typename numeric_t>
constexpr fixed_t<typename fixed_type::base_type, fixed_type::fraction_digits> fixed_cast(
    const typename setup::EnableIf<setup::IsIntegral<numeric_t>::value, numeric_t>::type& n
) noexcept;

template <class fixed_type, typename other_fixed_type>
constexpr fixed_t<typename fixed_type::base_type, fixed_type::fraction_digits> fixed_cast(
    const fixed_t<typename other_fixed_type::base_type, other_fixed_type::fraction_digits>& n
) noexcept;



/*-------------------------------------
    Cast to Integer
-------------------------------------*/
template <typename integral_type, typename fixed_type>
constexpr integral_type integer_cast(const fixed_type& f);



/*-------------------------------------
    Cast to Float
-------------------------------------*/
template <typename float_type, class fixed_type>
constexpr float_type float_cast(const fixed_type& f);



/*-------------------------------------
    abs
-------------------------------------*/
template<typename fixed_base_t, unsigned num_frac_digits>
constexpr LS_INLINE fixed_t <fixed_base_t, num_frac_digits> abs(const fixed_t<fixed_base_t, num_frac_digits>& num) noexcept;



/*-------------------------------------
    rcp
-------------------------------------*/
template<typename fixed_base_t, unsigned num_frac_digits>
constexpr LS_INLINE fixed_t <fixed_base_t, num_frac_digits> rcp(const fixed_t<fixed_base_t, num_frac_digits>& num) noexcept;



/*-------------------------------------
    sign
-------------------------------------*/
template<typename fixed_base_t, unsigned num_frac_digits>
constexpr LS_INLINE int sign_mask(const fixed_t<fixed_base_t, num_frac_digits>& x) noexcept;



/*-------------------------------------
    floor
-------------------------------------*/
template<typename fixed_base_t, unsigned num_frac_digits>
constexpr LS_INLINE fixed_t<fixed_base_t, num_frac_digits> floor(const fixed_t<fixed_base_t, num_frac_digits>& x) noexcept;



/*-------------------------------------
    floor
-------------------------------------*/
template<typename fixed_base_t, unsigned num_frac_digits>
constexpr LS_INLINE fixed_t<fixed_base_t, num_frac_digits> ceil(const fixed_t<fixed_base_t, num_frac_digits>& x) noexcept;



/*-------------------------------------
    round
-------------------------------------*/
template<typename fixed_base_t, unsigned num_frac_digits>
inline LS_INLINE fixed_t<fixed_base_t, num_frac_digits> round(const fixed_t<fixed_base_t, num_frac_digits>& x) noexcept;



/*-------------------------------------
    floor
-------------------------------------*/
template<typename fixed_base_t, unsigned num_frac_digits>
constexpr LS_INLINE fixed_t<fixed_base_t, num_frac_digits> fmod_1(const fixed_t<fixed_base_t, num_frac_digits>& x) noexcept;



/*-------------------------------------
    floor
-------------------------------------*/
template<typename fixed_base_t, unsigned num_frac_digits>
constexpr LS_INLINE fixed_t<fixed_base_t, num_frac_digits> fract(const fixed_t<fixed_base_t, num_frac_digits>& n) noexcept;



/*-------------------------------------
    sin
-------------------------------------*/
template<typename fixed_base_t, unsigned num_frac_digits>
inline LS_INLINE const fixed_t<fixed_base_t, num_frac_digits> sin(const fixed_t<fixed_base_t, num_frac_digits>& x) noexcept;



/*-------------------------------------
    cos
-------------------------------------*/
template<typename fixed_base_t, unsigned num_frac_digits>
inline LS_INLINE const fixed_t<fixed_base_t, num_frac_digits> cos(const fixed_t<fixed_base_t, num_frac_digits>& x) noexcept;



/*-------------------------------------
    tan
-------------------------------------*/
//template<typename fixed_base_t, unsigned num_frac_digits>
//inline LS_INLINE const fixed_t<fixed_base_t, num_frac_digits> tan(const fixed_t<fixed_base_t, num_frac_digits>& x) noexcept;



}//end math namespace




/*----------------------------------------------------------------------------
 * Type Information
----------------------------------------------------------------------------*/
namespace setup
{
/*-------------------------------------
 * Integral Determination
-------------------------------------*/
template<typename fixed_base_t, unsigned num_frac_digits>
struct IsIntegral<math::fixed_t<fixed_base_t, num_frac_digits>> : public ls::setup::FalseType<math::fixed_t<fixed_base_t, num_frac_digits>>
{
};



/*-------------------------------------
 * Float Determination
-------------------------------------*/
template<typename fixed_base_t, unsigned num_frac_digits>
struct IsFloat<math::fixed_t<fixed_base_t, num_frac_digits>> : public ls::setup::FalseType<math::fixed_t<fixed_base_t, num_frac_digits>>
{
};



} // end setup namespace
}//end ls namespace

#include "lightsky/math/generic/fixed_impl.h"

#endif    /* LS_MATH_FIXED_H */
