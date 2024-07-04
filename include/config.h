#pragma once
#ifndef CONFIG_H
#define CONFIG_H

#if defined(__x86_64__)
#define IS_X86_64 1
#define IS_ARM_64 0
#elif defined (__aarch64__) || defined(__ARM_ARCH) || defined(__ARM_ARCH_64)
#define IS_X86_64 0
#define IS_ARM_64 1
#endif


#endif // !CONFIG_H
