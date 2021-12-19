// code by userElaina
#include "encode.hpp"

// config
// std::string f_bmp="./Archive/87011701_p0.jpg";
std::string f_bmp="./Archive/83110343_p0.jpg";
#if defined(__WINDOWS_) || defined(_WIN32)
    std::string f_map="C:\\test\\BadApple\\1\\consola_0_0ff.data";
#else
    std::string f_map="~/test/BadApple/1/consola_0_0ff.data";
#endif
int width=256,height=256;

int main(){
    encode(f_bmp,f_map,width,height);
}
