// code by userElaina
#include "bmp24bits.hpp"

// default
const int L=0x20,R=0x7e;
int WHITE=0xff,BLACK=0x00;
const int MAXCHAR=0x100;

const int MAXCOL=0x100;
int ss[MAXCHAR],ssr=0,size;
LL m[MAXCHAR][2],_max,_min;


inline void bmp2data(std::string f_out,std::string fs_bmp,int offset=0){
    printf("bmp2data\n");

    for(auto i=L;i<=R;i++){
        ss[ssr++]=i;
    }

    FILE*f=fopen(f_out.c_str(),"w");
    BMP24bits*p;
    auto half=-1;
    for(auto i=0;i<ssr;i++){
        std::string f_bmp=fs_bmp+std::to_string(ss[i])+".bmp";
        p=new BMP24bits(f_bmp);
        if(half<0){
            size=p->size;
            half=((p->height>>1)+offset)*p->width;
            fprintf(f,"%d %d\n",ssr,size);
        }

        LL s1=0,s0=0;
        auto j=0;
        for(;j<half;j++){
            s1+=p->getb(j);
        }
        for(;j<p->size;j++){
            s0+=p->getb(j);
        }
        delete p;

        m[i][0]=s0;
        m[i][1]=s1;
        _max=mx(_max,s0);
        _max=mx(_max,s1);
        _min=mn(_min,s0);
        _min=mn(_min,s1);
        fprintf(f,"%d %lld %lld\n",ss[i],s0,s1);
        printf("%c",ss[i]);
        fflush(stdout);
    }
    printf("\n");
    fclose(f);
}

inline void load_data(std::string f_in){
    printf("Loading...\n");
    FILE*f=fopen(f_in.c_str(),"r");
    fscanf(f,"%d%d",&ssr,&size);
    for(auto i=0;i<ssr;i++){
        LL s0,s1;
        fscanf(f,"%d%lld%lld",&ss[i],&s0,&s1);

        m[i][0]=s0;
        m[i][1]=s1;
        _max=mx(_max,s0);
        _max=mx(_max,s1);
        _min=mn(_min,s0);
        _min=mn(_min,s1);
    }
    fclose(f);
}

inline void data2map(std::string f_out,std::string f_in=""){
    if(f_in.size()){
        load_data(f_in);
    }

    printf("data2map\n");

    FILE*f=fopen(f_out.c_str(),"w");

    const int LC=WHITE-BLACK;
    const LL lv=_max-_min;
    int ans[LC+1][LC+1];
    for(auto c=0;c<=LC;c++){
        const LL ext=_min*LC+lv*c;
        for(auto c2=0;c2<=LC;c2++){
            int mnc;
            LL mnl=lv<<8;
            const LL ext2=_min*LC+lv*c2;
            for(auto i=0;i<ssr;i++){
                LL v=m[i][0]*LC;
                v=absub(v,ext);
                LL v2=m[i][1]*LC;
                v+=absub(v2,ext2);
                if(v<mnl){
                    mnl=v;
                    mnc=ss[i];
                }
            }
            ans[c][c2]=mnc;
        }
    }
    for(auto c=0;c<MAXCOL;c++){
        auto c1=c>BLACK?(c<WHITE?c-BLACK:LC):0;
        for(auto c2=0;c2<MAXCOL;c2++){
            auto c3=c2>BLACK?(c2<WHITE?c2-BLACK:LC):0;
            if(c1==c3){
                printf("%d ",c1);
                fflush(stdout);
            }
            fputc(ans[c1][c3],f);
            fputc(ans[c1][c3],f);
        }
        fputc(10,f);
    }
    fclose(f);
}

inline void data2map(std::string f_out,int white,std::string f_in=""){
    WHITE=white;
    data2map(f_out,f_in);
}

inline void data2map(std::string f_out,int white,int black,std::string f_in=""){
    BLACK=black;
    data2map(f_out,white,f_in);
}
