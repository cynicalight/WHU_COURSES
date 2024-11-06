import smtplib
from email.mime.text import MIMEText
from email.header import Header
import ssl


# 第三方 SMTP 服务
mail_host = "smtp.qq.com"  # 设置服务器
mail_user = "391900788@qq.com"  # 用户名
mail_pass = "qlsxkylknpdhbibe"  # 口令

sender = '391900788@qq.com'
receivers = ['391900788@qq.com']  # 接收邮件，可设置为你的QQ邮箱或者其他邮箱

message = MIMEText('Python 邮件发送测试...', 'plain', 'utf-8')
message['From'] = Header("391900788@qq.com")
message['To'] = Header("测试", 'utf-8')

subject = 'Python SMTP 邮件测试'
message['Subject'] = Header(subject, 'utf-8')

try:
    smtpObj = smtplib.SMTP_SSL(mail_host, timeout=30)  # 使用 SSL 连接到 QQ SMTP 服务器
    smtpObj.connect(mail_host, 465)
    smtpObj.login(mail_user, mail_pass)
    smtpObj.sendmail(sender, receivers, message.as_string())
    print("邮件发送成功")
except smtplib.SMTPException as e:
    print("Error: 无法发送邮件:", e)

# qq

# 在第三方客户端/服务怎么设置
# 登录时，请在第三方客户端的密码输入框里面填入授权码进行验证。（不是填入QQ的密码）

# IMAP/SMTP 设置方法
# 用户名/帐户： 你的QQ邮箱完整的地址

# 密码： 生成的授权码

# 电子邮件地址： 你的QQ邮箱的完整邮件地址

# 接收邮件服务器： imap.qq.com，使用SSL，端口号993

# 发送邮件服务器： smtp.qq.com，使用SSL，端口号465或587
