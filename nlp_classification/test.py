# for data
from scipy.sparse import csr_matrix
import json
import pandas as pd
import numpy as np  # for plotting
import matplotlib.pyplot as plt
import seaborn as sns  # for bag-of-words
from sklearn import feature_extraction, model_selection, naive_bayes, pipeline, manifold, preprocessing  # for explainer
from sklearn import feature_selection
from sklearn.model_selection import train_test_split

from sklearn.metrics import f1_score
from lime import lime_text  # for word embedding

from tensorflow.keras import models, layers, preprocessing as kprocessing
from tensorflow.keras import backend as K  # for bert language model
import transformers
import os
import jieba
import re

print("success: imported")

'''
For english text
Preprocess a string.
:parameter
   :param text: string - name of column containing text
   :param lst_stopwords: list - list of stopwords to remove
   :param flg_stemm: bool - whether stemming is to be applied
   :param flg_lemm: bool - whether lemmitisation is to be applied
:return
   cleaned text
'''


# For chinese text  Preprocess a string.

def preprocess_chinese_text(text, lst_stopwords=None):
    # 清理文本（去除特殊字符）
    text = re.sub(r'[^\w\s]', '', str(text).strip())
    text = re.sub(r'\d', '', str(text).strip())

    # 分词（将字符串转换为词语列表）
    lst_text = jieba.lcut(text)

    # 去除停用词
    if lst_stopwords is not None:
        lst_text = [word for word in lst_text if word not in lst_stopwords]

    # 将处理后的词语列表重新组合成字符串
    text = " ".join(lst_text)

    return text

# transfer the data in file into json file
file_data = []
for class_num in range(1, 9):
    folder_path = "文本分类/实验数据/trainingdataset/class" + str(class_num)
    
    for filename in os.listdir(folder_path):
        file_path = folder_path + "/" + filename
        with open(file_path, mode='r', errors='ignore') as txt_file:
            lines = txt_file.readlines()[1:5]  # Skip the first line
            text = ' '.join(lines)
            text = preprocess_chinese_text(text,'\n')
        file_dict = {
            "foldername": "class" + str(class_num),
            "content": text
        }
        file_data.append(file_dict)
            

# create dtf
dtf = pd.DataFrame(file_data) 

# print 2 random rows
dtf = dtf.rename(columns={"foldername": "class", "content": "text"})
print(dtf.sample(2))

# split dataset
dtf_train, dtf_test = model_selection.train_test_split(dtf, test_size=0.3)  # get target
y_train = dtf_train["class"].values
y_test = dtf_test["class"].values

ngram_range = (1, 2)
vectorizer = feature_extraction.text.TfidfVectorizer(max_features=10000, ngram_range=(1, 2))
corpus = dtf_train["text"]
vectorizer.fit(corpus)
X_train = vectorizer.transform(corpus)
dic_vocabulary = vectorizer.vocabulary_
sns.heatmap(X_train.todense()[:,np.random.randint(0,X_train.shape[1],100)] == 0, vmin=0, vmax=1, cbar=False).set_title('Sparse Matrix Sample')
# plt.show()

# y = dtf_train["class"]
# X_names = vectorizer.get_feature_names_out()
# p_value_limit = 0.95
# dtf_features = pd.DataFrame()
# for cat in np.unique(y):
#     chi2, p = feature_selection.chi2(X_train, y == cat)
#     dtf_features = pd.concat([dtf_features, pd.DataFrame({"feature": X_names, "score": 1-p, "y": cat})], ignore_index=True)
#     dtf_features = dtf_features.sort_values(["y", "score"],ascending=[True, False])
#     dtf_features = dtf_features[dtf_features["score"] >p_value_limit]
#     X_names = dtf_features["feature"].unique().tolist()





# feature selection
p_value_limit = 0.95
dtf_features = pd.DataFrame()

X_names = vectorizer.get_feature_names_out()

for cat in np.unique(y_train):
    chi2, p = feature_selection.chi2(X_train, y_train == cat)
    for i in range(len(X_names)):
        if 1 - p[i] > p_value_limit:
            dtf_features = dtf_features._append({"feature": X_names[i], "score": 1 - p[i], "y": cat}, ignore_index=True)
            #print(dtf_features.columns)
dtf_features = dtf_features.sort_values(["y", "score"], ascending=[True, False])

for cat in np.unique(y_train):
   print("# {}:".format(cat))
   print("  . selected features:",
         len(dtf_features[dtf_features["y"] == cat]))
   print("  . top features:", ",".join(
       dtf_features[dtf_features["y"] == cat]["feature"].values[:10]))
   print(" ")


vectorizer_test = feature_extraction.text.TfidfVectorizer(
    max_features=10000, ngram_range=(1, 2), dtype=np.float64)
vectorizer_test.fit(dtf_test["text"])
X_test = vectorizer_test.transform(dtf_test["text"])


# vectorizer = feature_extraction.text.TfidfVectorizer(vocabulary=X_names)
vectorizer.fit(corpus)
X_train = vectorizer.transform(corpus)
dic_vocabulary = vectorizer.vocabulary_
sns.heatmap(X_train.todense()[:, np.random.randint(0, X_train.shape[1], 100)]
            == 0, vmin=0, vmax=1, cbar=False).set_title('Sparse Matrix Sample')

tfidf = feature_extraction.text.TfidfVectorizer(
    ngram_range=(1, 3), max_features=3000)

clf = naive_bayes.MultinomialNB()

# 将 dtf_train 和 dtf_test 合并为 train_test
train_test = pd.concat([dtf_train, dtf_test], ignore_index=True)

# 对 train_test 中的 "text" 列进行向量化
vectorizer_test.fit(train_test["text"])
X_test = vectorizer_test.transform(dtf_test["text"])

# 使用 train_test_split 函数重新划分训练集和测试集
X_train, X_test, y_train, y_test = train_test_split(
    train_test["text"], train_test["class"], test_size=0.3, random_state=42)

# 在训练集上进行特征提取
X_train = vectorizer_test.transform(X_train)

# 将稀疏矩阵转换为 Compressed Sparse Row (CSR) 格式
X_train = csr_matrix(X_train)

# 在训练集上拟合朴素贝叶斯分类器
clf.fit(X_train[:1000], y_train[:1000])

# 在测试集上进行预测
val_pred = clf.predict(X_train[1000:])
print(f1_score(y_train[1000:], val_pred, average='macro'))





# # 使用训练好的分类器进行预测
# classifier = naive_bayes.MultinomialNB()

# # 建立流水线
# pipeline_model = pipeline.Pipeline(
#     [("vectorizer", vectorizer), ("classifier", classifier)])

# # 在训练集上拟合分类器
# pipeline_model.fit(X_train, y_train)

# # 在测试集上进行预测
# #X_test = vectorizer.transform(dtf_test["text"])
# predicted = pipeline_model.predict(X_test)

# # 输出预测结果
# print(predicted)
