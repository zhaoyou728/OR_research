set V;          # Vertex
set E dimen 2;  # Edge
set L;          # Leyer {0, 1, ...}
set P;          # Team {a, b, c, d, e, f}

param f{V};     #
param w{E};     # Weight of edge
param s;        # Start
param u;        # Installing time for one waterstop
param M;        # Big-M
param lm;       # num of layer
param speed;    # 66.0
param st;       # start time, 60?

var x{V, L, P}, binary;  #
var y{E, L, P}, binary;  #
var t{L, P};             # Time
var t_{L, P};            # Ideal Time
var d{L, P}, >= 0.0;     # Delay

##################################################

minimize Objective:
  sum {l in L, p in P: l >= 1} d[l, p];
#sum{p in P}t[lm,p];
   
subject to InitialPosition {p in P}:
  x[s, 0, p] == 1;

subject to AllWaterstop {v in V}:
  sum {l in L, p in P: l >= 1} x[v, l, p] == 1;

subject to OneByOne {l in L, p in P}:
  sum {v in V} x[v, l, p] <= 1;

subject to SequentialInstall {v in V}:
  sum {(v_, v) in E, l in L, p in P: l >= 1} y[v_, v, l - 1, p] == 1;

subject to UsingEdge_1 {(v1, v2) in E, l in L, p in P: l >= 1}:
  x[v1, l - 1, p] >= y[v1, v2, l - 1, p];

subject to UsingEdge_2 {(v1, v2) in E, l in L, p in P: l >= 1}:
  x[v2, l, p] >= y[v1, v2, l - 1, p];

subject to UsingEdge_3 {(v1, v2) in E, l in L, p in P: l >= 1}:
  x[v1, l - 1, p] + x[v2, l, p] - y[v1, v2, l - 1, p] <= 1;

subject to InstallingTime {l in L, p in P: l >= 1}:
  t[l, p] == sum {l_ in L, (v1, v2) in E: l_ < l} y[v1, v2, l_, p] * w[v1, v2] / speed + (sum {v in V, l_ in L: l_ <= l && l_>=1} x[v, l_, p]) * u;

subject to IdealInstallingTime {l in L, p in P: l >= 1}:
  t_[l, p] == sum {v in V} (x[v, l, p] * (f[v] - st));

subject to DelayTime {l in L, p in P: l >= 1}:
  d[l, p] >= t[l, p] - t_[l, p] - (1 - sum {v in V} x[v, l, p]) * M;

#subject to TimeLimit {p in P}:
# t[lm, p] <= 30;

subject to secondvisit1:
  x[6205, 1, 1] == 1;

subject to thirdvisit1:
  x[1592, 2, 1] == 1;
 
subject to fourthvisit1:
  x[1813, 3, 1] == 1;

subject to fifthvisit1:
  x[8210, 4, 1] == 1;

subject to secondvisit2:
  x[15728, 1, 2] == 1;

subject to thirdvisit2:
  x[10955, 2, 2] ==1;

subject to fourthvisit2:
  x[11087, 3, 2] == 1;

subject to fifthvisit2:
  x[11356, 4, 2] == 1;

subject to sixthvisit2:
  x[12593, 5, 2] == 1;

subject to seventhvisit2:
  x[13107, 6, 2] == 1;

subject to secondvisit3:
  x[14140, 1, 3] == 1;

subject to thihrdvisit3:
  x[10635, 2, 3] == 1;

subject to fourthvisit3:
  x[10417, 3, 3] == 1;

subject to fifthvisit3:
  x[17207, 4, 3] == 1;

subject to sixthvisit3:
  x[15365, 5, 3] == 1;

subject to seventhvisit3:
  x[10688, 6, 3] == 1;

subject to secondvisit4:
  x[8236, 1, 4] == 1;

subject to thirdvisit4:
  x[8643, 2, 4] == 1;

subject to fourthvisit4:
  x[8169, 3, 4] == 1;

subject to fifthvisit4:
  x[6686, 4, 4] == 1;

subject to sixthvisit4:
  x[3527, 5, 4] == 1;

##### End of file #####
