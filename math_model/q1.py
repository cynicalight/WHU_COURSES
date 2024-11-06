import matplotlib.pyplot as plt
from scipy.interpolate import UnivariateSpline
import numpy as np
import json
import os

# 假设c为常数，lambda0为初始波长
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

# 题目要求的横坐标位置
x_new = [0.3, 0.4, 0.5, 0.6, 0.7]

# beatufy the output
print("Original data:")
print(json.dumps(sensors, indent=4))

# 创建保存文件的目录
dir_pic = 'q1_pic/'
if not os.path.exists(dir_pic):
    os.makedirs(dir_pic)

# 定义一个函数，用于计算某个位置的切线斜率
def slope_function(x):
    # 曲线斜率为曲率的导数
    h = 0.0001 # 取极小量
    return (curvature_function(x + h) - curvature_function(x)) / h

# 定义一个函数，用于计算某个位置的切线与水平方向的夹角
def angle_to_horizontal(x):
    slope = slope_function(x)
    return np.arctan(slope)


print("##########################################################")

# 线性插值
def linear_interpolate(x1, k1, x2, k2, x):
    return k1 + (k2 - k1) * (x - x1) / (x2 - x1)


print("Linear interpolation:")


# 遍历测试编号
for test_num in range(1, 3):
    # 提取对应测试编号的曲率数据
    y = [sensors[key][str(test_num)] for key in x]

    # 线性插值计算
    x_pic = np.linspace(0, 4, 100)
    y_pic = np.interp(x_pic, x, y)
    y_new = np.interp(x_new, x, y)

    # 将插值结果存储为字典，以便输出
    interpolated_curvatures = {x_new[j]: y_new[j] for j in range(len(x_new))}

    print("test_num: ", test_num)
    print(json.dumps(interpolated_curvatures, indent=4))

    # 绘制原始数据点和插值曲线
    plt.plot(x, y, 'o', label='Original data')
    plt.plot(x_pic, y_pic, label='Linear interpolation')
    plt.plot(x_new, y_new, 'o', label='New data')
    plt.xlabel('Position')
    plt.ylabel('Curvature')
    plt.title(f'Linear Interpolation for Test {test_num}')
    plt.legend()

    # 保存图形到文件
    plt.savefig(f'{dir_pic}q1_linear_test{test_num}.png')
    # print(f"Saved to {dir_pic}q1_linear_test{i}.png")
    plt.clf()
    # plt.show()
    
    print("-----------------------------------")


print("##########################################################")

# 以k=3为例演示建模算法

# 三次样条插值
print("Cubic spline interpolation:")


for test_num in range(1,3):
    y = [sensors[key][str(test_num)] for key in x]
    # 创建一个三次样条插值函数
    spline = UnivariateSpline(x, y, k=4)
    def curvature_function(x):
        return spline(x)

    # 新的数据点，用于插值
    x_pic = np.linspace(0, 4, 100)
    # 计算插值结果
    y_pic = spline(x_pic)
    y_new = spline(x_new)
    interpolated_curvatures = {x_new[i]: y_new[i] for i in range(len(x_new))}
    print("test_num: ", test_num)
    print(json.dumps(interpolated_curvatures, indent=4))

    
    
    # 绘制原始数据点和插值曲线

    plt.plot(x, y, 'o', label='Original data')
    plt.plot(x_pic, y_pic, label='Cubic spline interpolation')
    plt.plot(x_new, y_new, 'o', label='New data')
    plt.title(f'Cubic Spline Interpolation for Test {test_num}')
    plt.legend()
    # 保存图形到文件
    plt.savefig(f'{dir_pic}q1_spline_test{test_num}.png')
    plt.clf()

    print("-----------------------------------")
    
