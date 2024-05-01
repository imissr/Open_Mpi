

import matplotlib.pyplot as plt
import numpy as np


def custom_function(p, alpha):
    return 1 / ((1 - alpha) + alpha / p)


def plot_functions(alpha_values, p_range=(1, 1025), num_points=1000):
    p_values = np.linspace(p_range[0], p_range[1], num_points)

    for alpha in alpha_values:
        function_values = custom_function(p_values, alpha)
        plt.plot(p_values, function_values, label=f'α={alpha}')

    plt.title('Function Plot: 1/((1-α) + α/p)')
    plt.xlabel('p')
    plt.ylabel('Function Value')

    plt.legend()
    plt.grid(True)
    plt.show()


if __name__ == '__main__':

    alpha_values_to_plot = [0.25, 0.5, 0.75, 0.9]
    plot_functions(alpha_values_to_plot)