arm平台protobuf库例程代码

===================================================

由gcc-linaro-5.3.1-arm（arm-linux-gnueabi-g++）protobuf库与例程代码。
使用时将libpro.tar.xz文件解压在arm设备内lib文件夹中。

------------------------------

库需求：-lprotobuf -pthread -lcurl -ljansson（由交叉编译工具进行了strip操作以减小体积）。
有libprotobuf.so.30和libprotobuf.so.30-lite两个版本。如需使用lite版本，需要在proto文件开头加上“option optimize_for = LITE_RUNTIME;”。
curl库不用放到设备里，但是编译json2pb.cc文件的时候要用。

------------------------------

文件结构：

libpro.tar.xz:

由gcc-linaro-5.3.1-arm交叉编译生成的protobuf库以及其他运行需要的依赖库。

testjson：

由test_json.o test.pb.o json2pb.o三个.o文件链接生成的arm平台可执行文件，需求test.json文件（需要读取）。

test.json：

用来进行测试的json文件。用来测试json和pb文件的互相转换。

test.pb.o test.pb.cc test.pb.h：

由test.proto生成的proto文件，包含proto和message定义相关内容。

test_json.cc test_json.o：

包含工程主函数的文件。

json2pb.o json2pb.cc json2pb.h：

提供json和pb互相转换，还有读取、写入message信息的功能。

libjson2pb.so：

json2pb.o生成的so库，在本工程中没有用到。

bin2ascii.h：

为json和pb互相转化程序提供的一些数据类型转换功能支持。

Makefile：

自动编译用的。为了方便修改函数内容，本程序不采用生成libjson2pb.so库，而是用test_json.o test.pb.o json2pb.o三个.o文件链接生成testjson。

protoc：

该文件不交叉编译，使用linux下的gcc默认编译。用于在linux环境下由proto文件生成对应的.cc和.h文件。（具体可以参考reference中关于交叉编译那一条和word文档）

Protobuf.docx：

一些环境配置、编译时候的备忘文档。

------------------------------

功能介绍：

test_json.cc：

json2pb(msg, buf, size)：

顾名思义，把json文件转换为proto。msg为消息，buf和size的生成方法参考原文件。

msg1.set_str("hello"); 

向message中写内容，其他写入内容的方法见reference第二条。

int writemsg(const google::protobuf::Message &msg,std::string path)：

将msg内容写入文件（内容需要预先设定）。msg为目标信息，path为写入文件的目标路径。

int readmsg(const google::protobuf::Message &msg,std::string path)：

从指定路径文件读出目标信息内容到msg，并把内容打印出来。

-----------------------------

website at:

https://blog.csdn.net/oZuoZuo789

Reference:

https://blog.csdn.net/orange_littlegirl/article/details/98478537

https://herbort.blog.csdn.net/article/details/115474254 （对消息内容赋值的其他方法）

https://github.com/shramov/json2pb

https://blog.csdn.net/qq_22660775/article/details/89007294

https://blog.csdn.net/qq_24130227/article/details/122588217（关于交叉编译）
