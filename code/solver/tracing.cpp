//
// Created by meeve on 20.04.2022.
//

#include "tracing.h"

#include <cmath>
#include "code/utility/ODE.h"
#include "code/utility/Vector.h"

#include <string>

using scalar = float;

scalar n(Vector<scalar,2> r){
    return expf(r[1]);
}

Vector<scalar,2> dn(Vector<scalar,2> r){
    return Vector<scalar,2>{0,expf(r[1])};
}

Vector<scalar,4> propagator(const scalar& t, const Vector<scalar,4>& vec){
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

const std::string PATH = "../data/points/";
#include <fstream>

int tracing()
{
    Vector<scalar,2> r{1.0f, 1.0f};
    auto v = Vector<scalar,2>{cosf(M_PI_4), -sinf(M_PI_4)} * n(r);

    Vector<scalar,4> state{ r[0], r[1], v[0], v[1]};

    ODE_Solver<Vector<scalar,4>,scalar> solver(state, std::function{propagator});

    std::ofstream fout;

    int N = 20;
    int M = 100000;
    for(int k=-N; k<N; k++){
        v = Vector<scalar,2>{sinf(M_PI_4 * k/N), -cosf(M_PI_4 * k/N)} * n(r);
        state[2] = v[0]; state[3] = v[1];

        solver.start_state = state;

        std::string temp = PATH + "euler/" + std::to_string(k+N) + ".csv";

        fout.open(temp);
        solver.progress_heun(100.0f / float(M), M, [&fout](const Vector<scalar,4>& vec, int i){
            fout << i << ' ' << vec << '\n';
        });
        fout << std::endl;
        fout.close();
    }

    return 0;
}