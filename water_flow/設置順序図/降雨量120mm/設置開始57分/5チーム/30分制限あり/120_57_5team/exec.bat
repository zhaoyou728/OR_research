cd C:\home\sumitomo\sol-server\system\Upfiles\m2s1x2\prj\120_57_5team
glpsol -d 120_with_pump_whity_57min_5team.dat -m waterstop_5_180114.mod --check --wcpxlp waterstop_5_180114.lp
gurobi_cl ResultFile=waterstop_5_180114.sol LogFile=waterstop_5_180114.log TimeLimit=3600 Threads=4 waterstop_5_180114.lp