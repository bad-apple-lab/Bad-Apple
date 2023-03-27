```sh
g++ "badapple.cpp" -o "badapple-ffmpeg-win-amd64.exe" -w -g -O2 -static-libgcc
g++ "badapple.cpp" -o "badapple-opencv-win-amd64.exe" -I "$Env:OPENCV_PATH\include" -I "$Env:OPENCV_PATH\include\opencv2" -L "$Env:OPENCV_PATH\x64\mingw\lib" -llibopencv_world460 -w -g -O2 -static-libgcc
g++ "badapple.cpp" -o "badapple-ffmpeg-ubuntu-amd64.out"
chmod +x badapple-ffmpeg-ubuntu-amd64.out
g++ "badapple.cpp" -o "badapple-opencv-ubuntu-amd64.out" `pkg-config --cflags --libs opencv4`
chmod +x badapple-opencv-ubuntu-amd64.out
```
in Windows 10 Pro N f Workstation amd64 and it's Ubuntu 20.04 WSL.
`badapple-*-win-amd64.7z` is the `.exe` with its dependencies.
sha256 sums:
```sh
e5c248c7b890880d7d2b30cc18ded4c4d8d4265a150fabd8bfb7cbb2c3933119  badapple-ffmpeg-ubuntu-amd64.out
f311255ae199d9fd368982310aeca4b7ab35ff1f4e0ecc9e677489ceab8bf12c  badapple-ffmpeg-win-amd64.7z
17a9c298b662759aa37e96432889b59e9ddd14c603df3486002019bac4675233  badapple-ffmpeg-win-amd64.exe
95ecc9a5b91164130b5f935756d62ee4fc37c34badfc6226dfe6d71800dffbfa  badapple-opencv-ubuntu-amd64.out
88a90317c8c178f557da4827ef3535b037db4182842ad0a8cd9274b1ee6cab47  badapple-opencv-win-amd64.7z
6f662e596ff44de79c4773bf008924c62bf495b4c3dfbce63293370df96a7ce3  badapple-opencv-win-amd64.exe
```
