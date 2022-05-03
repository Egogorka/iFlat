import anneal
import numpy as np

SERIES_TYPES = ["fourier", "poly"]

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
        inp = input("Enter sweep angle: ")
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

def energy(series_type: str, n: np.array, h: float, alpha: float, number_of_rays: float, dt: float):
    pass


if __name__ == "__main__":
    main()


