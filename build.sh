#! /bin/sh
#  Builds Xitami/Open Source from source projects
#  Run 'sh build.sh' without arguments to build and install
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
