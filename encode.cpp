// code by userElaina
#include "encode.hpp"

// encode(std::string pth,std::string dir,int x,int y,double fps,int n,double time);
// encode_ascii(std::string pth,std::string data,std::string font,int offset=5);

int main(){
    std::string file_font="./consola_ascii_00ff.data";
    std::string file_data="./v54_15.data";
    std::string file_ba="./v54_15.badapple";

    encode(file_data,"./Frame/",76,54,15,6955,232.065167);
    encode_ascii(file_ba,file_data,file_font);
}
