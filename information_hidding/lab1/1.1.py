import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
import cv2
from scipy.fftpack import dct, idct

# 读取 BMP 图像文件
data1 = cv2.imread('c:/woman.bmp')
print("data1 (woman.bmp):\n", data1)

# 读取 JPG 图像文件
data1 = cv2.imread('./Lenna.jpg')
print("data1 (Lenna.jpg):\n", data1)

a = np.array([[1, 2],
              [2, 3]])
b = np.array([[1, 2],
              [2, 3]])
print(a, '\n', b)
print('a * b \n', a * b)
print('a dot b \n', a.dot(b))

zero = np.zeros((2, 2))
print('zero \n', zero)

# rand：均匀分布随机矩阵
# 无变量输入时只产生一个随机数
random_number = np.random.rand()
print("random_number:", random_number)
print()

# 生成 n*n 随机矩阵，其元素在（0,1）内
n = 3
y_n = np.random.rand(n, n)
print("y_n (n*n random matrix):\n", y_n)
print()

# 生成 m*n 的随机矩阵
m, n = 2, 3
y_mn = np.random.rand(m, n)
print("y_mn (m*n random matrix):\n", y_mn)
print()

# randn：正态分布随机矩阵
y_randn = np.random.randn(m, n)
print("y_randn (m*n normal distribution matrix):\n", y_randn)
print()

# randint：整数随机分布矩阵
# 生成一个 m 行 n 列的元素，元素值在 [0, rg-1] 之间
rg = 10
y_randint = np.random.randint(0, rg, (m, n))
print("y_randint (m*n integer random matrix in [0, rg-1]):\n", y_randint)
print()


# 设置一个种子，设置后下面的随机数是一定的
np.random.seed(1032)

# 生成 m*n 随机矩阵，其元素在（0,1）内
m, n = 5, 4
random_matrix = np.random.rand(m, n)
print("random_matrix (m*n random matrix):\n", random_matrix)
print()

# 生成一个 m 行 n 列的元素，元素值在 [0, rg-1] 之间
rg = 4
random_int_matrix = np.random.randint(0, rg, (m, n))
print(
    "random_int_matrix (m*n integer random matrix in [0, rg-1]):\n", random_int_matrix)
print()

df = pd.DataFrame(random_int_matrix)

# 写入 CSV 文件
df.to_csv('1.txt', index=False)


# 读取 CSV 文件
df = pd.read_csv('1.txt')
print("DataFrame:\n", df)


# # 读取 BMP 图像文件
# data1 = cv2.imread('c:/woman.bmp')
# print("data1 (woman.bmp):\n", data1)

# 读取 JPG 图像文件
data1 = cv2.imread('a.jpg')
data1_rgb = cv2.cvtColor(data1, cv2.COLOR_BGR2RGB)


# 提取红色通道
imageR = data1[:, :, 2]  # OpenCV 读取的图像是 BGR 格式

# 提取绿色通道
imageG = data1[:, :, 1]

# 提取蓝色通道
imageB = data1[:, :, 0]

print("Red channel:\n", imageR)
print("Green channel:\n", imageG)
print("Blue channel:\n", imageB)

imageZ = np.zeros_like(imageR)

# 色彩合成 merge 按照 RGB 顺序合成
Mix = cv2.merge([imageB, imageG, imageB])

# 保存合成后的图像
cv2.imwrite('merged_image.jpg', Mix)

# 获取图像的行和列
rows, cols, _ = data1.shape
print(f"Rows: {rows}, Columns: {cols}")

# 进行二维离散余弦变换
dct_data1 = dct(dct(data1.T, norm='ortho').T, norm='ortho')

# 进行二维离散余弦逆变换
idct_data1 = idct(idct(dct_data1.T, norm='ortho').T, norm='ortho')

# 显示原始图像、DCT 变换后的图像和逆变换后的图像
plt.figure(figsize=(15, 5))

plt.subplot(131)
plt.imshow(data1, cmap='gray')
plt.title('Original Image')
plt.axis('off')

plt.subplot(132)
plt.imshow(np.log(np.abs(dct_data1) + 1), cmap='gray')  # 使用对数变换增强显示效果
plt.title('DCT of Image')
plt.axis('off')

plt.subplot(133)
plt.imshow(idct_data1, cmap='gray')
plt.title('IDCT of Image')
plt.axis('off')

plt.show()

# plt.figure(figsize=(10, 10))
# # subplot(mnp): 两个参数表示将画画布为 m*n 个子图像， p表示子图像序号，排序顺序为从左至右，从上至下。
# plt.subplot(221)
# plt.imshow(data1_rgb)
# plt.subplot(222)
# plt.imshow(Mix)
# plt.show()
