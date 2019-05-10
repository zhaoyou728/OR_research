cd C:\home\sumitomo\sol-server\system\Upfiles\k867828\20170203_171247_198
glpsol -d 60_without_pump.dat -m waterstop_before50.mod --check --wcpxlp waterstop_before50.lp
gurobi_cl ResultFile=waterstop_before50.sol LogFile=waterstop_before50.log TimeLimit=86400 Threads=4 waterstop_before50.lp