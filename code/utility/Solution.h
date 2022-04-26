//
// Created by meeve on 24.04.2022.
//

#ifndef IFLAT_SOLUTION_H
#define IFLAT_SOLUTION_H

#include "ODE.h"
#include <vector>
#include <functional>

/**
 * Class that is solution to some one-dimensional differential equation ( Cauchy problem )
 * In other words, for y' = F(x,y), y(x) is of Solution class
 * @tparam V - type of output of y(x)
 * @tparam scalar - type of x
 */
template<typename scalar, typename V>
class Solution {
protected:
    /**
     * Vector containing all of the function values
     * at uniformly distributed points (we expect that) at our interval
     * In a sense:
     * t0, t0 + dt, t0 + 2*dt, ...
     */
    std::vector<V> values;
    scalar start;
    scalar dt;

    // Current time -
    scalar time;

    /**
     * Solver gives next point of solution
     *
     */
    std::function<V(scalar,V,scalar)> solver;
public:

    Solution(const V& state, const std::function<V(scalar,V,scalar)>& solver, scalar dt, scalar start = scalar{})
    : values(), start(start), time(start), dt(dt), solver(solver) {
        values.push_back(state);
    }

    Solution(const Solution& sol)
    : values(sol.values), start(sol.start), dt(sol.dt), time(sol.time), solver(sol.solver) {}

    /**
     * Function that extends the interval on which solution is defined
     * hence the name
     */
    void prolong(){
        values.push_back(solver(time, values.back(), dt));
        time += dt;
    }

    const std::vector<V>& get_values() const{
        return values;
    }

    /**
     * Returns V that corresponds to the closest point to t
     */
    V at_closest(scalar t){
        int N = static_cast<int>(t - start + scalar{1}/2);
        return values[N];
    }

    /**
     * Returns V using linear interpolation
     */
//    V at_lerp(){
//
//    }

    scalar get_dt() const {
        return dt;
    }

    scalar get_time() const {
        return time;
    }
};

#endif //IFLAT_SOLUTION_H
