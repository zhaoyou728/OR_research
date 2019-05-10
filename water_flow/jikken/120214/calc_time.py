import sys
import re
import math

argvs = sys.argv
argc = len(argvs)

if(argc != 2):
    print 'Usage: calc_time.py [stdout_file_path]'
    quit()

print argvs[1]

TIME_pattern = re.compile('Solving Time \(sec\) : ([0-9\.]*).*')
#TIME_pattern = re.compile('Solving Time (sec) : (.*)')
#TIME_pattern = re.compile('Solving Time \(sec\) : (.*)')

myData = open(argvs[1], "r");

TIME_matchList = [('1.0')]
TIME_List = []

for line in myData:
    TIME_matchList = TIME_pattern.findall(line)
    if(len(TIME_matchList) > 0):
        TIME_List.append(TIME_matchList[0])

#print TIME_List

ave = 0.0
for t in TIME_List:
    ave = ave + float(t)
ave = ave / len(TIME_List)
print 'average = %.2f' % ave

sd = 0.0
for t in TIME_List:
    sd = sd + float(t) * float(t)
sd = sd / len(TIME_List)
sd = sd - ave * ave
sd = math.sqrt(sd)
print 'sd = %.2f' % sd
