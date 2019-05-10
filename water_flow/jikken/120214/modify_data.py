import sys

argvs = sys.argv
argc = len(argvs)

if(argc != 3):
    print 'Usage: parse_stdout.py [stdout_file_path] [data_file_path]'
    quit()

myOrgData      = open(argvs[1], "r");
myModifiedData = open(argvs[2], "w");

dataList = []

for line in myOrgData:
    l = line.split()
    if(len(l) == 3):
        dataList.append(l)

#print dataList

margin = [0.05, 0.10, 0.15, 0.20, 0.25, 0.30]
ratio = [0.30, 0.40, 0.50, 0.60, 0.70, 0.80, 0.90, 1.00]

for i in margin:
    print
    myModifiedData.write('\n')
    for d in dataList:
        if(i == float(d[0])):
            if(float(d[2]) > 0):
                print d[0] + ' ' + d[1] + ' ' + d[2]
                myModifiedData.write(d[0] + ' ' + d[1] + ' ' + d[2] + '\n')
            else:
                print
                myModifiedData.write('\n')
                
for i in ratio:
    print
    myModifiedData.write('\n')
    for d in dataList:
        if(i == float(d[1])):
            if(float(d[2]) > 0):
                print d[0] + ' ' + d[1] + ' ' + d[2]
                myModifiedData.write(d[0] + ' ' + d[1] + ' ' + d[2] + '\n')
            else:
                print
                myModifiedData.write('\n')
                                
