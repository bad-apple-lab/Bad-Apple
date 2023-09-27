```sh
g++ "badapple-ffmpeg.cpp" -o "badapple-ffmpeg-v2.1.0-debian-amd64.out" -w -g -O3 -static
g++ "badapple-opencv.cpp" -o "badapple-opencv451s-v2.1.0-debian-amd64.out" -w -g -O3 -Bstatic `pkg-config --cflags --libs opencv4`
g++ "badapple-opencv.cpp" -o "badapple-opencv451d-v2.1.0-debian-amd64.out" -w -g -O3 -Bdynamic `pkg-config --cflags --libs opencv4`

g++ "badapple-ffmpeg.cpp" -o "badapple-ffmpeg-v2.1.0-win-amd64.exe" -w -g -O3 -static
g++ "badapple-opencv.cpp" -o "badapple-opencv481d-v2.1.0-win-amd64.exe" -w -g -O3 -Bdynamic -I"$Env:OPENCV481\include" -L"$Env:OPENCV481\x64\mingw\lib" -llibopencv_world481
g++ "badapple-opencv.cpp" -o "badapple-opencv481s-v2.1.0-win-amd64.exe" -w -g -O3 -static -I"$Env:OPENCV481A\include" -L"$Env:OPENCV481A\x64\mingw\staticlib" -lopencv_world481 -llibprotobuf -llibjpeg-turbo -llibwebp -llibpng -llibtiff -llibopenjp2 -lIlmImf -lzlib -lquirc -lade -lcomctl32 -lgdi32 -lole32 -lsetupapi -lwsock32 -lws2_32 -lpthread -luuid -loleaut32
```

in Windows 10 amd64 and Debian 5.10 amd64.

`badapple-*-win-amd64.*z*` are the `.exe`s with their dependencies.

sha256sum:

```sh
215914b7b946a763fe828cc12ec80dec2aded95d96825d802442ce486c3a9ad2  badapple-ffmpeg-v2.1.0-debian-amd64.out
46e01ed1afcf03462506a4a181527921f271ea707a9b60aae6a06068d663b4f0  badapple-ffmpeg-v2.1.0-win-amd64.7z
89501f04333b6b1fc4b13e8e9505dde87586ab966304162b4c5867d5992e7d83  badapple-ffmpeg-v2.1.0-win-amd64.exe
5c32ba6b20982c199c57f593d9feacd1414077ad0aa8cc0e0028c7b61bea23e0  badapple-ffmpeg-v2.1.0-win-amd64.zip
369678b00e635009b233127998c5117e53eb335fd40cadf8b4e7d238fdbea9c6  badapple-opencv451d-v2.1.0-debian-amd64.out
369678b00e635009b233127998c5117e53eb335fd40cadf8b4e7d238fdbea9c6  badapple-opencv451s-v2.1.0-debian-amd64.out
2d3ef92a848392668b087241a46d838abc34f9a97f0ee21e92610fe0b33a8992  badapple-opencv481d-v2.1.0-win-amd64.7z
506639d96ff672d1c264b660cb942bd730cf2698e76a96fd8984a4ab7d6dba35  badapple-opencv481d-v2.1.0-win-amd64.exe
a2106399ecff7c87e1a4f1f3e907dcd8450d5cacf7bf063ebc5db5efe5a0ad30  badapple-opencv481d-v2.1.0-win-amd64.zip
fe0a5623093aaa35cbbb8cef5a5ecfe9cecea730075a2f15e01c435455faad01  badapple-opencv481s-v2.1.0-win-amd64.7z
1fb2f6148ec3b3778ab110c8996a818f2e0d7237cea9013c5e271979ea4a47cf  badapple-opencv481s-v2.1.0-win-amd64.exe
405657d189aa06d71664ca7ea9105f6a02b567f2ceed0e86db7e285458ce8269  badapple-opencv481s-v2.1.0-win-amd64.zip
```
