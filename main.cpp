#include <iostream>
#include <string>
#include <vector>

#include "code/utility/arrfunc.h"

#include "code/utility/Vector.h"
#include "code/solver/RaySolver.h"
#include "code/goodness/goodness.h"

using std::cin, std::cout;

int poly(){
    int N;
    cin >> N;

    std::vector<float> poly;
    poly.reserve(N);
    for (int i = 0; i < N; ++i) {
        float temp;
        cin >> temp;
        poly.push_back(temp);
    }

    auto n_raw  = coef_func(poly);
    auto dn_raw = coef_func(poly_der(poly));

    auto n = [n_raw](Vector2f r){
        return n_raw(r[1]);
    };

    auto dn = [dn_raw](Vector2f r){
        return Vector2f{0,dn_raw(r[1])};
    };

    // Получаем начальные данные

    float H, alpha, dt; int M;
    cin >> H >> alpha >> dt >> M;

    int T;
    cin >> T; // пока пофиг на T

//    cout << H << ' ' << alpha << ' ' << dt << ' ' << M << '\n';

//    cout << n(Vector2f{0,1}) << '\n';

    auto solve = solver_basic(n, dn, H, alpha, M, dt, INT16_MAX);

//    for (auto& data : solve) {
//        std::cout << data.optical_length << '\n';
//        std::cout << data.end_x << '\n';
//        std::cout << data.start_angle << '\n';
//    }

    float good = goodness(solve, H, 1.0f, alpha, M);

    cout << good;

    return 0;
}

int main(int argc, char** argv) {
//    tracing();

    std::string type;
    cin >> type;

    if( type == "poly" ) poly();

}
