## Bad Apple!!

Play the video in the console as a character drawing..
~~You can watch anime by it while you are connected by **SSH**.~~

以字符画的形式在控制台中播放视频.
~~你甚至可以利用它在 **SSH** 中看番.~~

![GIF](./play.gif)

### Performance

The real-time mode's bottleneck is the decoding speed, and the preloaded-replay mode's is IO.

### Help

The file extension generated by preloading is `.badapple`.
Automatically enter preload-replay mode when the input file extension is `.badapple`.

```markdown
usage: badapple [options] ... 
options:
  -i, --input                   video file (string [=./badapple.mp4])
  -o, --output                  [preload] output file (string [=])
  -a, --audio                   audio file (string [=])
  -m, --map                     font data file (string [=])
  -s, --scale                   width:height (string [=72:54])
  -r, --rate                    frame rate (double [=1024])
      --not-clear               don't clear screen (using ANSI) before print a frame
      --contrast-enhancement    contrast Enhancement
      --preload                 [preload]
      --play-audio              play audio with ffplay
  -?, --help                    print this message
```

### Clone

```sh
git clone --recurse-submodules --remote-submodule https://github.com/userElaina/Bad-Apple.git
```

### To do

Performance Test

### License

The code is available under the [MIT license](./LICENSE).

### How to use

**[Fonts Pre-processing](#fonts-pre-processing)**

**[Windows-FFmpeg](#windows-ffmpeg)**
**[Windows-OpenCV](#windows-opencv)**

**[Linux-FFmpeg](#linux-ffmpeg)**
**[Linux-OpenCV](#linux-opencv)**

#### Fonts Pre-processing

##### Dependencies

```sh
pip install pillow
```

##### Interpret and Run

```sh
python -u "font/font.py"
```

#### Windows-FFmpeg

##### Dependencies

[FFmpeg](https://github.com/BtbN/FFmpeg-Builds/releases/tag/latest)
(Include `ffmpeg` `ffprobe` `ffplay`)

##### Compile and Run

```sh
clang++ "badapple.cpp" -o "badapple.exe" -w -g -O3 -static-libgcc --target=x86_64-w64-mingw
./badapple
```

or

```sh
g++ "badapple.cpp" -o "badapple.exe" -w -g -O3 -static-libgcc
./badapple
```

#### Windows-OpenCV

##### Dependencies

[OpenCV](https://opencv.org/)

You may need to [compile it yourself](https://github.com/userElaina/OpenCV-460-MinGW-W64-Build).

##### Compile and Run

```sh
clang++ "badapple.cpp" -o "badapple.exe" -I "$Env:OPENCV_PATH\include" -I "$Env:OPENCV_PATH\include\opencv2" -L "$Env:OPENCV_PATH\x64\mingw\lib" -llibopencv_world460 -w -g -O3 -static-libgcc --target=x86_64-w64-mingw
./badapple
```

or

```sh
g++ "badapple.cpp" -o "badapple.exe" -I "$Env:OPENCV_PATH\include" -I "$Env:OPENCV_PATH\include\opencv2" -L "$Env:OPENCV_PATH\x64\mingw\lib" -llibopencv_world460 -w -g -O3 -static-libgcc
./badapple
```

### Linux-FFmpeg

#### Compile

##### Dependencies

Use your package manager to install or upgrade gcc, g++, FFmpeg and dependencies if need, like

```sh
sudo apt update
sudo apt install upgrade gcc g++ ffmpeg
```

```sh
sudo pacman -Syu gcc ffmpeg
```

##### Compile and Run

```sh
g++ "badapple.cpp" -o "badapple.out" -w -g -O3 -static-libgcc
chmod +x ./badapple.out
./badapple.out
```

#### Linux-OpenCV

##### Dependencies

Use your package manager to install or upgrade gcc, g++, OpenCV and dependencies if need, like

```sh
sudo apt update
sudo apt install upgrade gcc g++ libopencv-dev
```

```sh
sudo pacman -Syu gcc opencv vtk hdf5 pkgconf
```

##### Compile and Run

```sh
g++ "badapple.cpp" -o "badapple.out" -w -g -O3 -static-libgcc `pkg-config --cflags --libs opencv4`
chmod +x ./badapple.out
./badapple.out
```

```sh
g++ "badapple.cpp" -o "badapple.out" -w -g -O3 -static-libgcc `pkgconf --cflags --libs opencv4`
chmod +x ./badapple.out
./badapple.out
```
