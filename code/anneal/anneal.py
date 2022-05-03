import numpy as np
import scipy.optimize
import random
import matplotlib.pyplot as plt


rand = random.Random()


def vary_series(coeffs, sigma, step, all_vary_dist):
    """
    Varies a polynomial given by its coefficients.
    :param coeffs: list of coefficients
    :param temp: current temperature of annealing
    :param min_c0: minimal value of 0-th coefficient
    :param max_c0: maximal value of 0-th coefficient
    """
    if step % all_vary_dist != 0:
        nc = coeffs.copy()
        i = rand.randint(0, len(coeffs) - 1)
        nc[i] += rand.gauss(0, sigma)

        return nc
    else:
        nc = []
        c = 0.03
        for i in range(len(coeffs)):
            offset = 0
            dc = rand.gauss(offset, sigma)
            nc.append((coeffs[i] + dc))

        return nc


def anneal(energy_func, initial_val=0, initial_temp=5000, q=1-1e-3, max_energy=1e-6, poly_power=20,
           sigma=1, max_steps=10000, reheat_temp=1e-10, reheat_degree=1e-5, all_vary_coeff=2.5):
    """
    Finds a global minimum of the function using simulated annealing
    :param energy_func: energy function, which minimum is being found
    :param x:
    :param initial_val:
    :param initial_temp:
    :param delta_temp:
    :param max_energy:
    :param poly_power:
    :param min_c0:
    :param max_c0:
    :return:
    """
    if poly_power < 0:
        raise ValueError()
    if initial_temp < 0:
        raise ValueError()
    if max_steps <= 0:
        raise ValueError()


    all_vary_dist = int(poly_power * all_vary_coeff)
    # coeff_energy_func = lambda cs: energy_func(calc_series(x, cs, series_type))

    step = 0
    temp = initial_temp

    energies = []

    sol_coeffs = np.zeros(poly_power)
    sol_coeffs[0] = initial_val
    sol_energy = energy_func(sol_coeffs)
    while step < max_steps and sol_energy > max_energy:
        new_coeffs = vary_series(sol_coeffs, sigma, step, all_vary_dist)
        new_energy = energy_func(new_coeffs)
        if step % 100 == 0:
            print(f'sol_energy: {sol_energy}, new_energy: {new_energy}')
            print(f'Take probability: {np.exp(-(new_energy - sol_energy) / temp)}')
            print('Coeffs:')
            print(sol_coeffs)
            print('--------')
        if new_energy < sol_energy or rand.uniform(0, 1) < np.exp(-(new_energy - sol_energy) / temp):
            sol_coeffs = new_coeffs
            sol_energy = new_energy

        if step % 100 == 0:
            print(f'step: {step}, temp: {temp}, sol_energy: {sol_energy}')
        step += 1
        temp *= q
        energies.append(sol_energy)
        if temp < initial_temp * reheat_temp:
            temp += initial_temp * reheat_degree

    print('Got energy: ', sol_energy)
    return sol_coeffs
