import cv2
import numpy as np
import matplotlib.pyplot as plt

# 读取图像文件
data = cv2.imread('a.jpg')
img = data[:, :, 0]  # B
print("img:", img)
img = np.float32(img)  # 将数值精度调整为32位浮点型
img_dct = cv2.dct(img)  # 使用dct获得img的频域图像
img_idct = cv2.idct(img_dct)  # 使用反dct从频域图像恢复出原图像(有损)
img_idct_int = np.clip(img_idct, 0, 255).astype(np.uint8)  # 将浮点型数据转换为整型数据
# 将三个通道合并
img_merge = cv2.merge([img_idct_int, data[:, :, 1], data[:, :, 2]])
cv2.imwrite('idct.jpg', img_merge)

plt.figure(figsize=(10, 5))

# 显示图像
plt.subplot(121)
plt.imshow(cv2.cvtColor(data, cv2.COLOR_BGR2RGB))
plt.title('Original Image'), plt.axis('off')
plt.subplot(122)
plt.imshow(cv2.cvtColor(img_merge, cv2.COLOR_BGR2RGB))
plt.title('IDCT of Image'), plt.axis('off')
plt.show()
plt.show()
