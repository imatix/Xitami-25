#
#   Boom make file for SFL 2.50
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
libsfl$(LIB): sflbits$(OBJ) sflcomp$(OBJ) sflcons$(OBJ) sflconv$(OBJ) sflcryp$(OBJ) sflcvbs$(OBJ) sflcvdp$(OBJ) sflcvds$(OBJ) sflcvns$(OBJ) sflcvsb$(OBJ) sflcvsd$(OBJ) sflcvsn$(OBJ) sflcvst$(OBJ) sflcvtp$(OBJ) sflcvts$(OBJ) sfldate$(OBJ) sfldbio$(OBJ) sfldir$(OBJ) sflenv$(OBJ) sflexdr$(OBJ) sflfile$(OBJ) sflfind$(OBJ) sflfort$(OBJ) sflhttp$(OBJ) sflini$(OBJ) sfllang$(OBJ) sfllbuf$(OBJ) sfllist$(OBJ) sflmail$(OBJ) sflmath$(OBJ) sflmem$(OBJ) sflmesg$(OBJ) sflmime$(OBJ) sflmysql$(OBJ) sflnode$(OBJ) sflprint$(OBJ) sflproc$(OBJ) sflslot$(OBJ) sflsock$(OBJ) sflstr$(OBJ) sflsymb$(OBJ) sflsyst$(OBJ) sfltok$(OBJ) sfltree$(OBJ) sfltron$(OBJ) sfluid$(OBJ) sflxml$(OBJ) sflxmll$(OBJ) 
	c -q -r libsfl$(LIB) sflbits$(OBJ) sflcomp$(OBJ) sflcons$(OBJ) sflconv$(OBJ) sflcryp$(OBJ) sflcvbs$(OBJ) sflcvdp$(OBJ) sflcvds$(OBJ) sflcvns$(OBJ) sflcvsb$(OBJ) sflcvsd$(OBJ) sflcvsn$(OBJ) sflcvst$(OBJ) sflcvtp$(OBJ) sflcvts$(OBJ) sfldate$(OBJ) sfldbio$(OBJ) sfldir$(OBJ) sflenv$(OBJ) sflexdr$(OBJ) sflfile$(OBJ) sflfind$(OBJ) sflfort$(OBJ) sflhttp$(OBJ) sflini$(OBJ) sfllang$(OBJ) sfllbuf$(OBJ) sfllist$(OBJ) sflmail$(OBJ) sflmath$(OBJ) sflmem$(OBJ) sflmesg$(OBJ) sflmime$(OBJ) sflmysql$(OBJ) sflnode$(OBJ) sflprint$(OBJ) sflproc$(OBJ) sflslot$(OBJ) sflsock$(OBJ) sflstr$(OBJ) sflsymb$(OBJ) sflsyst$(OBJ) sfltok$(OBJ) sfltree$(OBJ) sfltron$(OBJ) sfluid$(OBJ) sflxml$(OBJ) sflxmll$(OBJ) 
sflbits$(OBJ): sflbits.c #!mkdep
sflcomp$(OBJ): sflcomp.c #!mkdep
sflcons$(OBJ): sflcons.c #!mkdep
sflconv$(OBJ): sflconv.c #!mkdep
sflcryp$(OBJ): sflcryp.c #!mkdep
sflcvbs$(OBJ): sflcvbs.c #!mkdep
sflcvdp$(OBJ): sflcvdp.c #!mkdep
sflcvds$(OBJ): sflcvds.c #!mkdep
sflcvns$(OBJ): sflcvns.c #!mkdep
sflcvsb$(OBJ): sflcvsb.c #!mkdep
sflcvsd$(OBJ): sflcvsd.c #!mkdep
sflcvsn$(OBJ): sflcvsn.c #!mkdep
sflcvst$(OBJ): sflcvst.c #!mkdep
sflcvtp$(OBJ): sflcvtp.c #!mkdep
sflcvts$(OBJ): sflcvts.c #!mkdep
sfldate$(OBJ): sfldate.c #!mkdep
sfldbio$(OBJ): sfldbio.c #!mkdep
sfldir$(OBJ): sfldir.c #!mkdep
sflenv$(OBJ): sflenv.c #!mkdep
sflexdr$(OBJ): sflexdr.c #!mkdep
sflfile$(OBJ): sflfile.c #!mkdep
sflfind$(OBJ): sflfind.c #!mkdep
sflfort$(OBJ): sflfort.c #!mkdep
sflhttp$(OBJ): sflhttp.c #!mkdep
sflini$(OBJ): sflini.c #!mkdep
sfllang$(OBJ): sfllang.c #!mkdep
sfllbuf$(OBJ): sfllbuf.c #!mkdep
sfllist$(OBJ): sfllist.c #!mkdep
sflmail$(OBJ): sflmail.c #!mkdep
sflmath$(OBJ): sflmath.c #!mkdep
sflmem$(OBJ): sflmem.c #!mkdep
sflmesg$(OBJ): sflmesg.c #!mkdep
sflmime$(OBJ): sflmime.c #!mkdep
sflmysql$(OBJ): sflmysql.c #!mkdep
sflnode$(OBJ): sflnode.c #!mkdep
sflprint$(OBJ): sflprint.c #!mkdep
sflproc$(OBJ): sflproc.c #!mkdep
sflslot$(OBJ): sflslot.c #!mkdep
sflsock$(OBJ): sflsock.c #!mkdep
sflstr$(OBJ): sflstr.c #!mkdep
sflsymb$(OBJ): sflsymb.c #!mkdep
sflsyst$(OBJ): sflsyst.c #!mkdep
sfltok$(OBJ): sfltok.c #!mkdep
sfltree$(OBJ): sfltree.c #!mkdep
sfltron$(OBJ): sfltron.c #!mkdep
sfluid$(OBJ): sfluid.c #!mkdep
sflxml$(OBJ): sflxml.c #!mkdep
sflxmll$(OBJ): sflxmll.c #!mkdep
sflcvst.i: sflcvst.l
	lr sflcvst.l
sflcvst.d: sflcvst.l
	lr sflcvst.l
sflxmll.i: sflxmll.l
	lr sflxmll.l
sflxmll.d: sflxmll.l
	lr sflxmll.l

everything: libsfl$(LIB) 
