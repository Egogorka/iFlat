//
// Created by meeve on 25.04.2022.
//

#include "tracing.h"

#include "RaySolver.h"

#include <cmath>
#include <fstream>
#include <string>

using scalar = float;
using Vector4 = Vector<scalar,4>;

scalar n(Vector<scalar,2> r){
    return 1.25f+0.25f*tanhf(100*(1-r[1]));
}

Vector<scalar,2> dn(Vector<scalar,2> r){
    auto tmp = 5/coshf(100*(r[1]-1));
    return Vector<scalar,2>{0,-tmp*tmp};
}

Vector<scalar,2> normalize(Vector<scalar,2> v){
    return v/sqrtf(v*v);
}

const std::string PATH = "../data/points/";

int tracing(){

//    auto solver = solver_full(std::function{n},std::function{dn},1.0f,M_PI_2, 100, 1e-4, 1e+5);

//    for(const auto& ray : solver){

    float dt = 1e-5;


    for(int j = -10; j <= 10; ++j ){
        std::ofstream fout;
        auto v = Vector<scalar,2>{sinf(M_PI_2 * j/10), -cosf(M_PI_2 * j/10)} * n(Vector2f{0.0f, 2.0f});

        auto ray = solver_partial(n,dn,Vector2f{0.0f, 1.05f}, v, dt, int(.5f/dt));
        auto values = ray.get_values();

        std::string temp = PATH + "euler/" + std::to_string(10+j) + ".csv";

        fout.open(temp);
        for(int i = 0; i < values.size(); ++i){
            auto r = Vector2f{values[i][0], values[i][1]};
            auto v0 = Vector2f{values[i][2], values[i][3]};
            auto t = dt * i;
            // First integrals of the system:
            // |v| ~ (v,v)/n(r)/n(r) const
            // n*[v - (v,dn)/(dn,dn)*dn] ~ const

            fout << t << ' ' << values[i] << ' ' << (v0*v0)/n(r)/n(r) << '\n';
        }
        fout << std::endl;
        fout.close();
    }
    //    }
//    std::cout << "Number of points: " << solution.get_values().size() << '\n';
//    std::cout << "Start angle: " << solution.start_angle() << '\n';
//    std::cout << "End angle: " << solution.end_angle() << '\n';
//    std::cout << "End x position: " << solution.end_x() << '\n';
//    std::cout << "Travel time: " << solution.get_time() << '\n';
//    std::cout << "Optical length: " << solution.optical_length(n) << '\n';

    return 0;
}