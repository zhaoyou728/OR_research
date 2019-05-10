cd C:\home\sumitomo\sol-server\system\Upfiles\k867828\20170203_173553_22
glpsol -d 60_without_pump.dat -m waterstop_idousokudo50.mod --check --wcpxlp waterstop_idousokudo50.lp
gurobi_cl ResultFile=waterstop_idousokudo50.sol LogFile=waterstop_idousokudo50.log TimeLimit=86400 Threads=4 waterstop_idousokudo50.lp