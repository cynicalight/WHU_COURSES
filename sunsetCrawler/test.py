import pandas as pd
import numpy as np

# 读取原始数据
data = pd.read_csv("newData.csv")

# 生成随机数据
np.random.seed(42)  # 以确保生成的随机数据可复现
random_data = {
    "low": np.random.randint(10, 25, size=len(data)),
    "high": np.random.randint(20, 30, size=len(data)),
    "airqulity": np.random.choice([0, 1, 2], size=len(data))
}

# 将随机数据加入原始数据
new_data = pd.concat([data, pd.DataFrame(random_data)], axis=1)

# 将 "result" 列移到最后
new_data = new_data[["date", "low", "high", "airqulity", "result"]]

# 存储到新的 CSV 文件
new_data.to_csv("new_data_with_random_columns.csv", index=False)
