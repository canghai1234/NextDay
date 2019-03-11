# NextDay
NextDay 非官方安卓客户端， 使用 Qt  for Android 开发。 **目前还未实现全部功能**

**提示**： 长按（3秒）底部音乐栏，进入设置页面。

#Version 1.1
1. 添加保存当日图片功能
2. 添加保存当日背景图片的功能
3. 允许用户对字体进行一定比例的缩放
4. 添加关于页面

#ToDo（按优先级排序）
1. 读取安卓按键，使部分页面可以响应系统按键
2. 监测系统状态，当 app 挂起时保存程序状态，防止恢复时陷入 frozen 状态
3. 添加日历页面，以允许访问指定日期的信息
4. 添加每日自动更换壁纸功能
5. 添加使用每天音乐进行闹钟唤醒功能


## 安装
下载 apk 文件夹下的 apk 文件，安装即可。点击下载：[NextDay](https://github.com/canghai1234/NextDay/blob/master/apk/NextDay.apk?raw=true)

## 编译
建议使用 Qt5.12 或更高版本进行编译。使用 QtCreator 打开 src 文件夹下的 NextDay.pro 文件，选择相应的编译版本即可。

**注意1**：需将 apikey.h 中的 partner name 与 partner key 替换为自己的 partner name 与 partner key ,如需申请 api key，请[点击链接](https://github.com/NXMIX/nextday-public-api/wiki/%E5%A6%82%E4%BD%95%E7%94%B3%E8%AF%B7)查看申请方法。

**注意2**：因为 build.gradle 配置的缘故，首次进行 Qt For Android 编译需全局翻墙，以从 google 服务器下载数据，否则无法通过编译。
