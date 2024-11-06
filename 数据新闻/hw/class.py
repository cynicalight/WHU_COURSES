from io import StringIO
import pandas as pd
import matplotlib.pyplot as plt
import seaborn as sns


# 使用pandas读取数据
data = pd.read_csv("城镇分类.csv", encoding='gbk')

# 将数据转换为适合绘图的格式
data_melted = data.melt(id_vars=["指标"], var_name="年份", value_name="就业人数(万人)")
# id_vars 参数接收一个列名列表，这些列将被保留为标识变量
# var_name 参数指定新变量列的列名
# value_name 参数指定新值的行名

# replace "年" with "" and convert to int
data_melted["年份"] = data_melted["年份"].str.replace("年", "").astype(int)

# 设置Seaborn的主题
sns.set_theme(style="whitegrid")


# 配置中文字体
plt.rcParams['font.sans-serif'] = ['Arial Unicode MS']
plt.rcParams['axes.unicode_minus'] = False  # 解决负号显示问题


# 创建一个大图
plt.figure(figsize=(14, 10))

# 绘制多个折线图，每个行业一条线
sns.lineplot(data=data_melted, x="年份", y="就业人数(万人)", hue="指标", marker="o")

# 添加标题和标签
plt.title('最近10年城镇人员分类就业变化趋势', fontsize=16)
plt.xlabel('年份', fontsize=14)
plt.ylabel('就业人数(万人)', fontsize=14)
# 调整图例位置
plt.legend(title='指标', bbox_to_anchor=(1.05, 1), loc='upper left')

# 显示图表
plt.tight_layout()
# 保存图片到当前目录
plt.savefig('城镇分类就业人数变化趋势图.png')
plt.show()

