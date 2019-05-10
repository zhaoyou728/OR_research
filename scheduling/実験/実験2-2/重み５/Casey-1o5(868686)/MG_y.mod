set D;             #//時間帯
set S;             #//セッション
set S_{D};         #//セッションの組み合わせ
set R;             #//教室
set A{S};          #//セッション S, 教室 R での発表順序
set I;             #//生徒の学籍番号
set L;             #//研究室 (Lab)
set O dimen 2;     #//一体運用している研究室の組み合わせ (Operation)
set C dimen 2;     #//同セッションで発表したい学生の学籍番号の組み合わせ (Combination)
set G dimen 2;     #//研究を聞きたい研究室の組み合わせ（Gallery）


param u{S};                                    #//セッション毎の発表人数の上限
param b{L,I} binary default 0;                 #//学生が所属する研究室
param j{S, I} binary default 1;                #//学生が参加可能なセッション
param j_{S, L} binary default 1;               #//教員が参加可能なセッション

var x{s in S, R, I, A[s]} binary;              #//発表するかどうか(個人単位)
var y{S, R, L} binary;                         #//発表するかどうか(研究室単位)
var n_s{S, R},integer;                         #//各セッションの発表人数
var n_d{D, L},integer;                         #//各研究室の日程毎の発表人
var c{S, R, L} binary;                         #//教員が司会をするかどうか
var p1{S} binary;                              #//違反の有無（考慮制約１について）
var p2{D, L} binary;                           #//違反の有無（考慮制約２について）
var p3{D, D, L},integer;                       #//違反量　　（考慮制約３について）
var p4{C} binary;                              #//違反の有無（考慮制約４について）
var p5{G} binary;                              #//違反の有無（考慮制約５について）
var v1 integer;
var v2 integer;
var v3 integer;
var v4 integer;
var v5 integer;

minimize Objective:
v1 + v2 + 5*v3 + v4 + v5;

#// sum {s in S} p1[s] + sum {d in D, l in L} p2[d,l] + sum {d1 in D, d2 in D, l in L : d1 != d2 } p3[d1,d2,l] + sum{(i1, i2) in C} p4[i1,i2] + sum{(l1,l2) in G} p5[l1,l2];


#//全学生が1回発表する
subject to AllStudentOnePublish {i in I}:
 sum {s in S, r in R, a in A[s]} x[s,r,i,a] == 1;

#//学生は教員・自身が共に参加可能なセッションで発表できる
subject to AvailableSession {s in S, r in R, l in L, i in I, a in A[s] : b[l,i] == 1}:
 x[s,r,i,a] <= j[s,i] * j_[s,l];

#//各研究室は最低2セッションで発表する
subject to OneLabOverTwoRoom {l in L}:
 sum {s in S, r in R} y[s,r,l] >= 2;

#//同時刻のセッションで教室をまたいで発表しない
subject to OneTimeOneSession {s in S, l in L}:
 sum {r in R} y[s,r,l] <= 1;

#//研究室での発表がある場合，（その研究室の）学生が発表できる
subject to RelationPersonalAndLab1 {s in S, r in R, l in L, i in I : b[l,i] == 1}:
 sum {a in A[s]} x[s,r,i,a] <= y[s,r,l];

#//研究室の発表がある場合，（その研究室の）誰かしらは発表する
subject to RelationPersonalAndLab2 {s in S, r in R, l in L}:
 y[s,r,l] <= sum {i in I, a in A[s] : b[l,i]==1} x[s,r,i,a];

#//一体運用を行う研究室は同セッションにて発表する
subject to OneOperation {s in S, r in R, (l1, l2) in O}:
 y[s,r,l1] == y[s,r,l2];

#//各セッションの発表人数の計算
subject to NumOfSession {s in S, r in R}:
 n_s[s,r] == sum {i in I, a in A[s]} x[s,r,i,a];

#//各セッションの発表者数は上限を超えない
subject to UpperBoundOfSession {s in S, r in R}:
 n_s[s,r] <= u[s];

#//各研究室の，日程毎の発表者数
subject to NumOfPublishers {d in D, l in L}:
 n_d[d,l] == sum {s_ in S_[d], r in R, i in I, a in A[s_] :b[l,i] == 1} x[s_,r,i,a];

#//全セッションで教員の誰かが司会をする
subject to AllSessionHaveChairman {s in S, r in R}:
 sum {l in L} c[s,r,l] == 1;

#//研究室での発表がある場合，（その研究室の）教員が司会をすることがある
subject to ConditionOfChairman {s in S, r in R, l in L}:
 c[s,r,l] <= y[s,r,l];

#//各教員が司会をするのは1度まで
subject to OneLabOneChairman {l in L}:
 sum {s in S, r in R} c[s,r,l] <= 1;

#//同一セッション・教室内での発表順序が重ならない
subject to DifferenceOrder {s in S, r in R, a in A[s]}:
 sum {i in I} x[s,r,i,a] <= 1;

	
#//同時刻のセッションにおいて，発表人数の最大と最小の差は1以下
subject to DifferenceNumOfPublishers {s in S, r1 in R, r2 in R : r1 != r2}:
 n_s[s,r1] - n_s[s,r2] <= p1[s];

#//各研究室は1日目AM，1日目PM，2日目AMのそれぞれで発表するのが望ましい
subject to AllDaysPublish_L {d in D, l in L}:
 - p2[d,l] <= sum {r in R, s in S_[d]} (y[s,r,l])- 1;

subject to AllDaysPublish_R {d in D, l in L}:
 sum {r in R, s in S_[d]} (y[s,r,l]) - 1 <= p2[d,l];

#//各研究室の中で，日程毎の発表者数の差は，少ない状態が望ましい
subject to DifferenceBetweenDays_L {d1 in D, d2 in D, l in L : d1 != d2 }:
 -p3[d1,d2,l] <= n_d[d1,l] - n_d[d2,l];

subject to DifferenceBetweenDays_R {d1 in D, d2 in D, l in L : d1 != d2}:
 n_d[d1,l] - n_d[d2,l] <= p3[d1,d2,l];

#//個人単位で同セッションで発表したい組み合わせをできるだけ成立させる
subject to IdCombination_L {s in S, r in R, (i1, i2) in C}:
 -p4[i1,i2] <=sum{a in A[s]} x[s,r,i1,a] -sum{a in A[s]} x[s,r,i2,a];

subject to IdCombination_R {s in S, r in R, (i1, i2) in C}:
 sum{a in A[s]} x[s,r,i1,a] - sum{a in A[s] }x[s,r,i2,a] <= p4[i1,i2];


#//お互いに発表を聞きたい研究室の発表セッションができるだけ重ならない
subject to MakeGallery {s in S, (l1, l2) in G}:
 sum {r in R} ( y[s,r,l1] + y[s,r,l2] ) - 1 <= p5[l1,l2];



subject to c1:
v1 = sum{s in S} p1[s];

subject to c2:
v2 = sum{d in D, l in L} p2[d,l];

subject to c3:
v3 = sum{d1 in D, d2 in D, l in L : d1 != d2} p3[d1,d2,l];

subject to c4:
v4 = sum{(i1,i2) in C} p4[i1,i2];

subject to c5:
v5 = sum{(l1, l2) in G} p5[l1,l2];








