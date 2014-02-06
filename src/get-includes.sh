#!/bin/bash
# Seto Balian 06/02/2014

ls -1 *.h > temp
sed -e 's/^/#include "/' -i temp
sed -e 's/$/"/' -i temp
cat temp
rm temp

