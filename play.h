// code by userElaina
#include<stdio.h>
#include<time.h>

#define inline 
#define B unsigned char

FILE *f;

inline int gtc(){
    return getc(f);
}
inline int g13(){
    int c=gtc();
    while(c==13){
        c=gtc();
    }
    return c;
}

inline int uin(){
    int c=g13();
    while(c<'0'||'9'<c){
        c=g13();
    }
    int ans=0;
    while('0'<=c&&c<='9'){
        ans=(ans<<1)+(ans<<3)+c-'0';
        c=g13();
    }
    return ans;
}


inline void console_resize(int x,int y){
    char order[100];
    sprintf(order,"mode con cols=%d lines=%d",x,y);
    system(order);
}

inline void ffplay(char*muz){
    char order[100];
    sprintf(order,"start /B ffplay -nodisp -autoexit -hide_banner -v quiet \"%s\"",muz);
    system(order);
}

inline void play(const char*s,const char*music){
    f=fopen(s,"rb");
    const int x=uin();
    const int y=uin();
    const int n=uin();
    const int clk=uin();
    const int frame_size=y*(x+1);

    const int buf_size=frame_size+6;
    B*buf=(B*)malloc(buf_size);
    buf[frame_size]=0x1b;
    buf[frame_size+1]='[';
    buf[frame_size+2]='2';
    buf[frame_size+3]='5';
    buf[frame_size+4]='6';
    buf[frame_size+5]='F';

    printf("BEGINNING...");
    Sleep(1000);
    printf("\x1b[256F\x1b[0J");

    struct timeval t0;
    struct timeval t1;
    g13();
    if(strlen(music)){
        ffplay(music);
    }
    gettimeofday(&t0,NULL);
    for(int i=0;i<n;i++){
        g13();
        fread(buf,1,frame_size,f);
        fwrite(buf,1,buf_size,stdout);
        fflush(stdout);
        gettimeofday(&t1,NULL);
        while((t1.tv_sec-t0.tv_sec)*1000000+t1.tv_usec-t0.tv_usec<clk){
            gettimeofday(&t1,NULL);
        }
        t0=t1;
    }
    printf("\x1b[256F\x1b[0J");
}