// code by userElaina
#include "bmp24bits.hpp"

const int HALF=3932160;
const int L=0x20,R=0x7e;

int main(){
    FILE*f=fopen("./ascii.data","w");
    fprintf(f,"%d\n",HALF);
    BMP24bits*p;
    for(auto i=L;i<=R;i++){
        pt(i);
        for(auto j=2;j<8;j++){
            std::string str="./Char/";
            str+=std::to_string(i);
            str+='_';
            str+=std::to_string(j);
            str+=".bmp";
            p=new BMP24bits(str);
            LL s1=0,s2=0;
            for(auto x=0;x<HALF;x++)
                s1+=p->getb(x);
            for(auto x=HALF;x<HALF<<1;x++)
                s2+=p->getb(x);
            delete p;
            fprintf(f,"%d %d %lld %lld\n",i,j,s1,s2);
            // printf("%d %d %lld %lld\n",i,j,s1,s2);
        }
    }
    pt(10);
}
