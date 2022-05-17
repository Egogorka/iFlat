import anneal
import numpy as np
import subprocess as sp
import numpy as np
import sys
import datetime
import pathlib
import logging

SERIES_TYPES = ["fourier", "poly"]
EXECUTABLE_PATH = "../build/iFlat"
TIMEOUT = 120
LOG_PATH = "../log/"

def setup_logging():
    pathlib.Path(LOG_PATH).mkdir(exist_ok=True)
    log_file = LOG_PATH + datetime.datetime.now().strftime("%d.%m.%Y - %H.%M.%S") + ".log"

    formatter = logging.Formatter("%(asctime)s [%(levelname)s]: %(message)s", "%d.%m.%Y %H:%M:%S")

    sh = logging.StreamHandler(sys.stdout)
    sh.setFormatter(formatter)
    fh =logging.FileHandler(log_file)
    fh.setFormatter(formatter)
    logging.basicConfig(level=logging.DEBUG,
                        handlers=[
                            sh,
                            fh
    ])



def main():
    setup_logging()

    series_type = input("Enter series type(fourier/poly): ")
    if not series_type in SERIES_TYPES:
        logging.error("Unknown series type: " + series_type)
        return
    try:
        inp = input("Enter number of elements in series: ")
        series_length = int(inp)
    except ValueError:
        logging.error('Conversion error: \"' + inp + "\" is not an integer.")
        return
    except:
        logging.error("Unknown error")
        return
    if series_length <= 0:
        logging.error("Number of elements must be positive.")
        return

    try:
        inp = input("Enter viewpoint height(R=1): ")
        height = float(inp)
    except ValueError:
        logging.error('Conversion error: \"' + inp + "\" is not a float.")
        return
    except:
        logging.error("Unknown error")
        return
    if height < 0:
        logging.error('Height must be positive.')
        return

    try:
        inp = input("Enter sweep angle(from 0 to pi / 2): ")
        angle = float(inp)
    except ValueError:
        logging.error('Conversion error: \"' + inp + "\" is not a float.")
        return
    except:
        logging.error("Unknown error")
        return
    if angle < 0:
        logging.error('Sweep angle must be positive.')
        return
    elif angle > np.pi / 2:
        logging.error("Sweep angle must be less than pi / 2.")

    try:
        inp = input("Enter number of rays: ")
        number_of_rays = int(inp)
    except ValueError:
        logging.error('Conversion error: \"' + inp + "\" is not an integer.")
        return
    except:
        logging.error("Unknown error")
        return
    if number_of_rays <= 0:
        logging.error("Number of rays must be positive.")

    try:
        inp = input("Enter dt: ")
        dt = float(inp)
    except ValueError:
        logging.error('Conversion error: \"' + inp + "\" is not a float.")
        return
    except:
        logging.error("Unknown error")
        return
    if dt < 0:
        logging.error('Sweep angle must be positive.')
        return

    info_str = f"series type: {series_type}; series length: {series_length}; height: {height}; sweep angle: {angle}; number of rays: {number_of_rays}; dt: {dt}"
    logging.info(info_str)

    energy_f = lambda n, save_tr, step: energy(series_type, n, height, angle, number_of_rays, dt, save_tr, step)
    coeffs, sol_energy = anneal.anneal(energy_f, poly_power=series_length, max_steps=200, initial_temp=1,
                                       initial_val=np.array([1]))
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
    out, err = ppn.communicate(input=bytes(gen_string(), 'utf-8'), timeout=TIMEOUT)
    out = out.decode('utf-8')
    logging.debug("Energy " + out)
    logging.debug('Saving: ' + str(save_trajectories))
    if(save_trajectories):
        logging.debug(gen_string())
    return float(out)


if __name__ == "__main__":
    main()


