#generates the sin/cos tables for the goplane.

import math

number_of_angles = 32.0
speed = 128.0
degrees = 360.0 / number_of_angles

print "const s16 costable{0}[{0}] = ".format(int(number_of_angles))
print "{"

for i in range(int(number_of_angles)):
	radians = math.radians(degrees * i)
	cos = (math.cos(radians) * speed * 2.00) / 16
        cos = math.trunc(cos)
	print '    {0},'.format(cos)
print "};"

print "const s16 sintable{0}[{0}] = ".format(int(number_of_angles))
print "{"

for i in range(int(number_of_angles)):
	radians = math.radians(degrees * i)
	sin = (math.sin(radians) * speed * 2.00) / 16
	sin = math.trunc(sin)
	print '    {0},'.format(sin)

print "};"