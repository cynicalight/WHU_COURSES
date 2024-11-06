#! /usr/bin/env python

from urllib.request import urlopen, Request
from urllib.request import HTTPError
from bs4 import BeautifulSoup
import re
from urllib.parse import quote
import random
import time
import csv
from datetime import datetime

# 收集到的常用Header
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

n=0

for i in range(0,15):
    t = 1
    time.sleep(t)       
    pages = i * 10
    headers = {'user-agent': 'my-app/0.0.1'}
    # url = "http://www.baidu.com/s?wd=%E6%AD%A6%E6%B1%89%E6%99%9A%E9%9C%9E&pn=" + str(pages
    url = "http://www.baidu.com/s?wd=%E6%AD%A6%E6%B1%89%E6%99%9A%E9%9C%9E&pn=" + str(pages)
    response = Request(url)
    response.add_header('User-Agent', random.choice(my_headers))
    html = urlopen(response)
    # print("httpcode:" + str(html.getcode()))
    soup = BeautifulSoup(html, features="lxml")
    print("连接成功")
    time.sleep(t)
    
    htmlraw = html.read()
    htmlraw = htmlraw.decode('utf-8')		#根据网页的编码方式进行解码
    print(htmlraw)
    # "span", {"class":"c-color-gray2"}
    for link in soup.findAll("span", {"class":"c-color-gray2"}):
        n=n+1
        print(n,end='')
        print("-----------------")
        print(link.get_text())
        date_string = link.get_text()
        date_match = re.search(r"\d+年\d+月\d+日", date_string)
        if date_match:
            date_string = date_match.group(0)

        # 解析日期字符串
            date = datetime.strptime(date_string, "%Y年%m月%d日")
            formatted_date = date.strftime("%Y%m%d")
        with open('sun.csv', 'a') as csvFile:
            writer = csv.writer(csvFile)
            writer.writerow([formatted_date, '1'])
        
        # print(link.children[0]+"\n")
        
        
