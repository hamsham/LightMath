
#include "lightsky/setup/Api.h" // LS_INLINE



namespace ls
{

/*-----------------------------------------------------------------------------
// Function definitions
-----------------------------------------------------------------------------*/
/*-------------------------------------
    gcd
-------------------------------------*/
template <typename scalar_t>
constexpr scalar_t math::gcd(scalar_t a, scalar_t b) noexcept
{
    return b == 0 ? a : math::gcd<scalar_t>(b, a % b);
}



/*-------------------------------------
    min
-------------------------------------*/
template<typename scalar_t>
constexpr LS_INLINE scalar_t math::min(scalar_t a, scalar_t b) noexcept
{
    return (a < b) ? a : b;
}



/*-------------------------------------
    min
-------------------------------------*/
template<typename scalar_t, typename... scalars_t>
constexpr LS_INLINE scalar_t math::min(const scalar_t& a, const scalar_t& b, const scalars_t& ... nums) noexcept
{
    return math::min<scalar_t>(math::min<scalar_t>(a, b), nums...);
}



/*-------------------------------------
    mix
-------------------------------------*/
template<typename scalar_t>
constexpr LS_INLINE scalar_t math::mix(scalar_t a, scalar_t b, scalar_t percent) noexcept
{
    return a + ((b - a) * percent);
}



/*-------------------------------------
    max
-------------------------------------*/
template<typename scalar_t>
constexpr LS_INLINE scalar_t math::max(scalar_t a, scalar_t b) noexcept
{
    return (a > b) ? a : b;
}



/*-------------------------------------
    max
-------------------------------------*/
template<typename scalar_t, typename... scalars_t>
constexpr LS_INLINE scalar_t math::max(const scalar_t& a, const scalar_t& b, const scalars_t& ... nums) noexcept
{
    return math::max<scalar_t>(math::max<scalar_t>(a, b), nums...);
}



/*-------------------------------------
    clamp
-------------------------------------*/
template<typename scalar_t>
constexpr LS_INLINE scalar_t math::clamp(scalar_t n, scalar_t minVal, scalar_t maxVal) noexcept
{
    return (n < minVal) ? minVal : (n > maxVal) ? maxVal : n;
}



/*-------------------------------------
    floor
-------------------------------------*/
template<typename floating_t>
constexpr LS_INLINE floating_t math::floor(const floating_t n) noexcept
{
    return static_cast<floating_t>(static_cast<long long>(n) - (n < floating_t{0}));
}



/*-------------------------------------
    ranged-floor
-------------------------------------*/
template<typename floating_t, typename int_t, int_t range>
constexpr LS_INLINE int_t math::ranged_floor(const floating_t n) noexcept
{
    return (int_t)(n + (floating_t)range) - range;
}



/*-------------------------------------
    ceil
-------------------------------------*/
template<typename floating_t>
constexpr LS_INLINE floating_t math::ceil(const floating_t n) noexcept
{
    return (floating_t)((long long)n + (n >= floating_t{0.f} ? floating_t{1.f} : floating_t{0}));
}



/*-------------------------------------
    ranged-ceil
-------------------------------------*/
template<typename floating_t, typename int_t, int_t range>
constexpr LS_INLINE int_t math::ranged_ceil(const floating_t n) noexcept
{
    return range - (int_t)((floating_t)range - n);
}



/*-------------------------------------
    round
-------------------------------------*/
template<typename floating_t>
constexpr LS_INLINE floating_t math::round(const floating_t n) noexcept
{
    return math::floor<floating_t>(n + floating_t{0.5f});
}



/*-------------------------------------
    fract
-------------------------------------*/
template<typename floating_t>
constexpr LS_INLINE floating_t math::fract(const floating_t n) noexcept
{
    return n - math::floor<floating_t>(n);
}



/*-------------------------------------
 fmod
-------------------------------------*/
template<typename floating_t>
constexpr LS_INLINE floating_t math::fmod(const floating_t n1, const floating_t n2) noexcept
{
    return (n2 != floating_t{0})
        ? ((n1 < floating_t{0}) != (n2 < floating_t{0}))
            ? ((n1 - (math::floor<floating_t>(n1 / n2) * n2)) - n2)
            : (n1 - (math::floor<floating_t>(n1 / n2) * n2))
        : floating_t{0};
}



/*-------------------------------------
 fmod_1
-------------------------------------*/
template<typename floating_t>
constexpr LS_INLINE floating_t math::fmod_1(const floating_t n) noexcept
{
    return (n - math::floor<floating_t>(n)) - (floating_t)(n < floating_t{0});
}



/*-------------------------------------
 step
-------------------------------------*/
template<typename floating_t>
constexpr LS_INLINE floating_t math::step(const floating_t edge, const floating_t x) noexcept
{
    return x < edge ? floating_t{0} : floating_t{1};
}



/*-------------------------------------
    smoothstep
-------------------------------------*/
namespace math
{
namespace impl
{
    template<typename scalar_t>
    constexpr LS_INLINE scalar_t smoothstep_impl(const scalar_t t) noexcept
    {
        return t * t * (scalar_t{3.0} - scalar_t{2.0} * t);
    }
} // math::impl namespace
} // math namespace



template<typename floating_t>
constexpr LS_INLINE floating_t math::smoothstep(floating_t a, floating_t b, floating_t x) noexcept
{
    return math::impl::smoothstep_impl<floating_t>(math::clamp<floating_t>((x - a) / (b - a), floating_t{0}, floating_t{1}));
}



/*-------------------------------------
    fastInvSqrt

    The fast inverse square root method adopted for regular square rooting.
    this method was found at:
        http://rrrola.wz.cz/inv_sqrt.html
    and:
        http://jheriko-rtw.blogspot.com/2009/04/understanding-and-improving-fast.html

    However, after running some benchmarks on Clang and GCC, it turns out that
    Carmack's original implementation is still the fastest (I blame sunspots).
-------------------------------------*/
template<typename scalar_t>
inline LS_INLINE scalar_t math::inversesqrt(scalar_t input) noexcept
{
    const float x = (float)input;
    /*
    union
    {
        float f;
        unsigned long u;
    } y = {x};
    y.u = 0x5F1FFFF9ul - (y.u >> 1);
    return 0.703952253f * y.f * (2.38924456f - x * y.f * y.f);
    */

    union
    {
        float f;
        int32_t i;
    } y = {x};

    const float xhalf = 0.5f * x;
    y.i = 0x5f3759df - (y.i >> 1);
    return y.f * (1.5f - xhalf * y.f * y.f);
}



/*-------------------------------------
    fast_sqrt
-------------------------------------*/
// Nearest truncated integral closest to the actual square root.
template<typename scalar_t>
inline scalar_t math::fast_sqrt(typename setup::EnableIf<setup::IsIntegral<scalar_t>::value, scalar_t>::type x) noexcept
{

    // Return 0 if the input digit is less than 1.
    if (x < scalar_t{2})
    {
        return -(x > 0) & x;
    }

    const scalar_t i = fast_sqrt<scalar_t>(x >> scalar_t{2}) << scalar_t{1};
    const scalar_t j = i + scalar_t{1};
    return ((j*j) > x) ? i : j;
}



// Standard Float version
template<typename scalar_t>
inline LS_INLINE scalar_t math::fast_sqrt(scalar_t input) noexcept
{
    return (scalar_t)math::rcp(math::inversesqrt<float>((float)input));
}



/*-------------------------------------
    to radians
-------------------------------------*/
template<typename scalar_t>
constexpr LS_INLINE scalar_t math::radians(scalar_t degrees) noexcept
{
    return scalar_t{0.01745329251994329577f} * degrees;
}



/*-------------------------------------
    to degrees
-------------------------------------*/
template<typename scalar_t>
constexpr LS_INLINE scalar_t math::degrees(scalar_t radians) noexcept
{
    return scalar_t{57.2957795130823208768f} * radians;
}



/*-------------------------------------
    fast_mod
-------------------------------------*/
template <typename integral_t>
constexpr LS_INLINE integral_t math::fast_mod(const integral_t num, const integral_t denom) noexcept
{
    return (num >= denom) ? num%denom : num;
}



/*-------------------------------------
    log2
-------------------------------------*/
template<typename scalar_t>
inline LS_INLINE scalar_t math::log2(scalar_t n) noexcept
{
    return (scalar_t)math::log2<float>((float)n);
}



/*-------------------------------------
    log2

    Method derived from "Fast Approximate Logarithm, Exponential, Power, and Inverse Root"
        http://www.machinedlearnings.com/2011/06/fast-approximate-logarithm-exponential.html
    This method relies on the IEEE floating point specification
-------------------------------------*/
template<>
inline LS_INLINE float math::log2<float>(float n) noexcept
{
    static_assert(sizeof(float) == sizeof(int32_t), "Need IEEE754 32-bit floats for logarithm calculation.");

    #if 0
    int32_t* const exp = reinterpret_cast<int32_t*>(&n);
    int32_t x = *exp;

    // arithmetic right-shift
    const int32_t log2 = ((x >> 23) & 255) - 128;

    x &= ~(255 << 23);
    x += 127 << 23;

    *exp = x;
    const float ret = (((-0.333333333333f * n) + 2.f) * n) - 0.666666666666f;
    return ret + log2;
    #else
    union { float f; uint32_t i; } vx = { n };
    union { uint32_t i; float f; } mx = { (vx.i & 0x007FFFFFu) | 0x3f000000u };

    float y = (float)vx.i;
    y *= 1.1920928955078125e-7f;

    return ((y - 124.22551499f)
           - (1.498030302f * mx.f))
           - (1.72587999f / (0.3520887068f + mx.f));
    #endif
}



/*-------------------------------------
    log
-------------------------------------*/
template<typename scalar_t>
inline LS_INLINE scalar_t math::log(scalar_t n) noexcept
{
    return math::log2<scalar_t>(n) * 0.69314718056f; // ln( 2 )
}



/*-------------------------------------
    log10
-------------------------------------*/
template<typename scalar_t>
inline LS_INLINE scalar_t math::log10(scalar_t n) noexcept
{
    return (scalar_t)math::log10<float>((float)n);
}



/*-------------------------------------
    log10
-------------------------------------*/
template<>
inline LS_INLINE float math::log10<float>(float n) noexcept
{
    return math::log2<float>(n) * 0.3010299956639812f; // 1.0/log2(10)
}



/*-------------------------------------
    logN
-------------------------------------*/
template<typename scalar_t>
inline LS_INLINE scalar_t math::logN(scalar_t baseN, scalar_t n) noexcept
{
    return math::log2<scalar_t>(n) / log2<scalar_t>(baseN);
}



/*-------------------------------------
    next_pow2
-------------------------------------*/
inline LS_INLINE uint8_t math::next_pow2(uint8_t n) noexcept
{
    if (n == 0)
    {
        return 0;
    }

    --n;
    n |= n >> 1;
    n |= n >> 2;
    n |= n >> 4;
    return ++n;
}

inline LS_INLINE uint16_t math::next_pow2(uint16_t n) noexcept
{
    if (n == 0)
    {
        return 0;
    }

    --n;
    n |= n >> 1;
    n |= n >> 2;
    n |= n >> 4;
    n |= n >> 8;
    return ++n;
}

inline LS_INLINE uint32_t math::next_pow2(uint32_t n) noexcept
{
    if (n == 0)
    {
        return 0;
    }

    --n;
    n |= n >> 1;
    n |= n >> 2;
    n |= n >> 4;
    n |= n >> 8;
    n |= n >> 16;
    return ++n;
}

inline LS_INLINE uint64_t math::next_pow2(uint64_t n) noexcept
{
    if (n == 0)
    {
        return 0;
    }

    --n;
    n |= n >> 1;
    n |= n >> 2;
    n |= n >> 4;
    n |= n >> 8;
    n |= n >> 16;
    n |= n >> 32;
    return ++n;
}



/*-------------------------------------
    next_pow2
-------------------------------------*/
inline LS_INLINE int8_t math::next_pow2(int8_t n) noexcept
{
    return (int8_t)math::next_pow2((uint8_t)n);
}

inline LS_INLINE int16_t math::next_pow2(int16_t n) noexcept
{
    return (int16_t)math::next_pow2((uint16_t)n);
}

inline LS_INLINE int32_t math::next_pow2(int32_t n) noexcept
{
    return (int32_t)math::next_pow2((uint32_t)n);
}

inline LS_INLINE int64_t math::next_pow2(int64_t n) noexcept
{
    return (int64_t)math::next_pow2((uint64_t)n);
}




/*-------------------------------------
    prev_pow2
-------------------------------------*/
inline LS_INLINE uint8_t math::prev_pow2(uint8_t n) noexcept
{
    if (n == 0)
    {
        return 0;
    }

    --n;
    n |= n >> 1;
    n |= n >> 2;
    n |= n >> 4;
    return n - (n >> 1);
}

inline LS_INLINE uint16_t math::prev_pow2(uint16_t n) noexcept
{
    if (n == 0)
    {
        return 0;
    }

    --n;
    n |= n >> 1;
    n |= n >> 2;
    n |= n >> 4;
    n |= n >> 8;
    return n - (n >> 1);
}

inline LS_INLINE uint32_t math::prev_pow2(uint32_t n) noexcept
{
    if (n == 0)
    {
        return 0;
    }

    --n;
    n |= n >> 1;
    n |= n >> 2;
    n |= n >> 4;
    n |= n >> 8;
    n |= n >> 16;
    return n - (n >> 1);
}

inline LS_INLINE uint64_t math::prev_pow2(uint64_t n) noexcept
{
    if (n == 0)
    {
        return 0;
    }

    --n;
    n |= n >> 1;
    n |= n >> 2;
    n |= n >> 4;
    n |= n >> 8;
    n |= n >> 16;
    n |= n >> 32;
    return n - (n >> 1);
}



/*-------------------------------------
    prev_pow2
-------------------------------------*/
inline LS_INLINE int8_t math::prev_pow2(int8_t n) noexcept
{
    return (int8_t)math::prev_pow2((uint8_t)n);
}

inline LS_INLINE int16_t math::prev_pow2(int16_t n) noexcept
{
    return (int16_t)math::prev_pow2((uint16_t)n);
}

inline LS_INLINE int32_t math::prev_pow2(int32_t n) noexcept
{
    return (int32_t)math::prev_pow2((uint32_t)n);
}

inline LS_INLINE int64_t math::prev_pow2(int64_t n) noexcept
{
    return (int64_t)math::prev_pow2((uint64_t)n);
}



/*-------------------------------------
    nearest_pow2
-------------------------------------*/
template <typename data_t>
inline LS_INLINE data_t math::nearest_pow2(typename setup::EnableIf<setup::IsIntegral<data_t>::value, data_t>::type n) noexcept
{
    const data_t pp2 = math::prev_pow2(n);
    const data_t np2 = math::next_pow2(n);
    const data_t lo = n - pp2;
    const data_t hi = np2 - n;

    return lo < hi ? pp2 : np2;
}



/*-------------------------------------
    is_pow2
-------------------------------------*/
template <typename data_t>
constexpr LS_INLINE bool math::is_pow2(typename setup::EnableIf<setup::IsIntegral<data_t>::value, data_t>::type n) noexcept
{
    return (n != 0) && !(n & (n - (data_t)1));
}



/*-------------------------------------
    factorial
-------------------------------------*/
template<typename scalar_t>
constexpr scalar_t math::factorial(scalar_t x) noexcept
{
    return (scalar_t{1.f} < x) ? x * math::factorial(x - scalar_t{1.f}) : scalar_t{1.f};
}



/*-------------------------------------
    pow
-------------------------------------*/
namespace math
{
namespace impl
{
    template <typename scalar_t>
    constexpr scalar_t powi_impl(scalar_t p, scalar_t y, scalar_t result) noexcept
    {
        return (y < scalar_t{1}) ? result : math::impl::powi_impl<scalar_t>(p*p, y / scalar_t{2}, (y & scalar_t{1}) ? (result*p) : result);
    }
} // end impl namespace
} // end math namespace



template <typename scalar_t>
constexpr LS_INLINE scalar_t math::pow(
    typename setup::EnableIf<setup::IsIntegral<scalar_t>::value, scalar_t>::type x,
    typename setup::EnableIf<setup::IsIntegral<scalar_t>::value, scalar_t>::type y) noexcept
{
    return math::impl::powi_impl<scalar_t>(x, y, 1);
}



template<typename scalar_t>
inline LS_INLINE scalar_t math::pow(scalar_t x, scalar_t y) noexcept
{
    return math::exp2<scalar_t>(math::log2<scalar_t>(x) * y);
}



/*-------------------------------------
    exp

    Method derived from "Fast Approximate Logarithm, Exponential, Power, and Inverse Root"
        http://www.machinedlearnings.com/2011/06/fast-approximate-logarithm-exponential.html
    This method relies on the IEEE floating point specification
-------------------------------------*/
template<typename scalar_t>
inline LS_INLINE scalar_t math::exp(scalar_t x) noexcept
{
    /*
    x = scalar_t{1.f} + x / scalar_t{16384.f};

    x *= x;
    x *= x;
    x *= x;
    x *= x;
    x *= x;
    x *= x;
    x *= x;
    x *= x;

    x *= x;
    x *= x;
    x *= x;
    x *= x;
    x *= x;
    x *= x;

    return x;
    */
    float   p      = 1.442695040f * x; // x * 1/ln(2)
    float   offset = (p < 0.f) ? 1.f : 0.f;
    float   clipp  = (p < -126.f) ? -126.f : p;
    int32_t w      = (int32_t)clipp;
    float   z      = clipp - w + offset;

    union {
        uint32_t i;
        float f;
    } const v = {(uint32_t)((1 << 23) * (clipp + 121.2740575f+27.7280233f / (4.84252568f-z) - 1.49012907f*z))};

    return v.f;
}



/*-------------------------------------
    exp2

    Method derived from "Fast Approximate Logarithm, Exponential, Power, and Inverse Root"
        http://www.machinedlearnings.com/2011/06/fast-approximate-logarithm-exponential.html
    This method relies on the IEEE floating point specification
-------------------------------------*/
template<typename scalar_t>
inline LS_INLINE scalar_t math::exp2(scalar_t x) noexcept
{
    /*
    x = scalar_t{1.f} + x * scalar_t{0.002707606174}; // ln(2)/256
    x *= x;
    x *= x;
    x *= x;
    x *= x;
    x *= x;
    x *= x;
    x *= x;
    x *= x;

    return x;
    */
    float   p      = x;
    float   offset = (p < 0.f) ? 1.f : 0.f;
    float   clipp  = (p < -126.f) ? -126.f : p;
    int32_t w      = (int32_t)clipp;
    float   z      = clipp - w + offset;

    union {
        uint32_t i;
        float f;
    } const v = {(uint32_t)((1 << 23) * (clipp + 121.2740575f+27.7280233f / (4.84252568f-z) - 1.49012907f*z))};

    return v.f;
}



/*-------------------------------------
    sin
-------------------------------------*/
template<typename scalar_t>
constexpr LS_INLINE scalar_t math::sin(typename setup::EnableIf<!setup::IsFloat<scalar_t>::value, scalar_t>::type x) noexcept
{
    //static_assert(setup::IsFloat<scalar_t>::value, "Input value is not a floating-point type.");

    return x
           - (x * x * x / scalar_t{6.0})
           + (x * x * x * x * x / scalar_t{120.0})
           - (x * x * x * x * x * x * x / scalar_t{5040.0})
           + (x * x * x * x * x * x * x * x * x / scalar_t{362880.0});
}

// Alternate (non-taylor-series) method found here:
// https://blog.demofox.org/2014/11/04/four-ways-to-calculate-sine-without-trig/
namespace
{
    template <typename scalar_t>
    constexpr LS_INLINE scalar_t sin_step(scalar_t x) noexcept
    {
        return x * x * (scalar_t{3.0} - scalar_t{2.0} * x) * scalar_t{2.0} - scalar_t{1.0};
    }
}

template<typename scalar_t>
constexpr LS_INLINE scalar_t math::sin(scalar_t x) noexcept
{
    static_assert(setup::IsFloat<scalar_t>::value, "Input value is not a floating-point type.");
    return sin_step(ls::math::abs(ls::math::fract((x - scalar_t{LS_PI_OVER_2}) / scalar_t{LS_TWO_PI}) * scalar_t{2.0} - scalar_t{1.0}));
}



/*-------------------------------------
    cos
-------------------------------------*/
template<typename scalar_t>
constexpr LS_INLINE scalar_t math::cos(typename setup::EnableIf<!setup::IsFloat<scalar_t>::value, scalar_t>::type x) noexcept
{
    //static_assert(setup::IsFloat<scalar_t>::value, "Input value is not a floating-point type.");

    return scalar_t{1.0}
           - (x * x / scalar_t{2.0})
           + (x * x * x * x / scalar_t{24.0})
           - (x * x * x * x * x * x / scalar_t{720.0})
           + (x * x * x * x * x * x * x * x / scalar_t{40320.0});
}

// Alternate (non-taylor-series) method found here:
// https://blog.demofox.org/2014/11/04/four-ways-to-calculate-sine-without-trig/
namespace
{
    template <typename scalar_t>
    constexpr LS_INLINE scalar_t cos_step(scalar_t x) noexcept
    {
        return x * x * (scalar_t{3.0} - scalar_t{2.0} * x) * scalar_t{2.0} - scalar_t{1.0};
    }
}

template<typename scalar_t>
constexpr LS_INLINE scalar_t math::cos(scalar_t x) noexcept
{
    static_assert(setup::IsFloat<scalar_t>::value, "Input value is not a floating-point type.");
    return cos_step(ls::math::abs(ls::math::fract(x / scalar_t{LS_TWO_PI}) * scalar_t{2.0} - scalar_t{1.0}));
}



/*-------------------------------------
    tan
-------------------------------------*/
template<typename scalar_t>
constexpr LS_INLINE scalar_t math::tan(scalar_t x) noexcept
{
    //static_assert(setup::IsFloat<scalar_t>::value, "Input value is not a floating-point type.");
    return math::sin<scalar_t>(x) / math::cos<scalar_t>(x);
}



/*-------------------------------------
    atan2

    Reference implementation found here:
    https://dspguru.com/dsp/tricks/fixed-point-atan2-with-self-normalization/
-------------------------------------*/
template <typename scalar_t>
inline scalar_t math::atan2(scalar_t y, scalar_t x) noexcept
{
    //constexpr scalar_t cos10_9999 = scalar_t{0.9817};
    //constexpr scalar_t sin11_3222 = scalar_t{0.1963};

    constexpr scalar_t coeff_1 = scalar_t{LS_PI_OVER_4};
    constexpr scalar_t coeff_2 = scalar_t{3.f} * scalar_t{LS_PI_OVER_4};

    scalar_t absY = math::abs(y) + 1e-10f;
    scalar_t angle;

    if (x >= scalar_t{0})
    {
        scalar_t r = (x - absY) / (absY + x);
        angle = coeff_1 - coeff_1 * r;
        //angle = sin11_3222 * r * r * r - cos10_9999 * r + coeff_1;
    }
    else
    {
        scalar_t r = (x + absY) / (absY - x);
        angle = coeff_2 - coeff_1 * r;
        //angle = sin11_3222 * r * r * r - cos10_9999 * r + coeff_2;
    }

    // negate if in quad III or IV
    if (y < scalar_t{0})
    {
        return -angle;
    }

    return angle;
}



/*-------------------------------------
    rcp
-------------------------------------*/
template<typename scalar_t>
constexpr LS_INLINE scalar_t math::rcp(const scalar_t& num) noexcept
{
    static_assert(setup::IsFloat<scalar_t>::value, "Input value is not a floating-point type.");
    return scalar_t{1.f} / num;
}



/*-------------------------------------
    sum
-------------------------------------*/
template<typename scalar_t>
constexpr LS_INLINE scalar_t math::sum(const scalar_t& num) noexcept
{
    return num;
}



/*-------------------------------------
    sum
-------------------------------------*/
template<typename scalar_t, typename... scalars_t>
constexpr scalar_t math::sum(const scalar_t& num, const scalars_t& ... nums) noexcept
{
    return num + math::sum<scalars_t...>(nums...);
}



/*-------------------------------------
    sum_inv
-------------------------------------*/
template<typename scalar_t>
constexpr LS_INLINE scalar_t math::sum_inv(const scalar_t& num) noexcept
{
    return math::rcp<scalar_t>(num);
}



/*-------------------------------------
    sum_inv
-------------------------------------*/
template<typename scalar_t, typename... scalars_t>
constexpr LS_INLINE scalar_t math::sum_inv(const scalar_t& num, const scalars_t& ... nums) noexcept
{
    return math::rcp<scalar_t>(num + math::sum<scalars_t...>(nums...));
}



/*-------------------------------------
    average
-------------------------------------*/
template<typename scalar_t>
constexpr LS_INLINE scalar_t math::average() noexcept
{
    return scalar_t(0);
}



/*-------------------------------------
    average
-------------------------------------*/
template<typename scalar_t, typename... scalars_t>
constexpr LS_INLINE scalar_t math::average(const scalar_t& num, const scalars_t& ... nums) noexcept
{
    return math::sum(num, nums...) / scalar_t(sizeof...(scalars_t) + 1);
}



/*-------------------------------------
    Count the number of bits in an integer.
-------------------------------------*/
constexpr unsigned math::count_set_bits(const unsigned long long num) noexcept
{
    return num ? math::count_set_bits(num >> 1) + (1 & num) : 0;
}

template<typename scalar_t>
constexpr unsigned math::count_set_bits(const scalar_t num) noexcept
{
    return math::count_set_bits((unsigned long long)num);
}



/*-------------------------------------
    Scale a number from one number range to another.
-------------------------------------*/
template<typename in_type, typename out_type>
constexpr LS_INLINE out_type math::scale_to_range(
    const in_type num,
    const out_type oldMin,
    const out_type oldMax,
    const out_type newMin,
    const out_type newMax
) noexcept
{
    return (((num - oldMin) * (newMax - newMin)) / (oldMax - oldMin)) + newMin;
}



/*-------------------------------------
    Get a number's sign bit
-------------------------------------*/
template <typename data_t>
constexpr LS_INLINE int math::sign_mask(typename setup::EnableIf<setup::IsUnsigned<data_t>::value, data_t>::type) noexcept
{
    return 0;
}

template <typename data_t>
constexpr LS_INLINE int math::sign_mask(data_t x) noexcept
{
    return x < data_t{0};
}



/*-------------------------------------
    Determine if the sign-bit is set
-------------------------------------*/
template <typename data_t>
constexpr LS_INLINE data_t math::sign(
    typename setup::EnableIf<setup::IsIntegral<data_t>::value, data_t>::type x
) noexcept
{
    return setup::IsSigned<data_t>::value ? (int)(x >> (((sizeof(data_t)*CHAR_BIT)-1)) & 0x01) : 0;
}

template <typename data_t>
constexpr LS_INLINE data_t math::sign(data_t x) noexcept
{
    return (setup::IsSigned<data_t>::value  && (x < data_t{0})) ? data_t{1} : data_t{0};
}



/*-------------------------------------
    Absolute Value
-------------------------------------*/
namespace math
{
    namespace impl
    {
        template <typename data_t>
        constexpr LS_INLINE data_t abs(data_t x, data_t mask) noexcept
        {
            return (x^mask) - mask;
        }
    }
}

template <typename data_t>
constexpr LS_INLINE data_t math::abs(typename setup::EnableIf<setup::IsIntegral<data_t>::value, data_t>::type x) noexcept
{
    return setup::IsUnsigned<data_t>::value ? x : math::impl::abs<data_t>(x, x >> ((sizeof(data_t)*CHAR_BIT)-(data_t)1));
}

template <typename data_t>
constexpr LS_INLINE data_t math::abs(data_t x) noexcept
{
    return (x >= data_t{0}) ? x : -x;
}



/*-------------------------------------
    FMA
-------------------------------------*/
template <typename data_t>
constexpr LS_INLINE data_t math::fmadd(data_t x, data_t m, data_t a) noexcept
{
    return (x*m)+a;
}



/*-------------------------------------
    FMS
-------------------------------------*/
template <typename data_t>
constexpr LS_INLINE data_t math::fmsub(data_t x, data_t m, data_t a) noexcept
{
    return (x*m)-a;
}



} /* end ls namespace */
