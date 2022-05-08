## Bad Apple!!

Tool to convert video to character drawing.
~~You can watch anime by it while you are connected by **SSH**.~~

视频转字符画工具.
~~你甚至可以利用它在 **SSH** 中看番.~~

![GIF](./play.gif)

The real-time version supports up to **720p30Hz**, the bottleneck is the encoding and decoding speed.

The pre-loaded version supports up to **1080p30Hz**, and the bottleneck is IO.


### Help

```markdown
usage: badapple [options] ...
options:
  -i, --input                   video file (string [=./badapple.mp4])
  -m, --map                     font data file (string [=])
  -s, --scale                   width:height (string [=76:54])       
  -r, --rate                    set frame rate (int [=10])
      --contrast-enhancement    contrast enhancement
  -?, --help                    print this message
```


### Environmental Dependence

#### Preprocessing (fonts)

CPP and Python3.
Python module Pillow.

```sh
pip install Pillow
```

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


### Compile and Run

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

### To do

Nothing to do.

Ideas are welcome.
