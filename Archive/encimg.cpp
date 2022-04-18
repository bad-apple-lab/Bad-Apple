// code by userElaina
#include "encode.hpp"

// config
std::string f_bmp="./Archive/87011701_p0.jpg";
// std::string f_bmp="./Archive/83110343_p0.jpg";
#if defined(__WINDOWS_) || defined(_WIN32)
    std::string f_map="C:\\test\\BadApple\\1\\consola_0_0ff.data";
#else
    std::string f_map="~/test/BadApple/1/consola_0_0ff.data";
#endif

int width,height;

int main(){
    width=256,height=256;
    width=128,height=128;
    width=64,height=64;
    encode(f_bmp,f_map,width,height);
}
