// code by userElaina
#include "bmp24bits.hpp"

int main(){
    std::string s="./87011701_p0.jpg";
    BMP24bits*p=new BMP24bits(s);
    std::string s2="2.bmp";
    BMP24bits*p2=p->resize(p->width/3,p->height/4);
    p2->save(s2);
}
