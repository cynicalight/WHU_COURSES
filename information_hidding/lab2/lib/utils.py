# 计算彩色图的直方图
import cv2
import matplotlib as plt

def calchist_for_rgb(img):
    #histb = cv2.calcHist([img], [0], None, [256], [0, 255])
    #histg = cv2.calcHist([img], [1], None, [256], [0, 255])
    histr = cv2.calcHist([img], [0], None, [256], [0, 255])
    
    plt.plot(histr, color='blue', marker='o', linestyle='-')
    plt.xlim([50, 100])  # 设置X轴范围
    plt.ylim([0, 5000]) # 设置Y轴范围
    plt.xlabel('像素值')
    plt.ylabel('像素数量')

def int2byte(num) -> bytes:
    '''
    将int值转换为对应的bytes值例如将 11 转换为 b'\x0b'
    
    :param num: int值
    :return: bytes值
    '''
    return bytes.fromhex(hex(num)[2:].zfill(2))