#pragma once

#if defined(__WINDOWS_) || defined(_WIN32)
#include <Windows.h>
#else
#include <unistd.h>
#endif

inline void second_sleep(int x) {
#if defined(__WINDOWS_) || defined(_WIN32)
    Sleep(x * 1000);
#else
    sleep(x);
#endif
}

inline std::string background_process(std::string command) {
#if defined(__WINDOWS_) || defined(_WIN32)
    return "start /B " + command;
#else
    return command + " &";
#endif
}

inline FILE* r_popen(const char* cmd) {
#if defined(__WINDOWS_) || defined(_WIN32)
    return _popen(cmd, "r");
#else
    return popen(cmd, "r");
#endif
}

inline FILE* r_popen(std::string cmd) {
    return r_popen(cmd.c_str());
}

inline FILE* rb_popen(const char* cmd) {
#if defined(__WINDOWS_) || defined(_WIN32)
    return _popen(cmd, "rb");
#else
    return popen(cmd, "r");
#endif
}

inline FILE* rb_popen(std::string cmd) {
    return rb_popen(cmd.c_str());
}

inline void pipe_pclose(FILE* pipe) {
#if defined(__WINDOWS_) || defined(_WIN32)
    _pclose(pipe);
#else
    pclose(pipe);
#endif
}
