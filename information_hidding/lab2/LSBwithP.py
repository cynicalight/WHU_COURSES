import cv2
import numpy as np
import matplotlib.pyplot as plt


def embed_lsb(image, message, embedding_rate):
    data = image.copy()
    h, w = data.shape

    # 计算可以嵌入的最大比特数
    max_bits = h * w
    embed_bits = int(max_bits * embedding_rate)

    # 将图像展平为一维数组
    flat_data = data.flatten()

    # 生成随机比特作为消息（为了简化）
    secret_message = np.random.randint(0, 2, embed_bits)
    print("秘密信息：", secret_message)

    # 嵌入秘密信息
    for i in range(embed_bits):
        flat_data[i] = (flat_data[i] & 0xFE) | secret_message[i]

    # 将修改后的数据重新整形为原始图像形状
    data_with_secret = flat_data.reshape(data.shape)

    return data_with_secret


# 读取原始图像
original_image = cv2.imread('attach/a.png', 0)  # 读取为灰度图像
# 输出灰度图像
cv2.imwrite('attach/gray.png', original_image)

# 定义不同的嵌入率
embedding_rates = [0.25, 0.5, 0.75]

# 对每个嵌入率生成图像
for i, rate in enumerate(embedding_rates, 1):
    print(f"嵌入率为 {rate}")
    embedded_image = embed_lsb(original_image, "dummy_message", rate)
    cv2.imwrite(f'attach/lsb{i}.png', embedded_image)
    print(f"生成了嵌入率为 {rate} 的LSB图像：lsb{i}.png")

print("LSB嵌入完成")
