#ifndef MEMORY_USED_H
#define MEMORY_USED_H

#include <cstdio>

#ifdef __linux__
    #include <sys/sysinfo.h>
    #include <unistd.h>
#endif

#ifdef __APPLE__
    #include <mach/task.h>
    #include <mach/mach_init.h>
#endif

#ifdef _WINDOWS
    #include <windows.h>
#else
    #include <unistd.h>
#endif

/// The amount of memory currently being used by this process, in bytes.
/// By default, returns the full virtual arena, but if resident=true,
/// it will report just the resident set in RAM (if supported on that OS).
size_t memory_used (bool resident);

#endif /*MEMORY_USED_H*/