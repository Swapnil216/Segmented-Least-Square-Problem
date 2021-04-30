import random

radius = 200
rangeX = (-100,99)
rangeY = (-100,99)

print("Enter number of co-ordinates: ")

#Number of co-cordinates
qty = int(input())  

# Generate a set of all points within "radius" of the origin, to be used as offsets later

pts = set()
for x in range(-radius, radius+1):
    for y in range(-radius, radius+1):
        if x*x + y*y <= radius*radius:
            pts.add((x,y))

randPoints = []
excluded = set()
i = 0
while i<qty:
    x = random.randrange(*rangeX)
    y = random.randrange(*rangeY)
    #if (x,y) in excluded: continue
    randPoints.append((x,y))
    i += 1
    excluded.update((x+dx, y+dy) for (dx,dy) in pts)
    
#Creating the file to write the test cases along with the cost    
file = open("test.txt",'w')
file.write(str(qty))
file.write("\n")


for item in randPoints:
    x=item[0]
    y=item[-1]
    file.write("%s %s\n" % (str(x),str(y)))
    
    
print("Enter the cost: ")
cost = input()
file.write(cost)

file.close()
