cd C:\home\sumitomo\sol-server\system\Upfiles\k867828\20170208_211722_202
glpsol -d 60_without_pump_speed80.dat -m 60_without_pump_speed80.mod --check --wcpxlp 60_without_pump_speed80.lp
gurobi_cl ResultFile=60_without_pump_speed80.sol LogFile=60_without_pump_speed80.log TimeLimit=86400 Threads=4 60_without_pump_speed80.lp