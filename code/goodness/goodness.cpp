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

float dist_sphere(float theta, float h, float r) {
    return r * (-theta + asinf(((h + r) / r) * sinf(theta)));
}

float weight(int i, int N){
    return - 3.0f * pow(fabs((i - N / 2.0f) / N), 3) + 3.0f * pow((i - N / 2.0f) / N, 2);
}

float goodness(const std::vector<OpticalData> &optical_data, float h, float r, float alpha, int N, bool f){
    std::ofstream fout;
    fout.open("outfile.txt", std::ios::app);
    float g = 0, theta;
    float norm = 0;
    if (optical_data.empty()){
        fout << 0 << " " << 1e5 << std::endl;
        return 1e5;
    }
    for (int i = 0; i < optical_data.size(); ++i) {
        if (std::isnan(optical_data[i].end_x)) return -1;
        theta = alpha / 2 * (-1 + 2.0f * float(i) / float(N));
        if (f)
            g += fabs(start_angle(optical_data, h, r, i) - theta) * weight(i, N);
        else
            g += fabs(dist_sphere(theta, h, r) - optical_data[i].end_x) * weight(i, N);
        norm += weight(i, N);
    }
    g /= optical_data.size() * norm;
    fout << optical_data.size() << " " << g << std::endl;
    fout.close();
    return g;
};

