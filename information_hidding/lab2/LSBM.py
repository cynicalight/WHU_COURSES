import cv2
import numpy as np
import matplotlib.pyplot as plt

# 读取图像文件
data = cv2.imread('attach/a.png')

# 检查图像是否成功读取
if data is None:
    raise FileNotFoundError("无法读取图像文件 'a.jpg'，请检查文件路径和文件完整性。")

# 生成随机位置
np.random.seed(42)  # 固定随机种子以便复现
height, width, _ = data.shape
num_pixels = height * width
num_random_points = num_pixels // 10  # 随机选取10%的像素点
random_indices = np.random.choice(num_pixels, num_random_points, replace=False)
print('Random Indices:', random_indices)

# 将图像展平为一维数组
flat_data = data.flatten()
flat_data = flat_data & 0xFE  # 将所有像素的LSB设为0
 
# 嵌入秘密信息（例如，将所有随机位置的LSB设为1）
secret = 'Hello, World!'
print('secret:', secret)
# 将秘密信息转换为二进制
secret_message = np.unpackbits(np.frombuffer(secret.encode(), dtype=np.uint8))
print('secret_message:', secret_message)

# lsbm
for i in range(len(secret_message)):
    pixel_value = flat_data[random_indices[i]]
    lsb = pixel_value & 1
    if lsb != secret_message[i]:
        if np.random.rand() > 0.5:
            flat_data[random_indices[i]] += 1
        else:
            flat_data[random_indices[i]] -= 1
    # 处理边界情况
    flat_data[random_indices[i]] = np.clip(
        flat_data[random_indices[i]], 0, 255)

# 将修改后的数据重新整形为原始图像形状
data_with_secret = flat_data.reshape(data.shape)

# 提取秘密信息
flat_extracted_message = data_with_secret.flatten()
extracted_message = flat_extracted_message[random_indices] & 1 # 提取LSB
extracted_message = np.packbits(extracted_message).tobytes().decode()  # 将二进制转换为字符串
print('extracted_message:', extracted_message)

# 画出随机位置
#  unravel_index 函数将一维的平面索引转换为二维的坐标数组
random_positions = np.unravel_index(random_indices, (height, width))
print('Random Positions:', random_positions)
data_with_random_points = data.copy()
data_with_random_points[random_positions] = [0, 0, 255]  # 用红色标记随机位置

# 计算并绘制隐写前后的图像直方图
plt.figure(figsize=(15, 5))

plt.subplot(131)
plt.imshow(cv2.cvtColor(data, cv2.COLOR_BGR2RGB))
plt.title('Original Image')
plt.axis('off')

plt.subplot(132)
plt.imshow(cv2.cvtColor(data_with_secret, cv2.COLOR_BGR2RGB))
plt.title('Image with Secret')
plt.axis('off')
plt.savefig('attach/lsbm.png')


plt.subplot(133)
plt.imshow(cv2.cvtColor(data_with_random_points, cv2.COLOR_BGR2RGB))
plt.title('Random Points')
plt.axis('off')

plt.figure(figsize=(10, 5))
plt.subplot(121)
plt.hist(data.ravel(), bins=256, color='blue', alpha=0.5, label='Original')
plt.hist(data_with_secret.ravel(), bins=256,
         color='red', alpha=0.5, label='With Secret')
plt.legend()
plt.title('Histogram Comparison')

plt.show()
