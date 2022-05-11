//
// Created by meeve on 26.04.2022.
//

#ifndef IFLAT_RAYSOLVER_H
#define IFLAT_RAYSOLVER_H

#include "Ray.h"
#include <vector>

/**
 * @param n - function that returns n
 * @param dn - gradient of the n
 * @param h - Height of the emission point
 * @param alpha -
 * @param N - Amount of rays
 * @param dt - Time step size
 * @return
 */
std::vector<OpticalData> solver_basic(
        const std::function<float(Vector2f)>& n,
        const std::function<Vector2f(Vector2f)>& dn,
        float h, float alpha, int N, float dt, int M);

/**
 * Provides the full ray information
 * @param h
 * @param alpha
 * @param N
 * @param dt
 * @return
 */
std::vector<Ray> solver_full(
        const std::function<float(Vector2f)>& n,
        const std::function<Vector2f(Vector2f)>& dn,
        float h, float alpha, int N, float dt, int M);

std::vector<OpticalData> get_data(const std::vector<Ray>& rays, const std::function<scalar(Vector2)>& n);

/**
 * Solves only for 1 ray
 * @param n
 * @param dn
 * @param r0
 * @param v0
 * @param M - amount of steps
 * @return
 */
Ray solver_partial(
        const std::function<float(Vector2f)>& n,
        const std::function<Vector2f(Vector2f)>& dn,
        Vector2f r0, Vector2f v0, float dt, int M);

#endif //IFLAT_RAYSOLVER_H
