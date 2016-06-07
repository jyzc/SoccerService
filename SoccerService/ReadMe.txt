========================================================================
    控制台应用程序：SoccerService 项目概述 —— 球探网数据抓取
========================================================================
1、当天比赛线程。
	while (1)
	{
		//1.获取当天比赛列表

		//2.根据ID、fully、status和数据库中的比较

		//2.1 如果ID存在，且fully比数据库中的大，则Update
		//2.2 如果ID不存在，则Insert

	
	}	//end while

2、历史比赛线程。

/////////////////////////////////////////////////////////////////////////////

1、mysql环境变量
MYSQL_HOME=D:\Tools\mysql-5.7.12-winx64
PATH=.;%MYSQL_HOME%\bin;


2、用管理员身份打开cmd
//声明配置文件
mysqld install MySQL --defaults-file="D:\Tools\mysql-5.7.12-winx64\my.ini"
//安装mysql
mysqld -install

//初始化数据库
mysqld  --initialize-insecure
//启动服务
net start mysql
-----------------------------------------
mysql -u root -p

>show databases;
>use mysql;
//修改root默认密码为123456
>ALTER USER 'root'@'localhost' IDENTIFIED BY '123456';
>FLUSH PRIVILEGES;
>QUIT
-----------------------------------------
//设置远程登录
>GRANT ALL PRIVILEGES ON *.* TO 'root'@'%' IDENTIFIED BY '123456' WITH GRANT OPTION;

------------------------------------------
mysqld remove
net start mysql
net stop mysql
mysql -u root -p



/////////////////////////////////////////////////////////////////////////////
耗时的地方有：
1、请求网页数据耗时。
2、读写数据库耗时。
3、导出文件时读写文件耗时。
/////////////////////////////////////////////////////////////////////////////
