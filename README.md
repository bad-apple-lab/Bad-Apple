## Bad Apple!!

视频转字符画工具.

最高支持到 **1080p30Hz**, 瓶颈是 **IO**.

##### 编译

```sh
clang 'play.c' -o 'play.exe' -Wall -g -O2 -static-libgcc --target=x86_64-w64-mingw -std=c11
```

##### 测试环境

**5950x**, **3080ti**, **Windows 10 Pro N for Workstations 21H2**, **Windows Terminal**.
