g++ "badapple-ffmpeg.cpp" -o "ba.exe" -w -g -O3 -static
g++ "badapple-opencv.cpp" -o "ba.exe" -w -g -O3 -Bdynamic -I"$Env:OPENCV481\include" -L"$Env:OPENCV481\x64\mingw\lib" -llibopencv_world481

./ba --qwq
./ba
./ba -i aaa
./ba -i archive/Elysia1.mp4 -o archive/ely.badapple -s 0:72 -r 10
./ba -i archive/ely.badapple -a archive/addiction.flac
./ba -i archive/NCOP.mkv -s 96:0 --contrast --play_audio
./ba -i archive/87011701_p0.jpg -s 85:98 --contrast
