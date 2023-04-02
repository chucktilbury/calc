#ifndef _ERRORS_H
#define _ERRORS_H

void syntaxError(const char* fmt, ...);
void syntaxWarning(const char* fmt, ...);
void generalError(const char* fmt, ...);
void fatalError(const char* fmt, ...);
int getNumErrors();
int getNumWarnings();

#endif /* _ERRORS_H */
