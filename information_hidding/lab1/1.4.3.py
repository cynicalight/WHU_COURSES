import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
import cv2
from scipy.fftpack import dct, idct
import shutil
import os  
import seaborn as sns

from utils import extract_secret_message, embed_secret_message

# 选择两个系数的坐标
u1, v1 = 5, 2
u2, v2 = 4, 3
alpha = range(30, 91, 10)
quality = range(50, 81, 5)
filepath = 'a.jpg'
secret_message = 'abcdefgh'
secret_len = len(secret_message)
secret_bits = np.unpackbits(np.frombuffer(
    secret_message.encode(), dtype=np.uint8))
index = 0
# 创建输出文件夹
output_dir = './output143'
os.makedirs(output_dir, exist_ok=True)
# 创建一个 DataFrame 来存储结果
results = pd.DataFrame(index=alpha, columns=quality)
for a in alpha:
    for q in quality:
        outpath = embed_secret_message(filepath, secret_message, a, q)
        newpath = f'./output143/stego_{a}_{q}.jpg'
        shutil.copy(outpath, newpath)
        extract_secret_bits = extract_secret_message(outpath, secret_len)
        # 比较提取的bits和原始的bits
        num_different_bits = np.sum(secret_bits != extract_secret_bits)
        error_rate = num_different_bits / len(secret_bits)
        results.at[a, q] = error_rate

        print(f'\nalpha: {a}, q: {q}: \nsecret__bits: {secret_bits}, \nextract_bits: {extract_secret_bits}')
        print(f'num_different_bits: {num_different_bits}')
        print(f'error_rate: {error_rate}')
    index += 1
    print()

csv_path = f'{output_dir}/results.csv'
results.to_csv(csv_path)
print(f'Results saved to {csv_path}')
df = pd.read_csv(csv_path, index_col=0)
# 设置绘图风格
sns.set_theme(style="whitegrid")
# 创建一个热图
plt.figure(figsize=(10, 8))
heatmap = sns.heatmap(df, annot=True, cmap="Reds",
                      cbar_kws={'label': 'Error Rate'})

plt.title('Error Rate Heatmap')
plt.xlabel('Quality')
plt.ylabel('Alpha')
# save
plt.savefig(f'{output_dir}/heatmap.png')
if input('Do you want to plot the heatmap? (y/n): ') != 'y':
    exit(0)
plt.show()


