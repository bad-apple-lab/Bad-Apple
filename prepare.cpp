// code by userElaina
#include "prepare.hpp"

int main(){
    bmp2data("./consola_ascii.data",2,7);
    data2map("./consola_ascii_00ff.data");
    map2show("./consola_ascii_00ff.show");
}
