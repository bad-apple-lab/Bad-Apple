// code by userElaina
#include "bmp24bits.hpp"

const int L=0x20,R=0x7e;
const int MAXCOL=0x100;
const int MAXCHAR=0x100;
const int MAXO=0x16;
int ss[MAXCHAR],ssr=0,offsets,offsetA,half;
int WHITE=0xff,BLACK=0x00,LC=WHITE-BLACK;
LL m[MAXO][MAXCHAR][2],w[MAXO][2],b[MAXO][2];

inline void bmp2data(std::string pth,int offseta=2,int offsetb=7){
    offsetA=offseta;
    offsets=offsetb-offseta+1;
    for(auto j=L;j<=R;j++){
        ss[ssr++]=j;
    }

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
                if(half^3932160){printf("%d\n",half);exit(0);}
                fprintf(f,"%d %d %d %d\n",offsets,offseta,ssr,half);
                for(auto k=0;k<ssr;k++){
                    fprintf(f,"%d ",ss[k]);
                }
                fprintf(f,"\n");
                fflush(f);
            }

            LL s1=0,s0=0;
            for(auto x=0;x<half;x++)
                s1+=p->getb(x);
            for(auto x=half;x<half<<1;x++)
                s0+=p->getb(x);
            delete p;

            m[i][j][0]=s0;
            m[i][j][1]=s1;
            w[i][0]=mx(w[i][0],s0);
            w[i][0]=mx(w[i][0],s1);
            w[i][1]=mx(w[i][1],s0+s1);
            b[i][0]=mn(b[i][0],s0);
            b[i][0]=mn(b[i][0],s1);
            b[i][1]=mn(b[i][1],s0+s1);
            // split full
            
            fprintf(f,"%d %d %lld %lld\n",i+offseta,ss[j],s0,s1);
            fflush(f);
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

int ans_full[MAXO][MAXCOL],ans_split[MAXO][MAXCOL][MAXCOL];

inline void data2map(std::string pth,B white=0xff,B black=0x00,std::string pth_in=""){
    WHITE=white;BLACK=black;LC=WHITE-BLACK;
    if(pth_in.size()){
        FILE*f=fopen(pth_in.c_str(),"r");
        fscanf(f,"%d%d%d%d",&offsets,&offsetA,&ssr,&half);
        for(auto j=0;j<ssr;j++){
            fscanf(f,"%d",&ss[j]);
        }
        for(auto i=0;i<offsets;i++){
            for(auto j=0;j<ssr;j++){
                int _i,_j;
                LL s0,s1;
                fscanf(f,"%d%d%lld%lld",&_i,&_j,&s0,&s1);

                m[i][j][0]=s0;
                m[i][j][1]=s1;
                w[i][0]=mx(w[i][0],s0);
                w[i][0]=mx(w[i][0],s1);
                w[i][1]=mx(w[i][1],s0+s1);
                b[i][0]=mn(b[i][0],s0);
                b[i][0]=mn(b[i][0],s1);
                b[i][1]=mn(b[i][1],s0+s1);
            }
        }
        fclose(f);
    }

    FILE*f=fopen(pth.c_str(),"w");
    fprintf(f,"%d %d %d %d %d\n",offsets,offsetA,ssr,WHITE,BLACK);
    for(auto k=0;k<ssr;k++){
        fprintf(f,"%d ",ss[k]);
    }
    fprintf(f,"\n");
    fflush(f);
    for(auto i=0;i<offsets;i++){
        const LL lv_split=w[i][0]-b[i][0];
        const LL lv_full=w[i][1]-b[i][1];
        const LL min_split=b[i][0];
        const LL min_full=b[i][1];
        // split full

        // full
        for(auto c=0;c<=LC;c++){
            int mnc;
            LL mnl=lv_full<<8;
            const LL ext=min_full*LC+lv_full*c;
            for(auto j=0;j<ssr;j++){
                LL v=(m[i][j][0]+m[i][j][1])*LC;
                v=v<ext?ext-v:v-ext;
                if(v<mnl)mnl=v,mnc=ss[j];
            }
            fprintf(f,"%d ",mnc);
            ans_full[i][c+WHITE]=mnc;
        }
        fprintf(f,"\n");
        fflush(f);

        // split
        for(auto c=0;c<=LC;c++){
            const LL ext=min_split*LC+lv_split*c;
            for(auto c2=0;c2<=LC;c2++){
                int mnc;
                LL mnl=lv_split<<8;
                const LL ext2=min_split*LC+lv_split*c2;
                for(auto j=0;j<ssr;j++){
                    LL v=m[i][j][0]*LC;
                    v=v<ext?ext-v:v-ext;
                    LL v2=m[i][j][1]*LC;
                    v+=v2<ext2?ext2-v2:v2-ext2;
                    if(v<mnl)mnl=v,mnc=ss[j];
                }
                fprintf(f,"%d ",mnc);
                ans_split[i][c+WHITE][c2+WHITE]=mnc;
            }
            fprintf(f,"\n");
            fflush(f);
        }
    }
}

inline void map2show(std::string pth,std::string pth_in=""){
    if(pth_in.size()){
        FILE*f=fopen(pth_in.c_str(),"r");
        fscanf(f,"%d%d%d%d",&offsets,&offsetA,&ssr,&half,&WHITE,&BLACK);
        LC=WHITE-BLACK;
        for(auto j=0;j<ssr;j++){
            fscanf(f,"%d",&ss[j]);
        }
        for(auto i=0;i<offsets;i++){
            for(auto c=0;c<=LC;c++){
                fscanf(f,"%d",ans_full[i][c+WHITE]);
            }
            for(auto c=0;c<=LC;c++){
                for(auto c2=0;c2<=LC;c2++){
                    fscanf(f,"%d",ans_split[i][c+WHITE][c2+WHITE]);
                }
            }
        }
        fclose(f);
    }
    FILE*f=fopen(pth.c_str(),"w");
    for(auto i=0;i<offsets;i++){
        for(auto c=0;c<=LC;c++){
            fprintf(f,"%c",ans_full[i][c+WHITE]);
        }
        fprintf(f,"\n");
        fflush(f);
    }
    fprintf(f,"\n\n");
    fflush(f);

    for(auto i=0;i<offsets;i++){
        for(auto c=0;c<=LC;c++){
            for(auto c2=0;c2<=LC;c2++){
                fprintf(f,"%c",ans_split[i][c+WHITE][c2+WHITE]);
            }
            fprintf(f,"\n");
            fflush(f);
        }
        fprintf(f,"\n");
        fflush(f);
    }


}