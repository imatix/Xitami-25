#
#   Boom make file for GSL 2.01
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
libgsl$(LIB): ggcode$(OBJ) ggcomm$(OBJ) ggeval$(OBJ) ggfile$(OBJ) ggfunc$(OBJ) ggobjt$(OBJ) ggstrn$(OBJ) ggpars$(OBJ) 
	c -q -r libgsl$(LIB) ggcode$(OBJ) ggcomm$(OBJ) ggeval$(OBJ) ggfile$(OBJ) ggfunc$(OBJ) ggobjt$(OBJ) ggstrn$(OBJ) ggpars$(OBJ) 
gslgen$(OBJ): gslgen.c #!mkdep
gslgen$(EXE): gslgen$(OBJ) libgsl$(LIB) 
	c -q -L gslgen
ggcode$(OBJ): ggcode.c #!mkdep
ggcomm$(OBJ): ggcomm.c #!mkdep
ggeval$(OBJ): ggeval.c #!mkdep
ggfile$(OBJ): ggfile.c #!mkdep
ggfunc$(OBJ): ggfunc.c #!mkdep
ggobjt$(OBJ): ggobjt.c #!mkdep
ggstrn$(OBJ): ggstrn.c #!mkdep
ggpars$(OBJ): ggpars.c #!mkdep
gslgen.i: gslgen.l
	lr gslgen.l
gslgen.d: gslgen.l
	lr gslgen.l
ggcode.i: ggcode.l
	lr ggcode.l
ggcode.d: ggcode.l
	lr ggcode.l
ggpars.i: ggpars.l
	lr ggpars.l
ggpars.d: ggpars.l
	lr ggpars.l

everything: libgsl$(LIB) gslgen$(EXE) 
