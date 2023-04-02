#ifndef _FILEIO_H
#define _FILEIO_H

void openFile(const char* name);
int getChar();
int consumeChar();
int getLine();
int getCol();
const char* getFname();

#define END_OF_LINE -1
#define END_OF_FILE -2

#endif /* _FILEIO_H */
