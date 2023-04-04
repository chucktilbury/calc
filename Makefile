
TARGET	=	calc
OBJS	=	scan.o \
			ptrlst.o \
			memory.o \
			strings.o \
			value.o \
			errors.o \
			fileio.o \
			cmds.o \
			calc.o \
			parse.o
CARGS	=	-Wall -Wextra
DEBUG	=	-g3
LIBS	=	-lm -lreadline

%.o:%.c
	gcc $(CARGS) $(DEBUG) -c -o $@ $<

$(TARGET): $(OBJS) calc.c
	gcc $(DEBUG) -o $(TARGET) main.c $(OBJS) $(LIBS)

keyword_list.h: keyword_list.txt
	./sort.py

ptrlst.o: ptrlst.c ptrlst.h
memory.o: memory.c memory.h
strings.o: strings.c strings.h
value.o: value.c value.h
scan.o: scan.c scan.h keyword_list.h
errors.o: errors.c errors.h
parse.o: parse.c parse.h

clean:
	-rm -f $(OBJS) $(TARGET) keyword_list.h
