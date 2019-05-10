cd C:\home\sumitomo\sol-server\system\Upfiles\m2s1x2\prj\whity_2team_settitime5
glpsol -m waterstop.mod -d whity_2team_settitime5.dat --check --wcpxlp whity_2team_settitime5.lp
gurobi_cl ResultFile=whity_2team_settitime5.sol LogFile=whity_2team_settitime5.log TimeLimit=86400 Threads=4 whity_2team_settitime5.lp