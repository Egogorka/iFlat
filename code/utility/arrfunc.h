//
// Created by meeve on 26.04.2022.
//

#ifndef IFLAT_ARRFUNC_H
#define IFLAT_ARRFUNC_H


#include <vector>
#include <functional>
#include <utility>

/**
 * Converter function from array to std::function-like
 * @tparam scalar - scalar type, like int or float
 * @param coefs - array containing coefficients of a polynomial. coefs[0] must correspond to a_0, i.e. P(x) = a_0 + a_1 * x + ...
 * @return - function that is P(x)
 */
template<typename scalar>
std::function<scalar(scalar)> coef_func(std::vector<scalar> coefs){
    return [coefs](scalar x){
        auto iter = coefs.rbegin();
        auto out = scalar{};
        while(iter != coefs.rend()){
            out = *iter + x * (out);
            ++iter;
        }
        return out;
    };
}

/**
 *
 * @tparam scalar - scalar type, like int or float
 * @param coefs - array containing coefficients of a polynomial. coefs[0] must correspond to a_0, i.e. P(x) = a_0 + a_1 * x + ...
 * @return P'(x)
 */
template<typename scalar>
std::vector<scalar> poly_der(const std::vector<scalar>& coefs){
    std::vector<scalar> out;
    if(coefs.size() == 1){
        out.push_back(scalar{});
        return out;
    }
    out.reserve(coefs.size()-1);
    for(int i=1; i<coefs.size(); ++i){
        out.push_back(i*coefs[i]);
    }
    return out;
}



#endif //IFLAT_ARRFUNC_H
