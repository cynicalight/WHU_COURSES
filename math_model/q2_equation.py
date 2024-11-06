import numpy as np
import matplotlib.pyplot as plt
from scipy.interpolate import CubicSpline
from scipy.integrate import odeint

# 输入波长测量数据
lambda0_1 = 1529 * np.ones(6)
lambda_1 = np.array([1529.808, 1529.807, 1529.813,
                    1529.812, 1529.814, 1529.809])
lambda0_2 = 1540 * np.ones(6)
lambda_2 = np.array([1541.095, 1541.092, 1541.090,
                    1541.093, 1541.094, 1541.091])

# 计算曲率数据
c = 4200
kappa_1 = c * (lambda_1 - lambda0_1) / lambda0_1
kappa_2 = c * (lambda_2 - lambda0_2) / lambda0_2

# 构建三次样条插值函数
x = np.arange(0.6, 3.7, 0.6)
if len(x) != len(kappa_1):
    raise ValueError("Length of x and kappa_1 arrays must match.")
pp1 = CubicSpline(x, kappa_1)
pp2 = CubicSpline(x, kappa_2)

# 生成横坐标序列
x_interp = np.arange(0.3, 0.8, 0.1)

# 计算插值点处的曲率估计值
kappa_interp1 = pp1(x_interp)
kappa_interp2 = pp2(x_interp)

print('\n测试2的曲率估计值:\n')
print('横坐标x(米)\t曲率kappa')
for i in range(len(x_interp)):
    print('{:.1f}\t\t{:.6f}'.format(x_interp[i], kappa_interp2[i]))

# 初始条件
x0 = 0
y0 = 0
dy0 = 1

# 定义微分方程


def model(y, x, pp):
    return [y[1], pp(x)*(1 + y[1]**2)**(3/2)]


# 使用odeint求解微分方程
x_sol1 = np.linspace(x0, 0.6, 100)
y_sol1 = odeint(model, [y0, dy0], x_sol1, args=(pp1,))
x_sol2 = np.linspace(x0, 0.6, 100)
y_sol2 = odeint(model, [y0, dy0], x_sol2, args=(pp2,))

# 绘制曲线图像
plt.figure(figsize=(12, 6))

plt.subplot(2, 2, 1)
plt.plot(x_sol1, y_sol1[:, 0], 'b-', linewidth=2)
plt.xlabel('x (m)')
plt.ylabel('y (m)')
plt.title('测试1曲线')
plt.grid(True)

plt.subplot(2, 2, 2)
plt.plot(x_sol2, y_sol2[:, 0], 'b-', linewidth=2)
plt.xlabel('x (m)')
plt.ylabel('y (m)')
plt.title('测试2曲线')
plt.grid(True)

plt.subplot(2, 2, 4)
plt.plot(x_interp, kappa_interp2, 'ro-', linewidth=1.5)
plt.xlabel('横坐标x (m)')
plt.ylabel('曲率kappa (1/m)')
plt.title('测试2曲率估计值')
plt.grid(True)

plt.show()
