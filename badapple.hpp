// code by userElaina
#include<bits/stdc++.h>
#include<sys/time.h>
#include "consola_0_0ff.h"

#define LL long long
#define ULL unsigned long long
#define B unsigned char
#define pt putchar
#define gt getchar

#if defined(__WINDOWS_) || defined(_WIN32)
    std::string nul="nul";
    std::string split_path="\\";
    std::string awk_qm="\"";
    std::string mkdir_p="mkdir ";
#else
    #include<unistd.h>
    #include<sys/types.h>
    // #include<termios.h>
    std::string nul="/dev/null";
    std::string split_path="/";
    std::string awk_qm="'";
    std::string mkdir_p="mkdir -p ";
#endif

const int BUFFER_SIZE=1<<8;
const int STDOUT_SIZE=1<<20;
const int PIXEL_SIZE=3;
const int MAXCOL=0x100;

int exec_r(const char*cmd,char*result){
    #if defined(__WINDOWS_) || defined(_WIN32)
        FILE*pipe=_popen(cmd,"r");
    #else
        FILE*pipe=popen(cmd,"r");
    #endif

    if(!pipe)return 1;
    int code=0;

    int t=0;
    while(!feof(pipe)){
        fread(result+t,1,BUFFER_SIZE,pipe);
        t+=BUFFER_SIZE;
        if(t>=STDOUT_SIZE){
            code=2;
            break;
        }
    }

    #if defined(__WINDOWS_) || defined(_WIN32)
        _pclose(pipe);
    #else
        pclose(pipe);
    #endif
    return code;
}


FILE*f;
inline int g(){
    int c=getc(f);
    while(c==13||c==10){
        c=getc(f);
    }
    return c;
}

int play(std::string video,std::string font,int x,int y,int fps,int contrast_enhancement=0){
    std::string command;

    command=(std::string)"ffprobe -v quiet -show_streams -select_streams v \""+video+"\" | grep -E \"duration=|nb_frames=|coded_width=|coded_height=\" | awk -F= "+awk_qm+"{print $2}"+awk_qm;
    // printf("%s\n",command.c_str());

    double duration;
    int nb_frames;
    int width,height;
    char result[STDOUT_SIZE];
    if(!exec_r(command.c_str(),result)){
        sscanf(result,"%d%d%lf%d",&width,&height,&duration,&nb_frames);
    }

    int mo=0.5+((double)nb_frames)/duration/fps;
    if(!mo){
        mo=1;
    }
    const int n2=(nb_frames-1)/mo+1;
    const int clk=0.5+duration*1000000.0*(double)mo/(double)nb_frames;

    // x+=x&1;
    y+=y&1;
    const int xy=x*y;
    printf("[%d:%d %.2lfHz] -> [%d:%d %.2lfHz] %.3lfs\n",width,height,((double)nb_frames)/duration,x,y,((double)n2)/duration,duration);

    const int print_size=(x+1)*(y>>1);
    char buffer[print_size];

    char map[MAXCOL][MAXCOL];

    if(font.size()){
        f=fopen(font.c_str(),"rb");
        for(auto i=0;i<MAXCOL;i++){
            for(auto j=0;j<MAXCOL;j++){
                g();
                map[i][j]=g();
            }
            g();
        }
        fclose(f);
    }else{
        for(auto i=0;i<MAXCOL;i++){
            for(auto j=0;j<MAXCOL;j++){
                map[i][j]=default_map[i][j<<1];
            }
        }
    }

    // read video
    int t=0;
    command=(std::string)"ffmpeg -v quiet -i \""+video+"\" -vf scale="+std::to_string(x)+":"+std::to_string(y)+" -c:v rawvideo -pix_fmt gray -f rawvideo -";
    // printf("%s\n",command.c_str());

    // pipe
    #if defined(__WINDOWS_) || defined(_WIN32)
        FILE*pipe=_popen(command.c_str(),"rb");
    #else
        FILE*pipe=popen(command.c_str(),"r");
    #endif
    if(!pipe){
        printf("error: pipe\n\n");
        exit(0);
    }

    struct timeval t0;
    struct timeval t1;
    B*p=(B*)malloc(PIXEL_SIZE);
    B*f=(B*)malloc(xy);

    printf("BEGINNING...");
    fflush(stdout);

    #if defined(__WINDOWS_)||defined(_WIN32)
        _sleep(1000);
    #else
        sleep(1);
    #endif

    printf("\x1b[256F\x1b[0J");
    gettimeofday(&t0,NULL);
    for(auto i=0;i<nb_frames;i++){
        int max_pixel=-1,min_pixel=256;

        int z=fread(f,1,xy,pipe);
        if(xy^z){
            printf("error: fread=%d\n",z);
            return 1;
        }
        if(i%mo){
            continue;
        }

        if(contrast_enhancement){
            for(auto j=0;j<xy;j++){
                if(f[j]>max_pixel)max_pixel=f[j];
                if(f[j]<min_pixel)min_pixel=f[j];
            }
            if(max_pixel<0||min_pixel>255){
                printf("error: max_pixel=%d,min_pixel=%d\n",max_pixel,min_pixel);
                return 1;
            }

            if(max_pixel^min_pixel){
                for(auto j=0;j<xy;j++){
                    f[j]=(f[j]-min_pixel)*0xff/(max_pixel-min_pixel);
                }
            }else{
                memset(f,max_pixel&128?0xff:0x00,xy);
            }
        }

        for(auto j=0;j<(y>>1);j++){
            for(auto k=0;k<x;k++){
                buffer[j*(x+1)+k]=map[f[(j<<1)*x+k]][f[(j<<1|1)*x+k]];
            }
            buffer[j*(x+1)+x]=10;
        }

        printf("\x1b[256F");
        fwrite(buffer,1,print_size,stdout);
        fflush(stdout);

        gettimeofday(&t1,NULL);
        while((t1.tv_sec-t0.tv_sec)*1000000+t1.tv_usec-t0.tv_usec<clk){
            gettimeofday(&t1,NULL);
        }
        t0=t1;
    }

    // pipe close
    #if defined(__WINDOWS_) || defined(_WIN32)
        _pclose(pipe);
    #else
        pclose(pipe);
    #endif
    return 0;
}
