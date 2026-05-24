# probe2_plog_heartbeat

Minimal taiHEN user plugin load probe for PrincessLog/PLog.

It does not hook anything, does not write files, and does not read app0:param.sfo. `module_start` starts a thread that prints one `sceClibPrintf` line every second.

Install:

```txt
*KERNEL
ur0:tai/net_logging_mgr.skprx

*PCSG00005
ur0:tai/probe2_plog_heartbeat.suprx
```

Expected log:

```txt
[probe2_plog] module_start ENTER ...
[probe2_plog] sceKernelCreateThread ret=...
[probe2_plog] sceKernelStartThread ret=...
[probe2_plog] module_start LEAVE ret=0
[probe2_plog] module_start alive tick=0
[probe2_plog] module_start alive tick=1
```
