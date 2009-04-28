#! /bin/sh
#
#   c - C compile command
#
#   Copyright (c) 1991-2003 iMatix Corporation
#
#   Syntax:     c filename...     Compile ANSI C program(s)
#               c -c filename...  (Backwards compatible: compile C programs)
#               c -l main...      Compile and link main program(s)
#               c -L main...      Link main program(s), no compile
#               c -S              Report detected system name
#               c -C              Report C compiler command syntax
#               c -r lib file...  Replace object file(s) into library
#                 -li path        Local include path, additional to INCDIR
#                 -ll path        Local library path, additional to LIBDIR
#                 -g              Compile and link with debug information
#                 -v              Be verbose
#                 -q              Be quiet
#
#   Requires:   Bourne shell
#   Usage:      Compiles a subroutine or compiles/links a main program.
#
#               The following variables can be set to control the program:
#                   CCDEFINES     Options required for ANSI C compilation
#                   INCDIR        Directory to search for include files
#                   LIBDIR        Directory to search for libraries
#
#   ------------------ GPL Licensed Source Code ------------------
#   iMatix makes this software available under the GNU General
#   Public License (GPL) license for open source projects.  For
#   details of the GPL license please see www.gnu.org or read the
#   file license.gpl provided in this package.
#   
#   This program is free software; you can redistribute it and/or
#   modify it under the terms of the GNU General Public License as
#   published by the Free Software Foundation; either version 2 of
#   the License, or (at your option) any later version.
#   
#   This program is distributed in the hope that it will be useful,
#   but WITHOUT ANY WARRANTY; without even the implied warranty of
#   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#   GNU General Public License for more details.
#   
#   You should have received a copy of the GNU General Public
#   License along with this program in the file 'license.gpl'; if
#   not, write to the Free Software Foundation, Inc., 59 Temple
#   Place - Suite 330, Boston, MA 02111-1307, USA.
#   
#   You can also license this software under iMatix's General Terms
#   of Business (GTB) for commercial projects.  If you have not
#   explicitly licensed this software under the iMatix GTB you may
#   only use it under the terms of the GNU General Public License.
#   
#   For more information, send an email to info@imatix.com.
#   --------------------------------------------------------------
#----------------------------------------------------------------------------

#   If not already known, detect UNIX system type.  This algorithm returns 
#   one of these system names, as far as we know at present:
#
#       AIX      APOLLO   A/UX     BSD/OS    FreeBSD   HP-UX    IRIX
#       Linux    NCR      NetBSD   OpenBSD   NEXT      OSF1     SCO      
#       Pyramid  SunOS    ULTRIX   UnixWare  Generic   SINIX-N  BeOS
#
#   Sets the variable UTYPE to one of the UNIX system names above, and
#   CCOPTS to the appropriate compiler options for ANSI C compilation.

if [ -z "$UTYPE" ]; then
    UTYPE=Generic                       #   Default system name
    if [ -s /usr/bin/uname       ]; then UTYPE=`/usr/bin/uname`; fi
    if [ -s /bin/uname           ]; then UTYPE=`/bin/uname`;     fi

    if [ -s /usr/apollo/bin      ]; then UTYPE=APOLLO;   fi
    if [ -s /usr/bin/ncrm        ]; then UTYPE=NCR;      fi
    if [ -s /usr/bin/swconfig    ]; then UTYPE=SCO;      fi
    if [ -s /usr/lib/NextStep/software_version ]; \
                                    then UTYPE=NEXT;     fi
    if [ "$UTYPE" = "SMP_DC.OSx" ]; then UTYPE=Pyramid;  fi
    if [ -d /var/sadm/pkg/UnixWare ]; \
                                    then UTYPE=UnixWare; fi
fi

#   Set specific system compiler options and other flags
#   CCNAME      Name of compiler
#   CCOPTS      Compiler options, except -c
#   LINKTYPE    One of (before, after, gnu)
#   RANLIB      Use ranlib command to reindex library; else use 'ar rs'
#   NICE        nice command to use
#
#   CCOPTS has no sensible default; so has to be either set by the 
#   general configuration variables, or detected based on system type
#   and compiler.  If CCOPTS is set, we assume the other values are
#   set or the defaults are correct.
#
#   NOTE: CCNAME default is set below these checks, so that we can test
#   on CCNAME when setting CCOPTS, and/or set CCNAME and CCOPTS together.
#
#   NOTE: It is encouraged to check the value of CCPRODLEVEL when setting
#   the CCOPTS flags.

RANLIB="${RANLIB:-0}"               #   By default, "ar rs" is used
LINKTYPE="${LINKPATH:-after}"       #   By default, accept '-lsfl... -L.'
NICE="nice"                         #   Be nice to other users

if [ -z "$CCOPTS" ]; then
    if [ "$UTYPE" = "AIX" ]; then
        STDLIBS="-lm"
        CCOPTS="-O"

    elif [ "$UTYPE" = "BSD/OS" ]; then
        STDLIBS="-lm"
        CCOPTS="-O -Dbsd"
        RANLIB=1

    elif [ "$UTYPE" = "FreeBSD" ]; then
        STDLIBS="-lm"
        CCOPTS="-O2 -Wall"
        CCNAME="${CCNAME:-gcc}"             #   Use gcc if not set
        RANLIB=1
    	LINKTYPE=gnu

    elif [ "$UTYPE" = "NetBSD"  \
        -o "$UTYPE" = "OpenBSD" ]; then     #   NetBSD/OpenBSD do not use GNU ld
        STDLIBS="-lm"
        CCOPTS="-O2 -Wall"
        CCNAME="${CCNAME:-gcc}"             #   Use gcc if not set
        RANLIB=1

    elif [ "$UTYPE" = "HP-UX" ]; then
        STDLIBS="-lm"
        CCOPTS="-O -Ae -D_HPUX_SOURCE"      #   May need -Aa
        LINKTYPE=before

    elif [ "$UTYPE" = "Linux" ]; then
        STDLIBS="-lm"
        CCNAME="${CCNAME:-gcc}"             #   Use gcc if not set
        CCOPTS="-O2 -Wall" 
        LINKTYPE=gnu

    elif [ "$UTYPE" = "SCO" ]; then
        CCOPTS="-Dsco"                      #   -O switch can cause problems
        LINKTYPE=before
        STDLIBS="-lsocket -lm"

    elif [ "$UTYPE" = "SunOS" ]; then
        #   Must distinguish Solaris (SunOS 5.x and later)
        STDLIBS="-lm -lsocket -lnsl"
        RELEASE=`uname -r`
        MAJOR=`expr "$RELEASE" : '\([0-9]*\)\.'`
        MINOR=`expr "$RELEASE" : "$MAJOR\\.\\([0-9]*\\)"`
        if [ "$MAJOR" -gt 5 -o \( "$MAJOR" -eq 5 -a "$MINOR" -gt 1 \) ] ; then
            CCOPTS="-g -Xa -DSYSV"
        else
            CCOPTS="-O -Xa "
        fi
        LINKTYPE=before
        RANLIB=1

    elif [ "$UTYPE" = "OSF1" ]; then
        STDLIBS="-lm"
        CCOPTS="-O4 -fast -std1 -w0"

    elif [ "$UTYPE" = "UnixWare" ]; then
        STDLIBS="-lm -lsocket -lnsl"

    elif [ "$UTYPE" = "QNX" ]; then
        STDLIBS="-lm -lsocket"
        CCOPTS="-Oil"
        
    elif [ "$UTYPE" = "SINIX-N" ]; then
        STDLIBS="-lm"
        CCOPTS="-WO"

    elif [ "$UTYPE" = "BeOS" ]; then
        STDLIBS="-lm"
        CCNAME="${CCNAME:-gcc}"             #   Use gcc if not set
        NICE=""
        CCOPTS="-O2 -Wall" 

    elif [ "$CCNAME" = "gcc" ]; then
        STDLIBS="-lm -lsocket -lnsl"
        CCOPTS="-O2 -Wall" 

    fi
fi

# Set compiler to default (cc) if not set already
# And patch together the CC options and defines into one variable
#
CCNAME="${CCNAME:-cc}"
CCOPTS="$CCOPTS $CCDEFINES"

#   Parse command line arguments, figure out what we are doing
#   (Parsing is currently fairly simplistic, and depends on ordering
#   of flags.  Could be improved later if required.)
#
#   Set default values for compile & link options
LINKUP=no
COMPILE=yes
VERBOSE=no                        
QUIET=no                            #   Default is non-verbose messages 
LOCALLIBDIR=.                       #   By default, search current directory twice

#   Process switches in no particular order until there are none left
while true; do
    #   -v means verbose reports
    if [ /$1/ = /-v/ ]; then
        VERBOSE=yes
        shift

    #   -q means quiet
    elif [ /$1/ = /-q/ ]; then
        QUIET=yes
        shift

    #   -g means compile/link with debugging symbols
    elif [ /$1/ = /-g/ ]; then
        CCOPTS="-g $CCOPTS"
        shift
    
    #   -S means report detected system type
    elif [ /$1/ = /-S/ ]; then
        echo "$UTYPE"
        exit

    #   -C means report compiler syntax type
    elif [ /$1/ = /-C/ ]; then
        echo "$CCNAME -c $CCOPTS"
        exit

    #   -c means compile the object -- we were going to do that anyway,
    #   but this ensures backwards compatibility
    elif [ /$1/ = /-c/ ]; then
        shift

    #   -r means replace object file into library
    #   The RANLIB symbol should be set to 1 if 'ar rs' does not work.
    elif [ /$1/ = /-r/ ]; then
        LIBRARY=$2
        LIBNAME=`echo $LIBRARY | cut -d"." -f1`
        shift; shift
    
        for i in $*; do
            shift
            OBJECT=`echo $i | cut -d"." -f1`.o

            TRACE="Replacing object $OBJECT in library $LIBRARY"
            if [ "$RANLIB" = "1" ]; then
                COMMAND="ar r $LIBNAME.a $OBJECT"
            else
                COMMAND="ar rs $LIBNAME.a $OBJECT"
            fi
            if [ "$QUIET" = "no" ]; then
                if [ "$VERBOSE" = "no" ]; then
                    echo "$TRACE..."
                else
                    echo "$TRACE ($COMMAND)..."
                fi
            fi
            if [ ! -z "$CCTRACE" ]; then
                echo "$TRACE (COMMAND)">>$CCTRACE
            fi
            $COMMAND

            #   Run ranlib if necessary
            if [ "$RANLIB" = "1" ]; then
                ranlib $LIBNAME.a
            fi
        done
        exit 

    #   Compile/link main if -l is first argument
    elif [ /$1/ = /-l/ ]; then
        LINKUP=yes
        shift

    #   Link main if -L is first argument (assumed to already be compiled)
    elif [ /$1/ = /-L/ ]; then
        LINKUP=yes
        COMPILE=no
        shift

    #   -li means use local include path as well as INCDIR
    elif [ /$1/ = /-li/ ]; then
        CCOPTS="-I$2 $CCOPTS"
        shift; shift
    
    #   -ll means use local library path as well as LIBDIR
    elif [ /$1/ = /-ll/ ]; then
        LOCALLIBDIR=$2
        shift; shift

    else
        break       #   Not a switch
    fi
done

#   If we will be linking, then build list of libraries to link with.

if [ "$LINKUP" = "yes" -o /$1/ = // ]; then
    LIBLIST=""
    for LIBRARY in lib*.a $LOCALLIBDIR/lib*.a $LIBDIR/lib*.a; do
        if [ ! -f $LIBRARY ]; then
            continue
        fi
        #   Pull out the xxx from libxxx.a (or similar)
        LIBNAME=`basename $LIBRARY | sed -e 's/^...\([^\.]*\)\..*$/\1/'`
        LIBLIST="$LIBLIST -l$LIBNAME"
    done
    LIBLIST="$LIBLIST $CCLIBS"
fi

#   Show help if no arguments
if [ /$1/ = // ]; then
    echo "Detected system=$UTYPE, compiles with:"
    echo "     $CCNAME -c -I$INCDIR $CCOPTS"
    echo "Syntax: c filename...    Compile ANSI C program(s)"
    echo "        c -c filename... Compile ANSI C programs(s)"
    echo "        c -l main...     Compile and link main program(s)"
    echo "        c -L main...     Link main(s) with" ${LIBLIST-"no libraries"}
    echo "        c -S             Report detected system name"
    echo "        c -C             Report C compiler command syntax"
    echo "        c -r lib file    Replace file into specified library"
    echo "          -li path       Local include path, additional to INCDIR"
    echo "          -ll path       Local library path, additional to LIBDIR"
    echo "          -g             Compile and link with debug information"
    echo "          -v             Be verbose"
    echo "          -q             Be quiet"
    exit
fi

#   Compile and maybe link each filename on the command line
for i in $*; do
    shift
    FILENAME=`echo $i | cut -d"." -f1`

    #   Compile, if required
    if [ "$COMPILE" = "yes" -o ! -f $FILENAME.o ]; then
        if [ -f $FILENAME.o ]; then
            rm $FILENAME.o
        fi

        TRACE="Compiling $FILENAME"
        COMMAND="$CCNAME -c $CCOPTS -I$INCDIR $FILENAME.c"
        if [ "$QUIET" = "no" ]; then
            if [ "$VERBOSE" = "no" ]; then
                echo "$TRACE..."
            else
                echo "$TRACE ($COMMAND)..."
            fi
        fi
        if [ ! -z "$CCTRACE" ]; then
            echo "$TRACE (COMMAND)">>$CCTRACE
        fi
       
        $NICE $COMMAND 2> $FILENAME.lst

        #   Show listing and abort if there was a compile error
        if [ $? -eq 0 ]; then
            cat $FILENAME.lst
            rm  $FILENAME.lst
        else
            cat $FILENAME.lst
            if [ ! -z "$CCTRACE" ]; then
                cat $FILENAME.lst >>$CCTRACE
            fi
            exit 1
        fi
    fi

    #   If okay, link if required
    if [ "$LINKUP" = "yes" ]; then
        TRACE="Linking $FILENAME"
        COMMAND="$CCNAME $CCOPTS $FILENAME.o -o $FILENAME"

	case "$LINKTYPE" in
	    gnu)
		COMMAND="$COMMAND -Wl,--start-group $LIBLIST -Wl,--end-group -L. -L$LOCALLIBDIR -L$LIBDIR $STDLIBS"
		;;
	    before)
		COMMAND="$COMMAND -L. -L$LOCALLIBDIR -L$LIBDIR $LIBLIST $LIBLIST $STDLIBS"
		;;
	    after)
		COMMAND="$COMMAND $LIBLIST $LIBLIST -L. -L$LOCALLIBDIR -L$LIBDIR $STDLIBS"
		;;
	esac
        
	if [ "$QUIET" = "no" ]; then
            if [ "$VERBOSE" = "no" ]; then
                echo "$TRACE..."
            else
                echo "$TRACE ($COMMAND)..."
            fi
        fi
        if [ ! -z "$CCTRACE" ]; then
            echo "$TRACE (COMMAND)">>$CCTRACE
        fi

        $NICE $COMMAND 2> $FILENAME.lst

        #   Show listing and abort if there was a link error
        if [ $? -eq 0 ]; then
            cat $FILENAME.lst
            rm  $FILENAME.lst
        else
            cat $FILENAME.lst
            if [ ! -z "$CCTRACE" ]; then
                cat $FILENAME.lst >>$CCTRACE
            fi
            exit 1
        fi
    fi
done

