arm平台tar压缩工具及其函数封装

===================================================

由gcc-linaro-5.3.1-arm（arm-linux-gnueabi-g++）交叉编译生成的libtar压缩工具库及其函数封装例程代码。
使用时将libtar.so放入lib系统文件夹，将测试文件与可执行文件放入arm设备内同一路径下，运行tartest即可测试工具。

------------------------------

文件结构：

libtar.so：

由gcc-linaro-5.3.1-arm交叉编译生成的tar压缩/解压缩工具库。

tartest.cpp：

输入源文件和目标路径，压缩方式和压缩参数，实现对源文件进行tar压缩/解压缩的功能（例程代码中为压缩生成a.tar.gz）。

tartest：

由同名.cpp文件编译生成的可在设备测试运行的tar测试程序。

testjson：

被压缩的测试文件。

README.md:

本说明文档。

------------------------------

封装函数介绍：

int tarfile::tarzip(char* func,char* parm,char* input, char* output)

input为输出源文件地址，output为输出目标文件的地址，parm为功能参数，默认为-czvf（打包命令，使用-zcvf进行GNU zip压缩），func默认为tar。

-----------------------------

website at:

https://blog.csdn.net/oZuoZuo789


Reference:

http://www.gnu.org/software/tar/manual/

https://www.cnblogs.com/lbg-database/p/10109965.html （关于打包与压缩）

https://www.cnblogs.com/Pillar/p/4206452.html

https://www.cnblogs.com/sui776265233/p/10185402.html (tar命令详解)

-----------------------------

命令行备忘：

配置：./configure --host=arm-linux-gnueabi --prefix=${pwd}/install CC=/usr/local/external-toolchain/gcc-linaro-5.3.1-arm/bin/arm-linux-gnueabi-gcc CXX=/usr/local/external-toolchain/gcc-linaro-5.3.1-arm/bin/arm-linux-gnueabi-g++ CCLD=/usr/local/external-toolchain/gcc-linaro-5.3.1-arm/bin/arm-linux-gnueabi-ld RANLIB=/usr/local/external-toolchain/gcc-linaro-5.3.1-arm/bin/arm-linux-gnueabi-ranlib AR=/usr/local/external-toolchain/gcc-linaro-5.3.1-arm/bin/arm-linux-gnueabi-ar CFLAGS=-fPIC

编译：make

编译出so文件：gcc -shared -o tar.so *.o ../lib/*.o ../lib/libtar.a ../gnu/*.a

检查所需文件：ldd -r tar.so

可执行：g++ -g -o tartest3 tartest3.cpp -ldl -std=c++11 

