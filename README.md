CPU functionality checker for CLI

## Compiler
* Visual Studio 2019
* Clang 11.0.0

## How to Compile
### Windows

Step1) Start the libcpu/build/cpu_vs2019.sln file

Step2) Ctrl + Shift + B (Build Solution)

Step3) Setting cpuinfo project to Start App

Step4) cpuinfo.exe is generated to libcpu/build/bin/$(Platform)/%(Platform)/$(Configuration)

### Linux

Step1) Start terminal software(ex. msys2, cygwin)

Step2) Change directory to libcpu/build

Step3) Make `$make all`

Step4) cpuinfo is generated to libcpu/build/clang++

## Execution example (on Intel Core i7-7800x @3.5GHz)
```
$ ./clang++/cpuinfo.exe
Level    EAX      EBX      ECX      EDX
00000000 00000016 756e6547 6c65746e 49656e69
00000001 00050654 08100800 7ffefbbf bfebfbff
00000002 76036301 00f0b6ff 00000000 00c30000
00000003 00000000 00000000 00000000 00000000
00000004 00000000 00000000 00000000 00000000
00000005 00000040 00000040 00000003 00002020
00000006 00000077 00000002 00000009 00000000
00000007 00000000 00000000 00000000 00000000
00000008 00000000 00000000 00000000 00000000
00000009 00000000 00000000 00000000 00000000
0000000a 07300804 00000000 00000000 00000603
0000000b 00000000 00000000 000000ff 00000008
0000000c 00000000 00000000 00000000 00000000
0000000d 00000000 00000000 00000000 00000000
0000000e 00000000 00000000 00000000 00000000
0000000f 00000000 00000000 00000000 00000000
00000010 00000000 00000000 00000000 00000000
00000011 00000000 00000000 00000000 00000000
00000012 00000000 00000000 00000000 00000000
00000013 00000000 00000000 00000000 00000000
00000014 00000000 00000000 00000000 00000000
00000015 00000002 00000124 00000000 00000000
00000016 00000dac 00000fa0 00000064 00000000
80000000 80000008 00000000 00000000 00000000
80000001 00000000 00000000 00000121 2c100800
80000002 65746e49 2952286c 726f4320 4d542865
80000003 37692029 3038372d 43205830 40205550
80000004 352e3320 7a484730 00000000 00000000
80000005 00000000 00000000 00000000 00000000
80000006 00000000 00000000 01006040 00000000
80000007 00000000 00000000 00000000 00000100
80000008 0000302e 00000000 00000000 00000000

vendor                                              : GenuineIntel
brand                                               : Intel(R) Core(TM) i7-7800X CPU @ 3.50GHz
serialnumber                                        : 000000000000000000000000
stepping ID                                         : 4
model                                               : 5
family                                              : 6
processor type                                      : 0
extended model                                      : 5
extended family                                     : 0
brand index                                         : 0
CLFLUSH line size(bytes)                            : 64
number of logical processors per physical processor : 16
local APIC ID                                       : 8
-- cache 0 ---
cache type                                          : 1(Data)
cache level                                         : 1
cache size(KB)                                      : 32
self-initializing cache level                       : 1
fully associative cache                             : 0
extra threads sharing this cache                    : 2
extra processor cores on this die                   : 8
system coherency line size<(byte)                   : 64
physical line partitions                            : 1
ways of associativity                               : 8
WBINVD/INVD behavior on lower caches                : 0
inclusive to lower caches                           : 0
complex cache indexing                              : 0
number of sets                                      : 64
-- cache 1 ---
cache type                                          : 2(Instruction)
cache level                                         : 1
cache size(KB)                                      : 32
self-initializing cache level                       : 1
fully associative cache                             : 0
extra threads sharing this cache                    : 2
extra processor cores on this die                   : 8
system coherency line size<(byte)                   : 64
physical line partitions                            : 1
ways of associativity                               : 8
WBINVD/INVD behavior on lower caches                : 0
inclusive to lower caches                           : 0
complex cache indexing                              : 0
number of sets                                      : 64
-- cache 2 ---
cache type                                          : 3(Unified)
cache level                                         : 2
cache size(KB)                                      : 1024
self-initializing cache level                       : 1
fully associative cache                             : 0
extra threads sharing this cache                    : 2
extra processor cores on this die                   : 8
system coherency line size<(byte)                   : 64
physical line partitions                            : 1
ways of associativity                               : 16
WBINVD/INVD behavior on lower caches                : 0
inclusive to lower caches                           : 0
complex cache indexing                              : 0
number of sets                                      : 1024
-- cache 3 ---
cache type                                          : 3(Unified)
cache level                                         : 3
cache size(KB)                                      : 8448
self-initializing cache level                       : 1
fully associative cache                             : 0
extra threads sharing this cache                    : 16
extra processor cores on this die                   : 8
system coherency line size<(byte)                   : 64
physical line partitions                            : 1
ways of associativity                               : 11
WBINVD/INVD behavior on lower caches                : 0
inclusive to lower caches                           : 0
complex cache indexing                              : 1
number of sets                                      : 12288
-- TLB 0 ---
TLB type                                            : 1(Data)
TLB level                                           : 1
TLB Size                                            : 6(2MB/4MB)
TLB ways of assosiatvity                            : 4
TLB number of entories                              : 32
-- TLB 1 ---
TLB type                                            : 1(Data)
TLB level                                           : 1
TLB Size                                            : 8(1GB)
TLB ways of assosiatvity                            : 4
TLB number of entories                              : 4
-- TLB 2 ---
TLB type                                            : 1(Data)
TLB level                                           : 1
TLB Size                                            : 1(4KB)
TLB ways of assosiatvity                            : 4
TLB number of entories                              : 64
-- TLB 3 ---
TLB type                                            : 2(Instruction)
TLB level                                           : 1
TLB Size                                            : 6(2MB/4MB)
TLB ways of assosiatvity                            : 255
TLB number of entories                              : 8
-- TLB 4 ---
TLB type                                            : 2(Instruction)
TLB level                                           : 1
TLB Size                                            : 1(4KB)
TLB ways of assosiatvity                            : 8
TLB number of entories                              : 128
-- TLB 5 ---
TLB type                                            : 3(Unified)
TLB level                                           : 2
TLB Size                                            : 3(4KB/2MB)
TLB ways of assosiatvity                            : 6
TLB number of entories                              : 1536
-- TLB 6 ---
TLB type                                            : 3(Unified)
TLB level                                           : 2
TLB Size                                            : 8(1GB)
TLB ways of assosiatvity                            : 4
TLB number of entories                              : 16
Prefetch Size (byte)                                : 64
SSE3                                                : 1
PCLMULQDQ                                           : 1
64-bit debug store                                  : 1
MONITOR/MWAIT                                       : 1
CPL qualified debug store                           : 1
virtual machine extensions                          : 1
enhanced SpeedStep technology                       : 1
thermal Monitor 2                                   : 1
SSSE3                                               : 1
L1 Context ID                                       : 0
256-bit FMA extensions                              : 1
CMPXCHG16B                                          : 1
xTPR update control                                 : 1
Perf/Debug capability MSR                           : 1
direct cache access                                 : 1
SSE41                                               : 1
SSE42                                               : 1
x2APIC                                              : 1
MOVBE                                               : 1
POPCNT                                              : 1
TSC deadline                                        : 1
AES instruction set                                 : 1
XSAVE                                               : 1
OSXSAVE                                             : 1
AVX                                                 : 1
F16C (half-precision) FP support                    : 1
RDRAND                                              : 1
Running on a hypervisor                             : 0
Floating Point Unit On-Chip                         : 1
Virtual 8086 Mode Enhancements                      : 1
Debugging Extensions                                : 1
Page Size Extension                                 : 1
Time Stamp Counter                                  : 1
RDMSR and WRMSR Instructions                        : 1
Physical Address Extension                          : 1
Machine Check Exception                             : 1
CMPXCHG8B Instruction                               : 1
APIC On-Chip                                        : 1
SYSENTER and SYSEXIT Instructions                   : 1
Memory Type Range Registers                         : 1
Page Global Enable bit in CR4                       : 1
Machine Check Architecture                          : 1
CMOVE                                               : 1
Page Attribute Table                                : 0
36-Bit Page Size Extension                          : 1
Processor Serial Number                             : 0
CLFLUSH Instruction                                 : 1
Debug Store                                         : 1
Onboard thermal control MSRs for ACPI               : 1
MMX instructions                                    : 1
FXSAVE and FXRSTOR Instructions                     : 1
SSE                                                 : 1
SSE2                                                : 1
Self Snoop                                          : 1
Hyper Threading                                     : 1
Thermal Monitor                                     : 1
IA-64                                               : 0
Pending Break Enable                                : 1
Supports RDFSBASE/RDGSBASE/WRFSBASE/WRGSBASE        : 0
IA32_TSC_ADJUST MSR                                 : 0
SGX                                                 : 0
BMI1                                                : 0
HLE                                                 : 0
AVX2                                                : 0
Supports Supervisor Mode Execution Protection       : 0
BMI2                                                : 0
ERMS                                                : 0
INVPCID                                             : 0
RTM                                                 : 0
Supports Platform Quality of Service Monitoring     : 0
Deprecates FPU CS and FPU DS values                 : 0
Intel Memory Protection Extensions                  : 0
Supports Platform Quality of Service Enforcement    : 0
AVX512F                                             : 0
AVX512DQ                                            : 0
RDSEED                                              : 0
ADX                                                 : 0
SMAP                                                : 0
AVX512IFMA                                          : 0
CLFLUSHOPT                                          : 0
CLWB                                                : 0
Intel Processor Trace                               : 0
AVX512PF                                            : 0
AVX512ER                                            : 0
AVX512CD                                            : 0
SHA                                                 : 0
AVX512BW                                            : 0
AVX512VL                                            : 0
PREFETCHWT1 instruction                             : 0
AVX-512 Vector Bit Manipulation Instructions        : 0
User-mode Instruction Prevention                    : 0
Memory Protection Keys for User-mode pages          : 0
PKU enabled by OS                                   : 0
AVX-512 Vector Population Count D/Q                 : 0
Read Processor ID                                   : 0
SGX Launch Configuration                            : 0
AVX-512 Neural Network Instructions                 : 0
AVX-512 Multiply Accumulation Single precision      : 0
Version ID of architectural performance monitoring  : 4
Number of general-purpose PMC                       : 8
Bit width of general-purpose PMC                    : 48
Bit length vector to enumerate architectural PMEs   : 7
Core cycle event available                          : 1
Instruction retired event available                 : 1
Reference cycles event available                    : 1
Last-level cache reference event available          : 1
Last-level cache misses event available             : 1
Branch instruction retired event available          : 1
Branch mispredict retired event available           : 1
Number of fixed-function performance counters       : 3
Bit width of fixed-function performance counters    : 48
Processor Base Frequency (in MHz)                   : 3500
Maximum Frequency (in MHz)                          : 4000
Bus (Reference) Frequency (in MHz)                  : 100
```

