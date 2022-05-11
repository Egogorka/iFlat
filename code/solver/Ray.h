//
// Created by meeve on 24.04.2022.
//

#ifndef IFLAT_RAY_H
#define IFLAT_RAY_H

#include "code/utility/Vector.h"
#include "code/utility/Solution.h"

#include <vector>
#include <functional>
#include <cmath>

using scalar = float;
using Vector4 = Vector<scalar, 4>;
using Vector2 = Vector<scalar, 2>;

struct OpticalData {
    scalar start_angle;
    scalar end_angle;
    scalar end_x;
    scalar time;
    scalar optical_length;

    OpticalData(scalar startAngle, scalar endAngle, scalar endX, scalar time, scalar opticalLength);

    friend std::ostream& operator<<(std::ostream& out, const OpticalData& data);
};

class Ray : public Solution<scalar, Vector4> {
    using Solution::Solution;

    /**
     * Angle from y-axis (looking down) \/
     * Counter-clockwise is positive
     * @param v - vector, 2 - x dir, 3 - y dir
     * @return
     */
    static scalar angle(const Vector4& v);

public:
    [[nodiscard]] scalar optical_length(const std::function<scalar(Vector2)>& n) const;

    [[nodiscard]] scalar start_angle() const;

    [[nodiscard]] scalar end_angle() const;

    [[nodiscard]] scalar end_x() const;

    [[nodiscard]] OpticalData get_data(const std::function<scalar(Vector2)>& n) const;
};



#endif //IFLAT_RAY_H
