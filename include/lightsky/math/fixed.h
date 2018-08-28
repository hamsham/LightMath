
#ifndef LS_MATH_FIXED_H
#define LS_MATH_FIXED_H

#include <climits> // CHAR_BIT
#include <cstdint> // fixed-width types
#include <utility> // std::move()

#include "lightsky/setup/Api.h"
#include "lightsky/setup/Macros.h"

#include "lightsky/math/Types.h"

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
class LS_API fixed_t final {

    static_assert(num_frac_digits < (sizeof (fixed_base_t)) * CHAR_BIT, "Fixed-Point object has too much precision.");
    static_assert(num_frac_digits != 0, "Fixed-Point object has no precision.");

  public:
    typedef fixed_base_t base_type;

    static constexpr fixed_base_t fraction_digits = num_frac_digits;

    /**
     *  @brief number
     *  The singular piece of data contained within this class which
     *  represents a fractional decimal number using fixed-point
     *  arithmetic.
     */
    fixed_base_t number;

    /**
     *  @brief Constructors
     *  Initializes all data.
     */
    constexpr fixed_t();

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
    constexpr fixed_t(const fixed_t& f);

    /**
     *  @brief Move Constructor
     *
     *  Moves data from the input parameter into *this.
     *
     *  @param f
     *  A fixed-point number of the same type as *this.
     */
    constexpr fixed_t(fixed_t&& f);

    /**
     *  @brief Numeric Constructor
     *
     *  Constructs a fixed-point number using a plain data type.
     *
     *  @param
     *  An integral type that will be used to construct this object's
     *  internal data.
     *
     *
     */
    explicit constexpr fixed_t(fixed_base_t f);

    /**
     *  @brief Constructor
     *
     *  This constructor attempts to create a fixed-point value from a
     *  floating-point decimal value.
     *
     *  @param
     *  A single-precision floating point number.
     */
    explicit constexpr fixed_t(float f);

    /**
     *  @brief Constructor
     *
     *  This constructor attempts to create a fixed-point value from a
     *  floating-point decimal value using double-precision.
     *
     *  @param d
     *  A double precision floating-point number.
     */
    explicit constexpr fixed_t(double d);

    /**
     *  @brief Destructor
     *
     *  Defaulted in order to allow a fixed-precision type to be used in
     *  constexpr expressions.
     */
    ~fixed_t() = default;

    inline fixed_t& operator++();
    inline fixed_t& operator--();
    inline fixed_t operator++(int);
    inline fixed_t operator--(int);

    constexpr bool operator!() const;
    constexpr bool operator==(const fixed_t& f) const;
    constexpr bool operator!=(const fixed_t& f) const;
    constexpr bool operator>=(const fixed_t& f) const;
    constexpr bool operator<=(const fixed_t& f) const;
    constexpr bool operator>(const fixed_t& f) const;
    constexpr bool operator<(const fixed_t& f) const;

    constexpr fixed_t operator+(const fixed_t& f) const;
    constexpr fixed_t operator-(const fixed_t& f) const;
    constexpr fixed_t operator-() const;
    constexpr fixed_t operator*(const fixed_t& f) const;
    constexpr fixed_t operator/(const fixed_t& f) const;
    constexpr fixed_t operator%(const fixed_t& f) const;

    constexpr fixed_t operator&(const fixed_t& f) const;
    constexpr fixed_t operator|(const fixed_t& f) const;
    constexpr fixed_t operator ^ (const fixed_t& f) const;
    constexpr fixed_t operator~() const;
    constexpr fixed_t operator>>(int n) const;
    constexpr fixed_t operator<<(int n) const;

    inline fixed_t& operator=(const fixed_t& f) = default;
    inline fixed_t& operator=(fixed_t&& f) = default;
    inline fixed_t& operator+=(const fixed_t& f);
    inline fixed_t& operator-=(const fixed_t& f);
    inline fixed_t& operator*=(const fixed_t& f);
    inline fixed_t& operator/=(const fixed_t& f);
    inline fixed_t& operator%=(const fixed_t& f);

    inline fixed_t& operator&=(const fixed_t& f);
    inline fixed_t& operator|=(const fixed_t& f);
    inline fixed_t& operator^=(const fixed_t& f);
    inline fixed_t& operator>>=(int n);
    inline fixed_t& operator<<=(int n);

    constexpr operator float() const;
    explicit constexpr operator double() const;
    explicit inline operator fixed_base_t() const;


    inline fixed_t& operator=(float f);
    inline fixed_t& operator=(double d);
    inline fixed_t& operator=(fixed_base_t f);
};



template <class fixed_type>
constexpr fixed_t<typename fixed_type::base_type, fixed_type::fraction_digits> fixed_cast(const typename fixed_type::base_type n)
{
    return fixed_t<typename fixed_type::base_type, fixed_type::fraction_digits>{{n << fixed_type::fraction_digits}};
}



template <typename fixed_base_t, unsigned num_frac_digits>
constexpr fixed_base_t fixed_cast(const fixed_t<fixed_base_t, num_frac_digits>& n)
{
    return (fixed_base_t)n;
}



/*-------------------------------------
    Fixed-Point Template Specializations
-------------------------------------*/
/*
LS_DECLARE_CLASS_TYPE(lowp_t, fixed_t, int32_t, 8); // 23.8 (-1 for the sign)
LS_DECLARE_CLASS_TYPE(medp_t, fixed_t, int32_t, 12); // 19.12
LS_DECLARE_CLASS_TYPE(highp_t, fixed_t, int32_t, 16); // 15.16

LS_DECLARE_CLASS_TYPE(long_lowp_t, fixed_t, int64_t, 15); // 48.15
LS_DECLARE_CLASS_TYPE(long_medp_t, fixed_t, int64_t, 31); // 32.31
LS_DECLARE_CLASS_TYPE(long_highp_t, fixed_t, int64_t, 47); // 16.47

LS_DECLARE_CLASS_TYPE(ulowp_t, fixed_t, uint32_t, 8); // 24.8 (-1 for the sign)
LS_DECLARE_CLASS_TYPE(umedp_t, fixed_t, uint32_t, 16); // 16.16
LS_DECLARE_CLASS_TYPE(uhighp_t, fixed_t, uint32_t, 24); // 8.24

LS_DECLARE_CLASS_TYPE(ulong_lowp_t, fixed_t, uint64_t, 16); // 48.16
LS_DECLARE_CLASS_TYPE(ulong_medp_t, fixed_t, uint64_t, 32); // 32.32
LS_DECLARE_CLASS_TYPE(ulong_highp_t, fixed_t, uint64_t, 48); // 16.48
*/

typedef fixed_t<int32_t, 8> lowp_t; // 23.8 (-1 for the sign)
typedef fixed_t<int32_t, 12> medp_t; // 19.12
typedef fixed_t<int32_t, 15> highp_t; // 15.16
typedef fixed_t<int64_t, 15> long_lowp_t; // 48.15
typedef fixed_t<int64_t, 31> long_medp_t; // 32.31
typedef fixed_t<int64_t, 47> long_highp_t; // 16.47
typedef fixed_t<uint32_t, 8> ulowp_t; // 24.8 (-1 for the sign)
typedef fixed_t<uint32_t, 16> umedp_t; // 16.16
typedef fixed_t<uint32_t, 24> uhighp_t; // 8.24
typedef fixed_t<uint64_t, 16> ulong_lowp_t; // 48.16
typedef fixed_t<uint64_t, 32> ulong_medp_t; // 32.32
typedef fixed_t<uint64_t, 48> ulong_highp_t; // 16.48

}//end math namespace
}//end ls namespace

#include "lightsky/math/generic/fixed_impl.h"

#endif    /* LS_MATH_FIXED_H */
