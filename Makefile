
CC = g++
CFLAGS += -I./src
LDFLAGS += -lcurl

OBJS += src/HttpClient.o
OBJS += demo/main.o

all:httpclient

httpclient : $(OBJS)
	$(CC) -o $@ $^ $(LDFLAGS)


%.o:%.cpp
	$(CC) $(CFLAGS) -c -o $@ $^

.PHONY: clean

clean:
	rm httpclient $(OBJS)


