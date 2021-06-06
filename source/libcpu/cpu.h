//
// This file is subject to the terms and conditions defined in
// file 'LICENSE', which is part of this source code package.
//

#ifndef LIB_CPU_INFO_H
#define LIB_CPU_INFO_H

#include <vector>

namespace libcpu {

//!
//! @brief TLB(Translation Look-aside Buffer) informations
//!
struct Tlb
{
  //! @brief TLB type
  //!      0: null
  //!      1: data
  //!      2: instruction
  //!      3: unified
  int type = 0;

  //! @brief TLB level
  //!      0: null
  //!      1: L1
  //!      2: L2
  //!      3: L3
  int level = 0;

  //! @brief TLB page size bit flags:
  //!      0: null
  //!      1: 4KB
  //!      2: 2MB
  //!      3: 4MB
  //!      4: 1GB
  //!      5: 4K...256M(IA-64)
  //!   6-31: reserved
  int pageSizeFlags = 0;

  //! @brief TLB ways of assosiatvity
  //!      0: null
  //!      1: 1way
  //!      2: 2way
  //!      ...
  //!      ff: full
  int ways = 0;

  //! @brief number of entories
  int entories = 0;
};

//!
//! @brief Cache informations
//!
struct Cache
{
  //! @brief cache type
  //!      0: null
  //!      1: data
  //!      2: instruction
  //!      3: unified
  //! 4...31: reserved
  int type = 0;

  //! @brief cache level(start at 1)
  int level = 0;

  //! @brief extra threads sharing this cache
  int thread = 0;

  //! @brief extra processor cores on this die
  int cores = 0;

  //! @brief ways of associativity
  int ways = 0;

  //! @brief physical line partitions
  int partition = 0;

  //! @brief system coherency line size(byte)
  int coherencyLineSize = 0;

  //! @brief number of sets
  int sets = 0;

  //! @brief cache KB size(= sets * lineSize * way)
  int size = 0;

  //! @brief self-initializing ?
  bool selfInit = false;

  //! @brief fully associative ?
  bool fullAssociative = false;

  //! @brief write-back invalidate?
  bool writeBackInvalid = false;

  //! @brief inclusive of lower levels?
  bool inclusiveLowerLevels = false;

  //! @brief complex indexing?
  bool complexIndexing = false;
};

//!
//! @brief CPU informations
//!
//! @see https://software.intel.com/sites/default/files/managed/c5/15/architecture-instruction-set-extensions-programming-reference.pdf
//! @see https://www.amd.com/system/files/TechDocs/25481.pdf
//! @see https://en.wikipedia.org/wiki/CPUID#EAX.3D0:_Highest_Function_Parameter
//!
struct Cpu
{
  //! @brief Vendor ID string
  char vendor[32] = "";

  //! @brief Brand ID
  char brand[64] = "";

  //! @brief 96 bit processor serial number
  //! @note available in Pentium III processor only.
  char serialnumber[12] = { 0 };

  //! @brief TLB
  std::vector<Tlb> tlb;

  //! @brief Cache
  std::vector<Cache> cache;

  //! @brief Stepping ID
  //! @note Stepping ID is a product revision number assigned due to fixed 
  //!       errata or other changes
  int stepping = 0;

  //! @brief Model ID
  int model = 0;

  //! @brief Family ID
  int family = 0;

  //! @brief Processor Type
  int processorType = 0;

  //! @brief Extended Model ID
  int extModel = 0;

  //! @brief Extended Family ID
  int extFamily = 0;

  //! @brief Brand Index
  int brandIdx = 0;

  //! @brief CLFLUSH line size (Value ∗ 8 = cache line size in bytes)
  int clflashChunkCount = 0;

  //! @brief Maximum number of addressable IDs for logical processors in this
  //         physical package
  int logicalProcessors = 0;

  //! @brief Initial APIC ID
  int apicId = 0;

  //! @brief Physical Address Bits
  int physicalAddressBits = 0;

  //! @brief Virtual Address Bits
  int virtualAddressBits = 0;

  //! @brief Prefetch Size (byte)
  int prefetchSize = 0;

  //! @brief Version ID of architectural performance monitoring
  int apmVersion = 0;

  //! @brief Number of general-purpose performance monitoring counter per
  //!        logical processor
  int numGpPmc = 0;

  //! @brief Bit width of general-purpose, performance monitoring counter
  int widthGpPmc = 0;

  //! @brief Length of EBX bit vector to enumerate architectural performance 
  //!        monitoring events
  int lenEbxBit = 0;

  //! @brief Processor Base Frequency (in MHz)
  int baseFrequency = 0;

  //! @brief  Maximum Frequency (in MHz)
  int maxFrequency = 0;

  //! @brief Bus (Reference) Frequency (in MHz)
  int busFrequency = 0;

  //! @brief Prescott New Instructions-SSE3 (PNI)
  bool sse3 = false;

  //! @brief PCLMULQDQ support
  bool pclmulqdq = false;

  //! @brief 64-bit debug store (edx bit 21)
  bool dtes64 = false;

  //! @brief MONITOR and MWAIT instructions (SSE3). 
  //!        MISC_ENABLE.MONE, MISC_ENABLE.LCMV MONITOR_FILTER_LINE_SIZE MSR
  bool monitor = false;

  //! @brief CPL qualified debug store
  bool dscpl = false;

  //! @brief Virtual Machine eXtensions
  bool vmx = false;

  //! @brief Safer Mode Extensions (LaGrande)
  bool smx = false;

  //! @brief Enhanced SpeedStep
  bool est = false;

  //! @brief Thermal Monitor 2
  bool tm2 = false;

  //! @brief Supplemental SSE3 instructions
  bool ssse3 = false;

  //! @brief L1 Context ID
  bool cnxtid = false;

  //! @brief Silicon Debug interface
  bool sdbg = false;

  //! @brief Fused multiply-add (FMA3)
  bool fma = false;

  //! @brief CMPXCHG16B instruction
  bool cx16 = false;

  //! @brief Can disable sending task priority messages
  bool xtpr = false;

  //! @brief Perfmon and debug capability
  bool pdcm = false;

  //! @brief Process context identifiers (CR4 bit 17)
  bool pcid = false;

  //! @brief Direct cache access for DMA writes
  bool dca = false;

  //! @brief SSE4.1 instructions
  bool sse41 = false;

  //! @brief SSE4.2 instructions
  bool sse42 = false;

  //! @brief x2APIC support
  bool x2apic = false;

  //! @brief MOVBE instruction (big-endian)
  bool movebe = false;

  //! @brief POPCNT instruction
  bool popcnt = false;

  //! @brief APIC supports one-shot operation using a TSC deadline value
  bool tscDeadline = false;

  //! @brief AES instruction set
  bool ase = false;

  //! @brief XSAVE, XRESTOR, XSETBV, XGETBV
  bool xsave = false;

  //! @brief XSAVE enabled by OS
  bool osxsave = false;

  //! @brief Advanced Vector Extensions
  bool avx = false;

  //! @brief F16C (half-precision) FP support
  bool f16c = false;

  //! @brief RDRAND (on-chip random number generator) support
  bool rdrnd = false;

  //! @brief Running on a hypervisor (always 0 on a real CPU, but also with some
  //!        hypervisors)
  bool hypervisor = false;

  //! @brief Floating Point Unit On-Chip
  bool fpu = false;

  //! @brief Virtual 8086 Mode Enhancements
  bool mve = false;

  //! @brief Debugging Extensions
  bool de = false;

  //! @brief Page Size Extension
  bool pse = false;

  //! @brief Time Stamp Counter
  bool tsc = false;

  //! @brief Model Specific Registers RDMSR and WRMSR Instructions
  bool msr = false;

  //! @brief Physical Address Extension
  bool pae = false;

  //! @brief Machine Check Exception
  bool mce = false;

  //! @brief CMPXCHG8B Instruction
  bool cx8 = false;

  //! @brief APIC On-Chip
  bool apic = false;

  //! @brief SYSENTER and SYSEXIT Instructions
  bool sep = false;

  //! @brief Memory Type Range Registers
  bool mttr = false;

  //! @brief Page Global Enable bit in CR4
  bool pge = false;

  //! @brief Machine Check Architecture
  bool mca = false;

  //! @brief CMOVE
  bool cmov = false;

  //! @brief Page Attribute Table
  bool pat = false;

  //! @brief 36-Bit Page Size Extension
  bool pse36 = false;

  //! @brief Processor Serial Number
  bool psn = false;

  //! @brief CLFLUSH Instruction
  bool clfsh = false;

  //! @brief Debug Store
  bool ds = false;

  //! @brief Onboard thermal control MSRs for ACPI
  bool acpi = false;

  //! @brief MMX instructions
  bool mmx = false;

  //! @brief  FXSAVE and FXRSTOR Instructions
  bool fxsr = false;

  //! @brief SSE
  bool sse = false;

  //! @brief SSE2
  bool sse2 = false;

  //! @brief Self Snoop
  bool ss = false;

  //! @brief Hyper-Threading Technology
  bool htt = false;

  //! @brief Thermal Monitor
  bool tm = false;

  //! @brief IA-64
  bool ia64 = false;

  //! @brief Pending Break Enable
  bool pbe = false;

  //
  //
  // 04H Deterministic Cache Parameters Leaf 
  //
  //


  //
  //
  // 05H MONITOR/MWAIT Leaf 
  //
  //

  //! @brief Smallest monitor line size
  int smallestMonitorLineSize = 0;

  //! @brief Largest monitor line size
  int largestMonitorLineSize = 0;

  //! @brief Enumeration supported beyond EAX/EBX
  bool es = false;

  //! @brief Interrupts supported as break events
  bool ib = false;

  //! @brief Number of C0 sub C states supported using MWAIT
  int numC0Mwait = 0;

  //! @brief Number of C1 sub C states supported using MWAIT
  int numC1Mwait = 0;

  //! @brief Number of C2 sub C states supported using MWAIT
  int numC2Mwait = 0;

  //! @brief Number of C3 sub C states supported using MWAIT
  int numC3Mwait = 0;

  //! @brief Number of C4 sub C states supported using MWAIT
  int numC4Mwait = 0;

  //! @brief Number of C5 sub C states supported using MWAIT
  int numC5Mwait = 0;

  //! @brief Number of C6 sub C states supported using MWAIT
  int numC6Mwait = 0;

  //! @brief Number of C7 sub C states supported using MWAIT
  int numC7Mwait = 0;

  //
  //
  // 06H Thermal and Power Management Leaf
  //
  //

  //! @brief Digital temperature sensor is supported 
  bool digitalTempSensor = false;

  //! @brief Intel Turbo Boost Technology Available
  bool turboBoost = false;

  //! @brief ARAT. APIC-Timer-always-running feature is supported if set
  bool arat = false;

  //! @brief PLN. Power limit notification controls are supported if set
  bool pln = false;

  //! @brief ECMD. Clock modulation duty cycle extension is supported if set
  bool ecmd = false;

  //! @brief PTM. Package thermal management is supported if set
  bool ptm = false;

  //! @brief HWP. HWP base registers (IA32_PM_ENABLE[bit 0], 
  //!        IA32_HWP_CAPABILITIES, IA32_HWP_REQUEST, IA32_HWP_STATUS) are
  //!        supported if set
  bool hwp = false;

  //! @brief HWP_Notification. IA32_HWP_INTERRUPT MSR is supported if set
  bool hwpNotification = false;

  //! @brief HWP_Activity_Window. IA32_HWP_REQUEST[bits 41:32] is supported
  //!        if set
  bool hwpActivityWindow = false;

  //! @brief HWP_Energy_Performance_Preference. IA32_HWP_REQUEST[bits 31:24]
  //!        is supported if set
  bool hwpEnergyPerformancePreference = false;

  //! @brief HWP_Package_Level_Request. IA32_HWP_REQUEST_PKG MSR is supported
  //!        if set
  bool hwpPackageLevelRequest = false;

  //! @brief HDC. HDC base registers IA32_PKG_HDC_CTL, IA32_PM_CTL1,
  //!         IA32_THREAD_STALL MSRs are supported if set
  bool hdc = false;

  //! @brief Intel® Turbo Boost Max Technology 3.0 availabe
  bool turboBoostMax3 = false;

  //! @brief HWP Capabilities. Highest Performance change is supported if set
  bool hwpCapabilities = false;

  //! @brief HWP PECI override is supported if set
  bool hwpPeci = false;

  //! @brief Flexible HWP is supported if set
  bool flexHwp = false;

  //! @brief Fast access mode for the IA32_HWP_REQUEST MSR is supported if set
  bool fastAccessMode = false;

  //! @brief HW_FEEDBACK. IA32_HW_FEEDBACK_PTR, IA32_HW_FEEDBACK_CONFIG
  //!        IA32_PACKAGE_THERM_STATUS bit 26 and IA32_PACKAGE_THERM_INTERRUPT
  //!        bit 25 are supported if set
  bool hwFeedback = false;

  //! @brief Ignoring Idle Logical Processor HWP request is supported if set
  bool ignoringIdle = false;

  //! @brief Number of Interrupt Thresholds in Digital Thermal Sensor
  int numInterruptThresholds = 0;

  //! @brief Hardware Coordination Feedback Capability
  bool hwCoordinationFeedbackCapability = false;

  //! @brief The processor supports performance-energy bias preference
  bool performanceEnergyBiasPreference = false;

  //! @brief Bitmap of supported hardware feedback interface capabilities
  //!          0 = When set to 1, indicates support for performance capability
  //!              reporting
  //!          1 = When set to 1, indicates support for energy efficiency
  //!              capability reporting
  int bitmapHwFeedback = 0;

  //! @brief Enumerates the size of the hardware feedback interface structure
  //!        in number of 4 KB pages using minus-one notation
  int enumatatesSize = 0;

  //! @brief Index (starting at 0) of this logical processor’s row in the
  //!        hardware feedback interface structure
  int rowIndexOfLogicalProcessor = 0;

  //
  //
  // 07H Structured Extended Feature Flags Enumeration Leaf
  //
  //

  //! @brief Supports RDFSBASE/RDGSBASE/WRFSBASE/WRGSBASE 
  bool fsgsbase = false;

  //! @brief IA32_TSC_ADJUST MSR
  bool ia32TscAdjustMsr = false;

  //! @brief SGX (Softwware Gard Extension)
  bool sgx = false;

  //! @brief BMI1
  bool bmi1 = false;

  //! @brief HLE
  bool hle = false;

  //! @brief AVX2
  bool avx2 = false;

  //! @brief Supports Supervisor Mode Execution Protection
  bool smep = false;

  //! @brief BMI2
  bool bmi2 = false;

  //! @brief ERMS
  bool erms = false;

  //! @brief INVPCID
  bool invpcid = false;

  //! @brief RTM
  bool rtm = false;

  //! @brief Supports Platform Quality of Service Monitoring
  bool pqm = false; 

  //! @brief Deprecates FPU CS and FPU DS values
  bool fpucsds = false;

  //! @brief Intel Memory Protection Extensions
  bool mpx = false;

  //! @brief Supports Platform Quality of Service Enforcement
  bool pqe = false;

  //! @brief AVX512F
  bool avx512f = false;

  //! @brief AVX512DQ
  bool avx512dq = false;

  //! @brief RDSEED
  bool rdseed = false;

  //! @brief Multi-Precision Add-Carry Instruction Extension
  bool adx = false;

  //! @brief Supervisor Mode Access Prevention
  bool smap = false;

  //! @brief AVX512IFMA
  bool avx512ifma = false;
 
  //! @brief CLFLUSHOPT
  bool clflushopt = false;

  //! @brief CLWB
  bool clwb = false;

  //! @brief Intel Processor Trace
  bool pt = false;

  //! @brief AVX512PF
  bool avx512pf = false;

  //! @brief AVX512ER
  bool avx512er = false;

  //! @brief AVX512CD
  bool avx512cd = false;

  //! @brief SHA
  bool sha = false;

  //! @brief AVX512BW
  bool avx512bw = false;

  //! @brief AVX512VL
  bool avx512vl = false;

  //! @brief PREFETCHWT1 instruction
  bool prefetchwt1 = false;

  //! @brief AVX-512 Vector Bit Manipulation Instructions
  bool avx512vbmi = false;

  //! @brief User-mode Instruction Prevention
  bool umip = false;

  //! @brief Memory Protection Keys for User-mode pages
  bool pku = false;

  //! @brief PKU enabled by OS
  bool ospke = false;

  //! @brief WAITPKG
  bool waitPkg = false;

  //! @brief AVX512_VBMI2
  bool avx512vbmi2 = false;

  //! @brief GFNI
  bool gfni = false;

  //! @brief VAES
  bool vaes = false;

  //! @brief VPCLMULQDQ
  bool vpclmulqdq = false;

  //! @brief AVX512_VNNI
  bool avx512vnni = false;

  //! @brief AVX512_BITALG
  bool avx512bitalg = false;

  //! @brief AVX512 Vector Population Count D/Q
  bool avx512vpopcntdq = false;

  //! @brief MAWAU used by the BNDLDX and BNDSTX instructions in 64-bit mode
  int mawau = 0;

  //! @brief Read Processor ID
  bool rdpid = false;

  //! @brief CLDEMOTE. Supports cache line demote if 1
  bool cldemote = false;

  //! @brief MOVDIRI. Supports MOVDIRI if 1
  bool movdiri = false;

  //! @brief MOVDIR64B. Supports MOVDIR64B if 1
  bool movdir64b = false;

  //! @brief ENQCMD: Supports Enqueue Stores if 1
  bool enqcmd = false;

  //! @brief SGX Launch Configuration
  bool sgxlc = false;

  //! @brief AVX-512 Neural Network Instructions
  bool avx512vnniw = false;

  //! @brief AVX-512 Multiply Accumulation Single precision
  bool avx512fmaps = false;

  //! @brief Fast Short REP MOV
  bool repmov = false;

  //! @brief AVX512_VP2INTERSECT
  bool avx512Vp2intersect = false;

  //! @brief PCONFIG
  bool pconfig = false;

  //! @brief Enumerates support for indirect branch restricted speculation(IBRS)
  //!        and the indirect branch predictor barrier(IBPB)
  bool emuIbrs = false;

  //! @brief Enumerates support for single thread indirect branch
  //!        predictors(STIBP)
  bool emuStibp = false;

  //! @brief Enumerates support for the IA32_ARCH_CAPABILITIES MSR
  bool emuIa32ArchCapabilitiesMsr = false;

  //! @brief Enumerates support for the IA32_CORE_CAPABILITIES MSR
  bool emuIa32CoreCapabilitiesMsr = false;

  //! @brief Enumerates support for Speculative Store Bypass Disable(SSBD)
  bool emuSsbd = false;

  //
  //
  // 09H Direct Cache Access Information Leaf
  //
  //

  //! @brief Value of bits [31:0] of IA32_PLATFORM_DCA_CAP MSR
  int ia32PlatformDcaCap = 0;

  //
  //
  // 0AH Direct Architectural Performance Monitoring Leaf 
  //
  //

  //! @brief Core cycle event available
  bool cce = false;

  //! @brief Instruction retired event available
  bool ire = false;

  //! @brief Reference cycles event available
  bool rce = false;

  //! @brief Last-level cache reference event available
  bool llcre = false;

  //! @brief Last-level cache misses event available
  bool llcme = false;

  //! @brief Branch instruction retired event available
  bool bire = false;

  //! @brief Branch mispredict retired event available
  bool bmre = false;

  //! @brief Number of fixed-function performance counters(if Version ID > 1)
  int numFixedFuncPc = 0;

  //! @brief Bit width of fixed-function performance counters(if Version ID > 1)
  int widthFixedFuncPc = 0;

  //
  //
  // 0BH Direct Architectural Performance Monitoring Leaf
  //
  //

  //! @brief Number of bits to shift right on x2APIC ID to get a unique topology
  //!        ID of the next level type. All logical processors with the same
  //!        next level ID share current level

  //! @brief Number of logical processors at this level type. The number
  //!        reflects configuration as shipped by Intel

  //! @brief Branch mispredict retired event available

  //! @brief Branch mispredict retired event available



  //! @brief LAHF and SAHF in PM64
  bool ahf64 = false;

  //! @brief Core multi-processing legacy mode
  bool cmpLegacy = false;

  //! @brief Secure virtual machine
  bool svm = false;

  //! @brief Extended APIC space
  bool extApicSpace = false;

  //! @brief LOCK MOV CR0 means MOV CR8
  bool altMovCr8 = false;

  //! @brief Count the Number of Leading Zero Bits
  bool lzcnt = false;

  //! @brief Streaming SIMD Extensions 4a
  bool sse4a = false;

  //! @brief misaligned SSE mode
  bool misalignedSse = false;

  //! @brief PREFETCH and PREFETCHW (K8 Rev G and K8L+) for 3D-Now!
  bool prefetch3DNow = false;

  //! @brief SKINIT and STGI
  bool skinit = false;

  //! @brief SYSCALL and SYSRET instructions
  bool sysCallSysRet = false;

  //! @brief Page Attribute Table
  // bool pat = false;

  //! @brief MMX
  bool amdMmx = false;

  //! @brief FXSAVE and FXRSTOR instruction optimizations
  bool amdFfxsr = false;

  //! @brief 1-GB large page suppor
  bool amd1GBPage = false;

  //! @brief RDTSCP instruction
  bool rdtscp = false;

  //! @brief Processor Initialization and Long-Mode Activation
  bool amdLm = false;

  //! @brief AMD extensions to 3DNow! instructions
  bool amd3DNowExt = false;

  //! @brief 3DNow!™ instructions 
  bool amd3DNow = false;

  //! @brief number of address space identifiers (ASID) 
  int amdSvmRev = 0;

  //! @brief Number of address space identifiers
  int amdNasid = 0;

  //! @brief Nested Paging
  bool amdNp = false;

  //! @brief LBR virtualization
  bool amdLbr = false;

  //! @brief SVM lock
  bool amdSvml = false;

  //! @brief NRIP save
  bool amdNrips = false;

  //! @brief MSR based TSC rate control
  bool amdTscRateMsr = false;

  //! @brief VMCB clean bits
  bool amdVmcbClean = false;

  //! @brief flush by ASID
  bool amdFlushByAsid = false;

  //! @brief DecodeAssists
  bool amdDecodeAssists = false;

  //! @brief Pause intercept filter
  bool amdPauseFilter = false;

  //! @brief  PAUSE filter threshold
  bool amdPauseFilterThresh = false;

  //! @brief 128-bit SSE
  bool amdFp128 = false;

  //! @brief MOVU SSE
  bool amdMoveu = false;
};


//!
//! @brief cpu infomation detection
//!
void detect_cpu_info(Cpu *cpu);


//!
//! @brief print cpuid
//!
void print_cpuid();

} // namespace libcpu

#endif // LIB_CPU_INFO_H