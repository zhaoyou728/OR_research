##############################

set T; # time
set S; # senario

var WB{T} >= 0.0;
var WG{T} >= 0.0;
var BG{T} >= 0.0;
var AVE{T} >= 0.0;
var d11{T, S} binary;
var d12{T, S} binary;
var d21{T, S} binary;
var d22{T, S} binary;
var y1{T, S} >= 0.0;
var y2{T, S} >= 0.0;
var STE{T, S};

param M1; # big-M
param M2; # big-M
param Tnum; # |T|

param c{T, S};
param ps{S}; # previous senario
param price{T};
param prod{T, S};
param v{T, S};
param C;
param cpd;
param STE_init;
param allow_prod_1{T};
param allow_prod_2{T};
#param allow_vl;
#param allow_vu;
#param allow_vl_Tnum;
#param allow_vu_Tnum;
param margin;

##############################

maximize Objective: sum {t in T: t >= 1} (price[t] * (WG[t] + BG[t]));

##############################

subject to C1_1 {t in T}:
	WB[t] + WG[t] == AVE[t];

subject to C1_2 {t in T}:
	AVE[t] == sum {s in S: c[t, s] > 0} (prod[t, s] * v[t, s]);

subject to C2_1_1_1 {t in T, s in S: c[t, s] > 0}:
	- M1 * (1 - d11[t, s]) <= 0.98 * (WG[t] + BG[t]) - v[t, s];

subject to C2_1_1_2 {t in T, s in S: c[t, s] > 0}:
	0.98 * (WG[t] + BG[t]) - v[t, s] <= M1 * d11[t, s];

subject to C2_1_2_1 {t in T, s in S: c[t, s] > 0}:
	(0.98 * (WG[t] + BG[t]) - v[t, s]) - M1 * (1 - d11[t, s]) <= y1[t, s];

subject to C2_1_2_2 {t in T, s in S: c[t, s] > 0}:
	y1[t, s] <= (0.98 * (WG[t] + BG[t]) - v[t, s]) + M1 * (1 - d11[t, s]);

subject to C2_1_3_1 {t in T, s in S: c[t, s] > 0}:
	- M1 * d11[t, s] <= y1[t, s];

subject to C2_1_3_2 {t in T, s in S: c[t, s] > 0}:
	y1[t, s] <= M1 * d11[t, s];


subject to C2_2_1_1 {t in T, s in S: c[t, s] > 0}:
	- M1 * (1 - d12[t, s]) <= v[t, s] - 1.02 * (WG[t] + BG[t]);

subject to C2_2_1_2 {t in T, s in S: c[t, s] > 0}:
	v[t, s] - 1.02 * (WG[t] + BG[t]) <= M1 * d12[t, s];

subject to C2_2_2_1 {t in T, s in S: c[t, s] > 0}:
	(v[t, s] - 1.02 * (WG[t] + BG[t])) - M1 * (1 - d12[t, s]) <= y2[t, s];

subject to C2_2_2_2 {t in T, s in S: c[t, s] > 0}:
	y2[t, s] <= (v[t, s] - 1.02 * (WG[t] + BG[t])) + M1 * (1 - d12[t, s]);

subject to C2_2_3_1 {t in T, s in S: c[t, s] > 0}:
	- M1 * d12[t, s] <= y2[t, s];

subject to C2_2_3_2 {t in T, s in S: c[t, s] > 0}:
	y2[t, s] <= M1 * d12[t, s];

subject to C3_1 {t in T, s in S: c[t, s] > 0 && t >= 1}:
	STE[t, s] == STE[t - 1, ps[s]] - y1[t, s] / 0.9 + 0.95 * y2[t, s] - C;

subject to C3_2:
	STE[0, 0] == STE_init;

#subject to C4_1_1 {t in T, s in S: c[t, s] > 0}:
#	- M2 * (1 - d21[t, s]) <= 0.3 * cpd - STE[t, s];
#
#subject to C4_1_2 {t in T, s in S: c[t, s] > 0}:
#	0.3 * cpd - STE[t, s] <= M2 * d21[t, s];
#
#subject to C4_2_1 {t in T, s in S: c[t, s] > 0}:
#	- M2 * (1 - d22[t, s]) <= STE[t, s] - 0.7 * cpd;
#
#subject to C4_2_2 {t in T, s in S: c[t, s] > 0}:
#	STE[t, s] - 0.7 * cpd <= M2 * d22[t, s];

subject to C4_1_1 {t in T, s in S: c[t, s] > 0}:
	- M2 * (1 - d21[t, s]) <= margin * cpd - STE[t, s];

subject to C4_1_2 {t in T, s in S: c[t, s] > 0}:
	margin * cpd - STE[t, s] <= M2 * d21[t, s];

subject to C4_2_1 {t in T, s in S: c[t, s] > 0}:
	- M2 * (1 - d22[t, s]) <= STE[t, s] - (1.0 - margin) * cpd;

subject to C4_2_2 {t in T, s in S: c[t, s] > 0}:
	STE[t, s] - (1.0 - margin) * cpd <= M2 * d22[t, s];

subject to C5_1 {t in T}:
	sum {s in S: c[t, s] > 0} (d21[t, s] * prod[t, s]) <= allow_prod_1[t];

subject to C5_2 {t in T}:
	sum {s in S: c[t, s] > 0} (d22[t, s] * prod[t, s]) <= allow_prod_2[t];

#subject to C6_1:
#	allow_vl <= sum {s in S} (prod[Tnum, s] * STE[Tnum, s]);
#
#subject to C6_2:
#	sum {s in S} (prod[Tnum, s] * STE[Tnum, s]) <= allow_vu;

#subject to C6_1 {t in T: t > 0 && t < Tnum}:
#	allow_vl <= sum {s in S} (prod[t, s] * STE[t, s]);
#
#subject to C6_2 {t in T: t > 0 && t < Tnum}:
#	sum {s in S} (prod[t, s] * STE[t, s]) <= allow_vu;
#
#subject to C6_3:
#	allow_vl <= sum {s in S} (prod[Tnum, s] * STE[Tnum, s]);
#
#subject to C6_4:
#	sum {s in S} (prod[Tnum, s] * STE[Tnum, s]) <= allow_vu;

#subject to C6_1 {t in T: t > 0 && t < Tnum}:
#	margin * cpd <= sum {s in S} (prod[t, s] * STE[t, s]);
#
#subject to C6_2 {t in T: t > 0 && t < Tnum}:
#	sum {s in S} (prod[t, s] * STE[t, s]) <= (1.0 - margin) * cpd;
#
#subject to C6_3:
#	margin * cpd <= sum {s in S} (prod[Tnum, s] * STE[Tnum, s]);
#
#subject to C6_4:
#	sum {s in S} (prod[Tnum, s] * STE[Tnum, s]) <= (1.0 - margin) * cpd;

##### End of file #####
