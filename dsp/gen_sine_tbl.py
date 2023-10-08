#!/usr/bin/python
import math

factor = (2 * math.pi) / 256;
print "factor = %f" % (factor)

for i in range(0, 64):
    val = (65536/2) * math.sin(i * factor)
    val_rounded = round(val, 0)
    print "%d, " % (val_rounded)
    print "i=%i" %  (i)


