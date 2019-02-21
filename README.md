# NextDay
NextDay 非官方安卓客户端， 使用 Qt  for Android 开发

## 安装
下载 apk 文件夹下的 apk 文件，安装即可。点击下载：[NextDay](https://github.com/canghai1234/NextDay/blob/master/apk/NextDay.apk?raw=true)

## 编译
建议使用 Qt5.12 或更高版本进行编译。使用 QtCreator 打开 src 文件夹下的 NextDay.pro 文件，选择相应的编译版本即可。

**注意1**：需将 apikey.h 中的 partner name 与 partner key 替换为自己的 partner name 与 partner key ,如需申请 api key，请[点击链接](https://github.com/NXMIX/nextday-public-api/wiki/%E5%A6%82%E4%BD%95%E7%94%B3%E8%AF%B7)查看申请方法。

**注意2**：因为 build.gradle 配置的缘故，首次进行 Qt For Android 需进行全局翻墙，从 google 服务器下载数据，否则无法通过编译。