cd C:\home\sumitomo\sol-server\system\Upfiles\k867828\20170207_132712_103
glpsol -d 60_without_pump_speed7.2.dat -m 60_without_pump_speed7.2.mod --check --wcpxlp 60_without_pump_speed7.2.lp
gurobi_cl ResultFile=60_without_pump_speed7.2.sol LogFile=60_without_pump_speed7.2.log TimeLimit=86400 Threads=4 60_without_pump_speed7.2.lp