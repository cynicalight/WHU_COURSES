import numpy as np
from scipy.stats import chi2
import cv2
import matplotlib.pyplot as plt
plt.rcParams['font.sans-serif'] = ['Arial Unicode MS']


def calculate_chi_square(image, block_size=32):
    height, width = image.shape
    chi_square_values = []
    # 遍历图像的每个块
    for i in range(0, height - block_size + 1, block_size):
        for j in range(0, width - block_size + 1, block_size):
            block = image[i:i+block_size, j:j+block_size]
            histogram = np.histogram(block, bins=256, range=(0, 256))[0] # 计算直方图

            chi_square = 0
            # 遍历直方图的每个bin
            for k in range(1, 128):
                h_2k_minus_1 = histogram[2*k - 1]
                h_2k = histogram[2*k]
                if h_2k_minus_1 + h_2k > 0:
                    chi_square += (h_2k_minus_1 - h_2k)**2 / (2 * (h_2k_minus_1 + h_2k))

            chi_square_values.append(chi_square)

    return chi_square_values


def chi_square_analysis(image, block_size=32):
    if image is None:
        return None
    
    chi_square_values = calculate_chi_square(image, block_size)
 
    # 计算 p 值
    degrees_of_freedom = 127  # 根据公式，自由度为127
    p_values = 1 - chi2.cdf(chi_square_values, degrees_of_freedom)


    avg_p_value = np.mean(p_values)
    avg_chi_square = np.mean(chi_square_values)

    print(f"  平均卡方值: {avg_chi_square:.2f}")
    print(f"  平均 p 值: {avg_p_value:.6f}")

    return avg_p_value


def analyze_images(method):
    embedding_rates = [0, 0.25, 0.5, 0.75]  # 添加0表示原图
    # 修改图片路径列表，添加原图
    image_paths = [f'attach/a.png'] + [f'attach/{method}{i+1}.png' for i in range(3)]
    
    p_values = []
    
    for path in image_paths:
        print(f"分析图像: {path}")
        image = cv2.imread(path, cv2.IMREAD_GRAYSCALE)
        if image is None:
            print(f"无法读取图像: {path}")
            continue
        
        p_value = chi_square_analysis(image)
        p_values.append(p_value)
    
    return embedding_rates, p_values


def plot_results(lsb_results, lsbm_results):
    plt.figure(figsize=(12, 6))
    plt.plot(lsb_results[0], lsb_results[1], marker='o', label='LSB')
    plt.plot(lsbm_results[0], lsbm_results[1], marker='s', label='LSBM')
    
    plt.xlabel('嵌入率')
    plt.ylabel('平均 p 值')
    plt.title('LSB 和 LSBM 嵌入率与平均 p 值的关系')
    plt.legend()
    plt.grid(True)
    plt.savefig('attach/lsb_lsbm_p_values.png')
    plt.close()


# 主程序
print("\n原图分析:")
image = cv2.imread('attach/origin.png', cv2.IMREAD_GRAYSCALE)
if image is not None:
    print("分析图像: attach/origin.png")
    chi_square_analysis(image)

lsb_results = analyze_images('lsb')
lsbm_results = analyze_images('lsbm')

print("\nLSB 结果:")
for rate, p_value in zip(lsb_results[0], lsb_results[1]):
    print(f"嵌入率 {rate}: 平均 p 值 = {p_value:.6f}")

print("\nLSBM 结果:")
for rate, p_value in zip(lsbm_results[0], lsbm_results[1]):
    print(f"嵌入率 {rate}: 平均 p 值 = {p_value:.6f}")

plot_results(lsb_results, lsbm_results)
