cd C:\home\sumitomo\sol-server\system\Upfiles\k867828\20170204_185052_61
glpsol -d 60_without_pump_5team.dat -m waterstop.mod --check --wcpxlp waterstop.lp
gurobi_cl ResultFile=waterstop.sol LogFile=waterstop.log TimeLimit=86400 Threads=4 waterstop.lp