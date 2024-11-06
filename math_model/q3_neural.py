import numpy as np
import matplotlib.pyplot as plt
from scipy.interpolate import UnivariateSpline
from sklearn.neural_network import MLPRegressor
from sklearn.preprocessing import MinMaxScaler
from sklearn.metrics import mean_squared_error
from scipy.optimize import root
from scipy.interpolate import CubicSpline
from scipy.integrate import quad
from scipy.optimize import root
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

# 积分函数，用于计算弧长
def integrand(x):
    return np.sqrt(1 + first_derivative(x)**2)

# 等弧长采样点数量
num_samples = 10
endpoint = 1

# 计算曲线的总弧长
curve_length, _ = quad(integrand, 0, endpoint)
print("curve_length: ", curve_length)

# 计算等弧长采样点的弧长步长
arc_length_step = curve_length / (num_samples - 1)
print("arc_length_step: ", arc_length_step)

# 初始化等弧长采样点和曲率列表
x_samples = [0]
curvature_samples = [curvature(0)]


for i in range(1, num_samples):
    # 计算当前采样点的弧长
    current_arc_length = i * arc_length_step
    # 定义一个函数，这个函数返回从 x=0 到给定 x 的 integrand 函数的积分减去 current_arc_length

    def func(x):
        return quad(integrand, 0, x)[0] - current_arc_length
    # 使用 scipy.optimize.root 找到使得 func 等于 0 的 x 值
    x_sample = root(func, x_samples[-1]).x[0]
    print("x_sample: ", x_sample)
    # 添加当前采样点和曲率到列表中
    x_samples.append(x_sample)
    curvature_samples.append(curvature(x_sample))

x_samples_np = np.array(x_samples)


# 使用插值重构曲线
# 初始点和初始斜率
slope0 = 1  # 初始斜率为1，即45度
x_start = 0
y_start = 0  # 假设起始位置的纵坐标为0

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

x_values_np = np.array(x_values)
y_values_np = np.array(y_values)

# 神经网络模型训练
scaler = MinMaxScaler()
x_curvature_scaled = scaler.fit_transform(x_values_np.reshape(-1, 1))
y_curvature_scaled = scaler.fit_transform(y_values_np.reshape(-1, 1))
mlp = MLPRegressor(hidden_layer_sizes=(10, 10), max_iter=1000)
mlp.fit(x_curvature_scaled, curve_equation(x_samples_np))

# 使用神经网络进行曲线重构
x_new_scaled = scaler.transform(x_values_np.reshape(-1, 1))
y_path_reconstructed = mlp.predict(x_new_scaled)


# 绘制结果
plt.figure(figsize=(10, 5))

plt.plot(x_samples, curve_equation(x_samples_np), label='Original Curve')
plt.plot(x_values, y_values,
         label='Reconstructed Curve for Equiarc-length Sampling')

plt.plot(x_new_scaled, y_path_reconstructed,
         label='Reconstructed Path (Neural Network)')
plt.xlabel('X')
plt.ylabel('Y')
plt.title('Neural Network Optimization')
plt.legend()
plt.savefig(f'{dir_pic}q3_neural.png')

plt.tight_layout()
plt.show()
plt.clf()
