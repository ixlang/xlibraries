UNAME_S := $(shell uname -s)


ifeq ($(ARCH),)
ARCH := $(shell arch)
endif

ifeq ($(XBUILD),1)
CC = $(ARCH)-linux-gnu-gcc
C++ = $(ARCH)-linux-gnu-g++
LINK = $(ARCH)-linux-gnu-g++
else
ifeq ($(UNAME_S),Darwin)
CC = "/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/clang" 
C++ = "/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/clang++" 
LINK = "/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/clang++" 
else
CC = gcc
C++ = g++
LINK = g++
endif
endif

OUTPUTPATH=output/$(UNAME_S)/$(ARCH)

ifeq ($(UNAME_S),Darwin)
LIBGCC = 
SEH = 
IMPORTPATH=./fftw-3.3.6-pl2/.libs
LFLAGS = -fPIC -shared -w -static-libstdc++ $(LIBGCC) -lpthread -ldl -lz -lm -fvisibility=hidden
else
LIBGCC = -static-libgcc
SEH =  -fno-exceptions 
IMPORTPATH=./fftw-3.3.6-pl2/.libs
LFLAGS = -fPIC -shared -Wl,-Bsymbolic -w -static-libstdc++ $(LIBGCC) -lpthread -ldl -lz -lm -fvisibility=hidden -Wl,-z,defs
endif

LIBPATH:=objs/$(UNAME_S)/$(ARCH)
$(shell mkdir -p $(LIBPATH))


$(shell mkdir -p $(OUTPUTPATH))
GCFLAGS= -O3 -w -fPIC  -Wno-unused-parameter $(SEH) -Wno-strict-aliasing -Wno-sign-compare -Wno-extra -fno-stack-protector -fvisibility=hidden

CPPFLAGS= -std=c++11 $(GCFLAGS) -I ./fftw-3.3.6-pl2/api -I ./xfftw
CFLAGS= $(GCFLAGS) -I ./fftw-3.3.6-pl2/api -I ./xfftw



ifeq ($(UNAME_S),Darwin)
TARGET=$(OUTPUTPATH)/xfftw.dylib
else
TARGET=$(OUTPUTPATH)/xfftw.so
endif

SOURCE= ./xfftw/xfftw.cpp


LIBOBJ=$(addprefix $(LIBPATH)/, $(addsuffix .o, $(basename $(SOURCE)))) 



IMPORTLIB=	$(IMPORTPATH)/libfftw3.a

	
all: $(TARGET)

target: $(TARGET)

lib: $(TARGET)

$(LIBPATH)/%.o: %.c
	if [ ! -d $(dir $@) ]; then mkdir -p $(dir $@);  fi;\
	$(CC) $(CFLAGS) -o $@ -c $<

$(LIBPATH)/%.o: %.cpp
	if [ ! -d $(dir $@) ]; then mkdir -p $(dir $@); fi;\
	$(C++) $(CPPFLAGS) -o $@ -c $<

ifeq ($(UNAME_S),Darwin)
$(LIBPATH)/%.o: %.mm 
	if [ ! -d $(dir $@) ]; then mkdir -p $(dir $@); fi;\
	$(C++) $(CPPFLAGS) -o $@ -c $<
endif

$(TARGET): $(LIBOBJ)
	$(LINK) $(LFLAGS) -o $(TARGET) $(LIBOBJ) $(IMPORTLIB)

clean:
	rm -f $(TARGET) $(LIBOBJ)
