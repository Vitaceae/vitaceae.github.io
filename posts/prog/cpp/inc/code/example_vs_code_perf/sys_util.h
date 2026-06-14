/**
 * Copyright (C) 2018 Dexatek Technology Ltd.
 *
 * sys_def.h
 *
 * This is proprietary information of Dexatek Technology Ltd. All Rights
 * Reserved. Reproduction of this documentation or the accompanying programs in
 * any manner whatsoever without the written permission of Dexatek Technology
 * Ltd. is strictly forbidden.
 */

#ifndef SYS_UTIL_H
#define SYS_UTIL_H

#ifndef container_of
/* gcc-specific implementation
#define container_of(ptr, type, member) ({                          \
            const typeof( ((type *)0)->member ) *__mptr = (ptr);    \
            (type *)( (char *)__mptr - offsetof(type, member)       \
        );})
*/
#define container_of(ptr, type, member) \
            ((type *)((char *)(ptr)-(size_t)(&((type *)0)->member)))
#endif

#ifndef offsetof
#define offsetof(s, m) \
            (size_t)&(((s *)0)->m)
#endif

#ifndef ARRAY_SIZE
#define ARRAY_SIZE(arr) \
            (sizeof(arr) / sizeof((arr)[0]))
#endif

#endif //SYS_UTIL_H
