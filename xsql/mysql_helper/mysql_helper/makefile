.SUFFIXES:.cpp .o

CC=g++
CPPFLAGS=-I ./libmysql/$(shell uname -s)/$(shell arch)/include
$(warning,  $(CPPFLAGS))
SRCS=mysql_helper.cpp
#./libmysql/$(shell uname -s)/$(shell arch)/lib/libmysqlclient_r.a
OBJS=$(SRCS:.cpp=.o)
OUTPUT=./output/$(shell uname -s)/$(shell arch)
$(shell mkdir -p $(OUTPUT))

ifeq ($(shell uname -s),Darwin)
EXEC=$(OUTPUT)/mysql_helper.dylib
MYSQLIB=./libmysql/$(shell uname -s)/$(shell arch)/lib/libmysqlclient.a ./libmysql/$(shell uname -s)/$(shell arch)/lib/libcrypto.a ./libmysql/$(shell uname -s)/$(shell arch)/lib/libssl.a
else
EXEC=$(OUTPUT)/mysql_helper.so
MYSQLIB=./libmysql/$(shell uname -s)/$(shell arch)/lib/libmysqlclient_r.a
endif
start: $(OBJS)
	$(CC) $(CPPFLAGS) -shared -o $(EXEC) $(OBJS) $(MYSQLIB)   -fPIC

.cpp.o:
	$(CC) $(CPPFLAGS) -O2 -fPIC -Wall -o $@ -c $<

clean:
	rm -rf $(EXEC) $(OBJS)
