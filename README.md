## Bad Apple!!

视频转字符画工具. ~~**SSH** 看番指日可待.~~

![GIF](./play.gif)

预加载版最高支持到 **1080p30Hz**, 瓶颈是 **IO**.

实时版最高支持到 **720p30Hz**, 瓶颈是 **编码解码速度**.

### Environmental Dependence

#### Preprocessing (fonts)
CPP and Python3.
Python module Pillow (`pip install Pillow`).

#### Compile
Usually, as long as you can compile the CPP.

#### Run
`awk` `grep` `ffmpeg` (Include `ffmpeg` `ffprobe` `ffplay`).

##### Windows
[GnuWin](http://gnuwin32.sourceforge.net/)
[FFmpeg](https://github.com/BtbN/FFmpeg-Builds/releases/tag/latest)

##### Ubuntu / Debian
```sh
sudo apt update
sudo apt install ffmpeg
```

##### CentOS / RedHat
```sh
sudo yum update
sudo yum install ffmpeg
```

##### Arch Linux
```sh
sudo pacman -Syu ffmpeg
```

#### 编译运行

##### Windows
```sh
clang++ 'badapple.cpp' -lpthread -o 'badapple.exe' -w -g -O2 -static-libgcc --target=x86_64-w64-mingw -std=c++20 -finput-charset=UTF-8 -fexec-charset=UTF-8
./badapple
```

##### Linux
```sh
g++ ./badapple.cpp -o badapple
./badapple
```

#### To do

Nothing to do.

Ideas are welcome.

