#pragma once

#if defined(__WINDOWS_) || defined(_WIN32) || defined(_WIN64)
#include <Windows.h>
#else
#include <unistd.h>
#include <sys/ioctl.h>
#endif

inline std::string short_isa_name() {
#if defined(__x86_64__) || defined(_M_X64)
    return "x86_64";
#elif defined(i386) || defined(__i386__) || defined(__i386) || defined(_M_IX86)
    return "x86_32";
#elif defined(__ARM_ARCH_2__)
    return "ARM2";
#elif defined(__ARM_ARCH_3__) || defined(__ARM_ARCH_3M__)
    return "ARM3";
#elif defined(__ARM_ARCH_4T__) || defined(__TARGET_ARM_4T)
    return "ARM4T";
#elif defined(__ARM_ARCH_5_) || defined(__ARM_ARCH_5E_)
    return "ARM5"
#elif defined(__ARM_ARCH_6T2_) || defined(__ARM_ARCH_6T2_)
    return "ARM6T2";
#elif defined(__ARM_ARCH_6__) || defined(__ARM_ARCH_6J__) || defined(__ARM_ARCH_6K__) || defined(__ARM_ARCH_6Z__) || defined(__ARM_ARCH_6ZK__)
    return "ARM6";
#elif defined(__ARM_ARCH_7__) || defined(__ARM_ARCH_7A__) || defined(__ARM_ARCH_7R__) || defined(__ARM_ARCH_7M__) || defined(__ARM_ARCH_7S__)
    return "ARM7";
#elif defined(__ARM_ARCH_7A__) || defined(__ARM_ARCH_7R__) || defined(__ARM_ARCH_7M__) || defined(__ARM_ARCH_7S__)
    return "ARM7A";
#elif defined(__ARM_ARCH_7R__) || defined(__ARM_ARCH_7M__) || defined(__ARM_ARCH_7S__)
    return "ARM7R";
#elif defined(__ARM_ARCH_7M__)
    return "ARM7M";
#elif defined(__ARM_ARCH_7S__)
    return "ARM7S";
#elif defined(__aarch64__) || defined(_M_ARM64)
    return "ARM64";
#elif defined(mips) || defined(__mips__) || defined(__mips)
    return "MIPS";
#elif defined(__sh__)
    return "SUPERH";
#elif defined(__powerpc) || defined(__powerpc__) || defined(__powerpc64__) || defined(__POWERPC__) || defined(__ppc__) || defined(__PPC__) || defined(_ARCH_PPC)
    return "POWERPC";
#elif defined(__PPC64__) || defined(__ppc64__) || defined(_ARCH_PPC64)
    return "POWERPC64";
#elif defined(__sparc__) || defined(__sparc)
    return "SPARC";
#elif defined(__m68k__)
    return "M68K";
#else
    return "unknown";
#endif
}

inline std::string short_os_name() {
#if defined(__WINDOWS_) || defined(_WIN32) || defined(_WIN64)
    return "Windows";
#elif defined(__linux__)
    return "Linux";
#elif defined(__APPLE__) || defined(__MACH__)
    return "MacOSX";
#elif defined(__FreeBSD__)
    return "FreeBSD";
#elif defined(__unix) || defined(__unix__)
    return "Unix";
#else
    return "unknown";
#endif
}

inline void second_sleep(int x) {
#if defined(__WINDOWS_) || defined(_WIN32) || defined(_WIN64)
    Sleep(x * 1000);
#else
    sleep(x);
#endif
}

inline std::string background_process(std::string command) {
#if defined(__WINDOWS_) || defined(_WIN32) || defined(_WIN64)
    return "start /B " + command;
#else
    return command + " &";
#endif
}

inline FILE* r_popen(const char* cmd) {
#if defined(__WINDOWS_) || defined(_WIN32) || defined(_WIN64)
    return _popen(cmd, "r");
#else
    return popen(cmd, "r");
#endif
}

inline FILE* r_popen(std::string cmd) {
    return r_popen(cmd.c_str());
}

inline FILE* rb_popen(const char* cmd) {
#if defined(__WINDOWS_) || defined(_WIN32) || defined(_WIN64)
    return _popen(cmd, "rb");
#else
    return popen(cmd, "r");
#endif
}

inline FILE* rb_popen(std::string cmd) {
    return rb_popen(cmd.c_str());
}

inline void pipe_pclose(FILE* pipe) {
#if defined(__WINDOWS_) || defined(_WIN32) || defined(_WIN64)
    _pclose(pipe);
#else
    pclose(pipe);
#endif
}

inline int get_console_size() {
#if defined(__WINDOWS_) || defined(_WIN32) || defined(_WIN64)
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    int ret = GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    if (ret) {
        return ((int)csbi.dwSize.Y) << 16 | ((int)csbi.dwSize.X);
    }
#else
    struct winsize csbi;
    ioctl(0, TIOCGWINSZ, &csbi);
    return ((int)csbi.ws_row) << 16 | ((int)csbi.ws_col);
#endif
    return 0;
}
