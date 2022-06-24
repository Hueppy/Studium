#!/bin/sh

#
# cdeclSeltsam.sh
#
# Author: Carsten Gips
#

echo ""
echo "char* A[3];"
cdecl -a explain "char* A[3];"

echo ""
echo ""
echo "char*(*(*seltsam)(double, int))[3];"
cdecl -a explain "char*(*(*seltsam)(double, int))[3];"

echo ""
echo ""
echo "char *aname[];"
cdecl -a explain "char *aname[];"

echo ""
echo ""
echo "char bname[][15];"
cdecl -a explain "char bname[][15];"

echo ""
