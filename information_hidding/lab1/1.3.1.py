import cv2
import numpy as np
import matplotlib.pyplot as plt

# 读取图像
image_path = 'a.jpg'
image = cv2.imread(image_path, cv2.IMREAD_GRAYSCALE)

# 确保图像数据类型为 np.uint8
image = image.astype(np.uint8)
print('image:', image)

# 提取 LSB 位平面
lsb_plane = image & 1
print('LSB Plane:', lsb_plane)

# 修改 LSB 位平面
modified_image = image.copy()
modified_image = modified_image & 0xfe  # 清除 LSB


# 显示原始图像、LSB 位平面和修改后的图像
plt.figure(figsize=(15, 5))

plt.subplot(131)
plt.imshow(image, cmap='gray')
plt.title('Original Image')
plt.axis('off')

plt.subplot(132)
plt.imshow(lsb_plane * 255, cmap='gray')
plt.title('LSB Plane')
plt.axis('off')

plt.subplot(133)
plt.imshow(modified_image, cmap='gray')
plt.title('Modified Image')
plt.axis('off')

plt.show()