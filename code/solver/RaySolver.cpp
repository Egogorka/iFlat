//
// Created by meeve on 26.04.2022.
//

#include "RaySolver.h"
#include <cmath>
#include "code/utility/Vector.h"

using scalar = float;
using Vector4 = Vector<scalar, 4>;
using Vector2 = Vector<scalar, 2>;

Vector4 propagator(const scalar& t, const Vector4& vec,
                    const std::function<float(Vector2)>& n,
                    const std::function<Vector2(Vector2)>& dn){
    Vector2 r{vec[0], vec[1]};
    Vector2 v{vec[2], vec[3]};

    auto n_at = n(r);
    auto n_sqr = n_at*n_at;

    return {
        v[0]/n_sqr,
        v[1]/n_sqr,
        dn(r)[0]/n_at,
        dn(r)[1]/n_at
    };
}

bool check_last_collision(const Solution<scalar,Vector4>& solution){
    const auto& values = solution.get_values();
    return values.back()[1] <= scalar{};
}

Ray solver_partial(const std::function<float(Vector2f)> &n, const std::function<Vector2f(Vector2f)> &dn, Vector2f r0,
                   Vector2f v0, float dt, int M) {
    auto updater = [&n, &dn](const scalar& t, const Vector4& vec){
        return propagator(t, vec, n, dn);
    };

    Ray out{Vector4{r0[0],r0[1],v0[0],v0[1]}, heun_wrapper<float,Vector4f>(updater), dt};
    for(int j = 0; j < M; ++j){
        out.prolong();
    }
    return out;
}

std::vector<Ray> solver_full(
        const std::function<scalar(Vector2)>& n,
        const std::function<Vector2(Vector2)>& dn,
        scalar h, scalar alpha, int N, scalar dt, int M) {
    std::vector<Ray> out{};

    auto updater = [&n, &dn](const scalar& t, const Vector4& vec){
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
