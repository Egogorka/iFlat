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
    auto temp = ((h + r) / r) * sinf(theta);
    return r * (- theta + asinf(temp));
}

float weight(int i, int N){
    return 1;
    return - 3.0f * pow(fabs((i - N / 2.0f) / N), 3) + 3.0f * pow((i - N / 2.0f) / N, 2);
}

float goodness(const std::vector<OpticalData> &optical_data, float h, float r, float alpha, int N, bool f){
    std::ofstream fout;
    fout.open("outfile.txt", std::ios::app);

    if (optical_data.empty()){
        fout << 0 << " " << 1e9 << std::endl;
        return 1e9;
    }
    //
    //N = 20;
    //alpha = 1.5;

    //alpha = 3; //ATTENTION, EMERGENCY SITUATION

    float theta;
    int correct_size = 0;
    for (int i = 0; i < N; i++) {
        theta = optical_data[i].start_angle;
        if (!std::isnan(dist_sphere(theta, h, r))){
            correct_size++;
        }
    }
    //
    float g = 0;
    if (correct_size != optical_data.size()){
        g += 1e4 * abs(correct_size - optical_data.size());
    }
    //


    //float norm = 0.1;
    for (int i = 0; i < optical_data.size(); ++i) {
        //if (std::isnan(optical_data[i].end_x)) return -1;
        theta = optical_data[i].start_angle;
        if (false){}
            //g += fabs(start_angle(optical_data, h, r, i) - theta) * weight(i, N);
        else {
            //if (std::isnan(dist_sphere(theta, h, r))){
            //    if (std::isnan(optical_data[i].end_x)){
            //    g += 0;
            //}
            //    else{
            //        g += 100;
            //    }
            //}
            if (std::isnan(dist_sphere(theta, h, r))){}
            else {
                g += pow(dist_sphere(theta, h, r) - optical_data[i].end_x, 4); //* weight(i, N);
            }
        }
        //norm += 1; //weight(i, N);
    }
    //g /= optical_data.size() * norm;
    g *= 1e3;

    fout << optical_data.size() << "/" << correct_size << "/" << g << " ";

    for (int i = 0; i < optical_data.size(); ++i) {
        fout << optical_data[i].end_x << " ";
    }
    fout << std::endl;
    fout.close();
    return g;
};

