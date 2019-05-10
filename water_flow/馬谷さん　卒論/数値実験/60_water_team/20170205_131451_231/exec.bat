cd C:\home\sumitomo\sol-server\system\Upfiles\k867828\20170205_131451_231
glpsol -d 60_without_pump_7team.dat -m 60_without_pump_7team.mod --check --wcpxlp 60_without_pump_7team.lp
gurobi_cl ResultFile=60_without_pump_7team.sol LogFile=60_without_pump_7team.log TimeLimit=86400 Threads=4 60_without_pump_7team.lp