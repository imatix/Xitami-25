#
#   Boom make file for Xitami Administration Console 2.5
#   Generated from standard.pwl on 2004/07/22
#   See www.imatix.com for more information.
#   Copyright (c) 1991-2003 iMatix Corporation
#

#   Default values for object, library, and executable extensions.
#
OBJ = .o
LIB = .a
EXE = 

#   Reset the suffixes that will be considered to just our own list.
#
#   Unix make programs use the .SUFFIXES psuedo rule for this

.SUFFIXES:
.SUFFIXES: $(EXE) $(LIB) $(OBJ) .c .d .i .l

#   Objects depend on source files with the same name; and are compiled
#   with the iMatix c script without any arguments.
#
.c$(OBJ):
	c -q $<
#   And .c files _do_not_ depend on .l files (.l files are Libero files,
#   not lex input files as the default rules think).
#
#   The semicolon forces make to accept the rule as an override.
#
.l.c: ;

#
#   Default rule -- all depends on everything.
#   We do this so that we can define the rule at the end.
#
all: everything
#
#   Dependencies
#
libxac$(LIB): xiadmin$(OBJ) 
	c -q -r libxac$(LIB) xiadmin$(OBJ) 
xiadmin$(OBJ): xiadmin.c #!mkdep
xiadmin.i: xiadmin.l
	lr xiadmin.l
xiadmin.d: xiadmin.l
	lr xiadmin.l

everything: libxac$(LIB) 
