cd C:\home\sumitomo\sol-server\system\Upfiles\m2s1x2\prj\whity2_before50
glpsol -m waterstop_before50.mod -d whity_2team.dat --check --wcpxlp whity_2team.lp
gurobi_cl ResultFile=whity_2team.sol LogFile=whity_2team.log TimeLimit=86400 Threads=4 whity_2team.lp