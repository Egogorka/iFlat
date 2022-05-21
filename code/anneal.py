import numpy as np
import random
import logging


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

#[-2.692048728846623, -1.8632715352370754, 4.42001772511164, 9.352388772133152, -0.6427436802311683, 0]
#[0, 0, 0, 0, 0, 0]
def anneal(energy_func, initial_val=[0, 0, 0, 0, 0, 0], initial_temp=5000, q=1-1e-3, max_energy=1e-6, poly_power=20,
           sigma=1, max_steps=10000, reheat_temp=1e-10, reheat_degree=1e-5, all_vary_coeff=2.5, saving_interval=10):

    PRINT_INTERVAL = 1
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
    if len(initial_val) == poly_power:
        sol_coeffs = initial_val

    sol_energy = energy_func(sol_coeffs, False, step)
    while step <= max_steps and (sol_energy > max_energy or sol_energy < 0):
        new_coeffs = vary_series(sol_coeffs, sigma, step, all_vary_dist)
        save_tr = step % saving_interval == 0 or step == max_steps
        new_energy = energy_func(new_coeffs, save_tr, step)
        if step % PRINT_INTERVAL == 0:
            logging.debug(f'sol_energy: {sol_energy}, new_energy: {new_energy}')
            logging.debug(f'Take probability: {np.exp(-(new_energy - sol_energy) / temp)}')
            logging.debug('Coeffs:')
            logging.debug(sol_coeffs)
            logging.debug('--------')

        test_param = False
        if new_energy < sol_energy:
            test_param = True

        if new_energy < sol_energy or rand.uniform(0, 1) < np.exp(-(new_energy - sol_energy) / temp):
            sol_coeffs = new_coeffs
            sol_energy = new_energy

        if step % PRINT_INTERVAL == 0:
            logging.debug(f'step: {step}, temp: {temp}, sol_energy: {sol_energy}')
        step += 1

        #####
        if (test_param):
            temp *= q
        #####

        energies.append(sol_energy)
        if temp < initial_temp * reheat_temp:
            temp += initial_temp * reheat_degree

    logging.debug('Got energy: ', sol_energy)
    return sol_coeffs, sol_energy
