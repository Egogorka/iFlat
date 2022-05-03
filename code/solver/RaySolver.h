//
// Created by meeve on 26.04.2022.
//

#ifndef IFLAT_RAYSOLVER_H
#define IFLAT_RAYSOLVER_H

#include "Ray.h"
#include <vector>

struct OpticalData {
    float start_angle;
    float end_angle;
    float end_x;
    float time;
    float optical_length;

    OpticalData(float startAngle, float endAngle, float endX, float time, float opticalLength);
};

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

#endif //IFLAT_RAYSOLVER_H
