# 假设c为常数，lambda0为初始波长
import matplotlib.pyplot as plt
from scipy.interpolate import UnivariateSpline
import numpy as np
import json
import os

c = 4200
lambda0 = 1529
lambda1 = 1540

# 传感器位置和对应的曲率
# 创建一个字典，存储每个传感器位置及其两个下的曲率
sensors = {
    0.6: {
        '1': (1529.808 - lambda0) * c / lambda0,
        '2': (1541.095 - lambda1) * c / lambda1
    },
    1.2: {
        '1': (1529.807 - lambda0) * c / lambda0,
        '2': (1541.092 - lambda1) * c / lambda1
    },
    1.8: {
        '1': (1529.813 - lambda0) * c / lambda0,
        '2': (1541.090 - lambda1) * c / lambda1
    },
    2.4: {
        '1': (1529.812 - lambda0) * c / lambda0,
        '2': (1541.093 - lambda1) * c / lambda1
    },
    3.0: {
        '1': (1529.814 - lambda0) * c / lambda0,
        '2': (1541.094 - lambda1) * c / lambda1
    },
    3.6: {
        '1': (1529.809 - lambda0) * c / lambda0,
        '2': (1541.091 - lambda1) * c / lambda1
    }
}

# 给定的 x 值
x = np.array([0.6, 1.2, 1.8, 2.4, 3.0, 3.6])


def curvature_spline(x_new, i):
    y = [sensors[key][str(i)] for key in x]
    # 创建一个三次样条插值函数
    spline = UnivariateSpline(x, y, k=2)    
    return spline(x_new)
 
