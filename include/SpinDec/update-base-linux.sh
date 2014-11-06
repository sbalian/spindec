#!/bin/bash
#
# Updates SpinDec base.h
# Has to be in path SpinDec:src/include/SpinDec/
# Does not work on Mac
#
# Seto Balian, Nov 6, 2014

# Write part 1 of base.h
echo "#ifndef BASE_H_" >> temp1
echo "#define BASE_H_" >> temp1
echo "" >> temp1
echo "// SpinDec includes" >> temp1
echo "" >> temp1
echo "// Generated automatically using update-base.sh" >> temp1
date +"// Seto Balian, %b %d, %Y" >> temp1
echo "" >> temp1
# Write part 2 of base.h
# Include headers(.h files) (excluding base.h and types.h)
ls -1 [!(base.h)]*.h > temp2
sed -e 's/^/#include "SpinDec\//' -i temp2
sed -e 's/$/"/' -i temp2
# Write part 3 of base.h
echo "" >> temp3
echo "#endif // BASE_H_" >> temp3
echo "" >> temp3
# Combine parts 1, 2 and 3 to get base.h
cat temp1 temp2 temp3 > base.h
# Clean up (essential)
rm -f temp1 temp2 temp3

