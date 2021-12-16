// code by userElaina
#include "bmp24bits.hpp"

const int MAXCOL=0x100;

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


inline void split(std::string f_v,std::string f_bmp,std::string f_conf){
    std::string order=(std::string)"ffprobe -v quiet -show_streams -select_streams v \""+f_v+"\" | grep -E \"duration=|nb_frames=\" | awk -F= "+awk_qm+"{print $2}"+awk_qm+" > \""+f_conf+"\"";
    printf("%s\n",order.c_str());
    system(order.c_str());
    order="ffmpeg -v quiet -i \""+f_v+"\" \""+f_bmp+"\"";
    printf("%s\n",order.c_str());
    system(order.c_str());
}

inline int encode(std::string f_out,std::string fs_bmp,std::string f_conf,int x,int y,double fps){
    printf("enocde\n");
    double duration;
    int nb_frames;
    f=fopen(f_conf.c_str(),"r");
    fscanf(f,"%lf%d",&duration,&nb_frames);
    fclose(f);
    printf("duration=%.2lf\nnb_frames=%d\n",duration,nb_frames);

    int mo=0.5+((double)nb_frames)/duration/fps;
    if(!mo){
        mo=1;
    }
    const int n2=(nb_frames-1)/mo+1;
    const int clk=0.5+duration*1000.0*(double)mo/(double)nb_frames;
    const int x2=x+(x&1),y2=y+(y&1);
    const int xy2=x2*y2;

    printf("%dx%d\nfps=%d\nclk=%d\n",x2,y2,n2,clk);

    fp=fopen(f_out.c_str(),"wb");

    fwrite((B*)&x2,1,4,fp);
    fwrite((B*)&y2,1,4,fp);
    fwrite((B*)&n2,1,4,fp);
    fwrite((B*)&clk,1,4,fp);
    fflush(fp);

    int max=0xff,min=0x00;
    BMP24bits*p;
    BMP24bits*p2;
    B*map=(B*)malloc(xy2);
    for(auto i=1;i<=nb_frames;i+=mo){
        std::string pth=fs_bmp+std::to_string(i)+".bmp";
        p=new BMP24bits(pth);
        p2=p->resize(x,y);
        delete p;
        p2->gray();

        memset(map,0,xy2);
        for(int j=0;j<y;j++){
            const int delta=(y2-1-j)*x2;
            for(int i=0;i<x;i++){
                auto c=p2->getb(i,j);
                if(c>max){
                    max=c;
                }
                if(c<min){
                    min=c;
                }
                map[delta+i]=c;
            }
        }
        // pth=fs_bmp+std::to_string(i)+"g.png";
        // p2->save(pth);
        delete p2;

        fwrite(map,1,xy2,fp);
        fflush(fp);

        if(!((i/mo)&127)){
            printf("%d ",i/mo);
            fflush(stdout);
        }
    }
    pt(10);
    pt(10);
    fclose(fp);
    return max<<8|min;
}

inline void encode2(std::string f_out,std::string f_in,std::string f_map){
    printf("enocde2\n");

    f=fopen(f_map.c_str(),"rb");

    int map[MAXCOL][MAXCOL];
    for(auto i=0;i<MAXCOL;i++){
        for(auto j=0;j<MAXCOL;j++){
            g13();
            map[i][j]=g13();
        }
        g13();
    }
    fclose(f);

    for(auto i=0;i<MAXCOL;i++){
        pt(map[i][i]);
    }
    pt(10);

    f=fopen(f_in.c_str(),"rb");
    int x,y,n,clk;
    fread((B*)&x,1,4,f);
    fread((B*)&y,1,4,f);
    fread((B*)&n,1,4,f);
    fread((B*)&clk,1,4,f);
    y>>=1;

    fp=fopen(f_out.c_str(),"wb");

    uout(x);
    ptc(32);
    uout(y);
    ptc(32);
    uout(n);
    ptc(32);
    uout(clk);
    ptc(32);
    ptc(10);
    ptc(10);
    fflush(fp);

    int l[x];
    for(auto frame=0;frame<n;frame++){
        for(auto j=0;j<y;j++){
            for(auto i=0;i<x;i++){
                l[i]=gtc();
            }
            for(auto i=0;i<x;i++){
                ptc(map[l[i]][gtc()]);
            }
            ptc(10);
        }
        ptc(10);
        fflush(fp);

        if(!(frame&255)){
            printf("%d ",frame);
            fflush(stdout);
        }
    }
    pt(10);
    pt(10);
    fclose(f);
    fclose(fp);
}