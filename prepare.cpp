// code by userElaina
#include "prepare.hpp"

// config consola
std::string name="consola.ttf";
#if defined(__WINDOWS_) || defined(_WIN32)
    std::string dir="C:\\test\\BadApple\\1\\";
#else
    std::string dir="~/test/BadApple/";
#endif
int white=0xff,black=0x00;
int offset2=0;

inline std::string hex(LL x,int lower=1){
    std::string s=(std::string)"0123456789"+(lower?"abcdef":"ABCDEF");
    s+=std::to_string(x>>4);
    s+=std::to_string(x&15);
    std::string ans="";
    if(!x){
        ans="0";
        return ans;
    }
    while(x){
        ans=s[x&15]+ans;
        x>>=4;
    }
    return ans;
}

int main(){
    // preprocess
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
    std::string fs_bmp=fs_temp+namel+split_path;
    std::string f_data=fs_temp+namel+"_"+hex(offset2)+".data";
    std::string f_data2=dir+namel+"_"+hex(offset2)+"_"+hex(BLACK)+hex(WHITE)+".data";

    bmp2data(f_data,fs_bmp);
    data2map(f_data2,WHITE,BLACK);
    // data2map(f_data2,WHITE,BLACK,f_data);
}
