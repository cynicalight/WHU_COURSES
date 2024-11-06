import numpy as np
import matplotlib.pyplot as plt
import cv2
from PIL import Image
class LSB(object):
    '''
    最低位替换隐写，将最题为替换为想要隐写的信息。采用的是随机替换的方法
    '''
    def __init__(self, message_size, img_shape, key=None):
        '''
        可以选择是采用随机替换还是顺序替换
        
        :param message_size: 最长隐写信息
        :param image_shape: 图像形状
        :param key: 随机种子, if None 采用顺序替换
        '''
        self.img_shape = img_shape
        self.message_size = message_size
        if key is not None:
            self.seed = key %  4294967295 # 2^32 - 1
            self.random_map = self.generate_random_map()
        else:
            ## 如果没有设置种子，则采用顺序替换隐写   
            self.random_map = np.ones(self.img_shape[0]*self.img_shape[1]).reshape(self.img_shape[0], self.img_shape[1])

        
    def generate_random_map(self):
        np.random.seed(self.seed)
        random_map = np.zeros(self.img_shape[0]*self.img_shape[1])
        random_map[:self.message_size] = 1
        np.random.shuffle(random_map)
        random_map = random_map.reshape((self.img_shape[0], self.img_shape[1]))
        return random_map
    def encode(self, img: np.array, message: bytes, channel, LSBR=False):
        '''
        LSBR信息嵌入
        
        :param img: 需要嵌入的图像，numpy数组
        :param message: 需要嵌入的信息,二进制数据
        :param channel: 信息嵌入的通道
        :param LSBR: lsb matching嵌入 默认不使用
        
        '''         
        message +=  b'\x00'
        message = "".join([format(x, '08b') for x in message])
        message_size = len(message)
        if message_size > self.message_size:
            raise ValueError("Message too long")
        one_positions = np.argwhere(self.random_map)
        message_index = 0
        for pos in one_positions:
            x, y = pos
            if message_index < message_size:
                if LSBR == False:
                    img[x, y, channel] = img[x, y, channel] & 254 | int(message[message_index])
                else:
                    # Matching
                    if img[x, y, channel] & 1 != int(message[message_index]):
                        img[x, y, channel] += np.random.choice([-1, 1])
                message_index += 1
            else:
                break
        return img
    def decode(self, img, channel):
        '''
        LSBR信息提取
        
        :param img: 需要提取信息的图像，numpy数组
        :param channel: 从哪个通道提取出信息
        '''
        one_positions = np.argwhere(self.random_map == 1)
        message = ""
        for i, pos in enumerate(one_positions):
            x, y = pos
            message += str(img[x, y, channel] & 1)
        message = [message[i:i+8] for i in range(0, len(message), 8)]
        message = [int(x, 2) for x in message]
        message = bytes(message)
        end_idx = message.find(b'\x00')
        message = message[:end_idx]
        return message
    
    
class DCT_hidden(object):
    '''
    DCT域隐写，将信息嵌入到dct域中的低信息量区域。
    '''
    def __init__(self, a):
        self.a = a
        self.b1 = (5, 2)
        self.b2 = (4, 3)
        self.message_idx = 0
        self.message_size = 0
        
    def blkproc(self, image , block_size, fun, *args, **kwargs):
        # 获取图像的尺寸
        width, height = image.shape
        # 初始化结果数组
        result_array = np.zeros_like(image)
        # 遍历图像并应用函数到每个块
        for i in range(0, width, block_size[0]):
            for j in range(0, height, block_size[1]):
                # 提取块
                block = image[j:j+block_size[1], i:i+block_size[0]]
                # 应用函数
                processed_block = fun(block, *args, **kwargs)
                # 将处理后的块放回结果数组
                result_array[j:j+block_size[1], i:i+block_size[0]] = processed_block

        return result_array


    def encode(self, img, message, a):
        self.a = a
        message = bytes(message) + b'\x00'
        message = "".join([format(x, '08b') for x in message])
        self.message_size = len(message)
        self.message_idx = 0
        img = self.blkproc(img, (8, 8), cv2.dct)
        def hidden_block(block, message):
            if (self.message_idx >= self.message_size):
                return block
            b1 = block[self.b1[0], self.b1[1]]
            b2 = block[self.b2[0], self.b2[1]]
            gap = abs(b1 - b2)
            b1 = max(b1, b2)
            b2 = min(b1, b2)
            # 添加阈值，增加鲁棒性
            if(gap < self.a):
                b1 = b1 + (self.a - gap) / 2
                b2 = b2 - (self.a - gap) / 2
            if(message[self.message_idx] == '1'):
                block[self.b1[0], self.b1[1]] = b1
                block[self.b2[0], self.b2[1]] = b2
            else :
                block[self.b1[0], self.b1[1]] = b2
                block[self.b2[0], self.b2[1]] = b1
            self.message_idx += 1
            return block
        img = self.blkproc(img, (8, 8), hidden_block, message)
        self.message_size = 0
        self.message_idx = 0
        img = self.blkproc(img, (8, 8), cv2.idct)
        return img
    
    def decode(self,img):
        data = img.copy()
        data = self.blkproc(data, (8, 8), cv2.dct)
        message = []
        def get_block(block, message):
            b1 = block[self.b1[0], self.b1[1]]
            b2 = block[self.b2[0], self.b2[1]]
            if(b1 > b2):
                message.append('1')
            else:
                message.append('0')
            return block
        img = self.blkproc(data, (8, 8), get_block, message)
        message = "".join(message)
        message = [message[i:i+8] for i in range(0, len(message), 8)]
        message = [int(x, 2) for x in message]
        message = bytes(message)
        end = message.find(b'\x00')
        message = message[:end]
        return message 
