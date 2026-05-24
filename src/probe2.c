#include <psp2/types.h>
#include <psp2/kernel/clib.h>
#include <psp2/kernel/threadmgr.h>

// Some taiHEN user plugins use this weak alias so the loader can find the entry.
void _start() __attribute__ ((weak, alias ("module_start")));

static volatile int g_running = 0;
static SceUID g_thread = -1;

static int heartbeat_thread(SceSize args, void *argp) {
    int counter = 0;

    sceClibPrintf("[probe2_plog] heartbeat thread started args=0x%X argp=0x%08X\n",
                  (unsigned int)args, (unsigned int)argp);

    while (g_running) {
        sceClibPrintf("[probe2_plog] module_start alive tick=%d\n", counter++);
        sceKernelDelayThread(1000 * 1000); // 1 second
    }

    sceClibPrintf("[probe2_plog] heartbeat thread stopping\n");
    return 0;
}

int module_start(SceSize argc, const void *args) {
    sceClibPrintf("[probe2_plog] module_start ENTER argc=0x%X args=0x%08X\n",
                  (unsigned int)argc, (unsigned int)args);

    g_running = 1;
    g_thread = sceKernelCreateThread(
        "probe2_heartbeat",
        heartbeat_thread,
        0x10000100,
        0x10000,
        0,
        0,
        NULL
    );

    sceClibPrintf("[probe2_plog] sceKernelCreateThread ret=0x%08X\n", (unsigned int)g_thread);

    if (g_thread >= 0) {
        int ret = sceKernelStartThread(g_thread, 0, NULL);
        sceClibPrintf("[probe2_plog] sceKernelStartThread ret=0x%08X\n", (unsigned int)ret);
    }

    sceClibPrintf("[probe2_plog] module_start LEAVE ret=0\n");
    return 0;
}

int module_stop(SceSize argc, const void *args) {
    sceClibPrintf("[probe2_plog] module_stop ENTER argc=0x%X args=0x%08X\n",
                  (unsigned int)argc, (unsigned int)args);

    g_running = 0;
    // Do not block module_stop waiting forever; the heartbeat thread exits after at most ~1 second.

    sceClibPrintf("[probe2_plog] module_stop LEAVE ret=0\n");
    return 0;
}
