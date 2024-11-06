import cv2
import numpy as np
import matplotlib.pyplot as plt


def embed_lsbm(image, message, embedding_rate):
    data = image.copy()
    h, w = data.shape

    # 计算可以嵌入的最大比特数
    max_bits = h * w
    embed_bits = int(max_bits * embedding_rate)

    # 生成随机位置
    random_indices = np.random.choice(max_bits, embed_bits, replace=False)

    # 将图像展平为一维数组
    flat_data = data.flatten()

    # 生成随机比特作为消息（为了简化）
    secret_message = np.random.randint(0, 2, embed_bits)

    # 嵌入秘密信息（使用LSBM方法）
    for i in range(embed_bits):
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

    return data_with_secret


# 读取原始图像
original_image = cv2.imread('attach/a.png', 0)  # 读取为灰度图像

# 定义不同的嵌入率
embedding_rates = [0.25, 0.5, 0.75]

# 对每个嵌入率生成图像
for i, rate in enumerate(embedding_rates, 1):
    embedded_image = embed_lsbm(original_image, "dummy_message", rate)
    cv2.imwrite(f'attach/lsbm{i}.png', embedded_image)
    print(f"生成了嵌入率为 {rate} 的LSBM图像：lsbm{i}.png")

print("LSBM嵌入完成")
