#pragma once
#define YLOG_LEVEL 5

#ifdef RELEASE_BUILD
#define _HOW_YTRACE "{:>10} >>> {}\n", "[TRACE]"
#define _HOW_YINFO _YLOG_GREEN "{:>10} >>> {}\n" _YLOG_COLOR_RESET, "[INFO]"
#define _HOW_YWARN _YLOG_YELLOW "{:>10} >>> {}\n" _YLOG_COLOR_RESET, "[WARN]"
#define _HOW_YERROR _YLOG_RED "{:>10} >>> {}\n" _YLOG_COLOR_RESET, "[ERROR]"
#define _HOW_YCRITICAL _YLOG_MAGENTA "{:>10} >>> {}\n" _YLOG_COLOR_RESET, "[CRITICAL]"
#endif

#include <Yutils/Logger.hpp>
