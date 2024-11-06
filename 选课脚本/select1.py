from selenium import webdriver
from time import sleep
from selenium.webdriver.common.by import By
import time
from selenium.common.exceptions import NoSuchElementException

username = "2022302181314"
password = "111111"


def hour_task():
    driver = webdriver.Chrome()
    urlTest = "https://www.google.com/search?q=nihao"
    urlSelect = "https://jwgl.whu.edu.cn/xsxk/zzxkyzb_cxZzxkYzbIndex.html?gnmkdm=N253512&layout=default"
    driver.get(urlSelect)

    # cookie route=63e9b4695d67c8e6bf1495e67e5edb50; iPlanetDirectoryPro=Cc3XekR97iwZA2qJbjoQPR
    cookies = [
        #      {"name": "route", "value":"63e9b4695d67c8e6bf1495e67e5edb50"},
        {"name": "iPlanetDirectoryPro", "value": "Cc3XekR97iwZA2qJbjoQPR"}]

    for cookie in cookies:
        driver.add_cookie(cookie)
    sleep(1)

    buttonTyfs = driver.find_element("id", "tysfyzdl")
    buttonTyfs.click()
    sleep(1)

    user = driver.find_element("id", "username")
    user.send_keys(username)
    passw = driver.find_element("id", "password")
    passw.send_keys(password)

    buttonLogin = driver.find_element(By.CLASS_NAME, "auth_login_btn")
    buttonLogin.click()
    sleep(2)

    try:
        buttonQuery = driver.find_element("name", "query")
        buttonQuery.click()
        sleep(3)

        spanSykj = driver.find_element("id", "kcmc_3350530011033")
        spanSykj2 = spanSykj.find_element("xpath", "..")  # 找父元素
        spanSykj2.click()
        sleep(3)

        buttonSelect = driver.find_element(
            "id", "btn-xk-098B3D04C54C67DDE0630207010A3BE3")
        buttonSelect.click()
        sleep(3)

        buttonConfirm = driver.find_element("id", "btn_confirm")
        buttonConfirm.click()
        sleep(3)
        
    except NoSuchElementException:
        print("Element not found. Skipping task...")

    driver.quit()

hour_task()


# while True:
#     # 获取当前系统时间
#     current_time = time.localtime()

#     # 如果当前分钟为50，则执行操作
#     if current_time.tm_min == 50:
#         for i in range(1, 3):
#             hour_task()
#             zj = zj + 1
#             print("----------")
#             print(zj)
#             print(str(current_time.tm_hour) + ":" + str(current_time.tm_min))
            

#     # 等待1分钟，避免过快地消耗CPU资源
#     sleep(3)
#     print(str(current_time.tm_hour) + ":" + str(current_time.tm_min))

