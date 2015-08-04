#generates the table for distances and angles

import math

screen_width_in_tiles = 40
screen_height_in_tiles = 28
area_width_in_screens = 2
area_height_in_screens = 2

total_width_in_tiles = screen_width_in_tiles * area_width_in_screens
total_height_in_tiles = screen_height_in_tiles * area_height_in_screens
total_size = total_width_in_tiles * total_height_in_tiles

number_of_angles = 32.0
speed = 128.0
degrees = 360.0 / number_of_angles

tile_width = 8
tile_height = 8
origin_x = 0
origin_y = 0
destination_x = 0
destination_y = 0

with open('distance_and_angles_table.c', 'w') as f:
    f.write("const u16 distance_and_angles{0}[{0}] = \n".format(int(total_size)))
    f.write("{\n")

    for y in range(int(total_height_in_tiles)):
        f.write('    ')
        destination_y = y * tile_height
        for x in range(int(total_width_in_tiles)):
            destination_x = x * tile_width
            distance = math.sqrt( (destination_x)**2 + (destination_y)**2 )
            int_distance = int(distance)
            shifted_distance = int_distance << 6
            
            angle_rad = math.atan2(destination_y, destination_x)
            angle_deg = angle_rad*180.0/math.pi
            
            remapped_angle_deg = int(angle_deg / 90 * 63)
            
            writevalue = shifted_distance | remapped_angle_deg
            
            f.write('{}, '.format(writevalue))
        f.write('\n')
    f.write("};\n\n")

    f.write('/*\n')

    f.write('// distance values, unshifted\n')
    f.write("const u16 distance_and_angles{0}[{0}] = \n".format(int(total_size)))
    f.write("{\n")
    
    for y in range(int(total_height_in_tiles)):
        f.write('    ')
        destination_y = y * tile_height
        for x in range(int(total_width_in_tiles)):
            destination_x = x * tile_width
            distance = math.sqrt( (destination_x)**2 + (destination_y)**2 )
            int_distance = int(distance)
            shifted_distance = int_distance << 6
            
            angle_rad = math.atan2(destination_y, destination_x)
            angle_deg = angle_rad*180.0/math.pi
            
            remapped_angle_deg = int(angle_deg / 90 * 63)
            
            writevalue = shifted_distance | remapped_angle_deg
            
            f.write('{:0>5}, '.format(int_distance))
        f.write('\n')
    f.write("};\n\n")


    f.write('// distance values, shifted by 6 left\n')
    f.write("const u16 distance_and_angles{0}[{0}] = \n".format(int(total_size)))
    f.write("{\n")
    
    for y in range(int(total_height_in_tiles)):
        f.write('    ')
        destination_y = y * tile_height
        for x in range(int(total_width_in_tiles)):
            destination_x = x * tile_width
            distance = math.sqrt( (destination_x)**2 + (destination_y)**2 )
            int_distance = int(distance)
            shifted_distance = int_distance << 6
            
            angle_rad = math.atan2(destination_y, destination_x)
            angle_deg = angle_rad*180.0/math.pi
            
            remapped_angle_deg = int(angle_deg / 90 * 63)
            
            writevalue = shifted_distance | remapped_angle_deg
            
            f.write('{:0>5}, '.format(shifted_distance))
        f.write('\n')
    f.write("};\n\n")

    f.write('// angle values mapped to 0 to 63 instead of 0 to 90\n')
    f.write("const u16 distance_and_angles{0}[{0}] = \n".format(int(total_size)))
    f.write("{\n")
    
    for y in range(int(total_height_in_tiles)):
        f.write('    ')
        destination_y = y * tile_height
        for x in range(int(total_width_in_tiles)):
            destination_x = x * tile_width
            distance = math.sqrt( (destination_x)**2 + (destination_y)**2 )
            int_distance = int(distance)
            shifted_distance = int_distance << 6
            
            angle_rad = math.atan2(destination_y, destination_x)
            angle_deg = angle_rad*180.0/math.pi
            
            remapped_angle_deg = int(angle_deg / 90 * 63)
            
            writevalue = shifted_distance | remapped_angle_deg
            
            f.write('{:0>5}, '.format(remapped_angle_deg))
        f.write('\n')
    f.write("};")
    f.write('*/')
f.close()

#print "const s16 sintable{0}[{0}] = ".format(int(number_of_angles))
#print "{"

    #for i in range(int(number_of_angles)):
	#radians = math.radians(degrees * i)
	#sin = math.sin(radians) * speed
	#sin = math.trunc(sin)
#print '    {0},'.format(sin)

#print "};"