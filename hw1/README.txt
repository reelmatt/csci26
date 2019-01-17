##################################
#       CSCI e-26 -- hw1         #
#         Matthew Thomas         #
# matthew_thomas@hms.harvard.edu #
#           README.txt           #
##################################

/*
 * Some notes made here regarding files. For more detailed descriptions
 * of how the programs work, see comments in the files themselves.
 */

Misc. files:
--typescript
--typescript2 (see problem 3 below)

Problem 0:
Website address: http://sites.fas.harvard.edu/~mst611
Files -- add1.c
      -- counter.cgi
      -- welcome.html
      -- info.txt
      -- hello.cgi
      -- hello2.cgi
      -- index.html

/* 
 * All these files were created as part of the tutorial. They live in my public_html
 * directory, but copied here for submission on hw1. To separate them from the other
 * code, look for these files in the problem0 directory of the submission.
 */

Multiple users accessing the "hits" file at once would cause problems in that
an accurate count would not be guarenteed. The Unix system would either create a
lock on the file, preventing other users from opening/updating the count. Or,
probably more likely, if two users hit the website at the same time -- when the hit
count was say, 15 -- the add1.c program would increment the count to 16 twice
(separately), and write that value to the "hits" file. In other words, one of the
hit counts would be lost (instead of 17, it displays, inaccurately, 16).

Problem 1:
Files -- rmtags.c

Problem 2:
Files -- hello6.c (modified from class file)

Fixed bug mentioned in is_all_digits() to behave correctly when checking
empty strings. 

Problem 3:
Files -- extract_comments.c
Note: re-submitting assignment to add string_mode() to correctly interpret
      cases where /*comments like these*/ could appear within strings. The
      program now correctly ignores those cases. All other files remain the
      same. I generated a new script, "typescript2", to demonstrate the
      compiling and sample run of extract_comments.

Problem 4:
Files -- hello_large.c

Problem 5:
Website address: http://sites.harvard.edu/~mst611/first_train/first_train.html

/* active files live in public_html. Copied over to problem5 directory for hw submission */
Files -- first_train.html
      -- first_train.cgi
      -- first_train.sh

Problem 6:
Files -- badtime.c
      -- splitline.c (copied from class)
