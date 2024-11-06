# check the image in attach folder
import cv2
import numpy as np
import os


def get_lsb(image):
    """提取图像的最低有效位"""
    return image & 1


def compare_lsb(image1, image2):
    """比较两个图像的最低有效位"""
    lsb1 = get_lsb(image1)
    lsb2 = get_lsb(image2)
    return np.array_equal(lsb1, lsb2)


def check_lsb_images(folder_path):
    """检查指定文件夹中的 LSB1、LSB2、LSB3 图像是否相同"""
    lsb_images = ['lsb1.png', 'LSB2.png', 'LSB3.png']
    images = []

    for img_name in lsb_images:
        img_path = os.path.join(folder_path, img_name)
        if not os.path.exists(img_path):
            print(f"错误：找不到文件 {img_path}")
            return

        img = cv2.imread(img_path, cv2.IMREAD_GRAYSCALE)
        if img is None:
            print(f"错误：无法读取图像 {img_path}")
            return

        images.append(img)

    # 比较 LSB
    lsb1_vs_lsb2 = compare_lsb(images[0], images[1])
    lsb1_vs_lsb3 = compare_lsb(images[0], images[2])
    lsb2_vs_lsb3 = compare_lsb(images[1], images[2])

    # 输出结果
    print("LSB 比较结果：")
    print(f"LSB1 vs LSB2: {'相同' if lsb1_vs_lsb2 else '不同'}")
    print(f"LSB1 vs LSB3: {'相同' if lsb1_vs_lsb3 else '不同'}")
    print(f"LSB2 vs LSB3: {'相同' if lsb2_vs_lsb3 else '不同'}")

    if lsb1_vs_lsb2 and lsb1_vs_lsb3 and lsb2_vs_lsb3:
        print("结论：所有 LSB 图像都是相同的。")
    else:
        print("结论：LSB 图像不完全相同。")


# 使用程序
folder_path = 'attach'  # 假设图片在 'attach' 文件夹中
check_lsb_images(folder_path)
