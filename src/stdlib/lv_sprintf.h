/**
 * lv_snprintf.h
 *
 */

#ifndef _LV_SPRINTF_H_
#define _LV_SPRINTF_H_

#if defined(__has_include)
    #if __has_include(<inttypes.h>)
        #include <inttypes.h>
        /* platform-specific printf format for int32_t, usually "d" or "ld" */
        #define LV_PRId32 PRId32
        #define LV_PRIu32 PRIu32
        #define LV_PRIx32 PRIx32
        #define LV_PRIX32 PRIX32
    #else
        #define LV_PRId32 "d"
        #define LV_PRIu32 "u"
        #define LV_PRIx32 "x"
        #define LV_PRIX32 "X"
    #endif
#else
    /* hope this is correct for ports without __has_include or without inttypes.h */
    #define LV_PRId32 "d"
    #define LV_PRIu32 "u"
    #define LV_PRIx32 "x"
    #define LV_PRIX32 "X"
#endif

#ifdef __cplusplus
extern "C" {
#endif


#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif  /* _LV_SPRINTF_H_*/
