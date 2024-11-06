import numpy as np
import matplotlib.pyplot as plt
import function_selfdefined as fsd
import os

# 创建保存文件的目录
dir_pic = 'q2_pic/'
if not os.path.exists(dir_pic):
    os.makedirs(dir_pic)

# 曲率模型1: 数值积分法

def curvature_function(x, test_num):
    return fsd.curvature_spline(x, test_num)


for test_num in range(1, 3):
    # 初始点和初始斜率
    x0 = 0
    slope0 = 1  # 初始斜率为1，即45度

    # 确定曲线起始位置
    x_start = x0
    y_start = 0  # 假设起始位置的纵坐标为0

    # 定义积分步长
    delta_x = 0.01

    # 计算曲线路径
    x_values = [x_start]
    y_values = [y_start]
    slope = slope0

    for x in np.arange(x_start + delta_x, 10, delta_x):  # 这里假设曲线的终止位置为10
        # 计算当前点的曲率
        curvature = curvature_function(x, test_num)

        # 根据曲率和当前点的斜率计算下一个点的位置
        y = y_values[-1] + slope * delta_x
        slope += curvature * delta_x

        # 添加到路径列表中
        x_values.append(x)
        y_values.append(y)

    # 绘制曲线
    plt.plot(x_values, y_values)
    plt.xlabel('X')
    plt.ylabel('Y')
    plt.title(f'Reconstructed Curve by Numerical Integration{test_num}')
    plt.grid(True)
    plt.savefig(f'{dir_pic}q2_num_test{test_num}.png')
    # plt.show()
    plt.clf()

