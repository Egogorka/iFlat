//
// Created by meeve on 16.10.2021.
//

#ifndef MODELING_ODE_H
#define MODELING_ODE_H

#include <functional>

template<typename scalar, typename V>
using Operator = std::function<V(const scalar&, const V&)>;

template<typename V, typename scalar>
V identity(const scalar& t, const V& vec){
    return vec;
}

template<typename V, typename scalar>
class ODE_Solver {
private:
    // function_ that corresponds to y' = F(t,y)
    Operator<scalar, V> function_;
public:
    scalar time;
    scalar start_time;
    V state;
    V start_state;

    ODE_Solver(V& state, Operator<scalar, V> func) :
        state(state), start_state(state), function_(func)
        , start_time(scalar{}), time(scalar{})
        {};
    explicit ODE_Solver(V state): ODE_Solver(state, identity<scalar,V>) {};

    void reset_state(){
        time = start_time;
        state = start_state;
    }

    void euler(scalar dt) {
        state += function_(time, state) * dt;
        time += dt;
    }

    void heun(scalar dt) {
        // forecast
        auto forecast = state + function_(time, state) * dt;
        // better the forecast
        state += (function_(time, state) + function_(time, forecast)) / scalar(2) * dt;
        time += dt;
    }

    /**
     * Helper function that calls callback function on each iteration
     * @param dt - a small dt for which ODE progresses
     * @param N  - amount of steps
     * @param callback - a callback function that takes in current state and current step number
     */
    void progress_euler(scalar dt, int N, std::function<void(const V&, int)> callback){
        this->reset_state();
        for (int i = 0; i < N; ++i) {
            euler(dt);
            callback(state, i);
        }
    }

    /**
     * Helper function that calls callback function on each iteration
     * @param dt - a small dt for which ODE progresses
     * @param N  - amount of steps
     * @param callback - a callback function that takes in current state and current step number
     */
    void progress_heun(scalar dt, int N, std::function<void(const V&, int)> callback){
        this->reset_state();
        for (int i = 0; i < N; ++i) {
            heun(dt);
            callback(state, i);
        }
    }
};

#endif //MODELING_ODE_H
