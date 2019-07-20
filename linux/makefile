CFLAGS=-c -Wall -O2 -I../src
LIBS = -lm -lpthread

all: libss_oled.a

libss_oled.a: ss_oled.o
	ar -rc libss_oled.a ss_oled.o ;\
	sudo cp libss_oled.a /usr/local/lib ;\
	sudo cp ../src/ss_oled.h /usr/local/include

ss_oled.o: ../src/ss_oled.cpp
	$(CC) $(CFLAGS) -D_LINUX_ ../src/ss_oled.cpp

clean:
	rm *.o libss_oled.a
