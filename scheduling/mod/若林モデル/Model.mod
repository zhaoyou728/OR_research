set D;             #//日程 (Days)
set S{D};          #//セッション (Session)
set R;             #//教室 (Room)
set L;             #//研究室 (Lab)
set I;             #//生徒の学籍番号 (Id)
set O dimen 2;     #//一体運用している研究室の組み合わせ (Operation)
set C dimen 2;     #//同セッションで発表したい学生の学籍番号の組み合わせ (Combination)

param u{d in D, S[d]};                            #//セッション毎の発表人数の上限
param j{d in D, S[d], I} binary default 1;        #//学生が参加可能なセッション
param j_{d in D, S[d], L} binary default 1;       #//教員が参加可能なセッション
param b{L,I} binary default 0;                    #//学生が所属する研究室
#param w{L};

var x{d in D, S[d], R, I} binary;                 #//発表するかどうか(個人単位)
var x_l{d in D, S[d], R, L} binary;               #//発表するかどうか(研究室単位)
var n_s{d in D, S[d], R},integer;                 #//各セッションの発表人数
var n_d{D,L},integer;                             #//各研究室の日程毎の発表人数
var c{d in D, S[d], R, L} binary;                 #//教員が司会をするかどうか
var p1{d in D, S[d]} binary;                      #//違反の有無
var p2{D, L} binary;                              #//違反の有無
var p3{D, D, L},integer;                          #//違反量
var p4{C} binary;                                 #//違反の有無

minimize Objective:
 sum {d in D, s in S[d]} p1[d,s] + sum {d in D, l in L} p2[d,l] + sum {d1 in D, d2 in D, l in L : d1 != d2} p3[d1,d2,l] + sum{(i1, i2) in C} p4[i1,i2];

#//全学生が一回発表する
subject to AllStudentOnePublish {i in I}:
 sum {d in D, s in S[d], r in R} x[d,s,r,i] == 1;

#//学生は教員・自身が共に参加可能なセッションで発表できる
subject to AvailableSession {d in D, s in S[d], r in R, l in L, i in I : b[l,i] == 1}:
 x[d,s,r,i] <= j[d,s,i] * j_[d,s,l];

#//各研究室は最低2セッションで発表する
subject to OneLabOverTwoRoom {l in L}:
 sum {d in D, s in S[d], r in R} x_l[d,s,r,l] >= 2;

#//同時刻のセッションで教室をまたいで発表しない
subject to OneTimeOneSession {d in D, s in S[d], l in L}:
 sum {r in R} x_l[d,s,r,l] <= 1;

#//研究室での発表がある場合，（その研究室の）学生が発表できる
subject to RelationPersonalAndLab1 {d in D, s in S[d], r in R, l in L, i in I : b[l,i] == 1}:
 x[d,s,r,i] <= x_l[d,s,r,l];

#//研究室の発表がある場合，（その研究室の）誰かしらは発表する
subject to RelationPersonalAndLab2 {d in D, s in S[d], r in R, l in L}:
x_l[d,s,r,l] <= sum {i in I : b[l,i]==1} x[d,s,r,i];

#//一体運用を行う研究室は同セッションにて発表する
subject to OneOperation {d in D, s in S[d], r in R, (l1, l2) in O}:
 x_l[d,s,r,l1] == x_l[d,s,r,l2];

#//各セッションの発表人数
subject to NumOfSession {d in D, s in S[d], r in R}:
 n_s[d,s,r] == sum {i in I} x[d,s,r,i];

#//同時刻のセッションにおいて，発表人数の最大と最小の差は1以下
subject to DifferenceNumOfPublishers {d in D, s in S[d], r1 in R, r2 in R : r1 != r2}:
 n_s[d,s,r1] - n_s[d,s,r2] <= p1[d,s];

#//各セッションの発表者数の上限
subject to UpperBoundOfSession {d in D, s in S[d], r in R}:
 n_s[d,s,r] <= u[d,s];

#//各研究室の，日程毎の発表者数
subject to NumOfPublishers {d in D, l in L}:
 n_d[d,l] == sum {s in S[d], r in R, i in I : b[l,i] == 1} x[d,s,r,i];

#//全セッションで教員の誰かが司会をする
subject to AllSessionHaveChairman {d in D, s in S[d], r in R}:
 sum {l in L} c[d,s,r,l] == 1;

#//研究室での発表がある場合，（その研究室の）教員が司会をすることがある
subject to ConditionOfChairman {d in D, s in S[d], r in R, l in L}:
 c[d,s,r,l] <= x_l[d,s,r,l];

#//各教員が司会をするのは1度まで
subject to OneLabOneChairman {l in L}:
 sum {d in D, s in S[d], r in R} c[d,s,r,l] <= 1;

#//各研究室は1日目AM，1日目PM，2日目AMのそれぞれで発表するのが望ましい
subject to AllDaysPublish_L {d in D, s1 in S[d], s2 in S[d], l in L : s1 != s2}:
 - p2[d,l] <= sum {r in R} (x_l[d,s1,r,l] + x_l[d,s2,r,l]) - 1;

subject to AllDaysPublish_R {d in D, s1 in S[d], s2 in S[d], l in L : s1 != s2}:
 sum {r in R} (x_l[d,s1,r,l] + x_l[d,s2,r,l]) - 1 <= p2[d,l];

#//各研究室の中で，日程毎の発表者数の差は，少ない状態が望ましい
subject to DifferenceBetweenDays_L {d1 in D, d2 in D, r in R, l in L : d1 != d2}:
 -p3[d1,d2,l] <= n_d[d1,l] - n_d[d2,l];

subject to DifferenceBetweenDays_R {d1 in D, d2 in D, r in R, l in L : d1 != d2}:
 n_d[d1,l] - n_d[d2,l] <= p3[d1,d2,l];

#//個人単位で同セッションで発表したい組み合わせをできるだけ成立させる
subject to IdCombination_L {d in D, s in S[d], r in R, (i1, i2) in C}:
 x[d,s,r,i1] - x[d,s,r,i2] <= p4[i1,i2];

subject to IdCombination_R {d in D, s in S[d], r in R, (i1, i2) in C}:
 -p4[i1,i2] <= x[d,s,r,i1] - x[d,s,r,i2];

#/////////////////////////////////
#set G dimen2; //発表時間をずらしたい研究室の組合せ (Gallery)
#var p5{G} binary;
#subject to MakeGallery {d in D, s in S[d], r in R, (l1, l2) in G}:
# x_l[d,s,r,l1] + x_l[d,s,r,l2] <= 1;            #//絶対制約
# x_l[d,s,r,l1] + x_l[d,s,r,l2] <= p5[l1,l2];    #//考慮制約

#set U;        //セッションの中での発表順
