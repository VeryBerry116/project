CC = g++
CFLAGS = -O2
TARGET = Final_Rep
OBJS = project.o

ifeq ($(debug), 1)
	    CFLAGS += -g
	endif

$(TARGET) : $(OBJS)
		$(CC) $(CFLAGS) -o $@ $^

clean :
		rm -f *.o Final_Rep
		rm MemberList.txt
		rm db/*
