##################################
#       CSCI e-26 -- hw7         #
#         Matthew Thomas         #
# matthew_thomas@hms.harvard.edu #
#           README.txt           #
##################################

Files:

Exercise 1 - ncal2 and year.html
--args1.cgi
--name2num	(from course files)
--ncal2 	(from course files)
--ncal2.cgi
--ncal3.cgi
--year.html	(modified from course files)

Exercise 2 - webpage generator
--fl		(from course files)
--mwp.cgi
--mwp.footer

Exercise 3 - editing my web page
add-edit_item.cgi
cities.html
delete_item.cgi
dropdown.cgi
ewp.add
ewp.cgi
ewp.delete
ewp.delete.cgi
ewp.footer
ewp.header
ewp.html
ewp.view
ewp.view.cgi
get_option
header.cgi
row.fmt
view_page.cgi

Other
--qryparse	(from course files)
--qryparse.c	(from course files)
--README.txt

Notes:
For exercise 1, the extra credit option is implemented. Entering a month
that has already been passed in the current year will print out that month
in the following year. Comments describe this in the ncal3.cgi file.

For exercise 3, I implemented item a, "pick from lists" from the idea for
improvements list. For modularity, I split out the ewp.html files into
several text files (e.g. ewp.add, ewp.footer) to make echo-ing in the ewp.cgi
script easier. To implement the list portions, I wrote the dropdown.cgi script
which calls on the get_option helper script. dropdown.cgi is called on in
various places, both for the delete and view portions of the ewp site. These
can be seen in the ewp.delete.cgi and ewp.view.cgi scripts.

My initial attempt put each "pagename" file in an <optgroup> and then only
the corresponding titles as selectable options. However, this limited the
QUERY_STRING passed on to the calling scripts, so I had to modify the
implementation. There are two dropdowns, each listing *all* pagenames and
titles, with a user able to select a combination that does not exist. In this
case, the delete_item.cgi script will print an error message saying it cannot
find the record.

As the assignment alludes to, the benefit of this feature is that users are
not required to remember the pages and titles that exist to delete or view.
It also removes the need for checking case of input and possible punctuation
variations (e.g. st louis vs. St. Louis).
