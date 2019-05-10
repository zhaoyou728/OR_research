cd C:\home\sumitomo\sol-server\system\Upfiles\m2s1x2\prj\120_43_3team_no30
glpsol -d 120_with_pump_whity_43min_3team.dat -m waterstop_5_180114_2.mod --check --wfreemps waterstop_5_180114_2.mps
gurobi_cl ResultFile=waterstop_5_180114_2.sol LogFile=waterstop_5_180114_2.log TimeLimit=3600 Threads=4 waterstop_5_180114_2.mps