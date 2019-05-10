set logfile MakeSchedule.log
set emphasis numerical yes
set timelimit 10800
read MakeSchedule.lp
optimize
write MakeSchedule.sol
y
quit
