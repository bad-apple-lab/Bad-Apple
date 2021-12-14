// code by userElaina
#include "bmp24bits.hpp"

const int L=0x20,R=0x7e;
const int MAXCOL=0x100;
const int MAXCHAR=0x100;
const int MAXO=0x16;
int ss[MAXCHAR],ssr=0,offsets,offsetA,half;
int WHITE=0xff,BLACK=0x00,LC=WHITE-BLACK;
LL m[MAXO][MAXCHAR][2],max_split[MAXO],min_split[MAXO],max_full,min_full;

#define flush10(f) {fprintf(f,"\n");fflush(f);}

inline void bmp2data(std::string pth,int offseta=2,int offsetb=7){
    offsetA=offseta;
    offsets=offsetb-offseta+1;
    for(auto j=L;j<=R;j++)
        ss[ssr++]=j;

    FILE*f=fopen(pth.c_str(),"w");
    BMP24bits*p;
    half=0;
    for(auto i=0;i<offsets;i++){
        printf("%d\n",i+offseta);
        for(auto j=0;j<ssr;j++){
            std::string str="./Char/";
            str+=std::to_string(ss[j]);
            str+='_';
            str+=std::to_string(i+offseta);
            str+=".bmp";
            p=new BMP24bits(str);
            if(!half){
                half=p->size>>1;
                fprintf(f,"%d %d %d %d\n",offsets,offseta,ssr,half);
                for(auto k=0;k<ssr;k++)
                    fprintf(f,"%d ",ss[k]);
                flush10(f);
            }

            LL s1=0,s0=0;
            for(auto x=0;x<half;x++)
                s1+=p->getb(x);
            for(auto x=half;x<half<<1;x++)
                s0+=p->getb(x);
            delete p;

            m[i][j][0]=s0;
            m[i][j][1]=s1;
            max_split[i]=mx(max_split[i],s0);
            max_split[i]=mx(max_split[i],s1);
            min_split[i]=mn(min_split[i],s0);
            min_split[i]=mn(min_split[i],s1);
            if(!i){
                const LL s2=s0+s1;
                max_full=mx(max_full,s2);
                min_full=mn(min_full,s2);
            }
            fprintf(f,"%d %d %lld %lld",i+offseta,ss[j],s0,s1);
            flush10(f);
        }
    }
    pt(10);
}

/*
\begin{aligned}
    \frac{v-\min}{\max-\min}&=\frac{c-{\rm black}}{{\rm white}-{\rm black}},\\
    \frac{v-\min}{L_v}&=\frac{c'}{L_c},\\
    (v-\min)L_c&=L_vc',\\
    vL_c&=L_vc'+\min L_c,\\
    d&=|v'-v|,\\
    (v'-v)L_c&=v'L_c-vL_c\\
        &=v'L_c-(L_vc'+\min L_c)\\
        &=V-{\rm ext},\\
    d'&=dL_c\\
        &=|v'-v|L_c\\
        &=|V-{\rm ext}|\\
        &=V<{\rm ext}?{\rm ext}-V:V-{\rm ext}.\\
\end{aligned}
*/

int ans_full[MAXCOL],ans_split[MAXO][MAXCOL][MAXCOL];

inline void data2map(std::string pth,B white=0xff,B black=0x00,std::string pth_in=""){
    WHITE=white;BLACK=black;LC=WHITE-BLACK;
    if(pth_in.size()){
        FILE*f=fopen(pth_in.c_str(),"r");
        fscanf(f,"%d%d%d%d",&offsets,&offsetA,&ssr,&half);
        for(auto j=0;j<ssr;j++)
            fscanf(f,"%d",&ss[j]);
        for(auto i=0;i<offsets;i++)
            for(auto j=0;j<ssr;j++){
                int _i,_j;
                LL s0,s1;
                fscanf(f,"%d%d%lld%lld",&_i,&_j,&s0,&s1);

                m[i][j][0]=s0;
                m[i][j][1]=s1;
                max_split[i]=mx(max_split[i],s0);
                max_split[i]=mx(max_split[i],s1);
                min_split[i]=mn(min_split[i],s0);
                min_split[i]=mn(min_split[i],s1);
                if(!i){
                    const LL s2=s0+s1;
                    max_full=mx(max_full,s2);
                    min_full=mn(min_full,s2);
                }
            }
        fclose(f);
    }

    FILE*f=fopen(pth.c_str(),"w");
    fprintf(f,"%d %d %d %d %d\n",offsets,offsetA,ssr,WHITE,BLACK);
    for(auto k=0;k<ssr;k++)
        fprintf(f,"%d ",ss[k]);
    flush10(f);

    // full
    LL lv=max_full-min_full;
    for(auto c=0;c<=LC;c++){
        int mnc;
        LL mnl=lv<<8;
        const LL ext=min_full*LC+lv*c;
        for(auto j=0;j<ssr;j++){
            LL v=(m[0][j][0]+m[0][j][1])*LC;
            v=v<ext?ext-v:v-ext;
            if(v<mnl)mnl=v,mnc=ss[j];
        }
        ans_full[c+WHITE]=mnc;
        fprintf(f,"%d ",mnc);
    }flush10(f);

    // split
    for(auto i=0;i<offsets;i++){
        lv=max_split[i]-min_split[i];
        for(auto c=0;c<=LC;c++){
            const LL ext=min_split[i]*LC+lv*c;
            for(auto c2=0;c2<=LC;c2++){
                int mnc;
                LL mnl=lv<<8;
                const LL ext2=min_split[i]*LC+lv*c2;
                for(auto j=0;j<ssr;j++){
                    LL v=m[i][j][0]*LC;
                    v=absub(v,ext);
                    LL v2=m[i][j][1]*LC;
                    v+=absub(v2,ext2);
                    if(v<mnl)mnl=v,mnc=ss[j];
                }
                ans_split[i][c+WHITE][c2+WHITE]=mnc;
                fprintf(f,"%d ",mnc);
            }flush10(f);
        }
    }
}

inline void map2show(std::string pth,std::string pth_in=""){
    if(pth_in.size()){
        FILE*f=fopen(pth_in.c_str(),"r");
        fscanf(f,"%d%d%d%d%d",&offsets,&offsetA,&ssr,&WHITE,&BLACK);
        LC=WHITE-BLACK;
        for(auto j=0;j<ssr;j++)fscanf(f,"%d",&ss[j]);
        for(auto c=0;c<=LC;c++)fscanf(f,"%d",&ans_full[c+WHITE]);
        for(auto i=0;i<offsets;i++)
            for(auto c=0;c<=LC;c++)for(auto c2=0;c2<=LC;c2++)
                fscanf(f,"%d",&ans_split[i][c+WHITE][c2+WHITE]);
        fclose(f);
    }

    FILE*f=fopen(pth.c_str(),"w");
    for(auto c=0;c<=LC>>1;c++){
        for(auto c2=0;c2<=LC;c2++)
            fprintf(f,"%c",ans_full[c2+WHITE]);
        flush10(f);
    }flush10(f);

    for(auto i=0;i<offsets;i++){
        for(auto c=0;c<=LC;c++){
            for(auto c2=0;c2<=LC;c2++)
                fprintf(f,"%c%c",ans_split[i][c+WHITE][c2+WHITE],ans_split[i][c+WHITE][c2+WHITE]);
            flush10(f);
        }flush10(f);
    }

}