import anneal
import numpy as np
import subprocess as sp
import numpy as np

SERIES_TYPES = ["fourier", "poly"]
EXECUTABLE_PATH = "../../build/iFlat"

def main():
    series_type = input("Enter series type(fourier/poly): ")
    if not series_type in SERIES_TYPES:
        print("Unknown series type: " + series_type)
        return
    try:
        inp = input("Enter number of elements in series: ")
        series_length = int(inp)
    except ValueError:
        print('Conversion error: \"' + inp + "\" is not an integer.")
        return
    except:
        print("Unknown error")
        return
    if series_length <= 0:
        print("Number of elements must be positive.")
        return

    try:
        inp = input("Enter viewpoint height(R=1): ")
        height = float(inp)
    except ValueError:
        print('Conversion error: \"' + inp + "\" is not a float.")
        return
    except:
        print("Unknown error")
        return
    if height < 0:
        print('Height must be positive.')
        return

    try:
        inp = input("Enter sweep angle(from 0 to pi / 2): ")
        angle = float(inp)
    except ValueError:
        print('Conversion error: \"' + inp + "\" is not a float.")
        return
    except:
        print("Unknown error")
        return
    if angle < 0:
        print('Sweep angle must be positive.')
        return
    elif angle > np.pi / 2:
        print("Sweep angle must be less than pi / 2.")

    try:
        inp = input("Enter number of rays: ")
        number_of_rays = int(inp)
    except ValueError:
        print('Conversion error: \"' + inp + "\" is not an integer.")
        return
    except:
        print("Unknown error")
        return
    if number_of_rays <= 0:
        print("Number of rays must be positive.")

    try:
        inp = input("Enter dt: ")
        dt = float(inp)
    except ValueError:
        print('Conversion error: \"' + inp + "\" is not a float.")
        return
    except:
        print("Unknown error")
        return
    if dt < 0:
        print('Sweep angle must be positive.')
        return

    energy_f = lambda n, save_tr, step: energy(series_type, n, height, angle, number_of_rays, dt, save_tr, step)
    coeffs, sol_energy = anneal.anneal(energy_f, poly_power=series_length, max_steps=50, initial_temp=30)
    print(coeffs)


def energy(series_type: str, n: np.array, h: float, angle: float, number_of_rays: float, dt: float, save_trajectories: bool, step: int):
    def gen_string():
        return f"""{series_type}
        {len(n)}
        {' '.join(list(map(str, n)))}
        {h}
        {angle}
        {dt}
        {number_of_rays}
        {int(save_trajectories)}
        {step if save_trajectories else ""}
        """
    ppn = sp.Popen([EXECUTABLE_PATH], stdout=sp.PIPE, stdin=sp.PIPE, stderr=sp.PIPE)
    out, err = ppn.communicate(input=bytes(gen_string(), 'utf-8'), timeout=12)
    print("Energy ", out)
    print('Saving: ', save_trajectories)
    if(save_trajectories):
        print(gen_string())
    return float(out)


if __name__ == "__main__":
    main()


