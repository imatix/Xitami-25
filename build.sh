#! /bin/sh
#  Builds Xitami/Open Source from source projects
#  Run 'sh build.sh' without arguments to build and install
export IBASE=$HOME/xitami
export PATH=$IBASE/bin:$PATH
test ! -d $IBASE && mkdir $IBASE
test ! -d $IBASE/bin && mkdir $IBASE/bin
cp c $IBASE/bin

cd sfl
sh boomake build install
cd ..
cd gsl
sh boomake build install
cd ..
cd smt
sh boomake build install
cd ..
cd studio
sh boomake build install
cd ..
cd xiadmin
sh boomake build install
cd ..
cd xiopen
sh boomake build install
cd ..
