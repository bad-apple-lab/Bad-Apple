// code by userElaina
#include "encode.hpp"

/*
// config Bad Apple!!
std::string name="1080p.mp4";
#if defined(__WINDOWS_) || defined(_WIN32)
    std::string f_map="C:\\test\\BadApple\\1\\consola_0_0ff.data";
    std::string dir="C:\\test\\BadApple\\1\\";
#else
    std::string f_map="~/test/BadApple/1/consola_0_0ff.data";
    std::string dir="~/test/BadApple/";
#endif
// int width=361,height=270;
int width=76,height=54;
int fps=15;
*/

/*
// config Elaina
std::string name="NCOP.mkv";
#if defined(__WINDOWS_) || defined(_WIN32)
    std::string f_map="C:\\test\\BadApple\\1\\consola_0_0ff.data";
    std::string dir="C:\\Test\\BadApple\\Video\\";
#else
    std::string f_map="~/test/BadApple/1/consola_0_0ff.data";
    // std::string dir="~/test/BadApple/";
#endif
int width=384,height=216;
double fps=12;
*/

/*
// config 19260817
std::string name="19260817.mp4";
#if defined(__WINDOWS_) || defined(_WIN32)
    std::string f_map="C:\\test\\BadApple\\1\\consola_0_0ff.data";
    std::string dir="C:\\Test\\BadApple\\Video\\";
#else
    std::string f_map="~/test/BadApple/1/consola_0_0ff.data";
    // std::string dir="~/test/BadApple/";
#endif
int width=192,height=144;
double fps=999;
*/

// /*
// config
std::string name="pink_pet_bottle,_fujiwara_no_mokou,_houraisan_kaguya,_inaba_tewi.mp4";
#if defined(__WINDOWS_) || defined(_WIN32)
    std::string f_map="C:\\test\\BadApple\\1\\consola_0_0ff.data";
    std::string dir="C:\\All\\Desktop\\";
#else
    std::string f_map="~/test/BadApple/1/consola_0_0ff.data";
    // std::string dir="~/test/BadApple/";
#endif
int width=192,height=108;
double fps=15;
// */


int main(){
    // preprocess
    std::string f_v=dir+name;
    std::string named;
    for(int i=0;i<name.size();i++){
        if(name[i]==' '){
            name[i]='_';
        }else if(name[i]=='.'){
            named=name.substr(0,i);
            break;
        }
    }
    std::string fs_temp=dir+"temp"+split_path;
    std::string fs_bmp=fs_temp+named+split_path;
    system((mkdir_p+"\""+fs_bmp+"\" >"+nul+" 2>&1").c_str());
    std::string f_bmp=fs_bmp+"%"+"d.bmp";
    std::string f_conf=fs_temp+named+".conf";
    std::string ext="_"+std::to_string(width)+"x"+std::to_string(height)+"_"+std::to_string((int)fps);
    std::string f_data=fs_temp+named+ext+".data";
    std::string f_data2=dir+named+ext+".badapple";

    split(f_v,f_bmp,f_conf);
    encode(f_data,fs_bmp,f_conf,width,height,fps);
    encode2(f_data2,f_data,f_map);
}
