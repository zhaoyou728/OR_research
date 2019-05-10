
######################################################################
# �W���ƕϐ��C�p�����[�^

set V;          # �ߓ_�̏W��
set E dimen 2;  # �}�̏W���i�ߓ_�̑΂Ŏw�肷��j
set K;          # ���C���[�ԍ��̏W��
set P;          # �}�̎������i�ړ����ԁCMETs �l�Ȃǁj�̎��

var x{E, K}, binary;  # �e�}�̒ʉ߂̗L���i0-1 �ϐ��j
var z{V, K}, binary;  # �ߓ_���S�[���ɂȂ邩�ǂ����i0-1 �ϐ��j

param a{E, P};  # �e�}�̎������̒l
param s;        # �X�^�[�g�ߓ_�̔ԍ�
param g;        # �S�[���ߓ_�̔ԍ��i�w�肷��ꍇ�j
param Kmax;     # ���C���[�ԍ��̍ő�l

######################################################################

# �ړI�֐��F�}�̎����鐫���̐��`�a���ő�/�ŏ��ɂ���
# �e�ړI�ő����l�̎��p��ς���

maximize Objective:
	 sum{(i, j) in E, k in K} (a[i, j, p] * x[i, j, k]);

######################################################################

# �X�^�[�g�ߓ_�̐ݒ�

subject to SetStartVertex:
	sum{(s, j) in E} x[s, j, 0] == 1;

# ���C���[�ԂŒʉ߂��邱�Ƃ��ł���}�͍��X 1 �{

subject to ChooseLayerEdge {k in K: k <= Kmax}:
	sum{(i, j) in E} x[i, j, k] <= 1;

# �X�^�[�g�ߓ_�ȊO�ɂ����� In/Out �̃o�����X

subject to BalanceInOut_Misc {v in V, k in K: k < Kmax}:
	sum{(i, v) in E} x[i, v, k] == (sum{(v, j) in E} x[v, j, k + 1]) + z[v, k + 1];

#�����}��ʂ�Ȃ�����i0��1��1��0�͓����}����j

subject to BalanceInOut_Misc2 {(i, j) in E}:
	sum{k in K: k < Kmax} x[i, j, k] + sum{k in K: k < Kmax} x[j, i, k] <= 2;

# �S�[���ߓ_�̎w��

subject to SetGoalVertex:
	sum{k in K :k > 0} z[g, k] == 1;

#### �}�̎������̐��`�a�Ɋւ��鐧��                  ###########
#### �@�i������ۂ��K�v�̂��鐫���ɂ��Čʂɐ݂���j###########

# a[,,1]�f�[�^�͋���[m]
#subject to PropertyConst1:
#	sum{(i, j) in E, k in K} (a[i, j, 1] * x[i, j, k]) <= 1.92;

#subject to PropertyConst1_2:
#	sum{(i, j) in E, k in K} (a[i, j, 1] * x[i, j, k]) >= 1.8;

# a[,,2]�f�[�^�͈ړ�����
subject to PropertyConst2:
	sum{(i, j) in E, k in K} (a[i, j, 2] * x[i, j, k]) <= 15;

#subject to PropertyConst2_2:
#	sum{(i, j) in E, k in K} (a[i, j, 2] * x[i, j, k]) >= 25;


# a[,,3]�f�[�^��Mets
#subject to PropertyConst3:
#	sum{(i, j) in E, k in K} (a[i, j, 3] * x[i, j, k]) <= ###;

# a[,,4]�f�[�^�̓G�N�T�T�C�Y
#subject to PropertyConst4:
#	sum{(i, j) in E, k in K} (a[i, j, 4] * x[i, j, k]) <= 200;

# a[,,5]�͌i�ϐ����l,�@�@
subject to PropertyConst5{k in K: k <= Kmax}:
	sum{(i, j) in E } (a[i, j, 5] * x[i, j, k]) >= 2;

# a[,,6]�͊K�i�̗L��
#subject to PropertyConst6:
#	sum{(i, j) in E, k in K} (a[i, j, 6] * x[i, j, k]) <= 2;

# �}�ȊK�i(5-10�C3-4��)�̔r��
subject to PropertyConst6:
	 sum{ k in K} (x[5, 10, k] + x[10, 5, k] + x[3, 4, k] + x[4, 3, k] ) = 0;

# a[,,7]�͋x�e���̗L��
subject to PropertyConst7:
	sum{(i, j) in E, k in K} (a[i, j, 7] * x[i, j, k]) >= 2;


######################################################################

# ���ʂ̕\��

solve;

display {(i, j) in E, k in K: x[i, j, k] == 1} x[i, j, k];
display {v in V, k in K: z[v, k] == 1} z[v, k];

end;
##### End of file #####
