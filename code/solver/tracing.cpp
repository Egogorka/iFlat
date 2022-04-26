//
// Created by meeve on 25.04.2022.
//

#include "tracing.h"

#include <cmath>
#include "code/utility/ODE.h"
#include "code/utility/Solution.h"
#include "code/utility/Vector.h"

#include "Ray.h"

#include <string>

using scalar = float;
using Vector4 = Vector<scalar,4>;

scalar n(Vector<scalar,2> r){
    return expf(r[1]);
}

Vector<scalar,2> dn(Vector<scalar,2> r){
    return Vector<scalar,2>{0,expf(r[1])};
}

Vector4 propagator(const scalar& t, const Vector4& vec){
    Vector<scalar,2> r{vec[0], vec[1]};
    Vector<scalar,2> v{vec[2], vec[3]};

    auto dot = v * dn(r);
    auto temp = (dot > 0 ? 1.0f : -1.0f)*sqrtf(dot*(dot + 2)) - dot;
    auto temp2 = sqrtf(dn(r)*dn(r));

    return {
        v[0]/n(r),
        v[1]/n(r),
        dn(r)[0]/temp2,
        dn(r)[1]/temp2
    };
}

bool check_last_collision(const Solution<scalar,Vector4>& solution){
    const auto& values = solution.get_values();
    return values.back()[1] <= 0;
}

int tracing(){

    Vector<scalar,2> r{1.0f, 1.0f};
    auto v = Vector<scalar,2>{cosf(M_PI_4), -sinf(M_PI_4)} * n(r);

    Vector4 state{ r[0], r[1], v[0], v[1]};

    Ray solution(state, heun_wrapper<scalar, Vector4>(propagator), 1.0f/10000);

    for( int i = 0; i < 20000; i++) {
        solution.prolong();
        if(check_last_collision(solution)) break;
    }

    std::cout << "Number of points: " << solution.get_values().size() << '\n';
    std::cout << "Start angle: " << solution.start_angle() << '\n';
    std::cout << "End angle: " << solution.end_angle() << '\n';
    std::cout << "End x position: " << solution.end_x() << '\n';
    std::cout << "Travel time: " << solution.get_time() << '\n';
    std::cout << "Optical length: " << solution.optical_length(n) << '\n';

    return 0;
}