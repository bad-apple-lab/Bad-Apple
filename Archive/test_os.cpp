#include<bits/stdc++.h>

inline int is_posix(){
    #if defined(__WINDOWS_) || defined(_WIN32)
        return 0;
    #else
        return 1;
    #endif
}

int main(){
    printf(is_posix()?"*nux\n":"win\n");
}
