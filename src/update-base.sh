#!/bin/bash
#
# Updates SpinDecoherence base.h
# Has to be in path src/
#
# Seto Balian 21/02/2014

# Write part 1 of base.h
echo "#ifndef BASE_H_" >> temp1
echo "#define BASE_H_" >> temp1
echo "" >> temp1
echo "// SpinDecoherence includes" >> temp1
echo "" >> temp1
date +"// Seto Balian, %b %d, %Y" >> temp1
echo "" >> temp1
echo "#include <Eigen/Dense>" >> temp1
echo "" >> temp1
echo "#include \"types.h\"" >> temp1
echo "" >> temp1
# Write part 2 of base.h
# Include headers(.h files) (excluding base.h and types.h)
ls -1 [!(base.h types.h)]*.h > temp2
sed -e 's/^/#include "/' -i temp2
sed -e 's/$/"/' -i temp2
# Write part 3 of base.h
echo "" >> temp3
echo "#endif // BASE_H_" >> temp3
echo "" >> temp3
# Combine parts 1, 2 and 3 to get base.h
cat temp1 temp2 temp3 > base.h
# Clean up (essential)
rm -f temp1 temp2 temp3

