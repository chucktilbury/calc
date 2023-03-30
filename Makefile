
TARGET	=	syard
OBJS	=	ptrlst.o memory.o strings.o value.o syard.o
CARGS	=	-Wall -Wextra -g

%.o:%.c
	gcc $(CARGS) -c -o $@ $<

$(TARGET): $(OBJS)
	gcc -o $(TARGET) $(OBJS) -lm

ptrlst.o: ptrlst.c ptrlst.h
memory.o: memory.c memory.h
strings.o: strings.c strings.h
value.o: value.c value.h

syard.o: syard.c

clean:
	-rm -f $(OBJS) $(TARGET)
