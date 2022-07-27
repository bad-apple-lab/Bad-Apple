## Bad Apple!!

Play the video in the console as a character drawing..
~~You can watch anime by it while you are connected by **SSH**.~~

以字符画的形式在控制台中播放视频.
~~你甚至可以利用它在 **SSH** 中看番.~~

![GIF](./play.gif)

The real-time version supports up to **720p30Hz**, the bottleneck is the encoding and decoding speed.
The preloaded version supports up to **1080p30Hz**, and the bottleneck is IO.

|   | OS      | Load Mode | Decoder | Support   |
| - | -       | -         | -       | -         |
| 0 | Windows | real-time | FFmpeg  | 720p30Hz  |
| 1 | Linux   | real-time | FFmpeg  | 720p30Hz  |
| 2 | Windows | real-time | OpenCV  | 360p15Hz  |
| 3 | Linux   | real-time | OpenCV  | 360p15Hz  |


### Help

```markdown
usage: badapple [options] ... 
options:
  -i, --input                   video file (string [=./badapple.mp4])
  -o, --output                  [preloaded mode] output file (string [=])
  -a, --audio                   audio file (string [=])
  -m, --map                     font data file (string [=])
  -s, --scale                   width:height (string [=76:54])
  -r, --rate                    set frame rate (double [=10])
      --contrast-enhancement    contrast enhancement
      --play-audio              play audio with ffplay
  -?, --help                    print this message
```

### Clone

```sh
git clone --recurse-submodules --remote-submodule git@github.com:userElaina/Bad-Apple.git
```

### How to use

**[Fonts Pre-processing](#fonts-pre-processing)**

**[Windows-FFmpeg](#windows-ffmpeg)**
**[Windows-OpenCV](#windows-opencv)**

**[Linux-FFmpeg](#linux-ffmpeg)**
**[Linux-OpenCV](#linux-opencv)**

### To do

Add preload function to the command line tool

How to build OpenCV with MinGW-W64

Installer


#### Fonts Pre-processing

##### Dependencies

```sh
pip install Pillow
```

##### Compile and Run

Usually, as long as you can compile the CPP.

#### Windows-FFmpeg

##### Dependencies

[FFmpeg](https://github.com/BtbN/FFmpeg-Builds/releases/tag/latest)
(Include `ffmpeg` `ffprobe` `ffplay`)

##### Compile and Run

```sh
clang++ "badapple.cpp" -o "badapple.exe" -w -g -O2 -static-libgcc --target=x86_64-w64-mingw -std=c++2a
./badapple
```

or

```sh
g++ "badapple.cpp" -o "badapple.exe" -w -g -O2 -static-libgcc -std=c++2a
./badapple
```

#### Windows-OpenCV

##### Dependencies

[OpenCV](https://opencv.org/)

##### Compile and Run

```sh
clang++ "badapple.cpp" -o "badapple.exe" -I "$Env:OPENCV_PATH\include" -I "$Env:OPENCV_PATH\include\opencv2" -L "$Env:OPENCV_PATH\x64\mingw\lib" -llibopencv_world460 -w -g -O2 -static-libgcc --target=x86_64-w64-mingw
./badapple
```

or

```sh
g++ "badapple.cpp" -o "badapple.exe" -I "$Env:OPENCV_PATH\include" -I "$Env:OPENCV_PATH\include\opencv2" -L "$Env:OPENCV_PATH\x64\mingw\lib" -llibopencv_world460 -w -g -O2 -static-libgcc
./badapple
```

### Linux-FFmpeg

#### Compile

##### Dependencies

Use your package manager to install g++ and FFmpeg, like

```sh
sudo apt update
sudo apt install upgrade g++ ffmpeg
```

```sh
sudo pacman -Syu g++ ffmpeg
```

##### Compile and Run

```sh
g++ "badapple.cpp" -o "badapple.out"
chmod +x ./badapple.out
./badapple.out
```


#### Linux-OpenCV

##### Dependencies

Use your package manager to install g++ and OpenCV (and dependencies if need), like

```sh
sudo apt update
sudo apt install upgrade g++ libopencv-dev
```

```sh
sudo pacman -Syu g++ opencv vtk hdf5
```

##### Compile and Run

```sh
g++ "badapple.cpp" -o "badapple.out" `pkg-config --cflags --libs opencv4`
chmod +x ./badapple.out
./badapple.out
```

