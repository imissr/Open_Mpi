import matplotlib.pyplot as plt
import numpy as np


# Define the function
def custom_function(p, N1, N2, k, c, m):
    T_Comp = (k * N2 / p)
    T_comm = (c * N1 / p)
    T_idle = (m / p)
    T_total = T_Comp + T_comm + T_idle
    return T_total, T_Comp, T_comm, T_idle


if __name__ == '__main__':

    # Parameters
    N1 = 6 * 5000 * 5000
    N2 = 5000 * 5000 * 5000
    k = 0.8
    c = 5
    m = 0.5


    p_values = np.arange(1, 1025, 1)

    T_total_values, T_Comp_values, T_comm_values, T_idle_values = custom_function(p_values, N1, N2, k, c, m)




    plt.plot(p_values, T_Comp_values, label='T_Comp')
    plt.plot(p_values, T_comm_values, label='T_comm')
    plt.plot(p_values, T_idle_values, label='T_idle')

    # Plot the total function
    plt.plot(p_values, T_total_values, label='T_total', linestyle='--', linewidth=2)


    plt.xlabel('processes')
    plt.ylabel('Time')
    plt.yscale("log",base=2)
    plt.legend()
    plt.grid(True)
    plt.show()
