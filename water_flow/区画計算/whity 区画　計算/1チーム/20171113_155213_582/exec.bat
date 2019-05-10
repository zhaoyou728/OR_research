cd C:\home\sumitomo\sol-server\system\Upfiles\m2s1x2\20171113_155213_582
glpsol -m waterstop.mod -d whity.dat --check --wcpxlp whity.lp
gurobi_cl ResultFile=whity.sol LogFile=whity.log TimeLimit=86400 Threads=4 whity.lp