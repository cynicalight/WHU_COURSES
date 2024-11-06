import cv2
import numpy as np
import matplotlib.pyplot as plt
from scipy.fftpack import dct, idct

# 选择两个系数的坐标
u1, v1 = 5, 2
u2, v2 = 4, 3
alpha = 50


def embed_secret_message(filepath, secret_message):
    # 读取图像
    data = cv2.imread(filepath)

    # 获取图像的高度和宽度
    height, width, _ = data.shape
    height_b, width_b, _ = data.shape
    # 定义块的大小
    block_size = 8
    height_b = height_b - height_b % block_size
    width_b = width_b - width_b % block_size
    print(f"Image height_b: {height_b}, Image width_b: {width_b}")
    # 计算每行有多少个块
    blocks_inarow = width_b // block_size

    # 创建一个列表来存储图像块
    blocks = []

    # 遍历图像并提取块
    for i in range(0, height_b, block_size):
        for j in range(0, width_b, block_size):
            block = data[i:i+block_size, j:j+block_size]
            blocks.append(block)

    # 打印块的数量
    print(f"Total number of blocks: {len(blocks)}")

    # 将字符串转换为二进制表示
    # secret_bits = ''.join(format(ord(char), '08b') for char in secret_message)
    secret_bits = np.unpackbits(np.frombuffer(
        secret_message.encode(), dtype=np.uint8))

    for idx, block_img in enumerate(blocks):
        block = block_img[:, :, 2]  # 仅使用红色通道
        block = block.astype(np.float32)
        # print('block:', block)
        # 对块进行二维DCT变换
        dct_block = dct(dct(block.T, norm='ortho').T, norm='ortho')
        # print('dct_block:', dct_block)

        # 获取当前要嵌入的秘密信息位
        if idx < len(secret_bits):
            bit = secret_bits[idx]
        else:
            break  # 如果秘密信息已经嵌入完毕，则退出循环

        # 调整系数的大小关系
        if bit == 1:
            if dct_block[u1, v1] < dct_block[u2, v2]:
                dct_block[u1, v1], dct_block[u2,
                                             v2] = dct_block[u2, v2], dct_block[u1, v1]
            dct_block[u1, v1] = dct_block[u1, v1] + alpha
        else:
            if dct_block[u1, v1] > dct_block[u2, v2]:
                dct_block[u1, v1], dct_block[u2,
                                             v2] = dct_block[u2, v2], dct_block[u1, v1]
            dct_block[u1, v1] = dct_block[u1, v1] - alpha
            
        # print('dct_block[u1, v1]:', dct_block[u1, v1])
        # print('dct_block[u2, v2]:', dct_block[u2, v2])

        # 对块进行逆DCT变换
        idct_block = idct(idct(dct_block.T, norm='ortho').T, norm='ortho')
        idct_block = idct_block.astype(np.uint8)
        idct_block = cv2.merge(
            [block_img[:, :, 0], block_img[:, :, 1], idct_block])

        # 将处理后的块存回原图像
        blocks[idx] = idct_block

    # 重新组合图像
    stego_image = np.zeros((height, width, 3))
    for idx, block in enumerate(blocks):
        i = (idx // blocks_inarow) * block_size
        j = (idx % blocks_inarow) * block_size
        stego_image[i:i+block_size, j:j+block_size] = block
    stego_image[height_b:, :] = data[height_b:, :]
    stego_image[:, width_b:] = data[:, width_b:]
    stego_image = stego_image.astype(np.uint8)
    outpath = 'stego_image.png'
    # 保存嵌入秘密信息后的图像
    # 注意保存图片质量 100
    # cv2.imwrite(outpath, stego_image, [cv2.IMWRITE_JPEG_QUALITY, 100])
    cv2.imwrite(outpath, stego_image)

    # 显示原图像和嵌入秘密信息后的图像
    plt.figure(figsize=(10, 5))
    plt.subplot(1, 2, 1)
    plt.title('Original Image')
    plt.imshow(cv2.cvtColor(data, cv2.COLOR_BGR2RGB))
    plt.axis('off')
    plt.subplot(1, 2, 2)
    plt.title('Stego Image')
    plt.imshow(cv2.cvtColor(stego_image, cv2.COLOR_BGR2RGB))
    plt.axis('off')
    plt.show()
    return outpath

# 提取秘密信息


def extract_secret_message(filepath):
    # 读取图像
    data = cv2.imread(filepath)

    # 获取图像的高度和宽度
    height_b, width_b, _ = data.shape
    # 定义块的大小
    block_size = 8
    height_b = height_b - height_b % block_size
    width_b = width_b - width_b % block_size
    print(f"Image height_b: {height_b}, Image width_b: {width_b}")

    # 创建一个列表来存储图像块
    blocks = []

    # 遍历图像并提取块
    for i in range(0, height_b, block_size):
        for j in range(0, width_b, block_size):
            block = data[i:i+block_size, j:j+block_size]
            blocks.append(block)
            
    extracted_secret = np.zeros(secret_len * 8, dtype=np.uint8)
    # 打印块的数量
    print(f"Total number of blocks: {len(blocks)}")
    for idx, block_img in enumerate(blocks):
        block = block_img[:, :, 2]  # 仅使用红色通道
        block = block.astype(np.float32)
        # print('block:', block)
        # 对块进行二维DCT变换
        dct_block = dct(dct(block.T, norm='ortho').T, norm='ortho')
        # print('idx:', idx)
        # print('dct_block[u1, v1]:', dct_block[u1, v1])
        # print('dct_block[u2, v2]:', dct_block[u2, v2])
        if idx is secret_len * 8:
            break  
        if dct_block[u1, v1] > dct_block[u2, v2]:
            extracted_secret[idx] = 1
        else:
            extracted_secret[idx] = 0
    return extracted_secret
    # return np.packbits(extracted_secret).tobytes().decode()


filepath = 'lab.png'
secret_message = input('请输入要嵌入的秘密信息：')
secret_len = len(secret_message)
secret_bits = np.unpackbits(np.frombuffer(secret_message.encode(), dtype=np.uint8))
outpath = embed_secret_message(filepath, secret_message)
extract_secret_bits = extract_secret_message(outpath)
extract_secret = np.packbits(extract_secret_bits).tobytes().decode()
print('\nextract_secret:', extract_secret)

