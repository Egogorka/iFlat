import anneal
import subprocess as sp
import numpy as np
import sys
import datetime
import pathlib
import logging

SERIES_TYPES = ["fourier", "poly"]
EXECUTABLE_PATH = "../cmake-build-debug/iFlat"
TIMEOUT = 1200
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
    #series_type = 'poly'
    #series_length = 8
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
    #height = 0.1
    try:
        inp = input("Enter sweep angle(from 0 to pi): ")
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
    elif angle > np.pi:
        logging.error("Sweep angle must be less than pi.")
    # angle = 2 * np.arcsin(1 / (1 + height))

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
    #number_of_rays = 60
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

    file_prefix = datetime.datetime.now().strftime("%d.%m-%H.%M-")
    energy_f = lambda n, save_tr, step: energy(series_type, n, height, angle, number_of_rays, dt, save_tr, step, file_prefix)
    coeffs, sol_energy = anneal.anneal(energy_f,
                                       poly_power=series_length,
                                       max_steps=1023456789,
                                       initial_temp=1,
                                       q=1-1*1e-3,
                                       sigma=0.9,
                                       reheat_temp=1e-8,
                                       reheat_degree=0.04
                                       )
    print(coeffs)


def energy(series_type: str, n: np.array, h: float, angle: float, number_of_rays: float, dt: float, save_trajectories: bool, step: int, file_prefix: str):
    def gen_string():
        return f"""{series_type}
        {len(n)}
        {' '.join(list(map(str, n)))}
        {h}
        {angle}
        {dt}
        {number_of_rays}
        {int(save_trajectories)}
        {(file_prefix + str(step)) if save_trajectories else ""}
        """
    ppn = sp.Popen([EXECUTABLE_PATH], stdout=sp.PIPE, stdin=sp.PIPE, stderr=sp.PIPE)
    out, err = ppn.communicate(input=bytes(gen_string(), 'utf-8'), timeout=TIMEOUT)
    out = out.decode('utf-8')
    
    if(save_trajectories):
        logging.debug(gen_string())
        logging.debug("Energy " + out)
        logging.debug('Saving: ' + str(save_trajectories))
    return float(out)


if __name__ == "__main__":
    main()


