g++ "badapple-ffmpeg.cpp" -o "ba" -w -g -O3 -static
g++ "badapple-opencv.cpp" -o "ba" -w -g -O3 -Bdynamic `pkg-config --cflags --libs opencv4`

./ba --qwq
./ba
./ba -i aaa
./ba -i archive/Elysia1.mp4 -o archive/ely.badapple -s 128:72 -r 10
./ba -i archive/ely.badapple
./ba -i archive/NCOP.mkv -s 96:54 --contrast
./ba -i archive/87011701_p0.jpg -s 85:98 --contrast
