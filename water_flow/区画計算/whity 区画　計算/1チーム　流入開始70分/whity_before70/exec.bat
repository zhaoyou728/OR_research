cd C:\home\sumitomo\sol-server\system\Upfiles\m2s1x2\prj\whity_before70
glpsol -m 60_without_pump_WSafter70.mod -d whity.dat --check --wcpxlp whity.lp
gurobi_cl ResultFile=whity.sol LogFile=whity.log TimeLimit=86400 Threads=4 whity.lp