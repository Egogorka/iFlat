import anneal
import numpy as np
import subprocess as sp
import numpy as np

SERIES_TYPES = ["fourier", "poly"]
EXECUTABLE_PATH = ""

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

    energy_f = lambda n: energy(series_type, n, height, angle, number_of_rays, dt)
    anneal.anneal(energy_f)


def energy(series_type: str, n: np.array, h: float, angle: float, number_of_rays: float, dt: float):
    def gen_string():
        print(n)
        return f"""
        {series_type}
        {len(n)}
        {' '.join(list(map(str, n)))}
        {h}
        {angle}
        {dt}
        {number_of_rays}
        0
        """
    print(gen_string())
    ppn = sp.Popen([EXECUTABLE_PATH], stdout=sp.PIPE)
    out, err = ppn.communicate(input=bytes(gen_string()), timeout=15)
    print(out)
    return float(out)


if __name__ == "__main__":
    main()


