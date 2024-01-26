#include <cstdio>
#include <chrono>
#include <windows.h>

#define LL long long

class Cmd {
private:
    PROCESS_INFORMATION p;
    LL clk;  // microseconds

    inline LL micros(double s) {
        return s * 1000000.0 + 0.5;
    }

    inline LL now(std::chrono::steady_clock::time_point t) {
        return std::chrono::duration_cast<std::chrono::microseconds>(
                   std::chrono::steady_clock::now() - t)
            .count();
    }

public:
    std::string cmd;

    Cmd(std::string _cmd, double _clk = 0.1) : cmd(_cmd), clk(micros(_clk)) {}

    virtual int inline start() {
        // printf("%s\n", cmd.c_str());
        LPWSTR w;
        WCHAR _wt[265];
        mbstowcs(_wt, cmd.c_str(), cmd.length() + 1);
        w = _wt;
        STARTUPINFOW s;
        ZeroMemory(&s, sizeof(s));
        s.cb = sizeof(s);
        ZeroMemory(&p, sizeof(p));
        if (!CreateProcessW(NULL, w, NULL, NULL, 0, 0, NULL, NULL, &s, &p)) {
            return GetLastError();
        }
        return 0;
    }

    virtual int inline run() {
        start();
        wait();
    }

    virtual int inline is_alive() {
        DWORD lpExitCode = 0;
        int code = GetExitCodeProcess(p.hProcess, &lpExitCode);
        return lpExitCode == STILL_ACTIVE;
    }

    virtual int inline terminate() {
        /*
        DWORD lpExitCode = 0;
        int code = GetExitCodeProcess(p.hProcess, &lpExitCode);
        if (code) {
            if (lpExitCode == STILL_ACTIVE) {
                TerminateProcess(p.hProcess, 0);
            }
            CloseHandle(p.hProcess);
            CloseHandle(p.hThread);
        }
        return 0;
        */
        return kill();
    }

    virtual int inline kill() {
        TerminateProcess(p.hProcess, 0);
        CloseHandle(p.hProcess);
        CloseHandle(p.hThread);
        return 0;
    }

    virtual double inline wait(double s = -1.) {
        std::chrono::steady_clock::time_point t = std::chrono::steady_clock::now();
        if (s < 0.) {
            WaitForSingleObject(p.hProcess, INFINITE);
        } else {
            LL mms = micros(s);
            while (now(t) < mms && is_alive())
                ;
        }
        terminate();
        return now(t) / 1000000.0;
    }
};

class FFplay : public Cmd {
public:
    FFplay(std::string audio, double clk = 0.1) : Cmd(audio, clk) {
        cmd = "ffplay.exe -v quiet -nodisp -autoexit -hide_banner \"";
        cmd += audio + "\"";
    }
};

Cmd *ffplay(std::string audio, double _clk = 0.1) {
    std::string cmd = "ffplay.exe -v quiet -nodisp -autoexit -hide_banner \"";
    cmd += audio + "\"";
    Cmd *c = new Cmd(cmd, _clk);
    return c;
}
