//
// Created by nikita on 4/26/22.
//

#ifndef IFLAT_GOODNESS_H
#define IFLAT_GOODNESS_H

#include "RaySolver.h"
#include <cmath>
#include <vector>
#include <ofstream>

float start_angle(
        std::vector<OpticalData> *optical_data, float h, float r, int i);

float goodness(
        std::vector<OpticalData> *optical_data, float h, float r, int N);


#endif //IFLAT_GOODNESS_H
