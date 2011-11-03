# this builds an extension called 'yourextension'
# that extension will have the contents of *.c file in the current directory
# if you need something else, see ruby documentation.

require 'mkmf'
create_makefile('yourextension')
