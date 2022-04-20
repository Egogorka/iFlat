import matplotlib.pyplot as plt
import numpy as np

figure_size = (10,10)

def plot_data(t, phi, ksi):
    plt.subplot(1,1,1)
    plt.axis([-12,12,-12,12])
    plt.plot(phi, ksi)

if __name__ == '__main__':
    plt.figure(figsize=figure_size)

    PATH = "../../data/"

    # for N in range(30):
    for N in range(40):
        t, rx, ry, kx, ky = np.loadtxt(PATH+"/points/euler/"+str(N)+".csv", unpack=True)
        plot_data(t, rx, ry)
    plt.savefig(PATH+"images/phase_diagram.png")
    plt.show()