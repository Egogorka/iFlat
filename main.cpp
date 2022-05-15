#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "code/utility/arrfunc.h"

#include "code/utility/Vector.h"
#include "code/solver/RaySolver.h"
#include "code/goodness/goodness.h"

#include "code/solver/tracing.h"

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

    switch (T)
    {
        case 1:
        case 2:{

            std::string name;
            cin >> name;

            auto solve = solver_full(n, dn, H, alpha, M, dt, INT16_MAX);
            std::string PATH = "../data/points/data/" + name + '_';
            std::ofstream fout;

            for(int j = 0 ; j < solve.size(); ++j){
                std::string temp = PATH + std::to_string(j) + ".csv";
                fout.open(temp);
                if(T == 2) {
                    fout << solve[j].get_data(n) << '\n';
                    continue;
                }

                auto values = solve[j].get_values();
                for(int i = 0; i < values.size(); ++i){
                    auto r = Vector2f{values[i][0], values[i][1]};
                    auto v0 = Vector2f{values[i][2], values[i][3]};
                    auto t = dt * i;
                    // First integrals of the system:
                    // |v| ~ (v,v)/n(r)/n(r) const
                    // n*[v - (v,dn)/(dn,dn)*dn] ~ const
                    fout << t << ' ' << values[i] << '\n';
                }
                fout << std::endl;
                fout.close();
            }

        }
        default: {
            auto solve = solver_basic(n, dn, H, alpha, M, dt, INT16_MAX);
            float good = goodness(solve, H, 1.0f, alpha, M);
            cout << good;
            break;
        }
    }
    return 0;
}

int main(int argc, char** argv) {
//    tracing();

    std::string type;
    cin >> type;

    if( type == "poly" ) poly();
}
