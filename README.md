## Bad Apple!!

Play the video in the console as a character drawing..
~~You can watch anime by it while you are connected by **SSH**.~~

以字符画的形式在控制台中播放视频.
~~你甚至可以利用它在 **SSH** 中看番.~~

![GIF](./play.gif)

|   | OS      | Load Mode | Decoder | Support   | Bottleneck     |
| - | -       | -         | -       | -         | -              |
| 0 | Windows | real-time | FFmpeg  | 720p30Hz  | decoding speed |
| 1 | Linnux  | real-time | FFmpeg  | 720p30Hz  | decoding speed |
| 2 | Windows | preloaded | FFmpeg  | 1080p30Hz | IO             |
| 3 | Linux   | preloaded | FFmpeg  | 1080p30Hz | IO             |
| 4 | Windows | real-time | OpenCV  | 360p15Hz  | decoding speed |
| 5 | Linnux  | real-time | OpenCV  |           | decoding speed |
| 6 | Windows | preloaded | OpenCV  | 1080p30Hz | IO             |
| 7 | Linux   | preloaded | OpenCV  | 1080p30Hz | IO             |


### Help

```markdown
usage: badapple [options] ... 
options:
  -i, --input                   video file (string [=./badapple.mp4])
  -a, --audio                   audio file (string [=])
  -m, --map                     font data file (string [=])
  -s, --scale                   width:height (string [=76:54])       
  -r, --rate                    set frame rate (double [=10])        
      --contrast-enhancement    contrast enhancement
      --play-audio              play audio with ffplay
  -?, --help                    print this message
```

### To do

OpenCV Version for Windows

Add preload function to the command line tool

Installer

### Dependencies

#### Preprocessing (fonts)

CPP and Python3.
Python module Pillow.

```sh
pip install Pillow
```

#### Compile

Usually, as long as you can compile the CPP.

#### Run

`ffmpeg` (Include `ffmpeg` `ffprobe` `ffplay`).

##### Windows

[FFmpeg](https://github.com/BtbN/FFmpeg-Builds/releases/tag/latest)

`libstdc++-6.dll` `libgcc_s_seh-1.dll` `libwinpthread-1` (C++ compile dependencies)

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


### Clone

```sh
git clone --recurse-submodules --remote-submodule git@github.com:userElaina/Bad-Apple.git
```


### Compile and Run

##### Windows

```sh
clang++ 'badapple.cpp' -o 'badapple.exe' -w -g -O2 -static-libgcc --target=x86_64-w64-mingw -std=c++20
./badapple
```

##### Linux

```sh
g++ ./badapple.cpp -o badapple.out
./badapple.out
```

