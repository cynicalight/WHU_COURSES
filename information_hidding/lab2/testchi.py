import numpy as np
from scipy.stats import chi2

degrees_of_freedom = 127
for i in range(200):
    p_values = 1 - chi2.cdf(i, degrees_of_freedom)
    print(f"{i}: {p_values}")
