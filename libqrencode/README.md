arm平台libqrencode二维码生成库及其例程代码

===================================================

由gcc-linaro-5.3.1-arm（arm-linux-gnueabi-g++）交叉编译生成的二维码的库与例程代码。
使用时将libq4.tgz文件（so库）在arm设备内解压缩，若在PC端解压缩会出现so库软连接断开的问题。

------------------------------

文件结构：

libq4.tgz:

由gcc-linaro-5.3.1-arm交叉编译生成的libqrencode库，使用时将压缩包在设备lib路径下解压缩。

QRGenerator:

由同名.c文件编译生成的可在设备测试运行的二维码生成程序。

QRGenerator.c:

基于libqrencode的二维码生成程序，有生成指定内容、指定大小、指定颜色的二维码的功能。

info.bmp:

QRGenerator文件在设备中运行产生的示例二维码图片。

README.md:

即本说明文档。

------------------------------

封装函数介绍：

void QRGenerator::generate(string& text, string& bmpSavedPath,int OUT_FILE_PIXEL_PRESCALER,int VERSION,QRecLevel LEVEL)

string& text:

生成二维码的信息内容。

string& bmpSavedPath:

生成二维码的文件路径与文件名，默认为当前程序根目录下info.bmp文件。

int OUT_FILE_PIXEL_PRESCALER:

每一个维度占的像素的个数，即二维码放大比例，默认值为8，即二维码图片放大为原来的八倍。

int VERSION:

二维码一共有40个尺寸。官方叫版本Version。Version 1是21 x 21的矩阵，Version 2是 25 x 25的矩阵，Version 3是29的尺寸，每增加一个version，就会增加4的尺寸，公式是：(V-1)*4 + 21（V是版本号） 最高Version 40，(40-1)*4+21 = 177，所以最高是177 x 177 的正方形。程序中默认值为0（自适应）。

如果想更改二维码颜色，搜索PIXEL_COLOR更改GRB值。

QRecLevel LEVEL:

二维码中有四种级别的纠错，这就是为什么二维码有残缺还能扫出来，也就是为什么有人在二维码的中心位置加入图标。
二维码有4种纠错等级，可恢复的码字比例为：

QR_LEVEL_L //7%的字码可被修正
QR_LEVEL_M //15%的字码可被修正
QR_LEVEL_Q //25%的字码可被修正
QR_LEVEL_H //30%的字码可被修正

程序默认为 QR_LEVEL_H。

-----------------------------

website at:

https://blog.csdn.net/oZuoZuo789


Reference:

https://blog.csdn.net/jameskun77/article/details/53518113

https://coolshell.cn/articles/10590.html

https://fukuchi.org/works/qrencode/manual/
