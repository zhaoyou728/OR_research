cd C:\home\sumitomo\sol-server\system\Upfiles\m2s1x2\prj\120_43min_3team_60min
glpsol -d 120_with_pump_whity_43min_3team.dat -m waterstop_5_180114_kadou60.mod --check --wcpxlp waterstop_5_180114_kadou60.lp
gurobi_cl ResultFile=waterstop_5_180114_kadou60.sol LogFile=waterstop_5_180114_kadou60.log TimeLimit=3600 Threads=4 waterstop_5_180114_kadou60.lp