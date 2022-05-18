//
// Created by nikita on 4/26/22.
//

#ifndef IFLAT_GOODNESS_H
#define IFLAT_GOODNESS_H

#include "code/solver/RaySolver.h"
#include <cmath>
#include <vector>
#include <fstream>


float start_angle(
        const std::vector<OpticalData> &optical_data, float h, float r, int i);


float dist_sphere(
        float theta, float h, float r);


float weight(
        int i, int N);


float goodness(
        const std::vector<OpticalData> &optical_data, float h, float r, float alpha, int N, bool f = false);


#endif //IFLAT_GOODNESS_H
