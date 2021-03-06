import matplotlib.pyplot as plt
import numpy as np

import os, glob

figure_size = (10,10)

def plot_data(t, phi, ksi):
    plt.plot(phi, ksi)
    plt.ylim(bottom=0)
    plt.xlim(-np.pi, np.pi)

def plot_integral(t, I, I0):
    plt.subplot(1,2,2)
    plt.axis([0.0,0.5,-12,1])
    plt.plot(t, np.log(abs(I-I0)))
    plt.title("ln(|I-1|)")

if __name__ == '__main__':
    name = input()

    plt.figure(figsize=figure_size)

    MAINPATH = "../../data/"
    PATH = "points/data/"
    files = glob.glob(MAINPATH+PATH+name+"_*")
    if len(files) == 0:
        print('Warning: no files matching the pattern have been found')

    for file in files:
        t, rx, ry, kx, ky = np.loadtxt(file, unpack=True)
        plot_data(t, rx, ry)
    plt.savefig(MAINPATH+"images/"+name+"_diagram.png")
    plt.show()