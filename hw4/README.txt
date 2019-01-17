##################################
#       CSCI e-26 -- hw4         #
#         Matthew Thomas         #
# matthew_thomas@hms.harvard.edu #
#           README.txt           #
##################################

Files:
--wlfiler6.c
--wldata.c
--wlmain_mod.c
--wl_mods.h
--README.txt
--typescript

Note: base code in wlfiler6.c and wldata.c were copied/influence from code samples
in lectures 6 and 7, but with modifications made by me to work with the new linked list
structure for the hw4 assignment.

I moved some common definitions to a new header file, wl_mods.h, to avoid modifying the
wl.h file.

The wldata.c file implements the modularity approach Bruce discussed in lecture 7 to
separate the storage system from the containers themselves (a la wordstore2.c and
wlo.c).

The wlmain_mod.c file is my modified file that include the read_word() function for
question 9, part 3b.

In the typescript, I print out the cc-errors file located in _testdir/. The error is due
to the deltest.c file linked to from the course directory. For the typescript, I also copy
the dataset.big file located in _testdir/ and remove the comment lines at the beginning of
the file. I "cat" this out to show I do not change the remaind of the "big" text, and run
this through a second compilation using my wlmain_mod.c file to demonstrate my read_word()
function. This second compiled file I named wl6-mod.

---------------------

Part 1: see wlfiler6.c, wldata.c, and wl_mods.h for my modifications and implementations.

Part 2: see wlfiler6.c for my implementation of word_delete().

Part 3a: scanf() allows for buffer overflow because it reads in a data that matches a
string, "%s". In the starter file linked to for this assignment, this is placed in "buf"
which has a declared size of BUFLEN, or 512, limiting the size of a string scanf() can
read. Without this declared size, scanf() would read in data until it saw a whitespace
char, indicating the end of a string. This could lead to overflow scanf() reading in more
data than it should because there's no limit to how much should be read in (to handle
later) except for the appearance of whitespace. Declaring "buf" to be BUFLEN size, will
prevent overflow by limiting the size, but could lead to words being split, as the
assignment says. That's why a read_word() function is necessary -- see part 3b.

Part 3b: see wlmain_mod.c for my implementation of read_word().

Part 4: to avoid conflicts with the linked wlmain.c file from the course directory, I
copied the file and made my changes in the wlmain_mod.c file.
