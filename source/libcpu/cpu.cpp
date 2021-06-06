//
// This file is subject to the terms and conditions defined in
// file 'LICENSE', which is part of this source code package.
//
#include <cstdio>
#include <cstring>
#include <cstdint>

#if defined(_MSC_VER)
#include <intrin.h>
#elif defined(__GNUC__)
#include <cpuid.h>
#endif

#include "cpu.h"

using namespace std;
using namespace libcpu;

static void get_cpuid(int[4], int);
static void get_cpuidex(int[4], int, int);
static int detect_stdlevel_00000000(Cpu *);
static void detect_stdlevel_00000001(Cpu *);
static void detect_stdlevel_00000002(Cpu *);
static void detect_stdlevel_00000003(Cpu *);
static void detect_stdlevel_00000004(Cpu *);
static void detect_stdlevel_00000005(Cpu *);
static void detect_stdlevel_00000006(Cpu *);
static void detect_stdlevel_00000007(Cpu *);
//static void detect_stdlevel_00000008(Cpu *);
static void detect_stdlevel_00000009(Cpu *);
static void detect_stdlevel_0000000A(Cpu *);
static void detect_stdlevel_0000000B(Cpu *);
static void detect_stdlevel_00000016(Cpu *);
static int detect_extlevel_80000000(Cpu *);
static void detect_extlevel_80000001(Cpu *);
static void detect_extlevel_80000002(Cpu *);
static void detect_extlevel_80000003(Cpu *);
static void detect_extlevel_80000004(Cpu *);
static void detect_extlevel_80000005(Cpu *);
static void detect_extlevel_80000006(Cpu *);
static void detect_extlevel_80000008(Cpu *);
static void detect_extlevel_8000000A(Cpu *);
static void detect_extlevel_8000001A(Cpu *);
static void detect_stdlevel_00000002_partial(Cpu *, uint8_t);

void libcpu::detect_cpu_info(Cpu *cpu)
{
  int stdLevel, extLevel;

  stdLevel = detect_stdlevel_00000000(cpu);

  if (stdLevel >= 0x000000001)
    detect_stdlevel_00000001(cpu);

  if (stdLevel >= 0x000000002)
    detect_stdlevel_00000002(cpu);

  if (stdLevel >= 0x000000003)
    detect_stdlevel_00000003(cpu);

  if (stdLevel >= 0x000000004)
    detect_stdlevel_00000004(cpu);

  if (stdLevel >= 0x000000005)
    detect_stdlevel_00000005(cpu);

  if (stdLevel >= 0x000000006)
    detect_stdlevel_00000006(cpu);

  if (stdLevel >= 0x000000007)
    detect_stdlevel_00000007(cpu);

  // EAX=0x8: Reserved

  if (stdLevel >= 0x000000009)
    detect_stdlevel_00000009(cpu);

  if (stdLevel >= 0x00000000A)
    detect_stdlevel_0000000A(cpu);

  if (stdLevel >= 0x00000000B)
    detect_stdlevel_0000000B(cpu);

  // EAX=0x0C: Processor Extended State Enumeration Main

  // EAX=0x0D: Extended State Enumeration Sub

  // EAX=0x0E: Reserved

  // EAX=0x0F: Platform QoS Monitoring Enumeration Sub

  // EAX=0x10: Platform QoS Enforcement Enumeration Sub

  // EAX=0x11: Reserved

  // EAX=0x12: Reserved

  // EAX=0x13: Reserved

  // EAX=0x14: Intel Processor Trace Enumeration Main

  // EAX=0x15: Time Stamp Counter and Core Crystal Clock Information

  if (stdLevel >= 0x16)
    detect_stdlevel_00000016(cpu);

  // EAX=0x17: System-On-Chip Vendor Attribute Enumeration Main

  // EAX=0x18: Deterministic Address Translation Parameters Main

  extLevel = detect_extlevel_80000000(cpu);

  if (extLevel >= static_cast<int>(0x80000001))
    detect_extlevel_80000001(cpu);

  if (extLevel >= static_cast<int>(0x80000002))
    detect_extlevel_80000002(cpu);

  if (extLevel >= static_cast<int>(0x80000003))
    detect_extlevel_80000003(cpu);

  if (extLevel >= static_cast<int>(0x80000004))
    detect_extlevel_80000004(cpu);

  if (extLevel >= static_cast<int>(0x80000005))
    detect_extlevel_80000005(cpu);

  if (extLevel >= static_cast<int>(0x80000006))
    detect_extlevel_80000006(cpu);

  if (extLevel >= static_cast<int>(0x80000008))
    detect_extlevel_80000008(cpu);

  if (extLevel >= static_cast<int>(0x8000000a))
    detect_extlevel_8000000A(cpu);

  if (extLevel >= static_cast<int>(0x8000001a))
    detect_extlevel_8000001A(cpu);
}


void libcpu::print_cpuid()
{
  Cpu tmpCpu;
  int stdLevel, extLevel;
  int cpuInfo[4];

  stdLevel = detect_stdlevel_00000000(&tmpCpu);

  printf("%-8s %-8s %-8s %-8s %-8s\n", "Level", "EAX", "EBX", "ECX", "EDX");
  for (int i = 0; i <= stdLevel; ++i)
  {
    get_cpuid(cpuInfo, i);
    printf("%08x %08x %08x %08x %08x\n", i, cpuInfo[0], cpuInfo[1], cpuInfo[2],
           cpuInfo[3]);
  }

  extLevel = detect_extlevel_80000000(&tmpCpu);
  for (int i = 0x80000000; i <= extLevel; ++i)
  {
    get_cpuid(cpuInfo, i);
    printf("%08x %08x %08x %08x %08x\n", i, cpuInfo[0], cpuInfo[1], cpuInfo[2],
           cpuInfo[3]);
  }
}


//!
//! @brief read cpu id
//!
//! @param[out]   info    EAX, EBX, ECX, and EDX
//! @param[in]    id      function id
//!
static void get_cpuid(int info[4], int id)
{
#if defined(_MSC_VER)
  __cpuid(info, id);
#elif defined(__GNUC__)
  __cpuid(id, info[0], info[1], info[2], info[3]);
#endif
}


//!
//! @brief read cpu id
//!
//! @param[out]   info    EAX, EBX, ECX, and EDX
//! @param[in]    id      id
//! @param[in]    subId   sub functional id
//!
static void get_cpuidex(int info[4], int id, int subId)
{
#if defined(_MSC_VER)
  __cpuidex(info, id, subId);
#elif defined(__GNUC__)
  __cpuid_count(id, subId, info[0], info[1], info[2], info[3]);
#endif
}


//!
//! @brief EAX=0x0: Maximum supported standard level and vendor ID string
//!
//! @return standard level
//!
static int detect_stdlevel_00000000(Cpu *cpu)
{
  int stdLevel, eax, ebx, ecx, edx;
  int cpuInfo[4];

  get_cpuid(cpuInfo, 0);
  eax = cpuInfo[0];
  ebx = cpuInfo[1];
  ecx = cpuInfo[2];
  edx = cpuInfo[3];

  stdLevel = eax;
  memcpy(&cpu->vendor[0], &ebx, sizeof(ebx));
  memcpy(&cpu->vendor[4], &edx, sizeof(edx));
  memcpy(&cpu->vendor[8], &ecx, sizeof(ecx));

  return stdLevel;
}


//!
//! @brief EAX=0x1: Processor Info and Feature Bits
//!
static void detect_stdlevel_00000001(Cpu *cpu)
{
  int eax, ebx, ecx, edx;
  int cpuInfo[4];

  get_cpuid(cpuInfo, 1);
  eax = cpuInfo[0];
  ebx = cpuInfo[1];
  ecx = cpuInfo[2];
  edx = cpuInfo[3];

  // eax
  cpu->stepping                         = (eax >>  0) & 0x0f;
  cpu->model                            = (eax >>  4) & 0x0f;
  cpu->family                           = (eax >>  8) & 0x0f;
  cpu->processorType                    = (eax >> 12) & 0x03;
  /* 14-15 reserve */
  cpu->extModel                         = (eax >> 16) & 0x0f;
  cpu->extFamily                        = (eax >> 20) & 0xff;
  /* 28-31 reserve */

  // ebx
  cpu->brandIdx                         = (ebx >>  0) & 0xff;
  cpu->clflashChunkCount                = (ebx >>  8) & 0xff;
  cpu->logicalProcessors                = (ebx >> 16) & 0xff;
  cpu->apicId                           = (ebx >> 24) & 0xff;

  // ecx
  cpu->sse3                             = (ecx & 0x00000001) || false;
  cpu->pclmulqdq                        = (ecx & 0x00000002) || false;
  cpu->dtes64                           = (ecx & 0x00000004) || false;
  cpu->monitor                          = (ecx & 0x00000008) || false;
  cpu->dscpl                            = (ecx & 0x00000010) || false;
  cpu->vmx                              = (ecx & 0x00000020) || false;
  cpu->smx                              = (ecx & 0x00000040) || false;
  cpu->est                              = (ecx & 0x00000080) || false;
  cpu->tm2                              = (ecx & 0x00000100) || false;
  cpu->ssse3                            = (ecx & 0x00000200) || false;
  cpu->cnxtid                           = (ecx & 0x00000400) || false;
  cpu->sdbg                             = (ecx & 0x00000800) || false;
  cpu->fma                              = (ecx & 0x00001000) || false;
  cpu->cx16                             = (ecx & 0x00002000) || false;
  cpu->xtpr                             = (ecx & 0x00004000) || false;
  cpu->pdcm                             = (ecx & 0x00008000) || false;
  cpu->pcid                             = (ecx & 0x00010000) || false;
  /* 16 reserve */
  cpu->dca                              = (ecx & 0x00040000) || false;
  cpu->sse41                            = (ecx & 0x00080000) || false;
  cpu->sse42                            = (ecx & 0x00100000) || false;
  cpu->x2apic                           = (ecx & 0x00200000) || false;
  cpu->movebe                           = (ecx & 0x00400000) || false;
  cpu->popcnt                           = (ecx & 0x00800000) || false;
  cpu->tscDeadline                      = (ecx & 0x01000000) || false;
  cpu->ase                              = (ecx & 0x02000000) || false;
  cpu->xsave                            = (ecx & 0x04000000) || false;
  cpu->osxsave                          = (ecx & 0x08000000) || false;
  cpu->avx                              = (ecx & 0x10000000) || false;
  cpu->f16c                             = (ecx & 0x20000000) || false;
  cpu->rdrnd                            = (ecx & 0x40000000) || false;
  cpu->hypervisor                       = (ecx & 0x80000000) || false;

  // edx
  cpu->fpu                              = (edx & 0x00000001) || false;
  cpu->mve                              = (edx & 0x00000002) || false;
  cpu->de                               = (edx & 0x00000004) || false;
  cpu->pse                              = (edx & 0x00000008) || false;
  cpu->tsc                              = (edx & 0x00000010) || false;
  cpu->msr                              = (edx & 0x00000020) || false;
  cpu->pae                              = (edx & 0x00000040) || false;
  cpu->mce                              = (edx & 0x00000080) || false;
  cpu->cx8                              = (edx & 0x00000100) || false;
  cpu->apic                             = (edx & 0x00000200) || false;
  /* 10 reserve */
  cpu->sep                              = (edx & 0x00000800) || false;
  cpu->mttr                             = (edx & 0x00001000) || false;
  cpu->pge                              = (edx & 0x00002000) || false;
  cpu->mca                              = (edx & 0x00004000) || false;
  cpu->cmov                             = (edx & 0x00008000) || false;
  cpu->pat                              = (edx & 0x00010000) || false;
  cpu->pse36                            = (edx & 0x00020000) || false;
  cpu->psn                              = (edx & 0x00040000) || false;
  cpu->clfsh                            = (edx & 0x00080000) || false;
  /* 20 reserve */
  cpu->ds                               = (edx & 0x00200000) || false;
  cpu->acpi                             = (edx & 0x00400000) || false;
  cpu->mmx                              = (edx & 0x00800000) || false;
  cpu->fxsr                             = (edx & 0x01000000) || false;
  cpu->sse                              = (edx & 0x02000000) || false;
  cpu->sse2                             = (edx & 0x04000000) || false;
  cpu->ss                               = (edx & 0x08000000) || false;
  cpu->htt                              = (edx & 0x10000000) || false;
  cpu->tm                               = (edx & 0x20000000) || false;
  cpu->ia64                             = (edx & 0x40000000) || false;
  cpu->pbe                              = (edx & 0x80000000) || false;
}


static void detect_stdlevel_00000002_partial(Cpu *cpu, uint8_t val)
{
  auto set_tlb = [&](int type, int level, int sizeFlags, int ways, int entories)
  {
    Tlb tlb;
    tlb.type          = type;
    tlb.level         = level;
    tlb.pageSizeFlags = sizeFlags;
    tlb.ways          = ways;
    tlb.entories      = entories;
    cpu->tlb.push_back(tlb);
  };

  auto set_cache = [&](int type, int level, int size, int ways, int lineSize)
  {
    if (type == 0)
      return;
    Cache cache;
    cache.type     = type;
    cache.level    = level;
    cache.size     = size;
    cache.ways     = ways;
    cache.coherencyLineSize = lineSize;
    cpu->cache.push_back(cache);
  };

  switch (val)
  {
  case 0x00: // null descriptor (=unused descriptor)
    break;
  case 0x01: // code TLB, 4K pages, 4 ways, 32 entries
    set_tlb(2, 1, 0x1, 4, 32);
    break;
  case 0x02: // code TLB, 4M pages, fully, 2 entries
    set_tlb(2, 1, 0x4, 0xff,  2);
    break;
  case 0x03: // data TLB, 4K pages, 4 ways, 64 entries
    set_tlb(1, 1, 0x1, 4, 64);
    break;
  case 0x04: // data TLB, 4M pages, 4 ways, 8 entries
    set_tlb(1, 1, 0x4, 4, 8);
    break;
  case 0x05: // data TLB, 4M pages, 4 ways, 32 entries
    set_tlb(1, 1, 0x4, 4, 32);
    break;
  case 0x06: // code L1 cache, 8 KB, 4 ways, 32 byte lines
    set_cache(2, 1, 8,  4,  32);
    break;
  case 0x08: // code L1 cache, 16 KB, 4 ways, 32 byte lines
    set_cache(2, 1, 16,  4,  32);
    break;
  case 0x09: // code L1 cache, 32 KB, 4 ways, 64 byte lines
    set_cache(2, 1, 32,  4,  64);
    break;
  case 0x0A: // data L1 cache, 8 KB, 2 ways, 32 byte lines
    set_cache(1, 1, 8,  2,  32);
    break;
  case 0x0B: // code TLB, 4M pages, 4 ways, 4 entries
    set_tlb(2, 1, 0x4, 4, 4);
    break;
  case 0x0C: // data L1 cache, 16 KB, 4 ways, 32 byte lines
    set_cache(1, 1, 16,  4,  32);
    break;
  case 0x0D: // data L1 cache, 16 KB, 4 ways, 64 byte lines (ECC)
    set_cache(1, 1, 16,  4,  64);
    break;
  case 0x0E: // data L1 cache, 24 KB, 6 ways, 64 byte lines
    set_cache(1, 1, 24,  6,  64);
    break;
  case 0x10: // data L1 cache, 16 KB, 4 ways, 32 byte lines (IA-64)
    set_cache(1, 1, 16,  4,  32);
    break;
  case 0x15: // code L1 cache, 16 KB, 4 ways, 32 byte lines (IA-64)
    set_cache(2, 1, 16,  4,  32);
    break;
  case 0x1A: // code and data L2 cache, 96 KB, 6 ways, 64 byte lines (IA-64)
    set_cache(3, 2, 96,  6,  64);
    break;
  case 0x1D: // code and data L2 cache, 128 KB, 2 ways, 64 byte lines
    set_cache(3, 2, 128,  2,  64);
    break;
  case 0x21: // code and data L2 cache, 256 KB, 8 ways, 64 byte lines
    set_cache(3, 2, 256,  8,  64);
    break;
  case 0x22: // code and data L3 cache, 512 KB, 4 ways (!), 64 byte lines, dual-sectored
    set_cache(3, 3, 512,  4,  64);
    break;
  case 0x23: // code and data L3 cache, 1024 KB, 8 ways, 64 byte lines, dual-sectored
    set_cache(3, 3, 1024,  8,  64);
    break;
  case 0x24: // code and data L2 cache, 1024 KB, 16 ways, 64 byte lines
    set_cache(3, 2, 1024,  16,  64);
    break;
  case 0x25: // code and data L3 cache, 2048 KB, 8 ways, 64 byte lines, dual-sectored
    set_cache(3, 3, 2048,  8,  64);
    break;
  case 0x29: // code and data L3 cache, 4096 KB, 8 ways, 64 byte lines, dual-sectored
    set_cache(3, 3, 4096,  8,  64);
    break;
  case 0x2C: // data L1 cache, 32 KB, 8 ways, 64 byte lines
    set_cache(1, 1, 32,  8,  64);
    break;
  case 0x30: // code L1 cache, 32 KB, 8 ways, 64 byte lines
    set_cache(2, 1, 32,  8,  64);
    break;
  case 0x39: // code and data L2 cache, 128 KB, 4 ways, 64 byte lines, sectored
    set_cache(3, 2, 128,  4,  64);
    break;
  case 0x3A: // code and data L2 cache, 192 KB, 6 ways, 64 byte lines, sectored
    set_cache(3, 2, 192,  6,  64);
    break;
  case 0x3B: // code and data L2 cache, 128 KB, 2 ways, 64 byte lines, sectored
    set_cache(3, 2, 128,  2,  64);
    break;
  case 0x3C: // code and data L2 cache, 256 KB, 4 ways, 64 byte lines, sectored
    set_cache(3, 2, 256,  4,  64);
    break;
  case 0x3D: // code and data L2 cache, 384 KB, 6 ways, 64 byte lines, sectored
    set_cache(3, 2, 384,  6,  64);
    break;
  case 0x3E: // code and data L2 cache, 512 KB, 4 ways, 64 byte lines, sectored
    set_cache(3, 2, 512,  4,  64);
    break;
  case 0x40: // no integrated L2 cache (P6 core) or L3 cache (P4 core)
    break;
  case 0x41: // code and data L2 cache, 128 KB, 4 ways, 32 byte lines
    set_cache(3, 2, 128,  4,  32);
    break;
  case 0x42: // code and data L2 cache, 256 KB, 4 ways, 32 byte lines
    set_cache(3, 2, 256,  4,  32);
    break;
  case 0x43: // code and data L2 cache, 512 KB, 4 ways, 32 byte lines
    set_cache(3, 2, 512,  4,  32);
    break;
  case 0x44: // code and data L2 cache, 1024 KB, 4 ways, 32 byte lines
    set_cache(3, 2, 1024,  4,  32);
    break;
  case 0x45: // code and data L2 cache, 2048 KB, 4 ways, 32 byte lines
    set_cache(3, 2, 2048,  4,  32);
    break;
  case 0x46: // code and data L3 cache, 4096 KB, 4 ways, 64 byte lines
    set_cache(3, 3, 4096,  4,  64);
    break;
  case 0x47: // code and data L3 cache, 8192 KB, 8 ways, 64 byte lines
    set_cache(3, 3, 8192,  8,  64);
    break;
  case 0x48: // code and data L2 cache, 3072 KB, 12 ways, 64 byte lines
    set_cache(3, 2, 3072,  12,  64);
    break;
  case 0x49: // code and data L3 cache, 4096 KB, 16 ways, 64 byte lines (P4) or code and data L2 cache, 4096 KB, 16 ways, 64 byte lines (Core 2)
    break;
  case 0x4A: // code and data L3 cache, 6144 KB, 12 ways, 64 byte lines
    set_cache(3, 3, 6144,  12,  64);
    break;
  case 0x4B: // code and data L3 cache, 8192 KB, 16 ways, 64 byte lines
    set_cache(3, 3, 8192,  16,  64);
    break;
  case 0x4C: // code and data L3 cache, 12288 KB, 12 ways, 64 byte lines
    set_cache(3, 3, 12288,  12,  64);
    break;
  case 0x4D: // code and data L3 cache, 16384 KB, 16 ways, 64 byte lines
    set_cache(3, 3, 16384,  16,  64);
    break;
  case 0x4E: // code and data L2 cache, 6144 KB, 24 ways, 64 byte lines
    set_cache(3, 2, 6144,  24,  64);
    break;
  case 0x4F: // code TLB, 4K pages, ???, 32 entries
    break;
  case 0x50: // code TLB, 4K/4M/2M pages, fully, 64 entries
    set_tlb(2, 1, 0x7, 0xff,  64);
    break;
  case 0x51: // code TLB, 4K/4M/2M pages, fully, 128 entries
    set_tlb(2, 1, 0x7, 0xff,  128);
    break;
  case 0x52: // code TLB, 4K/4M/2M pages, fully, 256 entries
    set_tlb(2, 1, 0x7, 0xff,  256);
    break;
  case 0x55: // code TLB, 2M/4M, fully, 7 entries
    set_tlb(2, 1, 0x6, 0xff,  7);
    break;
  case 0x56: // data TLB, 4M pages, 4 ways, 16 entries
    set_tlb(1, 1, 0x4, 4, 16);
    break;
  case 0x57: // data TLB, 4K pages, 4 ways, 16 entries
    set_tlb(1, 1, 0x1, 4, 16);
    break;
  case 0x59: // data TLB, 4K pages, fully, 16 entries
    set_tlb(1, 1, 0x1, 0xff, 16);
    break;
  case 0x5A: // data TLB, 2M/4M, 4 ways, 32 entries
    set_tlb(1, 1, 0x6, 4, 32);
    break;
  case 0x5B: // data TLB, 4K/4M pages, fully, 64 entries
    set_tlb(1, 1, 0x5, 0xff, 64);
    break;
  case 0x5C: // data TLB, 4K/4M pages, fully, 128 entries
    set_tlb(1, 1, 0x5, 0xff, 128);
    break;
  case 0x5D: // data TLB, 4K/4M pages, fully, 256 entries
    set_tlb(1, 1, 0x5, 0xff, 256);
    break;
  case 0x60: // data L1 cache, 16 KB, 8 ways, 64 byte lines, sectored
    set_cache(1, 1, 16,  8,  64);
    break;
  case 0x61: // code TLB, 4K pages, fully, 48 entries
    set_tlb(2, 1, 1, 0xff, 48);
    break;
  case 0x63: // data TLB, 2M/4M pages, 4 ways, 32 entries, and data TLB, 1G pages, 4 ways, 4 entries
    set_tlb(1, 1, 0x6, 4, 32);
    set_tlb(1, 1, 0x8, 4, 4);
    break;
  case 0x64: // data TLB, 4K pages, 4 ways, 512 entries
    set_tlb(1, 1, 0x1, 4, 512);
    break;
  case 0x66: // data L1 cache, 8 KB, 4 ways, 64 byte lines, sectored
    set_cache(1, 1, 8,  4,  64);
    break;
  case 0x67: // data L1 cache, 16 KB, 4 ways, 64 byte lines, sectored
    set_cache(1, 1, 16,  4,  64);
    break;
  case 0x68: // data L1 cache, 32 KB, 4 ways, 64 byte lines, sectored
    set_cache(1, 1, 32,  4,  64);
    break;
  case 0x6A: // data TLB, 4K pages, 8 ways, 64 entries
    set_tlb(1, 1, 0x1, 8, 64);
    break;
  case 0x6B: // data TLB, 4K pages, 8 ways, 256 entries
    set_tlb(1, 1, 0x1, 8, 256);
    break;
  case 0x6C: // data TLB, 2M/4M pages, 8 ways, 126 entries
    set_tlb(1, 1, 0x6, 8, 126);
    break;
  case 0x6D: // data TLB, 1G pages, fully, 16 entries
    set_tlb(1, 1, 0x8, 0xff,  16);
    break;
  case 0x70: // trace L1 cache, 12 KμOPs, 8 ways
    break;
  case 0x71: // trace L1 cache, 16 KμOPs, 8 ways
    break;
  case 0x72: // trace L1 cache, 32 KμOPs, 8 ways
    break;
  case 0x73: // trace L1 cache, 64 KμOPs, 8 ways
    break;
  case 0x76: // code TLB, 2M/4M pages, fully, 8 entries
    set_tlb(2, 1, 0x6, 0xff,  8);
    break;
  case 0x77: // code L1 cache, 16 KB, 4 ways, 64 byte lines, sectored (IA-64)
    set_cache(2, 1, 16,  4,  64);
    break;
  case 0x78: // code and data L2 cache, 1024 KB, 4 ways, 64 byte lines
    set_cache(3, 2, 1024,  4,  64);
    break;
  case 0x79: // code and data L2 cache, 128 KB, 8 ways, 64 byte lines, dual-sectored
    set_cache(3, 2, 128,  8,  64);
    break;
  case 0x7A: // code and data L2 cache, 256 KB, 8 ways, 64 byte lines, dual-sectored
    set_cache(3, 2, 256,  8,  64);
    break;
  case 0x7B: // code and data L2 cache, 512 KB, 8 ways, 64 byte lines, dual-sectored
    set_cache(3, 2, 512,  8,  64);
    break;
  case 0x7C: // code and data L2 cache, 1024 KB, 8 ways, 64 byte lines, dual-sectored
    set_cache(3, 2, 1024,  8,  64);
    break;
  case 0x7D: // code and data L2 cache, 2048 KB, 8 ways, 64 byte lines
    set_cache(3, 2, 2048,  8,  64);
    break;
  case 0x7E: // code and data L2 cache, 256 KB, 8 ways, 128 byte lines, sect. (IA-64)
    set_cache(3, 2, 256,  8,  128);
    break;
  case 0x7F: // code and data L2 cache, 512 KB, 2 ways, 64 byte lines
    set_cache(3, 2, 512,  2,  64);
    break;
  case 0x80: // code and data L2 cache, 512 KB, 8 ways, 64 byte lines
    set_cache(3, 2, 512,  8,  64);
    break;
  case 0x81: // code and data L2 cache, 128 KB, 8 ways, 32 byte lines
    set_cache(3, 2, 128,  8,  32);
    break;
  case 0x82: // code and data L2 cache, 256 KB, 8 ways, 32 byte lines
    set_cache(3, 2, 256,  8,  32);
    break;
  case 0x83: // code and data L2 cache, 512 KB, 8 ways, 32 byte lines
    set_cache(3, 2, 512,  8,  32);
    break;
  case 0x84: // code and data L2 cache, 1024 KB, 8 ways, 32 byte lines
    set_cache(3, 2, 1024,  8,  32);
    break;
  case 0x85: // code and data L2 cache, 2048 KB, 8 ways, 32 byte lines
    set_cache(3, 2, 2048,  8,  32);
    break;
  case 0x86: // code and data L2 cache, 512 KB, 4 ways, 64 byte lines
    set_cache(3, 2, 512,  4,  64);
    break;
  case 0x87: // code and data L2 cache, 1024 KB, 8 ways, 64 byte lines
    set_cache(3, 2, 1024,  8,  64);
    break;
  case 0x88: // code and data L3 cache, 2048 KB, 4 ways, 64 byte lines (IA-64)
    set_cache(3, 3, 2048,  4,  64);
    break;
  case 0x89: // code and data L3 cache, 4096 KB, 4 ways, 64 byte lines (IA-64)
    set_cache(3, 3, 4096,  4,  64);
    break;
  case 0x8A: // code and data L3 cache, 8192 KB, 4 ways, 64 byte lines (IA-64)
    set_cache(3, 3, 8192,  4,  64);
    break;
  case 0x8D: // code and data L3 cache, 3072 KB, 12 ways, 128 byte lines (IA-64)
    set_cache(3, 3, 3072,  12,  128);
    break;
  case 0x90: // code TLB, 4K...256M pages, fully, 64 entries (IA-64)
    set_tlb(2, 1, 0x10, 0xff, 64);
    break;
  case 0x96: // data L1 TLB, 4K...256M pages, fully, 32 entries (IA-64)
    set_tlb(1, 1, 0x10, 0xff, 32);
    break;
  case 0x9B: // data L2 TLB, 4K...256M pages, fully, 96 entries (IA-64)
    set_tlb(1, 2, 0x10, 0xff, 96);
    break;
  case 0xA0: // data TLB, 4K pages, fully, 32 entries
    set_tlb(1, 1, 0x1, 0xff, 32);
    break;
  case 0xB0: // code TLB, 4K pages, 4 ways, 128 entries
    set_tlb(2, 1, 1, 4, 128);
    break;
  case 0xB1: // code TLB, 4M pages, 4 ways, 4 entries and code TLB, 2M pages, 4 ways, 8 entries
    set_tlb(2, 1, 0x4, 4, 4);
    set_tlb(2, 1, 0x2, 4, 8);
    break;
  case 0xB2: // code TLB, 4K pages, 4 ways, 64 entries
    set_tlb(2, 1, 1, 4, 64);
    break;
  case 0xB3: // data TLB, 4K pages, 4 ways, 128 entries
    set_tlb(1, 1, 0x1, 4, 128);
    break;
  case 0xB4: // data TLB, 4K pages, 4 ways, 256 entries
    set_tlb(1, 1, 0x1, 4, 256);
    break;
  case 0xB5: // code TLB, 4K pages, 8 ways, 64 entries
    set_tlb(2, 1, 1, 8, 64);
    break;
  case 0xB6: // code TLB, 4K pages, 8 ways, 128 entries
    set_tlb(2, 1, 1, 8, 128);
    break;
  case 0xBA: // data TLB, 4K pages, 4 ways, 64 entries
    set_tlb(1, 1, 0x1, 4, 64);
    break;
  case 0xC0: // data TLB, 4K/4M pages, 4 ways, 8 entries
    set_tlb(1, 1, 0x5, 4, 8);
    break;
  case 0xC1: // L2 code and data TLB, 4K/2M pages, 8 ways, 1024 entries
    set_tlb(3, 2, 0x3, 8, 1024);
    break;
  case 0xC2: // data TLB, 2M/4M pages, 4 ways, 16 entries
    set_tlb(1, 1, 0x6, 4, 16);
    break;
  case 0xC3: // L2 code and data TLB, 4K/2M pages, 6 ways, 1536 entries and L2 code and data TLB, 1G pages, 4 ways, 16 entries
    set_tlb(3, 2, 0x3, 6, 1536);
    set_tlb(3, 2, 0x8, 4, 16);
    break;
  case 0xC4: // data TLB, 2M/4M pages, 4 ways, 32 entries
    set_tlb(1, 1, 0x6, 4, 32);
    break;
  case 0xCA: // L2 code and data TLB, 4K pages, 4 ways, 512 entries
    set_tlb(1, 2, 0x1, 4, 512);
    break;
  case 0xD0: // code and data L3 cache, 512 KB, 4 ways, 64 byte lines
    set_cache(3, 3, 512,  4,  64);
    break;
  case 0xD1: // code and data L3 cache, 1024 KB, 4 ways, 64 byte lines
    set_cache(3, 3, 1024,  4,  64);
    break;
  case 0xD2: // code and data L3 cache, 2048 KB, 4 ways, 64 byte lines
    set_cache(3, 3, 2048,  4,  64);
    break;
  case 0xD6: // code and data L3 cache, 1024 KB, 8 ways, 64 byte lines
    set_cache(3, 3, 1024,  8,  64);
    break;
  case 0xD7: // code and data L3 cache, 2048 KB, 8 ways, 64 byte lines
    set_cache(3, 3, 2048,  8,  64);
    break;
  case 0xD8: // code and data L3 cache, 4096 KB, 8 ways, 64 byte lines
    set_cache(3, 3, 4096,  8,  64);
    break;
  case 0xDC: // code and data L3 cache, 1536 KB, 12 ways, 64 byte lines
    set_cache(3, 3, 1536,  12,  64);
    break;
  case 0xDD: // code and data L3 cache, 3072 KB, 12 ways, 64 byte lines
    set_cache(3, 3, 3072,  12,  64);
    break;
  case 0xDE: // code and data L3 cache, 6144 KB, 12 ways, 64 byte lines
    set_cache(3, 3, 6144,  12,  64);
    break;
  case 0xE2: // code and data L3 cache, 2048 KB, 16 ways, 64 byte lines
    set_cache(3, 3, 2048,  16,  64);
    break;
  case 0xE3: // code and data L3 cache, 4096 KB, 16 ways, 64 byte lines
    set_cache(3, 3, 4096,  16,  64);
    break;
  case 0xE4: // code and data L3 cache, 8192 KB, 16 ways, 64 byte lines
    set_cache(3, 3, 8192,  16,  64);
    break;
  case 0xEA: // code and data L3 cache, 12288 KB, 24 ways, 64 byte lines
    set_cache(3, 3, 12288,  24,  64);
    break;
  case 0xEB: // code and data L3 cache, 18432 KB, 24 ways, 64 byte lines
    set_cache(3, 3, 18432,  24,  64);
    break;
  case 0xEC: // code and data L3 cache, 24576 KB, 24 ways, 64 byte lines
    set_cache(3, 3, 24576,  24,  64);
    break;
  case 0xF0: // 64 byte prefetching
    cpu->prefetchSize = 64;
    break;
  case 0xF1: // 128 byte prefetching
    cpu->prefetchSize = 128;
    break;
  case 0xFF: // query standard level 0000_0004h instead
    break;
  default:
    break;
  }
}


//!
//! @brief EAX=0x2: Cache and TLB Descriptor information
//! @see http://www.sandpile.org/x86/cpuid.htm#level_0000_0002h
//!
static void detect_stdlevel_00000002(Cpu *cpu)
{
  int eax, ebx, ecx, edx;
  int cpuInfo[4];

  get_cpuid(cpuInfo, 2);
  eax = cpuInfo[0];
  ebx = cpuInfo[1];
  ecx = cpuInfo[2];
  edx = cpuInfo[3];

  // eax
  detect_stdlevel_00000002_partial(cpu, (eax >>  8) & 0xff);
  detect_stdlevel_00000002_partial(cpu, (eax >> 16) & 0xff);
  detect_stdlevel_00000002_partial(cpu, (eax >> 24) & 0xff);

  // ebx
  detect_stdlevel_00000002_partial(cpu, (ebx >>  0) & 0xff);
  detect_stdlevel_00000002_partial(cpu, (ebx >>  8) & 0xff);
  detect_stdlevel_00000002_partial(cpu, (ebx >> 16) & 0xff);
  detect_stdlevel_00000002_partial(cpu, (ebx >> 24) & 0xff);

  // ecx
  detect_stdlevel_00000002_partial(cpu, (ecx >>  0) & 0xff);
  detect_stdlevel_00000002_partial(cpu, (ecx >>  8) & 0xff);
  detect_stdlevel_00000002_partial(cpu, (ecx >> 16) & 0xff);
  detect_stdlevel_00000002_partial(cpu, (ecx >> 24) & 0xff);

  // edx
  detect_stdlevel_00000002_partial(cpu, (edx >>  0) & 0xff);
  detect_stdlevel_00000002_partial(cpu, (edx >>  8) & 0xff);
  detect_stdlevel_00000002_partial(cpu, (edx >> 16) & 0xff);
  detect_stdlevel_00000002_partial(cpu, (edx >> 24) & 0xff);
}


//!
//! @brief EAX=0x3: Processor Serial Number
//! @note Processor serial number (PSN) is not supported in the Pentium 4 
//!       processor or later. On all models, use the PSN flag to check for
//!       PSN support before accessing the feature.
//!
static void detect_stdlevel_00000003(Cpu *cpu)
{
  int eax, ebx, ecx, edx;
  char *serial;
  int cpuInfo[4];

  if (cpu->psn == false)
    return;

  get_cpuid(cpuInfo, 3);
  eax = cpuInfo[0];
  ebx = cpuInfo[1];
  ecx = cpuInfo[2];
  edx = cpuInfo[3];
  
  (void)eax;
  /* 0-31 reserve */

  (void)ebx;
  /* 0-31 reserve */

  // ecx
  serial = cpu->serialnumber;
  *reinterpret_cast<int*>(serial) = ecx;

  // edx
  serial = &cpu->serialnumber[4];
  *reinterpret_cast<int*>(serial) = edx;
}


//!
//! @brief EAX=0x4: Cache configuration descriptors
//!
static void detect_stdlevel_00000004(Cpu *cpu)
{
  int eax, ebx, ecx, edx;
  int cpuInfo[4];
  Cache cache;

  if (cpu->monitor == false)
     return;

  for (int i = 0; true; ++i)
  {
    get_cpuidex(cpuInfo, 4, i);

    eax = cpuInfo[0];
    ebx = cpuInfo[1];
    ecx = cpuInfo[2];
    edx = cpuInfo[3];

    if (eax == 0)
      break;

    // eax
    cache.type                 = (eax >>  0) & 0x1f;
    cache.level                = (eax >>  5) & 0x7;
    cache.selfInit             = (eax & 0x00000100) || false;
    cache.fullAssociative      = (eax & 0x00000200) || false;
    /* 10-13 reserved */
    cache.thread               = ((eax >> 14) & 0xfff) + 1;
    cache.cores                = ((eax >> 26) & 0x3f) + 1;

    // ebx
    cache.coherencyLineSize    = ((ebx >>  0) & 0xfff) + 1;
    cache.partition            = ((ebx >> 12) & 0x3ff) + 1;
    cache.ways                 = ((ebx >> 22) & 0x3ff) + 1;

    // ecx
    cache.sets                 = ecx + 1;

    // edx
    cache.writeBackInvalid     = (edx & 0x00000001) || false;
    cache.inclusiveLowerLevels = (edx & 0x00000002) || false;
    cache.complexIndexing      = (edx & 0x00000004) || false;
    /* 3-31 reserved */

    cache.size = (cache.coherencyLineSize * cache.sets * cache.ways) / 1024;

    cpu->cache.push_back(cache);
  }
}


//!
//! @brief EAX=0x5: MONITOR/MWAIT
//!
static void detect_stdlevel_00000005(Cpu *cpu)
{
  int eax, ebx, ecx, edx;
  int cpuInfo[4];

  get_cpuid(cpuInfo, 5);
  eax = cpuInfo[0];
  ebx = cpuInfo[1];
  ecx = cpuInfo[2];
  edx = cpuInfo[3];

  // eax
  cpu->smallestMonitorLineSize = (eax >>  0) & 0xff;
  /* 16-31 reserved */

  // ebx
  cpu->largestMonitorLineSize  = (ebx >>  0) & 0xff;
  /* 16-31 reserved */

  // ecx
  cpu->es                      = (ecx >>  0) & 0x01;
  cpu->ib                      = (ecx >>  1) & 0x01;
  /* 2-31 reserved */

  // edx
  cpu->numC0Mwait              = (edx >>  0) & 0x0f;
  cpu->numC1Mwait              = (edx >>  4) & 0x0f;
  cpu->numC2Mwait              = (edx >>  8) & 0x0f;
  cpu->numC3Mwait              = (edx >> 12) & 0x0f;
  cpu->numC4Mwait              = (edx >> 16) & 0x0f;
  cpu->numC5Mwait              = (edx >> 20) & 0x0f;
  cpu->numC6Mwait              = (edx >> 24) & 0x0f;
  cpu->numC7Mwait              = (edx >> 28) & 0x0f;
}


//!
//! @brief EAX=0x6: Thermal and Power Management
//!
static void detect_stdlevel_00000006(Cpu *cpu)
{
  int eax, ebx, ecx, edx;
  int cpuInfo[4];

  get_cpuid(cpuInfo, 6);
  eax = cpuInfo[0];
  ebx = cpuInfo[1];
  ecx = cpuInfo[2];
  edx = cpuInfo[3];

  // eax
  cpu->digitalTempSensor                = (eax >>  0) & 0x1;
  cpu->turboBoost                       = (eax >>  1) & 0x1;
  cpu->arat                             = (eax >>  2) & 0x1;
  /* 3 reserved */
  cpu->pln                              = (eax >>  4) & 0x1;
  cpu->ecmd                             = (eax >>  5) & 0x1;
  cpu->ptm                              = (eax >>  6) & 0x1;
  cpu->hwp                              = (eax >>  7) & 0x1;
  cpu->hwpNotification                  = (eax >>  8) & 0x1;
  cpu->hwpActivityWindow                = (eax >>  9) & 0x1;
  cpu->hwpEnergyPerformancePreference   = (eax >> 10) & 0x1;
  cpu->hwpPackageLevelRequest           = (eax >> 11) & 0x1;
  /* 12 reserved */
  cpu->hdc                              = (eax >> 13) & 0x1;
  cpu->turboBoostMax3                   = (eax >> 14) & 0x1;
  cpu->hwpCapabilities                  = (eax >> 15) & 0x1;
  cpu->hwpPeci                          = (eax >> 16) & 0x1;
  cpu->flexHwp                          = (eax >> 17) & 0x1;
  cpu->fastAccessMode                   = (eax >> 18) & 0x1;
  cpu->hwFeedback                       = (eax >> 19) & 0x1;
  cpu->ignoringIdle                     = (eax >> 20) & 0x1;
  /* 21-31 reserved */

  // ebx
  cpu->numInterruptThresholds           = (ebx >>  0) & 0xf;
  /* 4-31 reserved */

  // ecx
  cpu->hwCoordinationFeedbackCapability = (ecx >>  0) & 0x1;
  /* 1-2 reserved */
  cpu->performanceEnergyBiasPreference  = (ecx >>  3) & 0x1;
  /* 4-31 reserved */

  // edx
  cpu->bitmapHwFeedback                 = (edx >>  0) & 0x00ff;
  cpu->enumatatesSize                   = (edx >>  8) & 0x000f;
  cpu->rowIndexOfLogicalProcessor       = (edx >> 16) & 0xffff;
}


//!
//! @brief EAX=0x7: Structured Extended Feature Flags Enumeration Leaf
//!
static void detect_stdlevel_00000007(Cpu *cpu)
{
  int eax, ebx, ecx, edx;
  int cpuInfo[4];

  get_cpuid(cpuInfo, 7);
  eax = cpuInfo[0];
  ebx = cpuInfo[1];
  ecx = cpuInfo[2];
  edx = cpuInfo[3];

  if ((eax == 0) && (ebx == 0) && (ecx == 0) && (edx == 0))
    return;

  // ebx
  cpu->fsgsbase                       = (ebx & 0x00000001) ? false : true;
  cpu->ia32TscAdjustMsr               = (ebx & 0x00000002) ? false : true;
  cpu->sgx                            = (ebx & 0x00000004) ? false : true;
  cpu->bmi1                           = (ebx & 0x00000008) ? false : true;
  cpu->hle                            = (ebx & 0x00000010) ? false : true;
  cpu->avx2                           = (ebx & 0x00000020) ? false : true;
  /* 6 reserved */
  cpu->smep                           = (ebx & 0x00000080) ? false : true;
  cpu->bmi2                           = (ebx & 0x00000100) ? false : true;
  cpu->erms                           = (ebx & 0x00000200) ? false : true;
  cpu->invpcid                        = (ebx & 0x00000400) ? false : true;
  cpu->rtm                            = (ebx & 0x00000800) ? false : true;
  cpu->pqm                            = (ebx & 0x00001000) ? false : true;
  cpu->fpucsds                        = (ebx & 0x00002000) ? false : true;
  cpu->mpx                            = (ebx & 0x00004000) ? false : true;
  cpu->pqe                            = (ebx & 0x00008000) ? false : true;
  cpu->avx512f                        = (ebx & 0x00010000) ? false : true;
  cpu->avx512dq                       = (ebx & 0x00020000) ? false : true;
  cpu->rdseed                         = (ebx & 0x00040000) ? false : true;
  cpu->adx                            = (ebx & 0x00080000) ? false : true;
  cpu->smap                           = (ebx & 0x00100000) ? false : true;
  cpu->avx512ifma                     = (ebx & 0x00200000) ? false : true;
  /* 22 reserved */
  cpu->clflushopt                     = (ebx & 0x00800000) ? false : true;
  cpu->clwb                           = (ebx & 0x01000000) ? false : true;
  cpu->pt                             = (ebx & 0x02000000) ? false : true;
  cpu->avx512pf                       = (ebx & 0x04000000) ? false : true;
  cpu->avx512er                       = (ebx & 0x08000000) ? false : true;
  cpu->avx512cd                       = (ebx & 0x10000000) ? false : true;
  cpu->sha                            = (ebx & 0x20000000) ? false : true;
  cpu->avx512bw                       = (ebx & 0x40000000) ? false : true;
  cpu->avx512vl                       = (ebx & 0x80000000) ? false : true;

  // ecx
  cpu->prefetchwt1                    = (ecx & 0x00000001) ? false : true;
  cpu->avx512vbmi                     = (ecx & 0x00000002) ? false : true;
  cpu->umip                           = (ecx & 0x00000004) ? false : true;
  cpu->pku                            = (ecx & 0x00000008) ? false : true;
  cpu->ospke                          = (ecx & 0x00000010) ? false : true;
  cpu->waitPkg                        = (ecx & 0x00000020) ? false : true;
  cpu->avx512vbmi2                    = (ecx & 0x00000040) ? false : true;
  /* 7 reserved */
  cpu->gfni                           = (ecx & 0x00000100) ? false : true;
  cpu->vaes                           = (ecx & 0x00000200) ? false : true;
  cpu->vpclmulqdq                     = (ecx & 0x00000400) ? false : true;
  cpu->avx512vnni                     = (ecx & 0x00000800) ? false : true;
  cpu->avx512bitalg                   = (ecx & 0x00001000) ? false : true;
  /* 13 reserved */
  cpu->avx512vpopcntdq                = (ecx & 0x00004000) ? false : true;
  /* 14-15 reserved */
  cpu->mawau                          = (ecx >> 17) & 0x1f;
  cpu->rdpid                          = (ecx & 0x00400000) ? false : true;
  /* 23-24 reserved */
  cpu->cldemote                       = (ecx & 0x02000000) ? false : true;
  /* 26 reserved */
  cpu->movdiri                        = (ecx & 0x08000000) ? false : true;
  cpu->movdir64b                      = (ecx & 0x10000000) ? false : true;
  cpu->enqcmd                         = (ecx & 0x20000000) ? false : true;
  cpu->sgxlc                          = (ecx & 0x40000000) ? false : true;
  /* 31 reserved */

  // edx
  /* 0-1 reserved */
  cpu->avx512vnniw                    = (edx & 0x00000002) ? false : true;
  cpu->avx512fmaps                    = (edx & 0x00000004) ? false : true;
  cpu->repmov                         = (edx & 0x00000008) ? false : true;
  /* 5-7 reserved */
  cpu->avx512Vp2intersect             = (edx & 0x00000080) ? false : true;
  /* 9-17 reserved */
  cpu->pconfig                        = (edx & 0x00040000) ? false : true;
  /* 19-25 reserved */
  cpu->emuIbrs                        = (edx & 0x04000000) ? false : true;
  cpu->emuStibp                       = (edx & 0x08000000) ? false : true;
  /* 28 reserved */
  cpu->emuIa32ArchCapabilitiesMsr     = (edx & 0x20000000) ? false : true;
  cpu->emuIa32CoreCapabilitiesMsr     = (edx & 0x40000000) ? false : true;
  cpu->emuSsbd                        = (edx & 0x80000000) ? false : true;
}


//!
//! @brief EAX=0x9: Direct Cache Access Information
//!
static void detect_stdlevel_00000009(Cpu *cpu)
{
  int eax, ebx, ecx, edx;
  int cpuInfo[4];

  get_cpuid(cpuInfo, 9);
  eax = cpuInfo[0];
  ebx = cpuInfo[1];
  ecx = cpuInfo[2];
  edx = cpuInfo[3];

  cpu->ia32PlatformDcaCap = eax;

  (void)ebx; /* 0-31 reserved */
  (void)ecx; /* 0-31 reserved */
  (void)edx; /* 0-31 reserved */
}

//
// @brief EAX=0xA: Architectural Performance Monitoring
//
static void detect_stdlevel_0000000A(Cpu *cpu)
{
  int eax, ebx, ecx, edx;
  int cpuInfo[4];

  get_cpuid(cpuInfo, 0xA);
  eax = cpuInfo[0];
  ebx = cpuInfo[1];
  ecx = cpuInfo[2];
  edx = cpuInfo[3];

  // eax
  cpu->apmVersion                     = (eax >>  0) & 0xff;
  cpu->numGpPmc                       = (eax >>  8) & 0xff;
  cpu->widthGpPmc                     = (eax >> 16) & 0xff;
  cpu->lenEbxBit                      = (eax >> 24) & 0xff;

  // ebx
  cpu->cce                            = (ebx & 0x00000001) ? false : true;
  cpu->ire                            = (ebx & 0x00000002) ? false : true;
  cpu->rce                            = (ebx & 0x00000004) ? false : true;
  cpu->llcre                          = (ebx & 0x00000008) ? false : true;
  cpu->llcme                          = (ebx & 0x00000010) ? false : true;
  cpu->bire                           = (ebx & 0x00000020) ? false : true;
  cpu->bmre                           = (ebx & 0x00000040) ? false : true;
  /* 7-31 reserved */

  // ecx
  (void)ecx;
  /* 0-31 reserved */

  // edx
  cpu->numFixedFuncPc                 = (edx >> 0) & 0x1f;
  cpu->widthFixedFuncPc               = (edx >> 5) & 0xff;
  /* 13-31 reserved */
}

//
// @brief EAX=0x0B: Extended Topology Enumeration Leaf
//
static void detect_stdlevel_0000000B(Cpu *cpu)
{
  int eax, ebx, ecx, edx;
  int cpuInfo[4];

  get_cpuid(cpuInfo, 0xB);
  eax = cpuInfo[0];
  ebx = cpuInfo[1];
  ecx = cpuInfo[2];
  edx = cpuInfo[3];

  (void)cpu;

  // eax
  (void)eax;

  // ebx
  (void)ebx;

  // ecx
  (void)ecx;

  // edx
  (void)edx;
}

//
// @brief EAX=0x9: Direct Cache Access Information
//
static void detect_stdlevel_00000016(Cpu *cpu)
{
  int eax, ebx, ecx, edx;
  int cpuInfo[4];

  get_cpuid(cpuInfo, 0x16);
  eax = cpuInfo[0];
  ebx = cpuInfo[1];
  ecx = cpuInfo[2];
  edx = cpuInfo[3];

  // eax
  cpu->baseFrequency = (eax & 0xffff);
  /* 16-31 reserve */

  // ebx
  cpu->maxFrequency  = (ebx & 0xffff);
  /* 16-31 reserve */

  // ecx
  cpu->busFrequency  = (ecx & 0xffff);
  /* 16-31 reserve */

  // edx
  (void)edx; /* 0-31 reserve */
}

//
// @brief EAX=0x00000000: Maximum supported extended level and vendor ID string
//
static int detect_extlevel_80000000(Cpu *cpu)
{
  int extLevel, eax, ebx, ecx, edx;
  int cpuInfo[4];

  get_cpuid(cpuInfo, 0x80000000);

  eax = cpuInfo[0];
  ebx = cpuInfo[1];
  ecx = cpuInfo[2];
  edx = cpuInfo[3];

  extLevel = eax;
  if (ebx | ecx | edx)
  {
    *reinterpret_cast<int*>(cpu->vendor)     = ebx;
    *reinterpret_cast<int*>(cpu->vendor + 4) = edx;
    *reinterpret_cast<int*>(cpu->vendor + 8) = ecx;
  }

  return extLevel;
}

//
// @brief EAX=0x80000001: Extended Processor Signature and Feature Bits.
//
static void detect_extlevel_80000001(Cpu *cpu)
{
  int eax, ebx, ecx, edx;
  int cpuInfo[4];
  get_cpuidex(cpuInfo, 0x80000001, 0);

  eax = cpuInfo[0];
  ebx = cpuInfo[1];
  ecx = cpuInfo[2];
  edx = cpuInfo[3];

  // eax
  (void)eax;

  // ebx
  (void)ebx;

  // ecx
  cpu->ahf64                       = (ecx & 0x00000001) || false;
  cpu->cmpLegacy                   = (ecx & 0x00000002) || false;
  cpu->svm                         = (ecx & 0x00000004) || false;
  cpu->extApicSpace                = (ecx & 0x00000008) || false;
  cpu->altMovCr8                   = (ecx & 0x00000010) || false;
  cpu->lzcnt                       = (ecx & 0x00000020) || false;
  cpu->sse4a                       = (ecx & 0x00000040) || false;
  cpu->misalignedSse               = (ecx & 0x00000080) || false;
  cpu->prefetch3DNow               = (ecx & 0x00000100) || false;
  cpu->skinit                      = (ecx & 0x00001000) || false;

  // edx
  cpu->sysCallSysRet               = (edx & 0x00000800) || false;
  cpu->pat                         = (edx & 0x00010000) || false;
  cpu->amdMmx                      = (edx & 0x00040000) || false;
  cpu->amdFfxsr                    = (edx & 0x00200000) || false;
  cpu->amd1GBPage                  = (edx & 0x00400000) || false;
  cpu->rdtscp                      = (edx & 0x08000000) || false;
  cpu->amdLm                       = (edx & 0x20000000) || false;
  cpu->amd3DNowExt                 = (edx & 0x40000000) || false;
  cpu->amd3DNow                    = (edx & 0x80000000) || false;
}

//
// @brief EAX=0x80000002: Brand Name
//
static void detect_extlevel_80000002(Cpu *cpu)
{
  int cpuInfo[4];
  get_cpuidex(cpuInfo, 0x80000002, 0);
  memcpy(cpu->brand, &cpuInfo[0], 4 * sizeof(int));
}

//
// @brief EAX=0x80000003: Brand Name
//
static void detect_extlevel_80000003(Cpu *cpu)
{
  int cpuInfo[4];
  get_cpuidex(cpuInfo, 0x80000003, 0);
  memcpy(cpu->brand + 16, &cpuInfo[0], 4 * sizeof(int));
}

//
// @brief EAX=0x80000004: Brand Name
//
static void detect_extlevel_80000004(Cpu *cpu)
{
  int cpuInfo[4];
  get_cpuidex(cpuInfo, 0x80000004, 0);
  memcpy(cpu->brand + 32, &cpuInfo[0], 4 * sizeof(int));
}

//
// @brief L1 cache and L1 TLB configuration descriptors 
//
static void detect_extlevel_80000005(Cpu *cpu)
{
  int eax, ebx, ecx, edx;
  int cpuInfo[4];
  get_cpuidex(cpuInfo, 0x80000005, 0);

  eax = cpuInfo[0];
  ebx = cpuInfo[1];
  ecx = cpuInfo[2];
  edx = cpuInfo[3];

  (void)cpu;
  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edx;
}

//
// @brief EAX=0x80000006 Extended Function CPUID Information
//
static void detect_extlevel_80000006(Cpu *cpu)
{
#if 0
  static constexpr int asociate[] =
  {
    0,   // 0000b=disabled
    0,   // 0001b=undefined
    2,   // 0010b=2-way
    3,   // 0011b=3-way
    4,   // 0100b=4-way
    6,   // 0101b=6-way
    8,   // 0110b=8-way
    0,   // 0111b=undefined
    11,  // 1000b=16-way
    0,   // 1001b=undefined
    32,  // 1010b=32-way
    48,  // 1011b=48-way
    64,  // 1100b=64-way
    96,  // 1101b=96-way
    128, // 1110b=128-way
    255, // 1111b=full
  };
#endif

  int eax, ebx, ecx, edx;
  int cpuInfo[4];
  get_cpuidex(cpuInfo, 0x80000005, 0);

  eax = cpuInfo[0];
  ebx = cpuInfo[1];
  ecx = cpuInfo[2];
  edx = cpuInfo[3];

  (void)cpu;
  (void)eax;
  (void)ebx;
  (void)ecx;
  (void)edx;
}

//
// @brief EAX=0x80000008 Extended Function CPUID Information
//
static void detect_extlevel_80000008(Cpu *cpu)
{
  int eax, ebx, ecx, edx;
  int cpuInfo[4];
  get_cpuidex(cpuInfo, 0x80000008, 0);

  eax = cpuInfo[0];
  ebx = cpuInfo[1];
  ecx = cpuInfo[2];
  edx = cpuInfo[3];

  cpu->physicalAddressBits = eax & 0xff;
  cpu->virtualAddressBits  = (eax >> 8) & 0xff;

  (void)ebx;
  (void)ecx;
  (void)edx;
}

//
// @brief EAX=0x8000000A Extended Function CPUID Information
//
static void detect_extlevel_8000000A(Cpu *cpu)
{
  int eax, ebx, ecx, edx;
  int cpuInfo[4];
  get_cpuidex(cpuInfo, 0x8000000A, 0);

  eax = cpuInfo[0];
  ebx = cpuInfo[1];
  ecx = cpuInfo[2];
  edx = cpuInfo[3];

  cpu->amdNasid              = (eax & 0x000000ff);
  /* 8-31 reserve */

  cpu->amdNasid              = ebx;

  (void)ecx; /* 0-31 reserve */

  cpu->amdNp                 = (edx & 0x00000001) || false;
  cpu->amdLbr                = (edx & 0x00000002) || false;
  cpu->amdSvml               = (edx & 0x00000004) || false;
  cpu->amdNrips              = (edx & 0x00000008) || false;
  cpu->amdTscRateMsr         = (edx & 0x00000010) || false;
  cpu->amdVmcbClean          = (edx & 0x00000020) || false;
  cpu->amdFlushByAsid        = (edx & 0x00000040) || false;
  cpu->amdDecodeAssists      = (edx & 0x00000080) || false;
  /* 8 reserve */
  /* 9 reserve */
  cpu->amdPauseFilter        = (edx & 0x00000400) || false;
  /* 11 reserve */
  cpu->amdPauseFilterThresh  = (edx & 0x00001000) || false;
  /* 13-31 reserve */
}

//
// @brief EAX=0x8000001A Extended Function CPUID Information
//
static void detect_extlevel_8000001A(Cpu *cpu)
{
  int eax, ebx, ecx, edx;
  int cpuInfo[4];
  get_cpuidex(cpuInfo, 0x8000001A, 0);

  eax = cpuInfo[0];
  ebx = cpuInfo[1];
  ecx = cpuInfo[2];
  edx = cpuInfo[3];

  cpu->amdFp128           = (eax & 0x1) || false;
  cpu->amdMoveu           = (eax & 0x2) || false;
  /* 2-31 reserve */

  (void)ebx; /* 0-31 reserve */
  (void)ecx; /* 0-31 reserve */
  (void)edx; /* 0-31 reserve */
}
