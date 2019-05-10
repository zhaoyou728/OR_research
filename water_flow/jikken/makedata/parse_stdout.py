import sys
import re

argvs = sys.argv
argc = len(argvs)

if(argc != 3):
    print 'Usage: parse_stdout.py [stdout_file_path] [data_file_path]'
    quit()
    
RM_pattern = re.compile('Writing problem data to \`WFModel_C[1-9]_T[1-9]_M([0-9]\.[0-9][0-9])_R([0-9]\.[0-9][0-9]).lp\'\.\.\.')
OBJ_pattern = re.compile('Primal Bound       : ([+---][0-9\.]*e[+---][0-9]*) .*')

#mystdout = open("C:/home/dan/semi/2011/usuki/makedata/120205_1804.txt", "r");
#mydata   = open("C:/home/dan/semi/2011/usuki/makedata/120205_1804_data.txt", "w");
mystdout = open(argvs[1], "r");
mydata   = open(argvs[2], "w");

curr_RM_MatchList = [('-1.0', '-1.0')]
prev_RM_MatchList = [('-1.0', '-1.0')]

for line in mystdout:
    RM_MatchList = RM_pattern.findall(line)
    if(len(RM_MatchList) > 0):
        #print RM_MatchList
        curr_RM_MatchList = RM_MatchList
        if(prev_RM_MatchList[0][0] != curr_RM_MatchList[0][0]):
            mydata.write('\n')
            prev_RM_MatchList = curr_RM_MatchList
    OBJ_MatchList = OBJ_pattern.findall(line)
    if(len(OBJ_MatchList) > 0):
        mydata.write(curr_RM_MatchList[0][0] + ' ' + curr_RM_MatchList[0][1] + ' ' + OBJ_MatchList[0] + '\n')
    
mystdout.close()
mydata.close()
