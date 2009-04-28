@echo off
:- Builds Xitami/Open Source from source projects
:- Run this command without arguments to build and install
cd sfl
call boomake build install
cd ..
cd gsl
call boomake build install
cd ..
cd smt
call boomake build install
cd ..
cd studio
call boomake build install
cd ..
cd xiadmin
call boomake build install
cd ..
cd xiopen
call boomake build install
cd ..
