#ifndef _CMDS_H
#define _CMDS_H

#include <stdbool.h>

/*
 * HELP -- Print the help text
 * QUIT -- Quit the program
 * SYMS -- Show the symbol table
 * PRINT -- Print a symbol
 * VERBO -- Set the verbosity level
 * LOAD -- Load a set of lines from a file
 * SAVE -- Save the state so it could be loaded again
 * SOLVE -- Solve a stored expression
 */

bool do_HELP();
bool do_QUIT();
bool do_SYMS();
bool do_PRINT();
bool do_VERBOSITY();
bool do_LOAD();
bool do_SAVE();
bool do_SOLVE();

#endif /* _CMDS_H */
