#!/bin/bash
#touch osext.c
#touch libuser.c
#touch testlib.c
#touch testlib2.c
#touch testlib3.c
make -f "Makefile osext"
make -f "Makefile libuser"
make -f "Makefile testlib"
make -f "Makefile testlib2"
make -f "Makefile testlib3"
