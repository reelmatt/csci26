##################################
#       CSCI e-26 -- hw2         #
#         Matthew Thomas         #
# matthew_thomas@hms.harvard.edu #
#           README.txt           #
##################################

[1]
-------------------------------------------
List three or more Unix tools or files that are text tables.
	1) df - reports file system disk space usage
	2) ss - a utility to investigate sockets
	3) route - show / manipulate the IP routing table

[2]
-------------------------------------------
Files -- tt1.cgi
      -- table1.html
      -- whostyle.css
      -- style1.css
      -- who.html
      -- problem2.css

/* 
 * Note on files: 
 * For parts 3-5, I factored out common functions into a
 * table_tools.c file. This should be used when compiling tt2ht1.c,
 * tt2ht2.c, and tt2ht3.c. I list it for each part, but it is the same
 * file. Some functions like attribute_mode() and get_cell() exist in
 * more than one file with changes. Those changes are noted where they
 * appear.
 */
 
/*
 * Note for all three parts: in section on 10/3 we discussed only printing a row
 * and <tr> tags if data exists (i.e. not a blank row). My implementation prints
 * <tr> tags for all text table data it encounters (albeit with no <td> tags if
 * the row *is* empty). I think this could be more useful as sometimes it is nice
 * to have blank/empty rows displayed in a table. I couldn't find any requirement
 * in the assignment to ignore the <tr> tags for blank rows, so I hope this
 * implementation detail is okay.
 */

[3a]
-------------------------------------------
Files -- tt2ht1.c
      -- table_tools.c
      
[3b]
-------------------------------------------
Files -- part3b.cgi

[4a]
-------------------------------------------
Files -- tt2ht2.c
      -- table_tools.c
      
[4b]
-------------------------------------------
Files -- part4b.cgi
      -- part4b.top

[5]
-------------------------------------------
Files -- tt2ht3.c
      -- table_tools.c
      -- part5b.cgi
      
[Misc]
-------------------------------------------
README.txt
typescript

/*****************************************************************************************
 * Nested tags: tt2ht3 takes a hierarchical approach to tags, in order of the cases
 *     listed in main: noprocess -> attributes -> delim -> table text. I did this
 *     with the thinking/mindset of "trust the user". In other words, if the user enters
 *     poorly-formatted data, it will do some error checking (see 2-4 below), but will
 *     output what you write. The assignment mentions the example of having an
 *     <attributes> tag within a <noprocess> block might be useful. tt2ht3.c will dump
 *     that text to the screen for the user to see and decide: a) I forgot to close my
 *     <noprocess> tag; or b) I wanted to output those attributes as is (perhaps I'm
 *     writing a description of this assignment and want to show the raw form attributes
 *     take).
 *
 *     Bullets
 *     
 *     1) <noprocess> -- when in this block, it will print all lines regardless of
 *        content and ignore any definition of attributes or delimiters.
 *     2) <attributes> -- when in this block, it ignores any opening "noprocess" or
 *        "delim" tags. Instead, it inserts a blank row in the attribute array.
 *     3) <delim /> -- when not located within a "noprocess" or "attributes" block,
 *        any appearance of a delim tag will overwrite the previous delimiter found. It
 *        does look for the proper "/>" closing, and if it doesn't find that, discards the
 *        row.
 *     4) unmatched closing tags -- if the program encounters a closing tag that doesn't
 *        match the current mode it is currently in, it will ignore the line entirely.
 *        For example, if it sees a </noprocess> tag without a corresponding open
 *        <noprocess> tag, it will discard it.
 *
 ****************************************************************************************/