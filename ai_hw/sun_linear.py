import numpy as np
import pandas as pd

# 计算均方误差（Mean Squared Error，MSE）

def mean_squared_error(y_true, y_pred):
    n = len(y_true)
    squared_errors = np.square(y_true - y_pred)
    mse = np.sum(squared_errors) / n
    return mse


# 导入数据
sun = pd.read_csv("sun.csv", index_col="date")
print(sun)

# 处理数据 后两行作为测试
# 提取特征矩阵 X 和目标变量 y
# 选择列索引为1到3的数据作为训练集特征，即 'low'、'high'、'airquality'
X = sun.iloc[:-2, 1:3].values
# 选择列索引为4的数据作为训练集目标变量，即 'result'
y = sun.iloc[:-2, 3].values.reshape((-1, 1))


# x变成增广矩阵 后续计算
ones = np.ones(X.shape[0]).reshape(-1, 1)
X = np.hstack((X, ones))

# 计算系数
w_ = np.dot(np.dot(np.linalg.inv(np.dot(X.T, X)), X.T), y)
w = w_[:-1]
b = w_[-1]

print(w)
print(b)

X_test = sun.iloc[-2:, :2].values
y_test = sun.iloc[-2:, 3].values.reshape((-1, 1))
y_pred = np.dot(X_test, w) + b
# y_pred = np.dot(np.hstack((X_test, ones)), w_)
print("目标值：\n", y_test)
print("预测值：\n", y_pred)

# 示例用法
y_true = np.array(y_test)
y_pred = np.array(y_pred)

mse = mean_squared_error(y_true, y_pred)
print("MSE:", mse)
