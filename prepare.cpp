// code by userElaina
#include "bmp24bits.hpp"
const int X=11796480;

int main(){
    FILE*f=fopen("./ascii.data","w");
    BMP24bits*p;
    for(auto i=0x20;i<=0x7e;i++){
        pt(i);
        for(auto j=2;j<8;j++){
            std::string str="./Char/";
            str+=std::to_string(i);
            str+='_';
            str+=std::to_string(j);
            str+=".bmp";
            p=new BMP24bits(str);
            LL s1=0,s2=0;
            for(auto x=0;x<X;x+=3)
                s1+=p->o[x];
            for(auto x=X;x<X<<1;x+=3)
                s2+=p->o[x];
            delete p;
            fprintf(f,"%d %d %lld %lld\n",i,j,s1,s2);
            // printf("%d %d %lld %lld\n",i,j,s1,s2);
        }
    }
    pt(10);
}
