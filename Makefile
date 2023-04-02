
TARGET	=	calc
OBJS	=	ptrlst.o \
			memory.o \
			strings.o \
			value.o \
			scan.o \
			errors.o \
			fileio.o
CARGS	=	-Wall -Wextra
DEBUG	=	-g3
LIBS	=	-lm -lreadline

%.o:%.c
	gcc $(CARGS) $(DEBUG) -c -o $@ $<

$(TARGET): $(OBJS) calc.c
	gcc $(DEBUG) -o $(TARGET) main.c $(OBJS) $(LIBS)

ptrlst.o: ptrlst.c ptrlst.h
memory.o: memory.c memory.h
strings.o: strings.c strings.h
value.o: value.c value.h
scan.o: scan.c scan.h
errors.o: errors.c errors.h

clean:
	-rm -f $(OBJS) $(TARGET)
