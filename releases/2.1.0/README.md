```sh
g++ "badapple-ffmpeg.cpp" -o "badapple-ffmpeg-v2.1.0-win-amd64.exe" -w -g -O3 -static-libgcc
g++ "badapple-ffmpeg.cpp" -o "badapple-ffmpeg-v2.1.0-debian-amd64.out" -w -g -O3 -static-libgcc
g++ "badapple-ffmpeg.cpp" -o "badapple-ffmpeg-v2.1.0-arch-amd64.out" -w -g -O3 -static-libgcc

g++ "badapple-opencv.cpp" -o "badapple-opencv-v2.1.0-win-amd64.exe" -I "$Env:OPENCV470\include" -I "$Env:OPENCV470\include\opencv2" -L "$Env:OPENCV470\x64\mingw\lib" -llibopencv_world470 -w -g -O3 -static-libgcc
g++ "badapple-opencv.cpp" -o "badapple-opencv-v2.1.0-debian-amd64.out" -w -g -O3 -static-libgcc `pkg-config --cflags --libs opencv4`
g++ "badapple-opencv.cpp" -o "badapple-opencv-v2.1.0-arch-amd64.out" -w -g -O3 -static-libgcc `pkgconf --cflags --libs opencv4`
```