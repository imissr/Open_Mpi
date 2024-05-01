import matplotlib.pyplot as plt
import numpy as np

def custom_function(p, alpha):
    return ((1 - alpha) / p) + alpha

def s_function(p, alpha):
    return 1 - alpha + alpha * p

def plot_functions(alpha_values, p_range=(1, 1025), num_points=1000):
    p_values = np.linspace(p_range[0], p_range[1], num_points)

    plt.figure(figsize=(10, 6))

    for alpha in alpha_values:
        #function_values = custom_function(p_values, alpha)
      #  plt.plot(p_values, function_values, label=f'((1-{alpha})/p) + {alpha}')

        s_values = s_function(p_values, alpha)
        plt.plot(p_values, s_values, linestyle='--', label=f's(p) = 1 - {alpha} + {alpha} * p')


    plt.xlabel('p')
    plt.ylabel('Time')
    #plt.ylabel('E')

    plt.legend()
    plt.grid(True)
    plt.show()

if __name__ == '__main__':
    alpha_values_to_plot = [0.8]
    plot_functions(alpha_values_to_plot)