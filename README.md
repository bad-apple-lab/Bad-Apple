## Bad Apple!!

视频转字符画工具. ~~**SSH** 看番指日可待.~~

![GIF](./play.gif)

预加载版最高支持到 **1080p30Hz**, 瓶颈是 **IO**.

实时版最高支持到 **720p30Hz**, 瓶颈是 **编码解码速度**.

#### 环境依赖

预处理(字体):
CPP 环境.
Python3 环境.
Pillow 包 (安装方式: `pip install Pillow`).

编译:
CPP 环境.

运行:
命令行工具: `awk` `grep` `ffmpeg` (包括 `ffmpeg` `ffprobe` `ffplay`).


#### 编译运行

Windows
```sh
clang++ demo.cpp -o demo.exe -w -g -O2 -static-libgcc --target=x86_64-w64-mingw
./demo
```

Linux
```sh
g++ demo.cpp -o demo
./demo
```

#### To do

命令行工具

