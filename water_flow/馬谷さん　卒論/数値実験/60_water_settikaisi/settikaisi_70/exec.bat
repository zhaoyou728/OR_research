cd C:\home\sumitomo\sol-server\system\Upfiles\k867828\20170205_142259_96
glpsol -d 60_without_pump_WSafter70.dat -m 60_without_pump_WSafter70.mod --check --wcpxlp 60_without_pump_WSafter70.lp
gurobi_cl ResultFile=60_without_pump_WSafter70.sol LogFile=60_without_pump_WSafter70.log TimeLimit=86400 Threads=4 60_without_pump_WSafter70.lp