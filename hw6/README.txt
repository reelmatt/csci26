##################################
#       CSCI e-26 -- hw6         #
#         Matthew Thomas         #
# matthew_thomas@hms.harvard.edu #
#           README.txt           #
##################################

Files:
--supercal
--name2num (from class examples)
--get_range
--print_cal

--hangman
--play_hangman
--random_word (from class assignment)
--hm.0->hm.7 (hangman pictures, from class assignment)
--explode (from class assignment, moved to separate file)
--guess
--make_dashed
--print_ui
--check_guess
--fill_word

--myrm
--move_file
--pick_mode
--clean_mode

Other:
--README.txt
--typescript
	
Note: some files/scripts were copied from class lectures.
Those are noted in the list above.

Note on hangman: there's a known error when guessing "*" as
a character. I couldn't figure out how to escape it (or some
other special chars like the arrow keys). I got it not to crash
the program. For some reason it echoes the name of the function
"check_guess" that would cause the error. The list of guesses
that's passed in after does not show up when printing all args
available. Attempting to quote the argument and add a "\" did not
work either.