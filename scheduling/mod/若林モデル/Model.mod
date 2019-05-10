set D;             #//���� (Days)
set S{D};          #//�Z�b�V���� (Session)
set R;             #//���� (Room)
set L;             #//������ (Lab)
set I;             #//���k�̊w�Дԍ� (Id)
set O dimen 2;     #//��̉^�p���Ă��錤�����̑g�ݍ��킹 (Operation)
set C dimen 2;     #//���Z�b�V�����Ŕ��\�������w���̊w�Дԍ��̑g�ݍ��킹 (Combination)

param u{d in D, S[d]};                            #//�Z�b�V�������̔��\�l���̏��
param j{d in D, S[d], I} binary default 1;        #//�w�����Q���\�ȃZ�b�V����
param j_{d in D, S[d], L} binary default 1;       #//�������Q���\�ȃZ�b�V����
param b{L,I} binary default 0;                    #//�w�����������錤����
#param w{L};

var x{d in D, S[d], R, I} binary;                 #//���\���邩�ǂ���(�l�P��)
var x_l{d in D, S[d], R, L} binary;               #//���\���邩�ǂ���(�������P��)
var n_s{d in D, S[d], R},integer;                 #//�e�Z�b�V�����̔��\�l��
var n_d{D,L},integer;                             #//�e�������̓������̔��\�l��
var c{d in D, S[d], R, L} binary;                 #//�������i������邩�ǂ���
var p1{d in D, S[d]} binary;                      #//�ᔽ�̗L��
var p2{D, L} binary;                              #//�ᔽ�̗L��
var p3{D, D, L},integer;                          #//�ᔽ��
var p4{C} binary;                                 #//�ᔽ�̗L��

minimize Objective:
 sum {d in D, s in S[d]} p1[d,s] + sum {d in D, l in L} p2[d,l] + sum {d1 in D, d2 in D, l in L : d1 != d2} p3[d1,d2,l] + sum{(i1, i2) in C} p4[i1,i2];

#//�S�w������񔭕\����
subject to AllStudentOnePublish {i in I}:
 sum {d in D, s in S[d], r in R} x[d,s,r,i] == 1;

#//�w���͋����E���g�����ɎQ���\�ȃZ�b�V�����Ŕ��\�ł���
subject to AvailableSession {d in D, s in S[d], r in R, l in L, i in I : b[l,i] == 1}:
 x[d,s,r,i] <= j[d,s,i] * j_[d,s,l];

#//�e�������͍Œ�2�Z�b�V�����Ŕ��\����
subject to OneLabOverTwoRoom {l in L}:
 sum {d in D, s in S[d], r in R} x_l[d,s,r,l] >= 2;

#//�������̃Z�b�V�����ŋ������܂����Ŕ��\���Ȃ�
subject to OneTimeOneSession {d in D, s in S[d], l in L}:
 sum {r in R} x_l[d,s,r,l] <= 1;

#//�������ł̔��\������ꍇ�C�i���̌������́j�w�������\�ł���
subject to RelationPersonalAndLab1 {d in D, s in S[d], r in R, l in L, i in I : b[l,i] == 1}:
 x[d,s,r,i] <= x_l[d,s,r,l];

#//�������̔��\������ꍇ�C�i���̌������́j�N������͔��\����
subject to RelationPersonalAndLab2 {d in D, s in S[d], r in R, l in L}:
x_l[d,s,r,l] <= sum {i in I : b[l,i]==1} x[d,s,r,i];

#//��̉^�p���s���������͓��Z�b�V�����ɂĔ��\����
subject to OneOperation {d in D, s in S[d], r in R, (l1, l2) in O}:
 x_l[d,s,r,l1] == x_l[d,s,r,l2];

#//�e�Z�b�V�����̔��\�l��
subject to NumOfSession {d in D, s in S[d], r in R}:
 n_s[d,s,r] == sum {i in I} x[d,s,r,i];

#//�������̃Z�b�V�����ɂ����āC���\�l���̍ő�ƍŏ��̍���1�ȉ�
subject to DifferenceNumOfPublishers {d in D, s in S[d], r1 in R, r2 in R : r1 != r2}:
 n_s[d,s,r1] - n_s[d,s,r2] <= p1[d,s];

#//�e�Z�b�V�����̔��\�Ґ��̏��
subject to UpperBoundOfSession {d in D, s in S[d], r in R}:
 n_s[d,s,r] <= u[d,s];

#//�e�������́C�������̔��\�Ґ�
subject to NumOfPublishers {d in D, l in L}:
 n_d[d,l] == sum {s in S[d], r in R, i in I : b[l,i] == 1} x[d,s,r,i];

#//�S�Z�b�V�����ŋ����̒N�����i�������
subject to AllSessionHaveChairman {d in D, s in S[d], r in R}:
 sum {l in L} c[d,s,r,l] == 1;

#//�������ł̔��\������ꍇ�C�i���̌������́j�������i������邱�Ƃ�����
subject to ConditionOfChairman {d in D, s in S[d], r in R, l in L}:
 c[d,s,r,l] <= x_l[d,s,r,l];

#//�e�������i�������̂�1�x�܂�
subject to OneLabOneChairman {l in L}:
 sum {d in D, s in S[d], r in R} c[d,s,r,l] <= 1;

#//�e��������1����AM�C1����PM�C2����AM�̂��ꂼ��Ŕ��\����̂��]�܂���
subject to AllDaysPublish_L {d in D, s1 in S[d], s2 in S[d], l in L : s1 != s2}:
 - p2[d,l] <= sum {r in R} (x_l[d,s1,r,l] + x_l[d,s2,r,l]) - 1;

subject to AllDaysPublish_R {d in D, s1 in S[d], s2 in S[d], l in L : s1 != s2}:
 sum {r in R} (x_l[d,s1,r,l] + x_l[d,s2,r,l]) - 1 <= p2[d,l];

#//�e�������̒��ŁC�������̔��\�Ґ��̍��́C���Ȃ���Ԃ��]�܂���
subject to DifferenceBetweenDays_L {d1 in D, d2 in D, r in R, l in L : d1 != d2}:
 -p3[d1,d2,l] <= n_d[d1,l] - n_d[d2,l];

subject to DifferenceBetweenDays_R {d1 in D, d2 in D, r in R, l in L : d1 != d2}:
 n_d[d1,l] - n_d[d2,l] <= p3[d1,d2,l];

#//�l�P�ʂœ��Z�b�V�����Ŕ��\�������g�ݍ��킹���ł��邾������������
subject to IdCombination_L {d in D, s in S[d], r in R, (i1, i2) in C}:
 x[d,s,r,i1] - x[d,s,r,i2] <= p4[i1,i2];

subject to IdCombination_R {d in D, s in S[d], r in R, (i1, i2) in C}:
 -p4[i1,i2] <= x[d,s,r,i1] - x[d,s,r,i2];

#/////////////////////////////////
#set G dimen2; //���\���Ԃ����炵�����������̑g���� (Gallery)
#var p5{G} binary;
#subject to MakeGallery {d in D, s in S[d], r in R, (l1, l2) in G}:
# x_l[d,s,r,l1] + x_l[d,s,r,l2] <= 1;            #//��ΐ���
# x_l[d,s,r,l1] + x_l[d,s,r,l2] <= p5[l1,l2];    #//�l������

#set U;        //�Z�b�V�����̒��ł̔��\��
