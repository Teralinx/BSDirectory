# Use an official Debian runtime as a parent image
FROM debian

# 替换默认源为阿里云的镜像源
RUN touch /etc/apt/sources.list
RUN sed -i 's|http://deb.debian.org/debian|http://mirrors.aliyun.com/debian|g' /etc/apt/sources.list && \
   sed -i 's|http://security.debian.org/debian-security|http://mirrors.aliyun.com/debian-security|g' /etc/apt/sources.list

# 更新软件包列表并安装OpenSSH服务器
RUN apt-get update && apt-get install -y openssh-server

RUN apt-get install -y cmake

RUN apt-get install -y g++

# 创建运行时目录
RUN rm -rf /var/run/sshd

RUN mkdir /var/run/sshd

# 设置root用户密码
RUN echo 'root:123456' | chpasswd

# 配置SSH以允许root登录
RUN sed -i 's/#PermitRootLogin prohibit-password/PermitRootLogin yes/' /etc/ssh/sshd_config


# Expose the SSH port
EXPOSE 22

# Start the SSH service
CMD ["/usr/sbin/sshd", "-D"]