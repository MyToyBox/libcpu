//
// This file is subject to the terms and conditions defined in
// file 'LICENSE', which is part of this source code package.
//
#include <cstdio>
#include <string>

#include "libcpu/cpu.h"

using namespace libcpu;

static const char *TLB_PAGE_SIZE_STR[] = { "4KB", "2MB", "4MB", "1GB",
                                           "4KB...256MB(IA-64)" };

static const char *CACHE_AND_TLB_TYPE_STR[] = { "null", "Data", "Instruction",
                                              "Unified" };

static void tlb_page_size_str(int sizeFlags, std::string &name)
{
  if (sizeFlags & 0x00000001)
  {
    if (name != "")
      name += "/";
    name += TLB_PAGE_SIZE_STR[0];
  }

  if (sizeFlags & 0x00000002)
  {
    if (name != "")
      name += "/";
    name += TLB_PAGE_SIZE_STR[1];
  }

  if (sizeFlags & 0x00000004)
  {
    if (name != "")
      name += "/";
    name += TLB_PAGE_SIZE_STR[2];
  }

  if (sizeFlags & 0x00000008)
  {
    if (name != "")
      name += "/";
    name += TLB_PAGE_SIZE_STR[3];
  }

  if (sizeFlags & 0x00000010)
  {
    if (name != "")
      name += "/";
    name += TLB_PAGE_SIZE_STR[4];
  }
}

int main(void)
{
  Cpu cpu;
  detect_cpu_info(&cpu);

  print_cpuid();
  printf("\n");
  printf("vendor                                              : %s\n", cpu.vendor);
  printf("brand                                               : %s\n", cpu.brand);
  printf("serialnumber                                        : ");
  for (int i = sizeof(cpu.serialnumber) - 1; i >= 0; --i)
    printf("%02x", cpu.serialnumber[i]);
  printf("\n");
  printf("stepping ID                                         : %d\n", cpu.stepping);
  printf("model                                               : %d\n", cpu.model);
  printf("family                                              : %d\n", cpu.family);
  printf("processor type                                      : %d\n", cpu.processorType);
  printf("extended model                                      : %d\n", cpu.extModel);
  printf("extended family                                     : %d\n", cpu.extFamily);
  printf("brand index                                         : %d\n", cpu.brandIdx);
  printf("CLFLUSH line size(bytes)                            : %d\n", cpu.clflashChunkCount * 8);
  printf("number of logical processors per physical processor : %d\n", cpu.logicalProcessors);
  printf("local APIC ID                                       : %d\n", cpu.apicId);
  for (size_t i = 0; i < cpu.cache.size(); ++i)
  {
    const Cache &c = cpu.cache[i];
    printf("-- cache %zd ---\n", i);
    printf("cache type                                          : %d(%s)\n", c.type, CACHE_AND_TLB_TYPE_STR[c.type]);
    printf("cache level                                         : %d\n", c.level);
    printf("cache size(KB)                                      : %d\n", c.size);
    printf("self-initializing cache level                       : %d\n", c.selfInit);
    printf("fully associative cache                             : %d\n", c.fullAssociative);
    printf("extra threads sharing this cache                    : %d\n", c.thread);
    printf("extra processor cores on this die                   : %d\n", c.cores);
    printf("system coherency line size<(byte)                   : %d\n", c.coherencyLineSize);
    printf("physical line partitions                            : %d\n", c.partition);
    printf("ways of associativity                               : %d\n", c.ways);
    printf("WBINVD/INVD behavior on lower caches                : %d\n", c.writeBackInvalid);
    printf("inclusive to lower caches                           : %d\n", c.inclusiveLowerLevels);
    printf("complex cache indexing                              : %d\n", c.complexIndexing);
    printf("number of sets                                      : %d\n", c.sets);
  }
  for (size_t i = 0; i < cpu.tlb.size(); ++i)
  {
    const Tlb &t = cpu.tlb[i];
    std::string name = "";
    tlb_page_size_str(t.pageSizeFlags, name);
    printf("-- TLB %zd ---\n", i);
    printf("TLB type                                            : %d(%s)\n", t.type, CACHE_AND_TLB_TYPE_STR[t.type]);
    printf("TLB level                                           : %d\n", t.level);
    printf("TLB Size                                            : %d(%s)\n", t.pageSizeFlags, name.c_str());
    printf("TLB ways of assosiatvity                            : %d\n", t.ways);
    printf("TLB number of entories                              : %d\n", t.entories);
  }
  printf("Prefetch Size (byte)                                : %d\n", cpu.prefetchSize);
  printf("SSE3                                                : %d\n", cpu.sse3);
  printf("PCLMULQDQ                                           : %d\n", cpu.pclmulqdq);
  printf("64-bit debug store                                  : %d\n", cpu.dtes64);
  printf("MONITOR/MWAIT                                       : %d\n", cpu.monitor);
  printf("CPL qualified debug store                           : %d\n", cpu.dscpl);
  printf("virtual machine extensions                          : %d\n", cpu.vmx);
  printf("enhanced SpeedStep technology                       : %d\n", cpu.est);
  printf("thermal Monitor 2                                   : %d\n", cpu.tm2);
  printf("SSSE3                                               : %d\n", cpu.ssse3);
  printf("L1 Context ID                                       : %d\n", cpu.cnxtid);
  printf("256-bit FMA extensions                              : %d\n", cpu.fma);
  printf("CMPXCHG16B                                          : %d\n", cpu.cx16);
  printf("xTPR update control                                 : %d\n", cpu.xtpr);
  printf("Perf/Debug capability MSR                           : %d\n", cpu.pdcm);
  printf("direct cache access                                 : %d\n", cpu.dca);
  printf("SSE41                                               : %d\n", cpu.sse41);
  printf("SSE42                                               : %d\n", cpu.sse42);
  printf("x2APIC                                              : %d\n", cpu.x2apic);
  printf("MOVBE                                               : %d\n", cpu.movebe);
  printf("POPCNT                                              : %d\n", cpu.popcnt);
  printf("TSC deadline                                        : %d\n", cpu.tscDeadline);
  printf("AES instruction set                                 : %d\n", cpu.ase);
  printf("XSAVE                                               : %d\n", cpu.xsave);
  printf("OSXSAVE                                             : %d\n", cpu.osxsave);
  printf("AVX                                                 : %d\n", cpu.avx);
  printf("F16C (half-precision) FP support                    : %d\n", cpu.f16c);
  printf("RDRAND                                              : %d\n", cpu.rdrnd);
  printf("Running on a hypervisor                             : %d\n", cpu.hypervisor);
  printf("Floating Point Unit On-Chip                         : %d\n", cpu.fpu);
  printf("Virtual 8086 Mode Enhancements                      : %d\n", cpu.mve);
  printf("Debugging Extensions                                : %d\n", cpu.de);
  printf("Page Size Extension                                 : %d\n", cpu.pse);
  printf("Time Stamp Counter                                  : %d\n", cpu.tsc);
  printf("RDMSR and WRMSR Instructions                        : %d\n", cpu.msr);
  printf("Physical Address Extension                          : %d\n", cpu.pae);
  printf("Machine Check Exception                             : %d\n", cpu.mce);
  printf("CMPXCHG8B Instruction                               : %d\n", cpu.cx8);
  printf("APIC On-Chip                                        : %d\n", cpu.apic);
  printf("SYSENTER and SYSEXIT Instructions                   : %d\n", cpu.sep);
  printf("Memory Type Range Registers                         : %d\n", cpu.mttr);
  printf("Page Global Enable bit in CR4                       : %d\n", cpu.pge);
  printf("Machine Check Architecture                          : %d\n", cpu.mca);
  printf("CMOVE                                               : %d\n", cpu.cmov);
  printf("Page Attribute Table                                : %d\n", cpu.pat);
  printf("36-Bit Page Size Extension                          : %d\n", cpu.pse36);
  printf("Processor Serial Number                             : %d\n", cpu.psn);
  printf("CLFLUSH Instruction                                 : %d\n", cpu.clfsh);
  printf("Debug Store                                         : %d\n", cpu.ds);
  printf("Onboard thermal control MSRs for ACPI               : %d\n", cpu.acpi);
  printf("MMX instructions                                    : %d\n", cpu.mmx);
  printf("FXSAVE and FXRSTOR Instructions                     : %d\n", cpu.fxsr);
  printf("SSE                                                 : %d\n", cpu.sse);
  printf("SSE2                                                : %d\n", cpu.sse2);
  printf("Self Snoop                                          : %d\n", cpu.ss);
  printf("Hyper Threading                                     : %d\n", cpu.htt);
  printf("Thermal Monitor                                     : %d\n", cpu.tm);
  printf("IA-64                                               : %d\n", cpu.ia64);
  printf("Pending Break Enable                                : %d\n", cpu.pbe);
  printf("Supports RDFSBASE/RDGSBASE/WRFSBASE/WRGSBASE        : %d\n", cpu.fsgsbase);
  printf("IA32_TSC_ADJUST MSR                                 : %d\n", cpu.ia32TscAdjustMsr);
  printf("SGX                                                 : %d\n", cpu.sgx);
  printf("BMI1                                                : %d\n", cpu.bmi1);
  printf("HLE                                                 : %d\n", cpu.hle);
  printf("AVX2                                                : %d\n", cpu.avx2);
  printf("Supports Supervisor Mode Execution Protection       : %d\n", cpu.smep);
  printf("BMI2                                                : %d\n", cpu.bmi2);
  printf("ERMS                                                : %d\n", cpu.erms);
  printf("INVPCID                                             : %d\n", cpu.invpcid);
  printf("RTM                                                 : %d\n", cpu.rtm);
  printf("Supports Platform Quality of Service Monitoring     : %d\n", cpu.pqm);
  printf("Deprecates FPU CS and FPU DS values                 : %d\n", cpu.fpucsds);
  printf("Intel Memory Protection Extensions                  : %d\n", cpu.mpx);
  printf("Supports Platform Quality of Service Enforcement    : %d\n", cpu.pqe);
  printf("AVX512F                                             : %d\n", cpu.avx512f);
  printf("AVX512DQ                                            : %d\n", cpu.avx512dq);
  printf("RDSEED                                              : %d\n", cpu.rdseed);
  printf("ADX                                                 : %d\n", cpu.adx);
  printf("SMAP                                                : %d\n", cpu.smap);
  printf("AVX512IFMA                                          : %d\n", cpu.avx512ifma);
  printf("CLFLUSHOPT                                          : %d\n", cpu.clflushopt);
  printf("CLWB                                                : %d\n", cpu.clwb);
  printf("Intel Processor Trace                               : %d\n", cpu.pt);
  printf("AVX512PF                                            : %d\n", cpu.avx512pf);
  printf("AVX512ER                                            : %d\n", cpu.avx512er);
  printf("AVX512CD                                            : %d\n", cpu.avx512cd);
  printf("SHA                                                 : %d\n", cpu.sha);
  printf("AVX512BW                                            : %d\n", cpu.avx512bw);
  printf("AVX512VL                                            : %d\n", cpu.avx512vl);
  printf("PREFETCHWT1 instruction                             : %d\n", cpu.prefetchwt1);
  printf("AVX-512 Vector Bit Manipulation Instructions        : %d\n", cpu.avx512vbmi);
  printf("User-mode Instruction Prevention                    : %d\n", cpu.umip);
  printf("Memory Protection Keys for User-mode pages          : %d\n", cpu.pku);
  printf("PKU enabled by OS                                   : %d\n", cpu.ospke);
  printf("AVX-512 Vector Population Count D/Q                 : %d\n", cpu.avx512vpopcntdq);
  printf("Read Processor ID                                   : %d\n", cpu.rdpid);
  printf("SGX Launch Configuration                            : %d\n", cpu.sgxlc);
  printf("AVX-512 Neural Network Instructions                 : %d\n", cpu.avx512vnniw);
  printf("AVX-512 Multiply Accumulation Single precision      : %d\n", cpu.avx512fmaps);
  printf("Version ID of architectural performance monitoring  : %d\n", cpu.apmVersion);
  printf("Number of general-purpose PMC                       : %d\n", cpu.numGpPmc);
  printf("Bit width of general-purpose PMC                    : %d\n", cpu.widthGpPmc);
  printf("Bit length vector to enumerate architectural PMEs   : %d\n", cpu.lenEbxBit);
  printf("Core cycle event available                          : %d\n", cpu.cce);
  printf("Instruction retired event available                 : %d\n", cpu.ire);
  printf("Reference cycles event available                    : %d\n", cpu.rce);
  printf("Last-level cache reference event available          : %d\n", cpu.llcre);
  printf("Last-level cache misses event available             : %d\n", cpu.llcme);
  printf("Branch instruction retired event available          : %d\n", cpu.bire);
  printf("Branch mispredict retired event available           : %d\n", cpu.bmre);
  printf("Number of fixed-function performance counters       : %d\n", cpu.numFixedFuncPc);
  printf("Bit width of fixed-function performance counters    : %d\n", cpu.widthFixedFuncPc);
  printf("Processor Base Frequency (in MHz)                   : %d\n", cpu.baseFrequency);
  printf("Maximum Frequency (in MHz)                          : %d\n", cpu.maxFrequency);
  printf("Bus (Reference) Frequency (in MHz)                  : %d\n", cpu.busFrequency);

  return 0;
}