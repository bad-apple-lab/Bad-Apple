#include "player_win.hpp"

void test(Cmd* c) {
    printf("new\n");
    printf("code (%d)\n", c->start());
    printf("wait %.6lf\n", c->wait(3));
    printf("end %d\n", c->terminate());
}

int main() {
    std::string audio = "../badapple.mp4";
    test(ffplay(audio));
    test(new FFplay(audio));

    std::string cmd = "ffplay.exe -v quiet -nodisp -autoexit -hide_banner \"";
    cmd += audio + "\"";
    test(new Cmd(cmd));
    return 0;
}
