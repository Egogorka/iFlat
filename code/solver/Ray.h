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

using Vector4f = Vector<float, 4>;

class Ray : public Solution<float, Vector4f> {
    using Solution::Solution;

    /**
     * Angle from y-axis (looking down) \/
     * Counter-clockwise is positive
     * @param v - vector, 2 - x dir, 3 - y dir
     * @return
     */
    static float angle(const Vector4f& v){
        return atanf(-v[2]/v[3]);
    }

public:
    float optical_length(const std::function<float(Vector2f)>& n){
        float out = 0;

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

    float start_angle(){
        return angle(values.front());
    }

    float end_angle(){
        return angle(values.back());
    }

    float end_x(){
        return values.back()[0];
    }
};



#endif //IFLAT_RAY_H
