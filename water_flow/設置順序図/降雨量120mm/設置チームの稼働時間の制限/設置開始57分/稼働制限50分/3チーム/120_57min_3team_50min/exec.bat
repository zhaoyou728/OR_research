cd C:\home\sumitomo\sol-server\system\Upfiles\m2s1x2\prj\120_57min_3team_50min
glpsol -d 120_with_pump_whity_57_3team.dat -m waterstop_5_180114_kadou50.mod --check --wcpxlp waterstop_5_180114_kadou50.lp
gurobi_cl ResultFile=waterstop_5_180114_kadou50.sol LogFile=waterstop_5_180114_kadou50.log TimeLimit=3600 Threads=4 waterstop_5_180114_kadou50.lp