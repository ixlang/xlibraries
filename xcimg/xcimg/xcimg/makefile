.SUFFIXES:.cpp .o

CC=g++
$(warning,  $(CPPFLAGS))
SRCS=xcimg.cpp
#./libmysql/$(shell uname -s)/$(shell arch)/lib/libmysqlclient_r.a
OBJS=$(SRCS:.cpp=.o)
OUTPUT=./output/$(shell uname -s)/$(shell arch)
$(shell mkdir -p $(OUTPUT))
EXEC=$(OUTPUT)/xcimg.so

start: $(OBJS)
	$(CC) $(CPPFLAGS) -shared -o $(EXEC) $(OBJS) -fPIC -static-libstdc++ 

.cpp.o:
	$(CC) -std=c++11 $(CPPFLAGS) -O2 -fPIC -Wall -o $@ -c $<

clean:
	rm -rf $(EXEC) $(OBJS)
