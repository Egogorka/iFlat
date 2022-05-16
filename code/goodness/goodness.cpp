//
// Created by nikita on 4/26/22.
//

#include "goodness.h"

float start_angle(const std::vector<OpticalData> &optical_data, float h, float r, int i){
    float optical_length_sphere, phi, start_angle_calc;
    phi = optical_data[i].end_x / r;
    optical_length_sphere = sqrtf( (h + r) * (h + r) + r * r - 2 * r * (h + r) * cosf(phi) );
    start_angle_calc = asinf( (r / optical_length_sphere) * sinf(optical_data[i].end_x / r) );
    return start_angle_calc;
}

float goodness(const std::vector<OpticalData> &optical_data, float h, float r, float alpha, int N){
    float g = 0, theta;
    float norm = 0;
    if (!optical_data.size()) return 1e5;
    for (int i = 0; i < optical_data.size(); ++i) {
        theta = alpha / 2 * (-1 + 2.0f * float(i) / float(N));
        if (std::isnan(optical_data[i].end_x)) return -1;
        g += fabs(start_angle(optical_data, h, r, i) - theta) * exp( - i * i / N);
        norm += exp( - i * i / N);
    }
    g /= optical_data.size() * norm;
    return g;
};