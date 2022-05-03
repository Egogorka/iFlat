//
// Created by meeve on 25.04.2022.
//

#include "tracing.h"

#include "RaySolver.h"

#include <fstream>
#include <string>

using scalar = float;
using Vector4 = Vector<scalar,4>;

scalar n(Vector<scalar,2> r){
    return expf(r[1]);
}

Vector<scalar,2> dn(Vector<scalar,2> r){
    return Vector<scalar,2>{0,expf(r[1])};
}

int tracing(){

    auto solver = solver_basic(std::function{n},std::function{dn},1.0f,M_PI_2, 100, 1e-4, 1e+5);

    for (auto& data : solver) {
        std::cout << data.optical_length << '\n';
        std::cout << data.start_angle << '\n';
    }
//    std::cout << "Number of points: " << solution.get_values().size() << '\n';
//    std::cout << "Start angle: " << solution.start_angle() << '\n';
//    std::cout << "End angle: " << solution.end_angle() << '\n';
//    std::cout << "End x position: " << solution.end_x() << '\n';
//    std::cout << "Travel time: " << solution.get_time() << '\n';
//    std::cout << "Optical length: " << solution.optical_length(n) << '\n';

    return 0;
}