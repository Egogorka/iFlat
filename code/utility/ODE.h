//
// Created by meeve on 25.04.2022.
//

#ifndef IFLAT_ODE_H
#define IFLAT_ODE_H

#include <functional>

template<typename scalar, typename V>
using Operator = std::function<V(const scalar&, const V&)>;

template<typename scalar, typename V>
class ODE_Solver {
    Operator<scalar, V> func;
public:
    ODE_Solver(const Operator<scalar, V>& func) : func(func) {}

    V euler(scalar time, V state, scalar dt) const {
        return state + func(time, state) * dt;
    }

    V heun(scalar time, V state, scalar dt) const {
        // forecast
        auto forecast = state + func(time, state) * dt;
        // better the forecast
        return state + (func(time, state) + func(time, forecast)) / scalar(2) * dt;
    }
};

template<typename scalar, typename V>
std::function<V(scalar, V, scalar)> euler_wrapper(const Operator<scalar, V>& func){
    return [&func](scalar time, V state, scalar dt){
        return state + func(time, state) * dt;
    };
}

template<typename scalar, typename V>
std::function<V(scalar, V, scalar)> heun_wrapper(const Operator<scalar, V>& func){
    return [&func](scalar time, V state, scalar dt){
        auto forecast = state + func(time, state) * dt;
        // better the forecast
        return state + (func(time, state) + func(time, forecast)) / scalar(2) * dt;
    };
}

#endif //IFLAT_ODE_H
