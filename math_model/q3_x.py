from scipy.interpolate import CubicSpline
import numpy as np
import matplotlib.pyplot as plt
import os

# 创建保存文件的目录
dir_pic = 'q3_pic/'
if not os.path.exists(dir_pic):
    os.makedirs(dir_pic)

# 定义曲线方程
def curve_equation(x):
    return x**3 + x

# 计算曲线上各点的一阶和二阶导数
def first_derivative(x):
    return 3 * x**2 + 1

def second_derivative(x):
    return 6 * x

# 计算曲率
def curvature(x):
    return np.abs(second_derivative(x)) / (1 + first_derivative(x)**2)**(3/2)


# 选择采样点间距
num_samples = 8
endpoint = 1
x_samples = np.linspace(0, endpoint, num_samples)

# 计算采样点的曲率
curvature_samples = curvature(x_samples)

# 使用插值重构曲线
# 初始点和初始斜率
slope0 = 1  # 初始斜率为1，即45度
x_start = 0
y_start = 0  # 假设起始位置的纵坐标为0

# 定义积分步长
# delta_x = 0.1

# 计算曲线路径
x_values = [x_start]
y_values = [y_start]
slope = slope0

for x, curvature in zip(x_samples[1:], curvature_samples):
    # 根据曲率和当前点的斜率计算下一个点的位置
    y = y_values[-1] + slope * (x - x_values[-1])
    slope += curvature * (x - x_values[-1])

    # 添加到路径列表中
    x_values.append(x)
    y_values.append(y)


# 绘制原始曲线和重构曲线
plt.figure(figsize=(10, 5))
plt.plot(x_samples, curve_equation(x_samples), label='Original Curve')
def pic():
    plt.plot(x_values, y_values, label='Reconstructed Curve for Equidistant Sampling')
pic()
plt.xlabel('x')
plt.ylabel('y')
plt.title('Comparison of Original and Interpolated Curves')
plt.legend()
plt.grid(True)
# 保存图形到文件
plt.savefig(f'{dir_pic}q3_x.png')
plt.show()
plt.clf()
