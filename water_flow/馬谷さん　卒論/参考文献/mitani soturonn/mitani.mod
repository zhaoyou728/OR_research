
######################################################################
# 集合と変数，パラメータ

set V;          # 節点の集合
set E dimen 2;  # 枝の集合（節点の対で指定する）
set K;          # レイヤー番号の集合
set P;          # 枝の持つ性質（移動時間，METs 値など）の種類

var x{E, K}, binary;  # 各枝の通過の有無（0-1 変数）
var z{V, K}, binary;  # 節点がゴールになるかどうか（0-1 変数）

param a{E, P};  # 各枝の持つ性質の値
param s;        # スタート節点の番号
param g;        # ゴール節点の番号（指定する場合）
param Kmax;     # レイヤー番号の最大値

######################################################################

# 目的関数：枝の持つある性質の線形和を最大/最小にする
# 各目的で属性値の種類pを変える

maximize Objective:
	 sum{(i, j) in E, k in K} (a[i, j, p] * x[i, j, k]);

######################################################################

# スタート節点の設定

subject to SetStartVertex:
	sum{(s, j) in E} x[s, j, 0] == 1;

# レイヤー間で通過することができる枝は高々 1 本

subject to ChooseLayerEdge {k in K: k <= Kmax}:
	sum{(i, j) in E} x[i, j, k] <= 1;

# スタート節点以外における In/Out のバランス

subject to BalanceInOut_Misc {v in V, k in K: k < Kmax}:
	sum{(i, v) in E} x[i, v, k] == (sum{(v, j) in E} x[v, j, k + 1]) + z[v, k + 1];

#同じ枝を通らない制約（0→1と1→0は同じ枝する）

subject to BalanceInOut_Misc2 {(i, j) in E}:
	sum{k in K: k < Kmax} x[i, j, k] + sum{k in K: k < Kmax} x[j, i, k] <= 2;

# ゴール節点の指定

subject to SetGoalVertex:
	sum{k in K :k > 0} z[g, k] == 1;

#### 枝の持つ性質の線形和に関する制約                  ###########
#### 　（制約を課す必要のある性質について個別に設ける）###########

# a[,,1]データは距離[m]
#subject to PropertyConst1:
#	sum{(i, j) in E, k in K} (a[i, j, 1] * x[i, j, k]) <= 1.92;

#subject to PropertyConst1_2:
#	sum{(i, j) in E, k in K} (a[i, j, 1] * x[i, j, k]) >= 1.8;

# a[,,2]データは移動時間
subject to PropertyConst2:
	sum{(i, j) in E, k in K} (a[i, j, 2] * x[i, j, k]) <= 15;

#subject to PropertyConst2_2:
#	sum{(i, j) in E, k in K} (a[i, j, 2] * x[i, j, k]) >= 25;


# a[,,3]データはMets
#subject to PropertyConst3:
#	sum{(i, j) in E, k in K} (a[i, j, 3] * x[i, j, k]) <= ###;

# a[,,4]データはエクササイズ
#subject to PropertyConst4:
#	sum{(i, j) in E, k in K} (a[i, j, 4] * x[i, j, k]) <= 200;

# a[,,5]は景観性質値,　　
subject to PropertyConst5{k in K: k <= Kmax}:
	sum{(i, j) in E } (a[i, j, 5] * x[i, j, k]) >= 2;

# a[,,6]は階段の有無
#subject to PropertyConst6:
#	sum{(i, j) in E, k in K} (a[i, j, 6] * x[i, j, k]) <= 2;

# 急な階段(5-10，3-4間)の排除
subject to PropertyConst6:
	 sum{ k in K} (x[5, 10, k] + x[10, 5, k] + x[3, 4, k] + x[4, 3, k] ) = 0;

# a[,,7]は休憩所の有無
subject to PropertyConst7:
	sum{(i, j) in E, k in K} (a[i, j, 7] * x[i, j, k]) >= 2;


######################################################################

# 結果の表示

solve;

display {(i, j) in E, k in K: x[i, j, k] == 1} x[i, j, k];
display {v in V, k in K: z[v, k] == 1} z[v, k];

end;
##### End of file #####
