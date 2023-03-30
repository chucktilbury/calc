
TARGET	=	sy
OBJS	=	ptrlst.o memory.o strings.o syard.o
CARGS	=	-Wall -Wextra -g

%.o:%.c
	gcc $(CARGS) -c -o $@ $<

$(TARGET): $(OBJS)
	gcc -o $(TARGET) $(OBJS) -lm

ptrlst.o: ptrlst.c ptrlst.h
memory.o: memory.c memory.h
strings.o: strings.c strings.h
tree.o: tree.c tree.h
syard.o: syard.c

clean:
	-rm -f $(OBJS) $(TARGET)
