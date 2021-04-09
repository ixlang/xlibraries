.SUFFIXES:.cpp .o

CC=clang++
CPPFLAGS= -std=c++11 -I ./zxing_cpp/core/src
$(warning,  $(CPPFLAGS))
SRCS=./zxing_cpp/core/src/forxlang.cpp

OBJS=$(SRCS:.cpp=.o)
OUTPUT=./output/$(shell uname -s)/$(shell arch)
$(shell mkdir -p $(OUTPUT))

ifeq ($(shell uname -s),Darwin)
EXEC=$(OUTPUT)/ZXingCore.dylib
ZXINGLIB=./zxing_cpp/build/core/libZXingCore.a
else
EXEC=$(OUTPUT)/ZXingCore.so
ZXINGLIB=./zxing_cpp/core/libZXingCore.a
endif
start: $(OBJS)
	$(CC) $(CPPFLAGS) -shared -o $(EXEC) $(OBJS) $(ZXINGLIB) -fPIC -static-libstdc++ 

.cpp.o:
	$(CC) $(CPPFLAGS) -O2 -fPIC -Wall -o $@ -c $<

clean:
	rm -rf $(EXEC) $(OBJS)
