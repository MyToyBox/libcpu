# compiler setting
CXX          = clang++
CXXFLAGS     = -std=c++14 -O2 -Wall -Wextra -MMD -MP -save-temps=obj

# target name
TARGETDIR    = ./$(CXX)
TARGET       = $(TARGETDIR)/cpuinfo
STATICLIBCPU = $(TARGETDIR)/libcpu.a

# source files
INCLUDE      = ../source
SRCDIR       = $(INCLUDE)
SRCLIBCPUDIR = $(SRCDIR)/libcpu
SRCLIBCPU    = $(wildcard $(SRCLIBCPUDIR)/*.cpp)
SRCTARGETDIR = $(SRCDIR)/cpuinfo
SRCTARGET    = $(wildcard $(SRCTARGETDIR)/*.cpp)

# object files
OBJDIR       = ./$(CXX)/obj
OBJLIBCPU    = $(addprefix $(OBJDIR)/, $(notdir $(SRCLIBCPU:.cpp=.o)))
OBJTARGET    = $(addprefix $(OBJDIR)/, $(notdir $(SRCTARGET:.cpp=.o)))

all: outdir $(TARGET)

outdir:
	mkdir -p $(TARGETDIR)
	mkdir -p $(OBJDIR)

clean:
	rm -R -f $(OBJDIR)
	rm -R -f $(TARGETDIR)

$(TARGET): $(OBJTARGET) $(STATICLIBCPU) 
	$(CXX) $(CXXFLAGS) -I$(INCLUDE) -o $@ $^

$(STATICLIBCPU): $(OBJLIBCPU)
	ar r $@ $^

$(OBJDIR)/%.o: $(SRCLIBCPUDIR)/%.cpp
	$(CXX) $(CXXFLAGS) -I$(INCLUDE) -o $@ -c $<

$(OBJDIR)/%.o: $(SRCTARGETDIR)/%.cpp
	$(CXX) $(CXXFLAGS) -I$(INCLUDE) -o $@ -c $<

.PHONY: all clean outdir
