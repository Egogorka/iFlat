//
// Created by meeve on 26.04.2022.
//

#include "RaySolver.h"
#include <cmath>
#include "code/utility/Vector.h"

Vector4f propagator(const float& t, const Vector4f& vec,
                    const std::function<float(Vector2f)>& n,
                    const std::function<Vector2f(Vector2f)>& dn){
    Vector<float, 2> r{vec[0], vec[1]};
    Vector<float, 2> v{vec[2], vec[3]};

    auto dot = v * dn(r);
    auto temp = (dot > 0 ? 1.0f : -1.0f)*sqrtf(dot*(dot + 2)) - dot;
    auto temp2 = sqrtf(dn(r)*dn(r));

    if(temp2 == 0.0f){
        return {
            v[0]/n(r),
            v[1]/n(r),
            0,
            0
        };
    }

    return {
        v[0]/n(r),
        v[1]/n(r),
        dn(r)[0]/temp2,
        dn(r)[1]/temp2
    };
}

bool check_last_collision(const Solution<float,Vector4f>& solution){
    const auto& values = solution.get_values();
    return values.back()[1] <= 0;
}

std::vector<Ray> solver_full(
        const std::function<float(Vector2f)>& n,
        const std::function<Vector2f(Vector2f)>& dn,
        float h, float alpha, int N, float dt, int M) {
    std::vector<Ray> out{};

    auto updater = [&n, &dn](const float& t, const Vector4f& vec){
        return propagator(t, vec, n, dn);
    };

    Vector2f r{0.0f, h};
    for(int i = 0; i < N; ++i){
        float theta = alpha/2 * ( -1 + 2.0f * float(i)/float(N) );
        Vector2f k{sinf(theta), -cosf(theta)};
        Vector4f state{r[0], r[1], k[0], k[1]};

        Ray ray{state, heun_wrapper<float,Vector4f>(updater), dt};
        for(int j = 0; j < M; ++j){
            ray.prolong();
            if(check_last_collision(ray)) continue;
        }
        out.push_back(ray);
    }
    return out;
}

std::vector<OpticalData> solver_basic(
        const std::function<float(Vector2f)>& n,
        const std::function<Vector2f(Vector2f)>& dn,
        float h, float alpha, int N, float dt, int M) {
    auto rays = solver_full(n, dn, h, alpha, N, dt, M);
    std::vector<OpticalData> out;
    out.reserve(rays.size());
    for(auto & ray : rays){
        out.emplace_back(
                ray.start_angle(),
                ray.end_angle(),
                ray.end_x(),
                ray.get_time(),
                ray.optical_length(n)
                );
    }

    return out;
}

OpticalData::OpticalData(float startAngle, float endAngle, float endX, float time, float opticalLength) : start_angle(
        startAngle), end_angle(endAngle), end_x(endX), time(time), optical_length(opticalLength) {}
