import pandas as pd
from sklearn.model_selection import train_test_split
from sklearn.svm import SVC
from sklearn.metrics import accuracy_score

# 读取 CSV 文件
data = pd.read_csv("sun.csv")

# 提取特征和目标变量
X = data[['low', 'high', 'airqulity']]
y = data['result']

# 划分训练集和测试集
X_train, X_test, y_train, y_test = train_test_split(
    X, y, test_size=0.2, random_state=42)

# 创建支持向量机模型
svm_model = SVC(kernel='linear')

# 训练模型
svm_model.fit(X_train, y_train)

# 在测试集上进行预测
y_pred = svm_model.predict(X_test)

# 计算准确度
accuracy = accuracy_score(y_test, y_pred)
print(f"模型准确度：{accuracy * 100:.2f}%")
