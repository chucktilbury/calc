#!/usr/bin/env python3

# This is a quick and dirty sort program to sort the list of key words.
# I was not getting expected results from the Linux sort program. Longer
# words are sorted before a similar shorter word and strcmp() says that
# the longer word should be after the shorter word. File names are hard
# coded from simplicity.

infile = "keyword_list.txt"
outfile = "keyword_list.h"

lst = []
with open(infile, "r") as ifp:
    lst = ifp.readlines()

lst.sort()
with open(outfile, "w") as ofp:
    for item in lst:
        ofp.write(item)
