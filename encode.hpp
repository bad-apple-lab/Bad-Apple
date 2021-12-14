// code by userElaina
#include "bmp24bits.hpp"

FILE*f;
FILE*fp;

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

inline void ptc(int c){
    putc(c,fp);
}
inline void p32(){
    ptc(' ');
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


inline void uout(int x){
    if(x<10){
        ptc('0'+x);
    }else{
        uout(x/10);
        ptc('0'+x%10);
    }
}

inline void encode(std::string pth,std::string dir,int x,int y,double fps,int n,double time){
    int mo=0.5+((double)n)/time/fps;
    if(!mo){
        mo=1;
    }
    const int n2=(n-1)/mo+1;
    const int clk=0.5+time*1000.0*(double)mo/(double)n;
    const int x2=x+(x&1),y2=y+(y&1);
    const int xy2=x2*y2;

    fp=fopen(pth.c_str(),"wb");

    // fprintf(fp,"%d %d %d %d ",x2,y2,n2,clk);
    uout(x2);
    p32();
    uout(y2);
    p32();
    uout(n2);
    p32();
    uout(clk);
    p32();
    fflush(fp);

    BMP24bits*p;
    BMP24bits*p2;
    B*map=(B*)malloc(xy2);
    for(auto frame=1;frame<=n;frame+=mo){
        p=new BMP24bits(dir+std::to_string(frame)+".bmp");
        p2=p->resize(x,y);
        delete p;
        p2->gray();

        memset(map,0,xy2);
        for(int j=0;j<y;j++){
            const int delta=(y2-1-j)*x2;
            for(int i=0;i<x;i++){
                map[delta+i]=p2->getb(i,j);
            }
        }
        delete p2;

        fwrite(map,1,xy2,fp);
        fflush(fp);

        if(frame%(mo<<4)==1){
            printf("%d\n",frame);
        }
    }
    fclose(fp);
}

inline void encode_ascii(std::string pth,std::string data,std::string font,int offset=5){
    f=fopen(font.c_str(),"rb");
    uin();
    int offseta=uin();
    int c=g13();
    while(offseta<offset){
        for(auto i=0x00;i<=0xff;i++){
            for(auto j=0x00;j<=0xff;j++){
                // g13(),g13();
                int c1;
                if((c=g13())^(c1=g13()))printf("%d %d %d %d\n",i,j,c,c1),exit(0);
                
            }
            // g13();
            if((c=g13())^10)printf("%d %c\n",c,c),exit(0);
        }
        g13();
        offseta++;
    }

    int map[0x100][0x100];
    for(auto i=0x00;i<=0xff;i++){
        for(auto j=0x00;j<=0xff;j++){
            g13();
            map[i][j]=g13();
        }
        g13();
    }
    fclose(f);

    for(auto i=0x00;i<=0xff;i++){
        pt(map[i][i]);
    }
    pt(10);

    f=fopen(data.c_str(),"rb");
    int x=uin();
    int y=uin()>>1;
    int n=uin();
    int clk=uin();

    fp=fopen(pth.c_str(),"wb");

    // fprintf(fp,"%d %d %d %d ",x,y,n,clk);
    uout(x);
    p32();
    uout(y);
    p32();
    uout(n);
    p32();
    uout(clk);
    p32();
    flush10(fp);
    flush10(fp);

    int l[x];
    for(auto frame=0;frame<n;frame++){
        for(auto j=0;j<y;j++){
            for(auto i=0;i<x;i++){
                l[i]=gtc();
            }
            for(auto i=0;i<x;i++){
                ptc(map[l[i]][gtc()]);
            }
            flush10(fp);
        }
        flush10(fp);

        if(!(frame&255)){
            printf("%d\n",frame);
        }
    }
    fclose(f);
    fclose(fp);
}