cd C:\home\sumitomo\sol-server\system\Upfiles\k508951\20170204_183542_533
glpsol -d 60_without_pump_settizikann.dat -m waterstop.mod --check --wcpxlp waterstop.lp
gurobi_cl ResultFile=waterstop.sol LogFile=waterstop.log TimeLimit=86400 Threads=4 waterstop.lp