cd C:\home\sumitomo\sol-server\system\Upfiles\m2s1x2\prj\120_64_3team_no30
glpsol -d 120_with_pump_whity_64min_3team.dat -m waterstop_5_180114_2.mod --check --wcpxlp waterstop_5_180114_2.lp
gurobi_cl ResultFile=waterstop_5_180114_2.sol LogFile=waterstop_5_180114_2.log TimeLimit=3600 Threads=4 waterstop_5_180114_2.lp