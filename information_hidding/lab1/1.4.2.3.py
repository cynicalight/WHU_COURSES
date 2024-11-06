import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
import cv2
from scipy.fftpack import dct, idct
import shutil  # 导入 shutil 模块

from utils import extract_secret_message, embed_secret_message

# 选择两个系数的坐标
u1, v1 = 5, 2
u2, v2 = 4, 3
alpha = [30, 50, 100]
quality = [50, 80, 100]
filepath = 'a.jpg'
secret_message = 'hellozj'
secret_len = len(secret_message)
secret_bits = np.unpackbits(np.frombuffer(secret_message.encode(), dtype=np.uint8))
index = 0
for a in alpha:
    for q in quality:
        outpath = embed_secret_message(filepath, secret_message, a, q)
        # 复制图片到新的路径
        newpath = f'./output1423/stego_{a}_{q}.jpg'
        shutil.copy(outpath, newpath)
        extract_secret_bits = extract_secret_message(outpath, secret_len)
        extract_secret = np.packbits(extract_secret_bits).tobytes().decode()
        print(f'\nalpha: {a}, q: {q}, extract_secret: {extract_secret}')
    index += 1
    print()

