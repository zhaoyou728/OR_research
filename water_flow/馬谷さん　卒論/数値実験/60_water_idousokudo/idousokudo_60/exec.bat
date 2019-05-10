cd C:\home\sumitomo\sol-server\system\Upfiles\k867828\20170207_132356_468
glpsol -d 60_without_pump_speed6_0.dat -m 60_without_pump_speed6_0.mod --check --wcpxlp 60_without_pump_speed6_0.lp
gurobi_cl ResultFile=60_without_pump_speed6_0.sol LogFile=60_without_pump_speed6_0.log TimeLimit=86400 Threads=4 60_without_pump_speed6_0.lp