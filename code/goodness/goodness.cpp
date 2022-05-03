//
// Created by nikita on 4/26/22.
//

#include "goodness.h"

float start_angle(std::vector<OpticalData> *optical_data, float h, float r, int i){
    float optical_length_sphere, phi, start_angle_calc;
    phi = *optical_data[i].end_x / r;
    optical_length_sphere = sqrtf( (h + r) * (h + r) + r * r - 2 * r * (h + r) * cosf(phi) );
    start_angle_calc = asinf( (r / optical_length_sphere) * sinf(*optical_data[i].end_x / r) );
    return start_angle_calc;
}

float goodness(std::vector<OpticalData> *optical_data, float h, float r, int N){
    float g = 0;
    ofstream fout;
    fout.open("goodness.txt");
    for (int i = 0; i < N; ++i) {
        theta = alpha / 2 * (-1 + 2.0f * float(i) / float(N));
        g += abs(start_angle(optical_data, h, r, i) - theta) * exp( - i * i / N);
    }
    fout << g;
    fout.close;
    return g;
};