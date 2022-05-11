import matplotlib.pyplot as plt
import numpy as np

figure_size = (10,10)

def plot_data(t, phi, ksi):
    plt.subplot(1,2,1)
    plt.axis([-0.5,0.5,0.5,1.5])
    plt.plot(phi, ksi)

def plot_integral(t, I, I0):
    plt.subplot(1,2,2)
    plt.axis([0.0,0.5,-12,1])
    plt.plot(t, np.log(abs(I-I0)))
    plt.title("ln(|I-1|)")

if __name__ == '__main__':
    plt.figure(figsize=figure_size)

    PATH = "../../data/"

    for N in range(21):
        print(N)
        t, rx, ry, kx, ky, I = np.loadtxt(PATH+"/points/euler/"+str(N)+".csv", unpack=True)
        plot_data(t, rx, ry)
        I0 = I[0]
        plot_integral(t, I, I0)
    plt.savefig(PATH+"images/phase_diagram.png")
    plt.show()