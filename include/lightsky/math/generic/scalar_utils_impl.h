


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
constexpr scalar_t math::min(scalar_t a, scalar_t b) noexcept
{
    return (a < b) ? a : b;
}



/*-------------------------------------
    min
-------------------------------------*/
template<typename scalar_t, typename... scalars_t>
constexpr scalar_t math::min(const scalar_t& a, const scalar_t& b, const scalars_t& ... nums) noexcept
{
    return math::min<scalar_t>(math::min<scalar_t>(a, b), nums...);
}



/*-------------------------------------
    mix
-------------------------------------*/
template<typename scalar_t>
constexpr scalar_t math::mix(scalar_t a, scalar_t b, scalar_t percent) noexcept
{
    return a + ((b - a) * percent);
}



/*-------------------------------------
    max
-------------------------------------*/
template<typename scalar_t>
constexpr scalar_t math::max(scalar_t a, scalar_t b) noexcept
{
    return (a > b) ? a : b;
}



/*-------------------------------------
    max
-------------------------------------*/
template<typename scalar_t, typename... scalars_t>
constexpr scalar_t math::max(const scalar_t& a, const scalar_t& b, const scalars_t& ... nums) noexcept
{
    return math::max<scalar_t>(math::max<scalar_t>(a, b), nums...);
}



/*-------------------------------------
    clamp
-------------------------------------*/
template<typename scalar_t>
constexpr scalar_t math::clamp(scalar_t n, scalar_t minVal, scalar_t maxVal) noexcept
{
    return (n < minVal) ? minVal : (n > maxVal) ? maxVal : n;
}



/*-------------------------------------
    floor
-------------------------------------*/
template<typename floating_t>
constexpr floating_t math::floor(const floating_t n) noexcept
{
    return static_cast<floating_t>(static_cast<long long>(n) - (n < floating_t{0}));
}



/*-------------------------------------
    ranged-floor
-------------------------------------*/
template<typename floating_t, typename int_t, int_t range>
constexpr int_t math::ranged_floor(const floating_t n) noexcept
{
    return (int_t)(n + (floating_t)range) - range;
}



/*-------------------------------------
    ceil
-------------------------------------*/
template<typename floating_t>
constexpr floating_t math::ceil(const floating_t n) noexcept
{
    return (floating_t)((long long)n + (n >= floating_t{0} ? floating_t{1} : floating_t{0}));
}



/*-------------------------------------
    ranged-ceil
-------------------------------------*/
template<typename floating_t, typename int_t, int_t range>
constexpr int_t math::ranged_ceil(const floating_t n) noexcept
{
    return range - (int_t)((floating_t)range - n);
}



/*-------------------------------------
    round
-------------------------------------*/
template<typename floating_t>
constexpr floating_t math::round(const floating_t n) noexcept
{
    return math::floor<floating_t>(n + floating_t{0.5f});
}



/*-------------------------------------
    fract
-------------------------------------*/
template<typename floating_t>
constexpr floating_t math::fract(const floating_t n) noexcept
{
    return n - math::floor<floating_t>(n);
}



/*-------------------------------------
 fmod
-------------------------------------*/
template<typename floating_t>
constexpr floating_t math::fmod(const floating_t n1, const floating_t n2) noexcept
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
constexpr floating_t math::fmod_1(const floating_t n) noexcept
{
    return (n - math::floor<floating_t>(n)) - (floating_t)(n < floating_t{0});
}



/*-------------------------------------
    smoothstep
-------------------------------------*/
namespace math
{
namespace impl
{
    template<typename scalar_t>
    constexpr scalar_t smoothstep_impl(const scalar_t t) noexcept
    {
        return (scalar_t{3} * t * t * t) - (scalar_t{2} * t * t);
    }
} // math::impl namespace
} // math namespace



template<typename scalar_t>
constexpr scalar_t math::smoothstep(scalar_t a, scalar_t b, scalar_t x) noexcept
{
    return (x <= a)
           ? scalar_t{0}
           : (x >= b)
             ? scalar_t{1}
             : math::impl::smoothstep_impl<scalar_t>(x - a) / (b - a);
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
inline scalar_t math::fast_inv_sqrt(scalar_t input) noexcept
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
inline scalar_t math::fast_sqrt(typename utils::EnableIf<IsIntegral<scalar_t>::value, scalar_t>::type x) noexcept
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
inline scalar_t math::fast_sqrt(scalar_t input) noexcept
{
    return (scalar_t)(1.f / math::fast_inv_sqrt<float>((float)input));
}



/*-------------------------------------
    degToRad
-------------------------------------*/
template<typename scalar_t>
constexpr scalar_t math::deg_to_rad(scalar_t input) noexcept
{
    return LS_DEG2RAD(input);
}



/*-------------------------------------
    radToDeg
-------------------------------------*/
template<typename scalar_t>
constexpr scalar_t math::rad_to_deg(scalar_t input) noexcept
{
    return LS_RAD2DEG(input);
}



/*-------------------------------------
    fast_mod
-------------------------------------*/
template <typename integral_t>
constexpr integral_t math::fast_mod(const integral_t num, const integral_t denom) noexcept
{
    return (num >= denom) ? num%denom : num;
}



/*-------------------------------------
    fastLog2
-------------------------------------*/
template<typename scalar_t>
inline scalar_t math::fast_log2(scalar_t n) noexcept
{
    return (scalar_t)math::fast_log2<float>((float)n);
}



/*-------------------------------------
    fastLog2

    Fast Approximate logarithms
    This method was found on flipcode:
        http://www.flipcode.com/archives/Fast_log_Function.shtml
    Accurate to within 5 decimal places.
    This method relies on the IEEE floating point specification
-------------------------------------*/
template<>
inline float math::fast_log2<float>(float n) noexcept
{
    long* const exp = reinterpret_cast<long*>(&n);
    long x = *exp;

    const long log2 = ((x >> 23) & 255) - 128;

    x &= ~(255 << 23);
    x += 127 << 23;

    *exp = x;
    const float ret = ((-1.f / 3.f) * n + 2.f) * n - 2.f / 3.f;
    return ret + log2;
}



/*-------------------------------------
    fastLog
-------------------------------------*/
template<typename scalar_t>
inline scalar_t math::fast_log(scalar_t n) noexcept
{
    return math::fast_log2<scalar_t>(n) * 0.693147181f; // ln( 2 )
}



/*-------------------------------------
    fastLogN
-------------------------------------*/
template<typename scalar_t>
inline scalar_t math::fast_logN(scalar_t baseN, scalar_t n) noexcept
{
    return math::fast_log2<scalar_t>(n) / fast_log2<scalar_t>(baseN);
}



/*-------------------------------------
    nextPow2
-------------------------------------*/
inline unsigned math::next_pow2(unsigned n) noexcept
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



/*-------------------------------------
    nextPow2
-------------------------------------*/
inline int math::next_pow2(int n) noexcept
{
    return (int)math::next_pow2((unsigned)n);
}



/*-------------------------------------
    prevPow2
-------------------------------------*/
inline unsigned math::prev_pow2(unsigned n) noexcept
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



/*-------------------------------------
    prevPow2
-------------------------------------*/
inline int math::prev_pow2(int n) noexcept
{
    return (int)math::prev_pow2((unsigned)n);
}



/*-------------------------------------
    nearPow2
-------------------------------------*/
inline unsigned math::nearest_pow2(unsigned n) noexcept
{
    const unsigned pp2 = math::prev_pow2(n);
    const unsigned np2 = math::next_pow2(n);
    const unsigned lo = n - pp2;
    const unsigned hi = np2 - n;

    return lo < hi ? pp2 : np2;
}



/*-------------------------------------
    nearPow2
-------------------------------------*/
inline int math::nearest_pow2(int n) noexcept
{
    return (int)math::nearest_pow2((unsigned)n);
}



/*-------------------------------------
    isPow2
-------------------------------------*/
constexpr bool math::is_pow2(unsigned n) noexcept
{
    return n && !(n & (n - 1));
}



/*-------------------------------------
    isPow2
-------------------------------------*/
constexpr bool math::is_pow2(int n) noexcept
{
    return (int)math::is_pow2((unsigned)n);
}



/*-------------------------------------
    factorial
-------------------------------------*/
template<typename scalar_t>
constexpr scalar_t math::factorial(scalar_t x) noexcept
{
    return (1 < x) ? x * math::factorial(x - 1) : 1;
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
        return (y < scalar_t{1}) ? result : math::impl::powi_impl<scalar_t>(p*p, y >> scalar_t{2}, (y & scalar_t{1}) ? (result*p) : result);
    }
} // end impl namespace
} // end math namespace



template <typename scalar_t>
constexpr scalar_t math::pow(
    typename utils::EnableIf<math::IsIntegral<scalar_t>::value, scalar_t>::type x,
    typename utils::EnableIf<math::IsIntegral<scalar_t>::value, scalar_t>::type y) noexcept
{
    return math::impl::powi_impl<scalar_t>(x, y, 1);
}



template<typename scalar_t>
constexpr scalar_t math::pow(scalar_t x, scalar_t y) noexcept
{
    return math::exp<scalar_t>(math::fast_log<scalar_t>(x) * y);
}



/*-------------------------------------
    exp
-------------------------------------*/
template<typename scalar_t>
inline scalar_t math::exp(scalar_t x) noexcept
{
    x = 1.f + x / 256.f;
    x *= x;
    x *= x;
    x *= x;
    x *= x;
    x *= x;
    x *= x;
    x *= x;
    x *= x;

    return x;
}



/*-------------------------------------
    const_sin
-------------------------------------*/
template<typename scalar_t>
constexpr scalar_t math::const_sin(scalar_t x) noexcept
{
    static_assert(math::IsFloat<scalar_t>::value, "Input value is not a floating-point type.");

    return x
           - (x * x * x * (scalar_t{1} / scalar_t{6}))
           + (x * x * x * x * x * (scalar_t{1} / scalar_t{120}))
           - (x * x * x * x * x * x * x * (scalar_t{1} / scalar_t{5040}))
           + (x * x * x * x * x * x * x * x * x * (scalar_t{1} / scalar_t{362880}));
}



/*-------------------------------------
    const_cos
-------------------------------------*/
template<typename scalar_t>
constexpr scalar_t math::const_cos(scalar_t x) noexcept
{
    static_assert(math::IsFloat<scalar_t>::value, "Input value is not a floating-point type.");

    return scalar_t{1}
           - (x * x * (scalar_t{1} / scalar_t{2}))
           + (x * x * x * x * (scalar_t{1} / scalar_t{24}))
           - (x * x * x * x * x * x * (scalar_t{1} / scalar_t{720}))
           + (x * x * x * x * x * x * x * x * (scalar_t{1} / scalar_t{40320}));
}



/*-------------------------------------
    const_tan
-------------------------------------*/
template<typename scalar_t>
constexpr scalar_t math::const_tan(scalar_t x) noexcept
{
    static_assert(math::IsFloat<scalar_t>::value, "Input value is not a floating-point type.");

    return x
           + (x * x * x * (scalar_t{1} / scalar_t{3}))
           + (x * x * x * x * x * (scalar_t{2} / scalar_t{15}))
           + (x * x * x * x * x * x * x * (scalar_t{17} / scalar_t{315}))
           + (x * x * x * x * x * x * x * x * x * (scalar_t{62} / scalar_t{2835}));
}



/*-------------------------------------
    rcp
-------------------------------------*/
template<typename scalar_t>
constexpr scalar_t math::rcp(const scalar_t& num) noexcept
{
    static_assert(math::IsFloat<scalar_t>::value, "Input value is not a floating-point type.");
    return scalar_t{1} / num;
}



/*-------------------------------------
    sum
-------------------------------------*/
template<typename scalar_t>
constexpr scalar_t math::sum(const scalar_t& num) noexcept
{
    return num;
}



/*-------------------------------------
    sum
-------------------------------------*/
template<typename scalar_t, typename... scalars_t>
constexpr scalar_t math::sum(const scalar_t& num, const scalars_t& ... nums) noexcept
{
    return num + math::sum(nums...);
}



/*-------------------------------------
    sum_inv
-------------------------------------*/
template<typename scalar_t>
constexpr scalar_t math::sum_inv(const scalar_t& num) noexcept
{
    return scalar_t{1} / num;
}



/*-------------------------------------
    sum_inv
-------------------------------------*/
template<typename scalar_t, typename... scalars_t>
constexpr scalar_t math::sum_inv(const scalar_t& num, const scalars_t& ... nums) noexcept
{
    return scalar_t{1} / (num + math::sum(nums...));
}



/*-------------------------------------
    average
-------------------------------------*/
template<typename scalar_t>
constexpr scalar_t math::average() noexcept
{
    return scalar_t(0);
}



/*-------------------------------------
    average
-------------------------------------*/
template<typename scalar_t, typename... scalars_t>
constexpr scalar_t math::average(const scalar_t& num, const scalars_t& ... nums) noexcept
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
constexpr out_type math::scale_num_to_range(
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
constexpr int math::sign_bit(
    typename utils::EnableIf<math::IsIntegral<data_t>::value, data_t>::type x
) noexcept
{
    return math::IsSigned<data_t>::value ? (int)(x >> (((sizeof(data_t)*CHAR_BIT)-1)) & 0x01) : 0;
}

template <typename data_t>
constexpr int math::sign_bit(data_t x) noexcept
{
    return math::IsSigned<data_t>::value ? (x < data_t{0}) : 0;
}



} /* end ls namespace */
