#
#   Boom make file for Studio 2.2
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
libstu$(LIB): ctxman$(OBJ) wtplib$(OBJ) formio$(OBJ) wtpman$(OBJ) browtp$(OBJ) brocgi$(OBJ) fxtest1$(OBJ) fxtest2$(OBJ) fxtest3$(OBJ) wtpmsg$(OBJ) 
	c -q -r libstu$(LIB) ctxman$(OBJ) wtplib$(OBJ) formio$(OBJ) wtpman$(OBJ) browtp$(OBJ) brocgi$(OBJ) fxtest1$(OBJ) fxtest2$(OBJ) fxtest3$(OBJ) wtpmsg$(OBJ) 
ctxman$(OBJ): ctxman.c #!mkdep
wtplib$(OBJ): wtplib.c #!mkdep
formio$(OBJ): formio.c #!mkdep
wtpman$(OBJ): wtpman.c #!mkdep
browtp$(OBJ): browtp.c #!mkdep
brocgi$(OBJ): brocgi.c #!mkdep
wtpmsg.h: wtpmsg.xml
	gsl -q wtpmsg.xml
testbro$(OBJ): testbro.c #!mkdep
testbro$(EXE): testbro$(OBJ) libstu$(LIB) 
	c -q -L testbro
fxtest1$(OBJ): fxtest1.c #!mkdep
fxtest2$(OBJ): fxtest2.c #!mkdep
fxtest3$(OBJ): fxtest3.c #!mkdep
fxdemo$(OBJ): fxdemo.c #!mkdep
fxdemo$(EXE): fxdemo$(OBJ) libstu$(LIB) 
	c -q -L fxdemo
fxdemo2$(OBJ): fxdemo2.c #!mkdep
fxdemo2$(EXE): fxdemo2$(OBJ) libstu$(LIB) 
	c -q -L fxdemo2
fxdemo3$(OBJ): fxdemo3.c #!mkdep
fxdemo3$(EXE): fxdemo3$(OBJ) libstu$(LIB) 
	c -q -L fxdemo3
wtpman.i: wtpman.l
	lr wtpman.l
wtpman.d: wtpman.l
	lr wtpman.l
browtp.i: browtp.l
	lr browtp.l
browtp.d: browtp.l
	lr browtp.l
brocgi.i: brocgi.l
	lr brocgi.l
brocgi.d: brocgi.l
	lr brocgi.l
wtpmsg$(OBJ): wtpmsg.c #!mkdep
wtpmsg.c: wtpmsg.xml
	gsl -q wtpmsg.xml
wtpmsg.c: wtpmsg.xml
	gsl -q wtpmsg.xml
fdlgen.d: fdlgen.l
	lr fdlgen.l
fmlgen.d: fmlgen.l
	lr fmlgen.l
fxtest1.htm: fxtest1.fdl
	perl fdlgen fxtest1.fdl
	perl fmlgen fxtest1.fdl
fxtest1.log: fxtest1.fdl
	perl fdlgen fxtest1.fdl
	perl fmlgen fxtest1.fdl
fxtest1.h: fxtest1.fdl
	perl fdlgen fxtest1.fdl
	perl fmlgen fxtest1.fdl
fxtest1.i: fxtest1.l
	lr fxtest1.l
fxtest1.d: fxtest1.l
	lr fxtest1.l
fxtest2.htm: fxtest2.fdl
	perl fdlgen fxtest2.fdl
	perl fmlgen fxtest2.fdl
fxtest2.log: fxtest2.fdl
	perl fdlgen fxtest2.fdl
	perl fmlgen fxtest2.fdl
fxtest2.h: fxtest2.fdl
	perl fdlgen fxtest2.fdl
	perl fmlgen fxtest2.fdl
fxtest2.i: fxtest2.l
	lr fxtest2.l
fxtest2.d: fxtest2.l
	lr fxtest2.l
fxtest3.htm: fxtest3.fdl
	perl fdlgen fxtest3.fdl
	perl fmlgen fxtest3.fdl
fxtest3.log: fxtest3.fdl
	perl fdlgen fxtest3.fdl
	perl fmlgen fxtest3.fdl
fxtest3.h: fxtest3.fdl
	perl fdlgen fxtest3.fdl
	perl fmlgen fxtest3.fdl
fxtest3.i: fxtest3.l
	lr fxtest3.l
fxtest3.d: fxtest3.l
	lr fxtest3.l

everything: libstu$(LIB) testbro$(EXE) fxdemo$(EXE) fxdemo2$(EXE) fxdemo3$(EXE) 
