import pandas as pd
import requests
from bs4 import BeautifulSoup
import time
import re
from fake_useragent import UserAgent
import random

my_headers = [
    "Mozilla/5.0 (Windows NT 6.3; WOW64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/39.0.2171.95 Safari/537.36",
    "Mozilla/5.0 (Macintosh; Intel Mac OS X 10_9_2) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/35.0.1916.153 Safari/537.36",
    "Mozilla/5.0 (Windows NT 6.1; WOW64; rv:30.0) Gecko/20100101 Firefox/30.0",
    "Mozilla/5.0 (Macintosh; Intel Mac OS X 10_9_2) AppleWebKit/537.75.14 (KHTML, like Gecko) Version/7.0.3 Safari/537.75.14",
    "Mozilla/5.0 (compatible; MSIE 10.0; Windows NT 6.2; Win64; x64; Trident/6.0)",
    'Mozilla/5.0 (Windows; U; Windows NT 5.1; it; rv:1.8.1.11) Gecko/20071127 Firefox/2.0.0.11',
    'Opera/9.25 (Windows NT 5.1; U; en)',
    'Mozilla/4.0 (compatible; MSIE 6.0; Windows NT 5.1; SV1; .NET CLR 1.1.4322; .NET CLR 2.0.50727)',
    'Mozilla/5.0 (compatible; Konqueror/3.5; Linux) KHTML/3.5.5 (like Gecko) (Kubuntu)',
    'Mozilla/5.0 (X11; U; Linux i686; en-US; rv:1.8.0.12) Gecko/20070731 Ubuntu/dapper-security Firefox/1.5.0.12',
    'Lynx/2.8.5rel.1 libwww-FM/2.14 SSL-MM/1.4.1 GNUTLS/1.2.9',
    "Mozilla/5.0 (X11; Linux i686) AppleWebKit/535.7 (KHTML, like Gecko) Ubuntu/11.04 Chromium/16.0.912.77 Chrome/16.0.912.77 Safari/535.7",
    "Mozilla/5.0 (X11; Ubuntu; Linux i686; rv:10.0) Gecko/20100101 Firefox/10.0 "
]

# 清洗一个日期列
sun = pd.read_csv("sun.csv")
date_column = sun.loc[:, "date"]
cleaned_dates = date_column.str.strip()
date_format = '%Y年%m月%d日'
converted_dates = pd.to_datetime(
    cleaned_dates, format=date_format).dt.strftime('%Y%m%d')
converted_dates = converted_dates.sort_values()
converted_dates = converted_dates.reset_index(drop=True)

# 截取2023年的日期
newData = pd.DataFrame()
newData["date"] = converted_dates[21:].reset_index(drop=True)

# 删除重复日期
newData["date"] = newData["date"].drop_duplicates()
newData = newData.dropna().reset_index(drop=True)


# 生成2023年五月到十月的日期范围
date_range = pd.date_range(start="2023-05-01", end="2023-10-31", freq="D")
# 将日期范围转换为字符串格式
additional_dates = date_range.strftime("%Y%m%d").tolist()

# 将额外的日期添加到newData中
additional_data = pd.DataFrame({"date": additional_dates})
newData = pd.concat([newData, additional_data], ignore_index=True)

# 删除重复日期
newData["date"] = newData["date"].drop_duplicates()
newData = newData.dropna().reset_index(drop=True)

# 设置结果(有无晚霞)
newData['result'] = pd.Series([1] * 15 + [0] * (len(newData) - 15))

# 存储到新的 CSV 文件
newData.to_csv("newData.csv", index=False)


# 设置显示
pd.set_option('display.max_rows', None)
# print(newData)

# 创建需要采集的数据列
lowTem = pd.Series()
highTem = pd.Series()


# 设置代理
# proxyUrl = "http://127.0.0.1:5010/get/"

# response = requests.get(proxyUrl)
# print("proxywebsite status:" + str(response.status_code))


# def get_proxy():
#     return requests.get(proxyUrl).json()


url1 = "https://lishi.tianqi.com/wuhan/"


for date in reversed(newData["date"]):
    # set proxy
    # proxy = get_proxy().get("proxy")
    # print(proxy)
    # set agent
    user_agent = UserAgent()
    headers = {
        'User-Agent': user_agent.random
    }

    response = requests.get(url1 + date + ".html", headers=headers)
    time.sleep(0.1)
    count = 0
    if(response.status_code == 200):
    # while (response.status_code != 200):

    #     if (count > 3):
    #         count = 0
    #         break
    #     print(f"{date}-请求失败: {response.status_code}")
    #     proxy = get_proxy().get("proxy")
    #     print(proxy)
    #     user_agent = UserAgent()
    #     headers = {
    #         'User-Agent': user_agent.random
    #     }
    #     response = requests.get(
    #         url1 + date + ".html", headers=headers, proxies={"http": "http://{}".format(proxy)})
    #     time.sleep(0.2)
    #     count = count + 1
        print(date + "---success!")
    else:
        print(f"responseerror:{response.status_code}")

#     html = response.text
#     # print(date)

#     soup = BeautifulSoup(html, 'html.parser')
#     low = soup.find("div", {"class": "hisdailytemp"}).find("span", {"class": "tred"}).text
#     low = re.sub(r'\D', '', low) # 正则筛选数字
#     print(low)


#     lowTem = pd.concat([lowTem, pd.Series([low])])
