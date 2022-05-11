//
// Created by meeve on 24.04.2022.
//

#include "Ray.h"

OpticalData::OpticalData(float startAngle, float endAngle, float endX, float time, float opticalLength) : start_angle(
        startAngle), end_angle(endAngle), end_x(endX), time(time), optical_length(opticalLength) {}

std::ostream &operator<<(std::ostream &out, const OpticalData &data) {
    out << data.start_angle << ' ' << data.end_angle << ' ' << data.end_x << ' ' << data.time << ' ' << data.optical_length;
    return out;
}

scalar Ray::angle(const Vector4 &v) {
    return atanf(-v[2]/v[3]);
}

scalar Ray::optical_length(const std::function<scalar(Vector2)> &n) const {
    scalar out{};

    auto iter = values.cbegin();
    auto pre_iter = iter;
    ++iter;
    while (iter != values.cend()){
        auto dv = *iter - *pre_iter;
        auto dx = sqrtf(dv[0]*dv[0] + dv[1]*dv[1]);
        Vector2f r{(*pre_iter)[0], (*pre_iter)[1]};
        out += dx * n(r);
        ++pre_iter;
        ++iter;
    }
    return out;
}

scalar Ray::start_angle() const {
    return angle(values.front());
}

scalar Ray::end_angle() const {
    return angle(values.back());
}

scalar Ray::end_x() const {
    return values.back()[0];
}

OpticalData Ray::get_data(const std::function<scalar(Vector2)> &n) const {
    return {start_angle(), end_angle(), end_x(), get_time(), optical_length(n)};
}
