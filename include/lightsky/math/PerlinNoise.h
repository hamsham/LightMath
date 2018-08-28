/*
 * File:   math/perlinNoise.h
 * Author: miles
 *
 * Created on August 15, 2014, 9:23 PM
 */

#ifndef LS__MATH_PERLIN_NOISE_H
#define LS__MATH_PERLIN_NOISE_H

#include <chrono>
#include <utility> // std::move

#include "lightsky/setup/Api.h"

#include "lightsky/math/vec3.h"
#include "lightsky/utils/Copy.h"
#include "lightsky/utils/RandomNum.h"

namespace ls {
namespace math {



/**
 * @brief Simple class to generate Perlin noise
 *
 * Most of the code for this is based on a tutorial found here:
 * http://flafla2.github.io/2014/08/09/perlinnoise.html
 */
template <typename num_t = float>
class LS_API PerlinNoise {
  private:
    /**
     * Pointer to a pseudo-random number generator that will be used to
     * generate random noise.
     */
    utils::RandomNum* prng = nullptr;

    /**
     * An array of 512 randomly ordered integers that are used to generate
     * noise.
     */
    int* permutations = nullptr;

    /**
     * Helper function to blend different noise values.
     *
     * @param num_t
     *
     * @return num_t
     */
    static double fade(double) noexcept;

    /**
     * Linearly interpolate two values over a certain percentage.
     *
     * @param a
     * The value to be interpolated to B.
     *
     * @param b
     * A reference value that A will interpolate towards.
     *
     * @param x
     * The percent to interpolate A->B
     *
     * @return A linear interpolation of A->B
     */
    static double lerp(double a, double b, double x) noexcept;

    /**
     * Generate a gradient value based on a hash function at the points x,
     * y, and z.
     *
     * @param hash
     *
     * @param x
     *
     * @param y
     *
     * @param z
     *
     * @return A gradient value that will assist in smoothly transitioning
     * from one set of points to another.
     */
    static double grad(int hash, double x, double y, double z) noexcept;

  public:
    /**
     * Destructor
     * Frees all memory used by *this.
     */
    ~PerlinNoise() noexcept;

    /**
     * Constructor
     */
    PerlinNoise() noexcept;

    /**
     * Seed Constructor
     *
     * @param s
     * A long, unsigned integral value that will be used to seed the random
     * number generator.
     */
    explicit PerlinNoise(unsigned long s) noexcept;

    /**
     * Copy Constructor
     *
     * @param A constant reference to another Perlin noise object
     */
    PerlinNoise(const PerlinNoise&) noexcept;

    /**
     * Move Constructor
     * Moves all data from the input parameter into *this. No copies are
     * performed.
     *
     * @param An R-Value reference to a Perlin noise object that's about to
     * go out of scope.
     */
    PerlinNoise(PerlinNoise&&) noexcept;

    /**
     * Copy Operator
     *
     * @param A constant reference to another Perlin noise object
     *
     * @return A reference to *this.
     */
    PerlinNoise& operator=(const PerlinNoise&) noexcept;

    /**
     * Move Operator
     *
     * @param An R-Value reference to a Perlin noise object that's about to
     * go out of scope.
     *
     * @return A reference to *this.
     */
    PerlinNoise& operator=(PerlinNoise&&) noexcept;

    /**
     * Seed the random number generator in order to generate new noise.
     */
    void seed() noexcept;

    /**
     * Seed the random number generator in order to generate new noise.
     *
     * @param s
     * A long, unsigned integral value that will be used to seed the random
     * number generator.
     */
    void seed(unsigned long s) noexcept;

    /**
     * Get a [pseudo] randomly generated noise value within a 3D Cartesian
     * coordinate space.
     *
     * @param point
     * A point within a linear 3D space from which a noise value will be
     * calculated.
     *
     * @return A Perlin noise value, calculated at the point specified by
     * the input parameter. This value will be between [-1,1].
     */
    template <typename point_t>
    num_t get_noise(const vec3_t<point_t>& point) const noexcept;

    /**
     * Get a [pseudo] randomly generated noise value within a 3D Cartesian
     * coordinate space. This value will be modified by a frequency
     * specified by the number of octaves and persistence provided.
     *
     * @see http://freespace.virgin.net/hugo.elias/models/m_perlin.htm for
     * more details.
     *
     * @param point
     * A point within a linear 3D space from which a noise value will be
     * calculated.
     *
     * @param octaves
     * The inverse of the number of times that the noise function will be
     * added onto itself (for example, 1/2, 1/4, 1/sqrt(2), etc.).
     *
     * @param persistance
     * The length of effect that the noise value at a given point will have
     * on other noise values.
     *
     * @return A Perlin noise value, calculated at the point specified by
     * the input parameter. This value will be between [-1,1].
     */
    num_t get_octave_noise(const vec3_t<num_t>& point, unsigned octaves, num_t persistance) const noexcept;
};

/*-------------------------------------
    Perlin Noise Specializations
-------------------------------------*/
LS_DECLARE_CLASS_TYPE(PerlinNoisef, PerlinNoise, float);
LS_DECLARE_CLASS_TYPE(PerlinNoised, PerlinNoise, double);
LS_DECLARE_CLASS_TYPE(PerlinNoisei, PerlinNoise, int);
LS_DECLARE_CLASS_TYPE(PerlinNoiseuu, PerlinNoise, unsigned);
LS_DECLARE_CLASS_TYPE(PerlinNoisex, PerlinNoise, medp_t);

} // end math namespace
} // end ls namespace

#include "lightsky/math/generic/perlinNoise_impl.h"

#endif  /* LS__MATH_PERLIN_NOISE_H */
