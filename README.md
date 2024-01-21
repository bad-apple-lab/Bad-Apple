## Bad Apple!!

Play the video in the console as ASCII art. 
~~You can watch anime by it while you are connected by **SSH**.~~

Where there is light, there is [Bad Apple!!](https://www.youtube.com/watch?v=FtutLA63Cp8)

[Python Module](https://github.com/bad-apple-lab/Bad-Apple-Python-Module)

![GIF](./play.gif)

### Performance

1080p60Hz on modern high-performance PCs.

### Help

The file extension generated by preloading is `.badapple`.
Automatically enter preload-replay mode when the input file extension is `.badapple`.

```markdown
usage: badapple [options] ... 
  (BadApple-FFmpeg_or_OpenCV-OS-ISA-Version)
options:
  -i, --input                   video file (string [=./badapple.mp4])
  -o, --output                  [preload] output file (string [=])
  -f, --font                    font data file (string [=])
  -a, --audio                   [play_audio] audio file (string [=])
  -s, --scale                   width:height (string [=72:54])
  -r, --rate                    frame rate (double [=1024])
      --not_clear               not clear screen (using ANSI) before print a frame
      --contrast_enhancement    contrast Enhancement
      --preload                 preload video (not play)
      --play_audio              play audio with ffplay
  -?, --help                    print this message
```

### Clone

```sh
git clone --recurse-submodules --remote-submodule https://github.com/userElaina/Bad-Apple.git
```

### How to build

*Only tested on x86_64

**[Fonts Pre-processing](#fonts-pre-processing)**

**[Windows-FFmpeg](#windows-ffmpeg)**
**[Windows-OpenCV](#windows-opencv)**

**[Linux-FFmpeg](#linux-ffmpeg)**
**[Linux-OpenCV](#linux-opencv)**

#### Fonts Pre-processing

If you don't want to change the font, then you don't need to use Python.

##### Dependencies

```sh
pip install pillow
```

##### Interpret and Run

Change this line

```py
f_font = 'font/consola.ttf'
```

to your font file path.

```sh
python -u "font/font.py"
```

#### Windows-FFmpeg

##### Dependencies

[FFmpeg](https://github.com/BtbN/FFmpeg-Builds/releases/tag/latest)
(Include `ffmpeg` `ffprobe` `ffplay`)

##### Compile

```sh
g++ "badapple-ffmpeg.cpp" -o "badapple-ffmpeg-win.exe" -w -g -O3
```

#### Windows-OpenCV

##### Dependencies

[OpenCV](https://opencv.org/)

You may need to [compile it yourself](https://github.com/userElaina/OpenCV-MinGW-W64-Build).

##### Compile

```sh
# Dynamic (libopencv_world481.dll)
g++ "badapple-opencv.cpp" -o "badapple-opencv481d-v2.1.0-win-amd64.exe" -w -g -O3 -I"$Env:OPENCV481\include" -L"$Env:OPENCV481\x64\mingw\lib" -llibopencv_world481
```

```sh
# Static (libopencv_world481.a)
g++ "badapple-opencv.cpp" -o "badapple-opencv481s-v2.1.0-win-amd64.exe" -w -g -O3 -static -I"$Env:OPENCV481A\include" -L"$Env:OPENCV481A\x64\mingw\staticlib" -lopencv_world481 -llibprotobuf -llibjpeg-turbo -llibwebp -llibpng -llibtiff -llibopenjp2 -lIlmImf -lzlib -lquirc -lade -lcomctl32 -lgdi32 -lole32 -lsetupapi -lwsock32 -lws2_32 -lpthread -luuid -loleaut32
```

### Linux-FFmpeg

#### Compile

##### Dependencies

Use your package manager to install or upgrade C++ compiler, FFmpeg and dependencies if need, like

```sh
# Debian Ubuntu
sudo apt update
sudo apt install --upgrade gcc g++ ffmpeg
```

```sh
# Arch
sudo pacman -Syu gcc ffmpeg
```

##### Compile

```sh
g++ "badapple-ffmpeg.cpp" -o "badapple-ffmpeg-linux.out" -w -g -O3
```

#### Linux-OpenCV

##### Dependencies

Use your package manager to install or upgrade C++ compiler, OpenCV and dependencies if need, like

```sh
# Debian Ubuntu
sudo apt update
sudo apt install --upgrade gcc g++ libopencv-dev pkg-config
```

```sh
# Arch
sudo pacman -Syu gcc opencv vtk hdf5 pkgconf
```

##### Compile

```sh
g++ "badapple-opencv.cpp" -o "badapple-opencv-linux.out" -w -g -O3 `pkg-config --cflags --libs opencv4`
```

### To Do

Use `make` to compile.

Automatic parameter setting through information from video and hardware.

Choose audio player.
