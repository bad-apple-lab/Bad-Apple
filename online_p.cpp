// code by userElaina
#include "bmp24bits.hpp"

int main(){
    std::string order=(std::string)"ffmpeg -v quiet -i 0.png -vf scale=192:108 -c:v rawvideo -f rawvideo -";
    printf("%s\n",order.c_str());

    int width,height;
    width=192;
    height=108;

    BMP24bits*p=new BMP24bits(width,height);

    int line_size=width*3;
    int full_size=height*line_size;
    B*t=p->o+full_size;
    
    FILE*pipe=_popen(order.c_str(),"rb");
    if(!pipe){printf("what the fuck1\n");return 1;}

    int i=0;
    while(!feof(pipe)){
        t-=line_size;
        int z=fread(t,1,line_size,pipe);
        if(z^line_size){
            printf("%d %d\n",i,z);
        }
        i++;
    }
    _pclose(pipe);
    p->save("0test.bmp");

    // system("pause"); //暂停以查看结果
}

// raw: 左上角 按行 rgb
// bmp: 左下角 按行 bgr