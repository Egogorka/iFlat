import numpy as np
import scipy.optimize
import random
import matplotlib.pyplot as plt


N0 = np.vectorize(lambda x: 3 + x**2 - 2 * x * np.sin(x))
n = 10000
X = np.linspace(0, 1, n)
n0_val = N0(X)
DX = 1 / n

rand = random.Random()

n0_norm = np.sqrt(np.trapz(np.abs(n0_val)**2, X))


def energy(n: np.array):
    y = np.abs(n - n0_val)**2
    y = y[100:-100]
    # if True:
    #     y_max = np.max(y)
    #     y = [0 if abs(yi - y_max) / y_max > 0.98 else yi for yi in y]

    l2_norm = np.sqrt(np.trapz(y, X[100:-100]))
    return l2_norm / n0_norm


def calc_series(x, coeffs, series_type: str):
    if series_type == "poly":
        return np.polyval(coeffs, x)
    elif series_type == "fourier":
        return sum([coeffs[k] * (np.cos(k/2 * x)
                                 if k % 2 == 0 else np.sin((k+1)/2 * x)) for k in range(len(coeffs))])


def vary_series(coeffs, min_c0, max_c0, step, all_vary_dist):
    """
    Varies a polynomial given by its coefficients.
    :param coeffs: list of coefficients
    :param temp: current temperature of annealing
    :param min_c0: minimal value of 0-th coefficient
    :param max_c0: maximal value of 0-th coefficient
    """
    if step % all_vary_dist != 0:
        nc = coeffs.copy()
        # sigma = (max_c0 - min_c0) * temp / initial_temp
        sigma = (max_c0 - min_c0) / 2
        c = 0.03
        i = rand.randint(0, len(coeffs) - 1)
        nc[i] += rand.gauss(0, sigma)

        return nc
    else:
        nc = []
        # sigma = (max_c0 - min_c0) * temp / initial_temp
        sigma = (max_c0 - min_c0) / 2
        c = 0.03
        for i in range(len(coeffs)):
            # offset = -c * temp / initial_temp * np.sign(coeffs[i]) * (max_c0 - min_c0)
            offset = 0
            dc = rand.gauss(offset, sigma)
            # dc = max(min_c0, dc)
            # dc = min(max_c0, dc)
            nc.append((coeffs[i] + dc))

        return nc


def anneal(energy_func, initial_val=0, initial_temp=5000, q=1-1e-3, max_energy=1e-6, poly_power=20,
           min_c0=-1, max_c0=1, max_steps=10000, reheat_temp=1e-10, reheat_degree=1e-5, all_vary_coeff=2.5):
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
        new_coeffs = vary_series(sol_coeffs, min_c0, max_c0, step, all_vary_dist)
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
#
# print(energy(n0_val))
#
# sol, ens = anneal(energy, X, max_c0=2, min_c0=-2, poly_power=30, q=0.99, initial_temp=500, series_type="fourier", max_steps=10000)
# plt.plot(X, n0_val)
# plt.plot(X, sol, '-r')
# plt.show()
