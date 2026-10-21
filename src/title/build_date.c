#include "types.h"
#include "title.h"

// The ROM's build date in __DATE__ format. No reader was found; the main
// menu presumably showed it in development builds.
#ifdef VERSION_JP
const char g_szBuildDate[] = "Apr 12 2004";
#else
const char g_szBuildDate[] = "Apr  5 2004";
#endif
