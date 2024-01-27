#include "clplayer.hpp"

void test(Cmd* c) {
    printf("new %s\n", c->name);
    printf("code %d\n", c->start());
    printf("wait %.6lf\n", c->wait(3));
    printf("end %d\n\n", c->terminate());
}

int main() {
    std::string audio = "../archive/badapple.mp3";
    test(new FFplayPlayer(audio));
    test(new MpvPlayer(audio));
    test(new Mpg123Player(audio));
    test(new CmusPlayer(audio));
    return 0;
}
