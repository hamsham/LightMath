
namespace ls {

/*-----------------------------------------------------------------------------
// Function definitions
-----------------------------------------------------------------------------*/

/*-------------------------------------
    min
-------------------------------------*/
template <typename scalar_t> constexpr
scalar_t math::min(scalar_t a, scalar_t b) {
    return (a < b) ? a : b;
}

/*-------------------------------------
    mix
-------------------------------------*/
template <typename scalar_t> constexpr
scalar_t math::mix(scalar_t a, scalar_t b, scalar_t percent) {
    return a + ((b - a) * percent);
}

/*-------------------------------------
    mac
-------------------------------------*/
template <typename scalar_t> constexpr
scalar_t math::max(scalar_t a, scalar_t b) {
    return (a > b) ? a : b;
}

/*-------------------------------------
    clamp
-------------------------------------*/
template <typename scalar_t>
constexpr scalar_t math::clamp(scalar_t n, scalar_t minVal, scalar_t maxVal) {
    return (n < minVal) ? minVal : (n > maxVal) ? maxVal : n;
}

/*-------------------------------------
    floor
-------------------------------------*/
template <typename float_t>
constexpr float_t math::floor(const float_t n) {
    return (float_t) ((long long) n - (n >= float_t{0} ? 0 : 1));
}

/*-------------------------------------
    ranged-floor
-------------------------------------*/
template <typename float_t, typename int_t, int_t range>
constexpr int_t math::ranged_floor(const float_t n) {
    return (int_t)(n + (float_t)range) - range;
}

/*-------------------------------------
    ceil
-------------------------------------*/
template <typename float_t>
constexpr float_t math::ceil(const float_t n) {
    return (float_t) ((long long) n + (n >= float_t{0.0} ? 1 : 0));
}

/*-------------------------------------
    ranged-ceil
-------------------------------------*/
template <typename float_t, typename int_t, int_t range>
constexpr int_t math::ranged_ceil(const float_t n) {
    return range - (int_t)((float_t)range - n);
}

/*-------------------------------------
    round
-------------------------------------*/
template <typename float_t>
constexpr float_t math::round(const float_t n) {
    return math::floor(n + float_t{0.5});
}

/*-------------------------------------
    fract
-------------------------------------*/
template <typename float_t>
constexpr float_t math::fract(const float_t n) {
    return n - math::floor(n);
}

/*-------------------------------------
 fmod
-------------------------------------*/
template <typename float_t>
inline float_t math::fmod(const float_t n1, const float_t n2) {
    if (n2 == float_t{0.0}) {
        return float_t{0.0};
    }
    
    const float_t f = n1 - (math::floor(n1/n2)*n2);
    
    return ((n1 < float_t{0.0}) != (n2 < float_t{0.0}))
        ? f-n2
        : f;
    
}

/*-------------------------------------
    smoothstep
-------------------------------------*/
namespace math {
namespace impl {

template <typename scalar_t> constexpr
scalar_t smoothstep_impl(const scalar_t& t) {
    return (scalar_t{3}
    *t * t * t) - (scalar_t{2}
    *t * t);
}
} // math::impl namespace
} // math namespace

template <typename scalar_t> constexpr
scalar_t math::smoothstep(scalar_t a, scalar_t b, scalar_t x) {
    return (x <= a)
        ? scalar_t {0}
        : (x >= b)
            ? scalar_t {1}
            : impl::smoothstep_impl(x - a) / (b - a);
}

/*-------------------------------------
    fastInvSqrt
-------------------------------------*/
template <typename scalar_t> inline
scalar_t math::fast_inv_sqrt(scalar_t input) {
    return (scalar_t) fast_inv_sqrt<float>((float) input);
}

/*-------------------------------------
    fastSqrt
-------------------------------------*/
template <typename scalar_t> inline
scalar_t math::fast_sqrt(scalar_t input) {
    return scalar_t(1.0f / fast_inv_sqrt<scalar_t>(input));
}

/*-------------------------------------
    fastInvSqrt

    The fast inverse square root method adopted for regular square rooting.
    this method was found at:
        http://rrrola.wz.cz/inv_sqrt.html
    and:
        http://jheriko-rtw.blogspot.com/2009/04/understanding-and-improving-fast.html
-------------------------------------*/
template <> inline
float math::fast_inv_sqrt<float>(float x) {
    union {
        float f;
        unsigned int u;
    } y = {x};
    y.u = 0x5F1FFFF9ul - (y.u >> 1);
    return 0.703952253f * y.f * (2.38924456f - x * y.f * y.f);
}

/*-------------------------------------
    fastInvSqrt
-------------------------------------*/
template <> inline
float math::fast_sqrt<float>(float input) {
    return float
    {
        1.0f / fast_inv_sqrt<float>(input)
    };
}

/*-------------------------------------
    degToRad
-------------------------------------*/
template <typename scalar_t> constexpr
scalar_t math::deg_to_rad(scalar_t input) {
    return LS_DEG2RAD(input);
}

/*-------------------------------------
    radToDeg
-------------------------------------*/
template <typename scalar_t> constexpr
scalar_t math::rad_to_deg(scalar_t input) {
    return LS_RAD2DEG(input);
}

/*-------------------------------------
    fastLog2
-------------------------------------*/
template <typename scalar_t> inline
scalar_t math::fast_log2(scalar_t n) {
    return (scalar_t) fast_log2<float>((float) n);
}

/*-------------------------------------
    fastLog2

    Fast Approximate logarithms
    This method was found on flipcode:
        http://www.flipcode.com/archives/Fast_log_Function.shtml
    Accurate to within 5 decimal places.
    This method relies on the IEEE floating point specification
-------------------------------------*/
template <> inline
float math::fast_log2<float>(float n) {
    long* const exp = reinterpret_cast<long*> (&n);
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
template <typename scalar_t> inline
scalar_t math::fast_log10(scalar_t n) {
    return fast_log2<scalar_t>(n) * 0.693147181f; // ln( 2 )
}

/*-------------------------------------
    fastLogN
-------------------------------------*/
template <typename scalar_t> inline
scalar_t math::fast_logN(scalar_t baseN, scalar_t n) {
    return fast_log2<scalar_t>(n) / fast_log2<scalar_t>(baseN);
}

/*-------------------------------------
    nextPow2
-------------------------------------*/
inline unsigned math::next_pow2(unsigned n) {
    if (n == 0) {
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
inline int math::next_pow2(int n) {
    return (int) next_pow2((unsigned) n);
}

/*-------------------------------------
    prevPow2
-------------------------------------*/
inline unsigned math::prev_pow2(unsigned n) {
    if (n == 0) {
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
inline int math::prev_pow2(int n) {
    return (int) prev_pow2((unsigned) n);
}

/*-------------------------------------
    nearPow2
-------------------------------------*/
inline unsigned math::nearest_pow2(unsigned n) {
    const unsigned pp2 = prev_pow2(n);
    const unsigned np2 = next_pow2(n);
    const unsigned lo = n - pp2;
    const unsigned hi = np2 - n;

    return lo < hi ? pp2 : np2;
}

/*-------------------------------------
    nearPow2
-------------------------------------*/
inline int math::nearest_pow2(int n) {
    return (int) nearest_pow2((unsigned) n);
}

/*-------------------------------------
    isPow2
-------------------------------------*/
constexpr bool math::is_pow2(unsigned n) {
    return n && !(n & (n - 1));
}

/*-------------------------------------
    isPow2
-------------------------------------*/
constexpr bool math::is_pow2(int n) {
    return (int) is_pow2((unsigned) n);
}

/*-------------------------------------
    factorial
-------------------------------------*/
template <typename scalar_t>
constexpr scalar_t math::factorial(scalar_t x) {
    return (1 < x) ? x * factorial(x - 1) : 1;
}

/*-------------------------------------
    pow
-------------------------------------*/
template <typename scalar_t, typename int_t>
constexpr scalar_t math::pow(scalar_t x, int_t y) {
    return (0 < y) ? x * pow(x, y - 1) : 1;
}

/*-------------------------------------
    const_sin
-------------------------------------*/
template <typename scalar_t>
constexpr scalar_t math::const_sin(scalar_t x) {
    return x
        - (x * x * x * scalar_t(1.f / 6))
        +(x * x * x * x * x * scalar_t(1.f / 120))
        -(x * x * x * x * x * x * x * scalar_t(1.f / 5040))
        +(x * x * x * x * x * x * x * x * x * scalar_t(1.f / 362880));
}

/*-------------------------------------
    const_cos
-------------------------------------*/
template <typename scalar_t>
constexpr scalar_t math::const_cos(scalar_t x) {
    return 1
    - (x * x * scalar_t(1.f / 2))
        +(x * x * x * x * scalar_t(1.f / 4))
        -(x * x * x * x * x * x * scalar_t(1.f / 720))
        +(x * x * x * x * x * x * x * x * scalar_t(1.f / 40320));
}

/*-------------------------------------
    const_tan
-------------------------------------*/
template <typename scalar_t>
constexpr scalar_t math::const_tan(scalar_t x) {
    return x
        + (x * x * x * scalar_t(1.f / 3))
        +(x * x * x * x * x * scalar_t(2.f / 15))
        +(x * x * x * x * x * x * x * scalar_t(17.f / 315))
        +(x * x * x * x * x * x * x * x * x * scalar_t(62.f / 2835));
}

/*-------------------------------------
    sum
-------------------------------------*/
template <typename scalar_t>
constexpr scalar_t math::sum(const scalar_t& num) {
    return num;
}

/*-------------------------------------
    sum
-------------------------------------*/
template <typename scalar_t, typename... scalars_t>
constexpr scalar_t math::sum(const scalar_t& num, const scalars_t&... nums) {
    return num + sum(nums...);
}

/*-------------------------------------
    average
-------------------------------------*/
template <typename scalar_t>
constexpr scalar_t math::average() {
    return scalar_t(0);
}

/*-------------------------------------
    average
-------------------------------------*/
template <typename scalar_t, typename... scalars_t>
constexpr scalar_t math::average(const scalar_t& num, const scalars_t&... nums) {
    return sum(num, nums...) / scalar_t(sizeof...(scalars_t) + 1);
}

/*-------------------------------------
    Count the number of bits in an integer.
-------------------------------------*/
constexpr unsigned math::count_set_bits(const unsigned long long num) {
    return num ? count_set_bits(num >> 1) + (1 & num) : 0;
}

template <typename scalar_t>
constexpr unsigned math::count_set_bits(const scalar_t num) {
    return count_set_bits((unsigned long long) num);
}

/*-------------------------------------
    Scale a number from one number range to another.
-------------------------------------*/
template <typename in_type, typename out_type>
constexpr out_type math::scale_num_to_range(
    const in_type num,
    const out_type oldMin,
    const out_type oldMax,
    const out_type newMin,
    const out_type newMax
) {
    return (((num - oldMin) * (newMax - newMin)) / (oldMax - oldMin)) + newMin;
}

} /* end ls namespace */
