#!/usr/bin/env python3

# This is a quick and dirty sort program to sort the list of key words.
# I was not getting expected results from the Linux sort program. Longer
# words are sorted before a similar shorter word and strcmp() says that
# the longer word should be after the shorter word. File names are hard
# coded from simplicity.

infile = "keyword_list.txt"
outfile = "keyword_list.h"

header = '''
#ifndef _KEYWORD_LIST_H
#define _KEYWORD_LIST_H
// Auto generated file. Do not modify.

static struct _keywords_ {
    const char* name;
    TokenType type;
} keyword_list [] = {
'''

footer = '''
    {NULL, -1}
};
static const int num_keywords =
                    (sizeof(keyword_list)/sizeof(struct _keywords_))-1;

#endif /* _KEYWORD_LIST_H */

'''

lst = []
with open(infile, "r") as ifp:
    lst = ifp.readlines()

lst.sort()
with open(outfile, "w") as ofp:
    ofp.write(header)
    for item in lst:
        ofp.write("    "+item)
    ofp.write(footer)
