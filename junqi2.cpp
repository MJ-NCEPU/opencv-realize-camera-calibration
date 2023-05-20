/* ************************************************************************ */
/* �������ӱ���Լ��:														*/
/*	a˾��,b����,cʦ��,d�ó�,e�ų�,fӪ��,g����,h�ų�,i����,j����kը��,l����	*/
/* �Է������ӱ���Լ��:														*/
/*	A˾��,B����,Cʦ��,D�ó�,E�ų�,FӪ��,G����,H�ų�,I����,J����Kը��,L����	*/
/*	Xδ֪�Է�����,0����λ													*/
/* �����£�2012-03-31  meixian@hrbust.edu.cn								*/
/* ˾����߷� ��31�����Ӿ���ѡ���С������ �����ڼ��������ϵ��ӣ�	���̵�����
��ܵз���31��	 ��һ������ʧ�ܣ���ȡ�ڶ��ַ�����  �����߷������ɣ�ը��  ������
/* ************************************************************************ */
#include <stdio.h>
#include <Windows.h>
#include <iostream>
#include <string.h>

using namespace std;

//int zz=0;
int z1 = 0, z2 = 0, z3 = 0, z4 = 0;//�жϼ������ӣ��Ƿ�Ϊ��һ�ν���Ӫ
int Ina_step[2] = { 2,0 };  //��һλ����˭�����ӵ�,1Ϊ�������ӵģ�2Ϊ�з������ӵġ��ڶ�λ��ʾδ���Ӵ�����
int tra = 0;
int track[100];
int jq = 0;//��ʾ�Է�˾��������з����ҷ��Է�����λ����Ϣ��1�����һ�η��ͣ���1�����ǵ�һ�η���
int x11, y11, x21, y21;//��¼�з���һ��������
int tongji = 0;
int bekilled[25] = {0};
int qipanfen[12][5] = 
{ 500 ,1000,600 ,1000,800,  
200 ,600 ,500 ,600 ,200,
250 ,800 ,20  ,800 ,250,
140 ,20  ,700 ,20  ,140,
130 ,400 ,20  ,400 ,130,
120 ,80  ,150 ,80  ,120,
110 ,100 ,150 ,100 ,110,
100 ,500 ,20  ,500 ,100,
100 ,20  ,400 ,20  ,100,
100 ,600 ,20  ,600 ,100,
500 ,100 ,100 ,100 ,500,
200 ,-1000 ,200 ,-1000 ,200 };
/* ************************************************************************ */
/* �������ܣ�i,jλ���Ƿ񱾷�����											*/
/* �ӿڲ�����																*/
/*     char cMap[12][5] ���̾���											*/
/*     int i,j ����λ�����к�												*/
/* ����ֵ��																	*/
/*     1�������ӣ�0����λ��Է�����											*/
/* ************************************************************************ */
int IsMyChess(char cMap[12][5], int i, int j)
{
	if (cMap[i][j] >= 'a'&& cMap[i][j] <= 'l')
		return 1;
	else
		return 0;
}

/* ************************************************************************ */
/* �������ܣ�i,jλ���Ƿ񱾷����ƶ�������									*/
/* �ӿڲ�����																*/
/*     char cMap[12][5] ���̾���											*/
/*     int i,j ����λ�����к�												*/
/* ����ֵ��																	*/
/*     1�������ƶ�����(˾��,����,...,����,ը��)��0����,����,�Է����ӻ����λ*/
/* ************************************************************************ */
int IsMyMovingChess(char cMap[12][5], int i, int j)
{
	if (cMap[i][j] >= 'a' && cMap[i][j] <= 'i' || cMap[i][j] == 'k')
		return 1;
	else
		return 0;
}

//���ڼ����ҷ����ƶ���������
//����ֵ ���Ӹ���
int MyMovingChess(char cMap[12][5])
{
	int i, j;
	int n = 0;
	int N = 0;
	for (i = 0; i < 12; i++)
		for (j = 0; j < 5; j++)
			if (cMap[i][j] >= 'a'&&cMap[i][j] <= 'i' || cMap[i][j] == 'k')
			{
				if (i == 11 && j == 1)
					;
				else if (i == 11 && j == 3)
					;
				else
					n++;
			}
	return n;
}

/* ************************************************************************ */
/* �������ܣ�i,jλ���Ƿ�ɽ���ı�վ										*/
/* �ӿڲ�����																*/
/*     int i,j ����λ�����к�												*/
/* ����ֵ��																	*/
/*     1����ɽ���0������ɽ���											*/
/* ************************************************************************ */
int IsAfterHill(int i, int j)
{
	if (i * 5 + j == 31 || i * 5 + j == 33)
		return 1;
	else
		return 0;
}

/* ************************************************************************ */
/* �������ܣ�i,jλ���Ƿ���Ӫ												*/
/* �ӿڲ�����																*/
/*     int i,j ����λ�����к�												*/
/* ����ֵ��																	*/
/*     1����Ӫ��0������Ӫ													*/
/* ************************************************************************ */
int IsMoveCamp(int i, int j)
{
	if (i * 5 + j == 11 || i * 5 + j == 13 || i * 5 + j == 17 || i * 5 + j == 21 || i * 5 + j == 23 || i * 5 + j == 36 || i * 5 + j == 38 || i * 5 + j == 42 || i * 5 + j == 46 || i * 5 + j == 48)
		return 1;
	else
		return 0;
}

//�������ܣ��ж������Ƿ���������
//int int ��i��j��Ϊ����λ�����к�
int IsRailway(int i, int j)
{
	if (i == 1 || i == 5 || i == 6 || i == 10 || ((j == 0 || j == 4) && i>0 && i<11))
		return 1;
	else
		return 0;
}
/* ************************************************************************ */
/* �������ܣ�i,jλ���Ƿ��Ƕ�������											*/
/* �ӿڲ�����																*/
/*     char cMap[12][5]	���̾���											*/
/*     int i, j	����λ�����к�												*/
/* ����ֵ��																	*/
/*     1�������ӣ�0����λ�򼺷�����											*/
/* ************************************************************************ */
int IsOppChess(char cMap[12][5], int i, int j)
{
	if (cMap[i][j] >= 'A' && cMap[i][j] <= 'X')
		return 1;
	else
		return 0;
}

//�������ܣ�i,jλ���Ƿ�ɽ��ǰ�ı�վ
int IsBehindHill(int i, int j)
{
	if (i * 5 + j == 26 || i * 5 + j == 28)
		return 1;
	else
		return 0;
}

/* ************************************************************************ */
/* �������ܣ��������������                                          		*/
/* �ӿڲ�����																*/
/*     char cTryMap	�������̾���											*/
/*     int x	������														*/
/*     int y	������														*/
/*     int iSaMove	��¼��������·���߷�									*/
/*     int iNum	�Ѵ��߷�����												*/
/* ����ֵ��	��ʼ: iNum=0															*/
/* ************************************************************************ */
int SapperRail(int iSaMove[40][2], char cTryMap[12][5], int x, int y, int iNum)
{
	int i, t;
	//����ǰ��:���ڵ�һ��,����ɽ���,ǰ���ǿ�,������������
	if (x>0 && !IsAfterHill(x, y) && (cTryMap[x - 1][y] == '0' || IsOppChess(cTryMap, x - 1, y)) && IsRailway(x - 1, y))
	{
		t = 0;
		for (i = 0; i <= iNum; i++)
		{
			if ((x - 1) == iSaMove[i][0] && y == iSaMove[i][1])//����ظ��߷�������ѭ��
				t = 1;
		}

		if (t == 0)
		{
			iNum++;
			iSaMove[iNum][0] = x - 1;
			iSaMove[iNum][1] = y;
			if (cTryMap[x - 1][y] == '0')
			{
				cTryMap[x][y] = '0';
				cTryMap[x - 1][y] = 'i';
				iNum = SapperRail(iSaMove, cTryMap, x - 1, y, iNum);
				cTryMap[x][y] = 'i';
				cTryMap[x - 1][y] = '0';
			}
		}
	}

	//��������:����������,����ǿ�,������������
	if (y>0 && (cTryMap[x][y - 1] == '0' || IsOppChess(cTryMap, x, y - 1)) && IsRailway(x, y - 1))
	{
		t = 0;
		for (i = 0; i <= iNum; i++)
		{
			if (x == iSaMove[i][0] && (y - 1) == iSaMove[i][1])
				t = 1;
		}

		if (t == 0)
		{
			iNum++;
			iSaMove[iNum][0] = x;
			iSaMove[iNum][1] = y - 1;
			if (cTryMap[x][y - 1] == '0')
			{
				cTryMap[x][y] = '0';
				cTryMap[x][y - 1] = 'i';
				iNum = SapperRail(iSaMove, cTryMap, x, y - 1, iNum);
				cTryMap[x][y] = 'i';
				cTryMap[x][y - 1] = '0';
			}
		}
	}

	//��������://����������,�Ҳ಻�Ǽ�������,������������
	if (y<4 && (cTryMap[x][y + 1] == '0' || IsOppChess(cTryMap, x, y + 1)) && IsRailway(x, y + 1))
	{
		t = 0;
		for (i = 0; i <= iNum; i++)
		{
			if (x == iSaMove[i][0] && (y + 1) == iSaMove[i][1])
				t = 1;
		}

		if (t == 0)
		{
			iNum++;
			iSaMove[iNum][0] = x;
			iSaMove[iNum][1] = y + 1;
			if (cTryMap[x][y + 1] == '0')
			{
				cTryMap[x][y] = '0';
				cTryMap[x][y + 1] = 'i';
				iNum = SapperRail(iSaMove, cTryMap, x, y + 1, iNum);
				cTryMap[x][y] = 'i';
				cTryMap[x][y + 1] = '0';
			}
		}
	}

	//���Ժ���:�������һ��,����ɽ��ǰ,�󷽲��Ǽ�������,������������
	if (x<11 && !IsBehindHill(x, y) && (cTryMap[x + 1][y] == '0' || IsOppChess(cTryMap, x + 1, y)) && IsRailway(x + 1, y))
	{
		t = 0;
		for (i = 0; i <= iNum; i++)
		{
			if ((x + 1) == iSaMove[i][0] && y == iSaMove[i][1])
				t = 1;
		}

		if (t == 0)
		{
			iNum++;
			iSaMove[iNum][0] = (x + 1);
			iSaMove[iNum][1] = y;
			if (cTryMap[x + 1][y] == '0')
			{
				cTryMap[x][y] = '0';
				cTryMap[x + 1][y] = 'i';
				iNum = SapperRail(iSaMove, cTryMap, x + 1, y, iNum);
				cTryMap[x][y] = 'i';
				cTryMap[x + 1][y] = '0';
			}
		}
	}

	return iNum;
}
/* ************************************************************************ */
/* �������ܣ��ж���ĳ�����ӵĸ���                                      		*/
/* �ӿڲ�����																*/
/*     int i													            */
/*     int j		  ��Ҫ�ж����ӵ�λ��								    */
/*     int k		  ���ӱ��  											*/
/*     int dz[25][14] �з����Ӹ���							                */
/* ************************************************************************ */
int Judge(int i, int j, int k, int dz[25][16])
{
	for (int n = 0; n<25; n++)
	{
		if (dz[n][12] == i && dz[n][13] == j)
			return dz[n][k];
	}
	return 0;
}
/* ************************************************************************ */
/* �������ܣ�i,jλ���Ƿ��Ӫ											*/
/* �ӿڲ�����																*/
/*     int i,j ����λ�����к�												*/
/* ����ֵ��																	*/
/*     1�Ǵ�Ӫ��0���Ǵ�Ӫ												*/
/* ************************************************************************ */
int IsBaseCamp(int i, int j)
{
	if (i * 5 + j == 1 || i * 5 + j == 3 || i * 5 + j == 56 || i * 5 + j == 58)
		return 1;
	else
		return 0;
}

/* ************************************************************************ */
/* �������ܣ�i,jλ���Ƿ�������ռλ����Ӫ										*/
/* �ӿڲ�����																*/
/*     char cMap[12][5] ���̾���											*/
/*     int i,j ����λ�����к�												*/
/* ����ֵ��																	*/
/*     1������ռλ����Ӫ,0������Ӫ���ǿ���Ӫ								*/
/* ************************************************************************ */
int IsFilledCamp(char cMap[12][5], int i, int j)
{
	if (IsMoveCamp(i, j) && cMap[i][j] != '0')
		return 1;
	else
		return 0;
}
int Iszuoqian(int i, int j)
{
	if (i * 5 + j == 19 || i * 5 + j == 29 || i * 5 + j == 27 || i * 5 + j == 44 || i * 5 + j == 52 || i * 5 + j == 54)
		return 1;
	else
		return 0;
}

//(i��j)Ϊ������Ӫ�ҿ�������ǰ���ƶ�������
//  1Ϊ�������㣬0����������
int Isyouqian(int i, int j)
{
	if (i * 5 + j == 15 || i * 5 + j == 25 || i * 5 + j == 27 || i * 5 + j == 40 || i * 5 + j == 50 || i * 5 + j == 52)
		return 1;
	else
		return 0;
}
//(i��j)Ϊ������Ӫ�ҿ���������ƶ�������
//          1Ϊ�������㣬0����������

int Iszuohou(int i, int j)
{
	if (i * 5 + j == 7 || i * 5 + j == 9 || i * 5 + j == 19 || i * 5 + j == 32 || i * 5 + j == 34 || i * 5 + j == 44)
		return 1;
	else
		return 0;
}
//(i��j)Ϊ������Ӫ�ҿ������Һ��ƶ�������
//         1Ϊ�������㣬0����������
int Isyouhou(int i, int j)
{
	if (i * 5 + j == 5 || i * 5 + j == 7 || i * 5 + j == 15 || i * 5 + j == 30 || i * 5 + j == 32 || i * 5 + j == 40)
		return 1;
	else
		return 0;
}
/* ************************************************************************ */
/* �������ܣ�˫�����ֺ���ֳ�ʼ��											*/
/* �ӿڲ�����																*/
/*     char cMap[12][5] ���̾���											*/
/*     char *cOutMessage �����ַ�����										*/
/* ************************************************************************ */
void InitMap(char cMap[12][5], char *cOutMessage)
{
	int i, j, k;
	for (i = 0; i<6; i++)	//��ǶԷ�����
		for (j = 0; j<5; j++)
			if (IsMoveCamp(i, j))
				cMap[i][j] = '0';
			else
				cMap[i][j] = 'X';
	k = 6;
	for (i = 6; i<12; i++)	//��Ǽ�������
		for (j = 0; j<5; j++)
			if (IsMoveCamp(i, j))
				cMap[i][j] = '0';
			else
				cMap[i][j] = cOutMessage[k++];

}

//�����ҷ����ӻ�ʣ���ٸ�
//���� cMap ��ǰ��ͼ
//����ֵΪ�ҷ�ʣ������
int NumChess(char cMap[12][5])
{
	int n = 0; //�ҷ�������
	int i, j;

	for (i = 0; i < 12; i++)
		for (j = 0; j < 5; j++)
			if (cMap[i][j] >= 'a'&&cMap[i][j] <= 'l')
				n++;
	return n;
}

//����з����ӻ�ʣ���ٸ�
//���� cMap ��ǰ��ͼ
//����ֵΪ�з�ʣ������
int NumOppChess(char cMap[12][5])
{
	int n = 0; //�ҵ�������
	int i, j;

	for (i = 0; i < 12; i++)
		for (j = 0; j < 5; j++)
			if (cMap[i][j] >= 'A'&&cMap[i][j] <= 'X')
				n++;
	return n;
}

void souhui(int n, int i, int sfen, int dz[26][16])         //sfen ���յķ���   nΪ����λ��   iΪ���Ӵ�С
{
	int zong = 0;
	int n1;
	zong = dz[25][i];
	for (n1 = 0; n1<25; n1++)
	{
		if (n1 != n && sfen != 0)
		{
			dz[n1][i] = (int)(dz[n1][i] - (dz[n1][i] / (zong*1.0 - dz[n][i] + 1.0)*sfen));
		}
	}
}
int Sappersearching(int n, char cMap[12][5], int dz[26][16], int i1, int j1, int i2, int j2)//�ҹ���
{
	int imax, imin, jmax, jmin, x, y, flag = 0;
	int zong = 1;
	imax = max(i1, i2);
	imin = min(i1, i2);
	jmax = max(j1, j2);
	jmin = min(j1, j2);
	x = (imax + imin) / 2 - 1;
	y = (jmax + jmin) / 2;
	if ((IsRailway(i1, j1) && IsRailway(i2, j2)))//�ж���ʼλ���Ƿ�������
	{
		if (i1 != i2 && j1 != j2)//ʼĩ���ݾ���ͬ��Ϊ����
		{
			flag = 1;
		}
		else
		{
			if (i1 == i2)
			{
				if (!IsRailway(i1, y))
				{
					flag = 1;
				}
				else
				{
					for (int n = jmin + 1; n < jmax; n++)
					{
						if (cMap[i1][n] != '0')
						{
							flag = 1;
							break;
						}
					}
				}
			}
			if (j1 == j2)
			{
				if (!IsRailway(x, j1))
				{
					flag = 1;
				}
				else
				{
					for (int n = imin + 1; n < imax; n++)
					{
						if (cMap[n][j1] != '0')
						{
							flag = 1;
							break;
						}
					}
				}
			}
			else
			{
				if ((IsAfterHill(i1, j1) && IsBehindHill(i2, j2)) || (IsAfterHill(i2, j2) && IsBehindHill(i1, j1)))//�ж��Ƿ��ɽ��
				{
					flag = 1;
				}

			}
		}
	}
	if (flag == 1)
	{
		for (int i = 0; i < 12; i++)
		{
			if (dz[n][i] != 0 && i != 8 && dz[n][i] != 10000)
			{
				if (i == 0 || i == 1 || i == 11)
				{
					zong = 10000;
				}
				else
				{
					if (i > 5 && i < 10)
					{
						zong = 30000;
					}
					else
					{
						zong = 20000;
					}
				}
			}
			for (int n1 = 0; n1 < 25; n1++)
			{
				dz[n1][i] = (int)(dz[n1][i] + (dz[n1][i] / (zong*1.0 - dz[n][i] + 1))*dz[n][i]);
			}
			dz[n][i] = 0;
		}
		souhui(n, 8, 10000 - dz[n][8], dz);
		dz[n][8] = 10000;
	}
	return flag;
}
int dabenying(int x, int m, int i2, int j2, int dz[26][16])
{
	int sum = 0, value = 0, zong, flag = 0;
	if (x == 0)
	{
		if (i2 == 0 && j2 == 1)
		{
			for (int i = m; i < 12; i++)
			{
				sum = sum + dz[1][i];
				if (dz[1][i] != 0)
				{
					zong = dz[25][i];
					for (int n1 = 0; n1 < 25; n1++)
					{
						if (n1 != 1)
						{
							dz[n1][i] = (int)(dz[n1][i] + (dz[n1][i] / (zong*1.0 - dz[1][i] + 1)*dz[1][i]));//��������ʰ�Ȩ��������λ��
						}
					}
				}
				dz[1][i] = 0;
			}
			for (int i = 0; i < m; i++)
			{
				if (dz[1][i] != 0)
				{
					value = (int)(dz[1][i] / (10000 * 1.0 - sum - dz[1][i])*sum);  //�ֵõĸ��ʷ�
					zong = dz[25][i];
					for (int n1 = 0; n1 < 25; n1++)
					{
						if (n1 != 1)
						{
							dz[n1][i] = (int)(dz[n1][i] - (dz[n1][i] / (zong*1.0 - dz[1][i] + 1)*value));
						}
					}
					dz[1][i] = dz[1][i] + value;
				}
			}
			for (int i = m; i < 12; i++)
			{
				if (i == 11)
				{
					zong = dz[25][11];
					for (int n1 = 0; n1 < 25; n1++)
					{
						if (n1 != 3)
						{
							dz[n1][i] = (int)(dz[n1][11] - (dz[n1][11] / (zong*1.0 - dz[3][11] + 1)*(10000 - dz[3][11])));
						}
					}
					dz[3][11] = 10000;
					continue;
				}
				if (dz[3][i] != 0)
				{
					zong = dz[25][i];
					for (int n1 = 0; n1 < 25; n1++)
					{
						if (n1 != 3)
						{
							dz[n1][i] = (int)(dz[n1][i] + (dz[n1][i] / (zong*1.0 - dz[3][i] + 1)*dz[3][i]));//��������ʰ�Ȩ��������λ��
						}
					}
					dz[3][i] = 0;
				}
			}
			sum = 0;
			flag = 1;
		}
		if (i2 == 0 && j2 == 3)
		{
			for (int i = m; i < 12; i++)
			{
				sum = sum + dz[1][i];
				if (dz[3][i] != 0)
				{
					zong = dz[25][i];
					for (int n1 = 0; n1 < 25; n1++)
					{
						if (n1 != 3)
						{
							dz[n1][i] = (int)(dz[n1][i] + (dz[n1][i] / (zong*1.0 - dz[3][i] + 1)*dz[3][i]));//��������ʰ�Ȩ��������λ��
						}
					}
				}
				dz[3][i] = 0;
			}
			for (int i = 0; i < m; i++)
			{
				if (dz[3][i] != 0)
				{
					value = (int)(dz[3][i] / (10000 * 1.0 - sum - dz[3][i])*sum);  //�ֵõĸ��ʷ�
					zong = dz[25][i];
					for (int n1 = 0; n1 < 25; n1++)
					{
						if (n1 != 3)
						{
							dz[n1][i] = (int)(dz[n1][i] - (dz[n1][i] / (zong*1.0 - dz[3][i] + 1)*value));
						}
					}
					dz[3][i] = dz[3][i] + value;
				}
			}
			for (int i = m; i < 12; i++)
			{
				if (i == 11)
				{
					zong = dz[25][11];
					for (int n1 = 0; n1 < 25; n1++)
					{
						if (n1 != 1)
						{
							dz[n1][i] = (int)(dz[n1][11] - (dz[n1][11] / (zong*1.0 - dz[1][11] + 1)*(10000 - dz[1][11])));
						}
					}
					dz[1][11] = 10000;
					continue;
				}
				if (dz[1][i] != 0)
				{
					zong = dz[25][i];
					for (int n1 = 0; n1 < 25; n1++)
					{
						if (n1 != 1)
						{
							dz[n1][i] = (int)(dz[n1][i] + (dz[n1][i] / (zong*1.0 - dz[1][i] + 1)*dz[1][i]));//��������ʰ�Ȩ��������λ��
						}
					}
					dz[1][i] = 0;
				}
			}
			sum = 0;
			flag = 1;
		}
	}
	if (x == 1)
	{
		if (i2 == 0 && j2 == 1)
		{
			for (int i = 0; i < 12; i++)
			{
				if (i > m&&i <= 8)
				{
					continue;
				}
				sum = sum + dz[1][i];
				if (dz[1][i] != 0)
				{
					zong = dz[25][i];
					for (int n1 = 0; n1 < 25; n1++)
					{
						if (n1 != 1)
						{
							dz[n1][i] = (int)(dz[n1][i] + (dz[n1][i] / (zong*1.0 - dz[1][i] + 1)*dz[1][i]));//��������ʰ�Ȩ��������λ��
						}
					}
				}
				dz[1][i] = 0;
			}
			for (int i = m; i < 8; i++)
			{
				if (dz[1][i] != 0)
				{
					value = (int)(dz[1][i] / (10000 * 1.0 - sum - dz[1][i])*sum);  //�ֵõĸ��ʷ�
					zong = dz[25][i];
					for (int n1 = 0; n1 < 25; n1++)
					{
						if (n1 != 1)
						{
							dz[n1][i] = (int)(dz[n1][i] - (dz[n1][i] / (zong*1.0 - dz[1][i] + 1)*value));
						}
					}
					dz[1][i] = dz[1][i] + value;
				}
			}
			for (int i = m; i < 12; i++)
			{
				if (i == 11)
				{
					zong = dz[25][11];
					for (int n1 = 0; n1 < 25; n1++)
					{
						if (n1 != 3)
						{
							dz[n1][i] = (int)(dz[n1][11] - (dz[n1][11] / (zong*1.0 - dz[3][11] + 1)*(10000 - dz[3][11])));
						}
					}
					dz[3][11] = 10000;
					continue;
				}
				if (dz[3][i] != 0)
				{
					zong = dz[25][i];
					for (int n1 = 0; n1 < 25; n1++)
					{
						if (n1 != 3)
						{
							dz[n1][i] = (int)(dz[n1][i] + (dz[n1][i] / (zong*1.0 - dz[3][i] + 1)*dz[3][i]));//��������ʰ�Ȩ��������λ��
						}
					}
					dz[3][i] = 0;
				}
			}
			sum = 0;
			flag = 1;
		}
		if (i2 == 0 && j2 == 3)
		{
			for (int i = m; i < 12; i++)
			{
				sum = sum + dz[1][i];
				if (dz[3][i] != 0)
				{
					zong = dz[25][i];
					for (int n1 = 0; n1 < 25; n1++)
					{
						if (n1 != 3)
						{
							dz[n1][i] = (int)(dz[n1][i] + (dz[n1][i] / (zong*1.0 - dz[3][i] + 1)*dz[3][i]));//��������ʰ�Ȩ��������λ��
						}
					}
				}
				dz[3][i] = 0;
			}
			for (int i = 0; i < m; i++)
			{
				if (dz[3][i] != 0)
				{
					value = (int)(dz[3][i] / (10000 * 1.0 - sum - dz[3][i])*sum);  //�ֵõĸ��ʷ�
					zong = dz[25][i];
					for (int n1 = 0; n1 < 25; n1++)
					{
						if (n1 != 3)
						{
							dz[n1][i] = (int)(dz[n1][i] - (dz[n1][i] / (zong*1.0 - dz[3][i] + 1)*value));
						}
					}
					dz[3][i] = dz[3][i] + value;
				}
			}
			for (int i = m; i < 12; i++)
			{
				if (i == 11)
				{
					zong = dz[25][11];
					for (int n1 = 0; n1 < 25; n1++)
					{
						if (n1 != 1)
						{
							dz[n1][i] = (int)(dz[n1][11] - (dz[n1][11] / (zong*1.0 - dz[1][11] + 1)*(10000 - dz[1][11])));
						}
					}
					dz[1][11] = 10000;
					continue;
				}
				if (dz[1][i] != 0)
				{
					zong = dz[25][i];
					for (int n1 = 0; n1 < 25; n1++)
					{
						if (n1 != 1)
						{
							dz[n1][i] = (int)(dz[n1][i] + (dz[n1][i] / (zong*1.0 - dz[1][i] + 1)*dz[1][i]));//��������ʰ�Ȩ��������λ��
						}
					}
					dz[1][i] = 0;
				}
			}
			sum = 0;
			flag = 1;
		}
	}
	else
	{
		if (i2 == 0 && j2 == 1)
		{
			for (int i = 0; i < 12; i++)
			{
				if (i == m)
				{
					continue;
				}
				if (dz[1][i] != 0)
				{
					zong = dz[25][i];
					for (int n1 = 0; n1 < 25; n1++)
					{
						if (n1 != 1)
						{
							dz[n1][i] = (int)(dz[n1][i] + (dz[n1][i] / (zong*1.0 - dz[1][i] + 1)*dz[1][i]));//��������ʰ�Ȩ��������λ��
						}
					}
				}
				dz[1][i] = 0;
			}
			for (int n1 = 0; n1 < 25; n1++)
			{
				if (n1 != 1)
				{
					dz[n1][m] = (int)(dz[n1][m] - (dz[n1][m] / (zong*1.0 - dz[1][m] + 1)*(10000 - dz[1][m])));
				}
			}
			dz[1][m] = 10000;
		}
		if (i2 == 0 && j2 == 3)
		{
			for (int i = 0; i < 12; i++)
			{
				if (i == m)
				{
					continue;
				}
				if (dz[3][i] != 0)
				{
					zong = dz[25][i];
					for (int n1 = 0; n1 < 25; n1++)
					{
						if (n1 != 3)
						{
							dz[n1][i] = (int)(dz[n1][i] + (dz[n1][i] / (zong*1.0 - dz[3][i] + 1)*dz[3][i]));//��������ʰ�Ȩ��������λ��
						}
					}
				}
				dz[3][i] = 0;
			}
			for (int n1 = 0; n1 < 25; n1++)
			{
				if (n1 != 3)
				{
					dz[n1][m] = (int)(dz[n1][m] - (dz[n1][m] / (zong*1.0 - dz[3][m] + 1)*(10000 - dz[3][m])));
				}
			}
			dz[3][m] = 10000;
		}
		flag = 1;
	}
	return flag;
}
//ˢ�²²���ʱ�   //�Է����ӱ������Ե�
void shuaxinG0(int m, char cMap[12][5], int dz[26][16], int i1, int j1, int i2, int j2)
{
	int flag = 0;
	int zong = 1, value, sum1 = 1, sum2 = 1;
	for (int n = 0; n < 25; n++)
	{
		if (dz[n][12] == i1 && dz[n][13] == j1)
		{
			dz[n][12] = 14;
			flag = Sappersearching(n, cMap, dz, i1, j1, i2, j2);
			if (flag == 1)
			{
				return;
			}
			dz[n][12] = 14;
			if (m < 8 && m >= 0)//��������Ϊ˾�����ų�
			{
				for (int i = 0; i <= m; i++)
				{
					sum1 = sum1 + dz[n][i];   //�����������ʻ���
					if (sum1 >= 10000)
					{
						sum1 = 10000 - 1500;
					}
					if (dz[n][i] != 0 && dz[n][i] != 10000)//�������ܵ����Ӹ�������
					{
						zong = dz[25][i];
						for (int n1 = 0; n1 < 25; n1++)
						{
							if (n1 != n && dz[n1][i] < 9000)
							{
								dz[n1][i] = (int)(dz[n1][i] + (dz[n1][i] / (zong*1.0 - dz[n][i] + 1)*dz[n][i]));//��������ʰ�Ȩ��������λ��
							}
						}
						dz[n][i] = 0;
					}
				}
				for (int i = m + 1; i <= 8; i++)
				{
					value = (int)(dz[n][i] / (10000 * 1.0 - sum1 - dz[n][i] + 1)*sum1);  //�ֵõĸ��ʷ�
					dz[n][i] = dz[n][i] + value;    //���Ű�Ȩ�ӷ�
					if (dz[n][i] != 0 && dz[n][i] != 10000)
					{
						zong = dz[25][i];
						for (int n1 = 0; n1 < 25; n1++)
						{
							if (n1 != n && dz[n1][i] < 9000)
							{
								dz[n1][i] = (int)(dz[n1][i] - (dz[n1][i] / (zong*1.0 - dz[n][i] + 1)*value));//���Ű�Ȩ����
							}
						}
					}
				}
				value = 0;
			}
			if (m == 9)//��������Ϊ����
			{
				for (int i = 8; i < 12; i++)
				{
					sum2 = sum2 + dz[n][i];
					if (sum2 >= 10000)
					{
						sum2 = 10000 - 1500;
					}
					if (dz[n][i] != 0 && dz[n][i] != 10000)
					{
						zong = dz[25][i];
						for (int n1 = 0; n1 < 25; n1++)
						{
							if (n1 != n && dz[n1][i] < 9000)
							{
								dz[n1][i] = (int)(dz[n1][i] + (dz[n1][i] / (zong*1.0 - dz[n][i] + 1)*dz[n][i]));//��������ʰ�Ȩ��������λ��
							}
						}
						dz[n][i] = 0;
					}
				}
				for (int i = 0; i < 8; i++)
				{
					value = (int)(dz[n][i] / (10000 * 1.0 - sum2 - dz[n][i])*sum2);  //�ֵõĸ��ʷ�
					dz[n][i] = dz[n][i] + value;           //���Ű�Ȩ�ӷ�
					if (dz[n][i] != 0 && dz[n][i] != 10000)
					{
						if (dz[n][i] != 0 && dz[n][i]<9000)
						{
							zong = dz[25][i];
							for (int n1 = 0; n1 < 25; n1++)
							{
								if (n1 != n)
								{
									dz[n1][i] = (int)(dz[n1][i] - (dz[n1][i] / (zong*1.0 - dz[n][i] + 1)*value));//���Ű�Ȩ����
								}
							}
						}
					}
				}
				value = 0;
			}
		}
	}
}
//�Է��Ե���������
void shuaxinG1(int m, char cMap[12][5], int dz[26][16], int i1, int j1, int i2, int j2)
{
	int flag = 0;
	int zong = 1, value, sum1 = 1, sum2 = 1;
	if (cMap[i2][j2] <= 'd')
	{
		for (int n = 0; n < 25; n++)
			if (dz[n][12] == i1 && dz[n][13] == j1)
			{
				track[tra] = n;
				tra++;
			}
	}
	for (int xa1 = 0; xa1 < 25; xa1++)
	{
		if (i1 == dz[xa1][12] && j1 == dz[xa1][13])
			bekilled[xa1]++;
	}
	for (int n = 0; n < 25; n++)
	{
		if (dz[n][12] == i1 && dz[n][13] == j1)
		{
			dz[n][12] = i2;
			dz[n][13] = j2;
			flag = Sappersearching(n, cMap, dz, i1, j1, i2, j2);
			if (flag == 1)
			{
				return;
			}
			if (m < 8 && m >= 0)//��������Ϊ˾�����ų�
			{
				for (int i = m; i <= 11; i++)
				{
					sum1 = sum1 + dz[n][i];
					if (sum1 >= 10000)
					{
						sum1 = 10000 - 1500;
					}
					if (dz[n][i] != 0 && dz[n][i] <9000)//�������ܵ����Ӹ�������
					{
						zong = dz[25][i];
						for (int n1 = 0; n1 < 25; n1++)
						{
							if (n1 != n)
							{
								dz[n1][i] = (int)(dz[n1][i] + (dz[n1][i] / (zong*1.0 - dz[n][i] + 1)*dz[n][i]));//��������ʰ�Ȩ��������λ��
							}
						}
						dz[n][i] = 0;
					}
				}
				FILE *fp = fopen("2", "a");
				fprintf(fp, "\n��ʱ��������ܷ�%d", sum1);
				//fclose(fp);
				for (int i = 0; i < m; i++)
				{
					value = (int)(dz[n][i] / (10000 * 1.0 - sum1)*sum1); //�ֵõĸ��ʷ�
					fprintf(fp, "value�֣�%d  ", value);
					if (dz[n][i] != 0 && dz[n][i] < 9000)
					{
						zong = dz[25][i];
						for (int n1 = 0; n1 < 25; n1++)
						{
							if (n1 != n)
							{
								dz[n1][i] = (int)(dz[n1][i] - (dz[n1][i] / (zong*1.0 - dz[n][i] + 1)*value));//���Ű�Ȩ����
							}
						}
					}
					dz[n][i] = dz[n][i] + value;
				}
				fclose(fp);
				value = 0;
			}
			if (m == 9)
			{
				for (int i = 0; i < 12; i++)
				{
					if (i == 8)
					{
						continue;
					}
					if (dz[n][i] != 0)
					{
						zong = dz[25][i];
						for (int n1 = 0; n1 < 25; n1++)
						{
							dz[n1][i] = (int)(dz[n1][i] + (dz[n1][i] / (zong*1.0 - dz[n][i] + 1)*dz[n][i]));//��������ʰ�Ȩ��������λ��
						}
						dz[n][i] = 0;
					}
				}
				value = 10000 - dz[n][8];
				if (dz[n][8] != 0 && dz[n][8] != 10000)
				{
					zong = dz[25][8];
					for (int n1 = 0; n1 < 25; n1++)
					{
						if (n1 != n && dz[n1][8] < 9000)
						{
							dz[n1][8] = (int)(dz[n1][8] - (dz[n1][8] / (zong*1.0 - dz[n][8] + 1)*value));//���Ű�Ȩ����
						}
					}
					dz[n][8] = 10000;
					cMap[i2][j2] = 'I';
				}
				value = 0;
			}
		}
	}
}
//�з������뼺�����Ӷ���
void shuaxinG2(int m, char cMap[12][5], int dz[26][16], int i1, int j1, int i2, int j2)
{
	int flag = 0;
	int zong = 0, sfen = 0, value;
	for (int n = 0; n < 25; n++)
	{
		if (dz[n][12] == i1 && dz[n][13] == j1)
		{
			dz[n][12] = 14;
			flag = Sappersearching(n, cMap, dz, i1, j1, i2, j2);
			if (flag == 1)
			{
				return;
			}
			if (m == 9)              //��������Ϊ����
			{
				for (int i = 0; i < 12; i++)
				{
					if (i == 10)
					{
						continue;
					}
					zong = dz[25][i];
					if (dz[n][i] != 0 && dz[n][i] <9000)
					{
						for (int n1 = 0; n1 < 25; n1++)
						{
							if (n1 != n)
							{
								dz[n1][i] = (int)(dz[n1][i] + (dz[n1][i] / (zong*1.0 - dz[n][i] + 1)*dz[n][i]));//��������ʰ�Ȩ��������λ��
							}
						}
						dz[n][i] = 0;
					}
				}
				value = 10000 - dz[n][10];
				dz[25][10] -= 10000;
				for (int n1 = 0; n1 < 25; n1++)
				{
					zong = dz[25][9];
					if (dz[n][10] != 0 && dz[n][10] < 9000)
					{
						if (n1 != n)
						{
							dz[n1][10] = (int)(dz[n1][10] - (dz[n1][10] / (zong*1.0 - dz[n][10] + 1)*value));
						}
					}
				}
				dz[n][10] = 10000;
			}
			value = 0;
			if (m >= 0 && m <= 8)
			{
				if (m == 0)
				{
					if (jq == 1)     //�Է�Ϊ˾��
					{
						for (int i = 1; i < 12; i++)
						{
							zong = dz[25][i];
							if (dz[n][i] != 0 && dz[n][i] != 10000)
							{
								for (int n1 = 0; n1 < 25; n1++)
								{
									if (n1 != n)
									{
										dz[n1][i] = (int)(dz[n1][i] + (dz[n1][i] / (zong*1.0 - dz[n][i] + 1)*dz[n][i]));
									}
								}
								dz[n][i] = 0;
							}
						}
						dz[n][0] = 10000;
						for (int n1 = 0; n1 < 25; n1++)
						{
							for (int i = 1; i < 12; i++)
							{
								if (dz[n1][i] != 0 && dz[n1][i] < 9000)
								{
									if (n1 != n)
									{
										dz[n1][i] = (int)(dz[n1][i] + (dz[n1][i] / (10000 * 1.0 - dz[n1][0] + 1)*dz[n1][0]));
										dz[n1][0] = 0;
									}
								}
							}
						}
					}
					else         //�Է�Ϊը��
					{
						for (int i = 0; i < 12; i++)
						{
							if (i == 10)
							{
								continue;
							}
							zong = dz[25][i];
							if (dz[n][i] != 0 && dz[n][i] < 9000)
							{
								for (int n1 = 0; n1 < 25; n1++)
								{
									if (n1 != n)
									{
										dz[n1][i] = (int)(dz[n1][i] + (dz[n1][i] / (zong*1.0 - dz[n][i] + 1)*dz[n][i]));
									}
								}
								dz[n][i] = 0;
							}
						}
						value = 10000 - dz[n][10];
						dz[25][10] -= 10000;
						for (int n1 = 0; n1 < 25; n1++)
						{
							zong = dz[25][10];
							if (dz[n][10] != 0 && dz[n][10] <9000)
							{
								if (n1 != n)
								{
									dz[n1][10] = (int)(dz[n1][10] - (dz[n1][10] / (zong*1.0 - dz[n][10] + 1)*value));
								}
							}
						}
						dz[n][10] = 10000;
					}
					value = 0;
				}
				else
				{
					for (int i = 0; i < 12; i++)
					{
						if (i == 10 || i == m)
						{
							continue;
						}
						if (dz[n][i] != 0 && dz[n][i] < 9000)
						{
							zong = dz[25][i];
							for (int n1 = 0; n1 < 25; n1++)
							{
								if (n1 != n)
								{
									dz[n1][i] = (int)(dz[n1][i] + (dz[n1][i] / (zong*1.0 - dz[n][i] + 1)*dz[n][i]));
								}
							}
							dz[n][i] = 0;
						}
					}
					value = 5000 - dz[n][m];
					zong = dz[25][m];
					for (int n1 = 0; n1 < 25; n1++)
					{
						zong = dz[25][m];
						if (dz[n1][m] != 0 && dz[n1][m] != 10000)
						{
							dz[n1][m] = (int)(dz[n1][m] - (dz[n1][m] / (zong*1.0 - dz[n][m] + 1)*value));
						}
					}
					dz[n][m] = 5000;
					value = 5000 - dz[n][10];
					zong = dz[25][10];
					for (int n1 = 0; n1 < 25; n1++)
					{
						zong = dz[25][10];
						if (dz[n1][10] != 0 && dz[n1][10] != 10000)
						{
							dz[n1][10] = (int)(dz[n1][10] - (dz[n1][10] / (zong*1.0 - dz[n][10] + 1)*value));
						}
					}
					dz[n][10] = 5000;
				}
			}
			value = 0;
		}
	}
}
//�з����ƶ�����
void shuaxinG3(int i1, int j1, int i2, int j2, int dz[26][16], char cMap[12][5]) //���ƶ�����
{
	int flag = 0, value = 0;
	int zong = 1;
	for (int n = 0; n < 25; n++)
	{
		if (dz[n][12] == i1 && dz[n][13] == j1)
		{
			dz[n][12] = i2;
			dz[n][13] = j2;
			flag = Sappersearching(n, cMap, dz, i1, j1, i2, j2);
			if (flag == 1)
			{
				return;
			}
			for (int i = 0; i < 12; i++)
			{
				if (i == 9)
				{
					continue;
				}
				if (dz[n][i] > 0 && dz[n][i] < 9000)
				{
					value = (int)(dz[n][i] / (12000 * 1.0 - dz[n][9])*dz[n][9]);
					dz[n][i] = dz[n][i] + value;
					for (int n1 = 0; n1 < 25; n1++)
					{
						zong = dz[25][i];
						if (dz[n1][i] > 0 && dz[n1][i] < 9000 && n1 != n)
						{
							dz[n1][i] = (int)(dz[n1][i] - dz[n1][i] / (zong*1.0 - dz[n][i])*value);
						}
					}
				}
			}
			for (int n1 = 0; n1 < 25; n1++)
			{
				if (dz[n1][9] > 0 && dz[n1][9] < 9000 && n1 != n)
				{
					dz[n1][9] = (int)(dz[n1][9] + (dz[n1][9] / (30000 * 1.0 - dz[n][9])*dz[n][9]));
				}
			}
			dz[n][9] = 0;
			/*for (n = 0; n<25; n++)
			{
			if (dz[n][12] == i1 && dz[n][13] == j1)
			{
			dz[n][12] = i2;
			dz[n][13] = j2;
			if (IsMoveCamp(i2, j2))  //���Ϊ��Ӫ����Ӫ����+1
			{
			dz[n][15]++;
			}
			if (z1 == 1 && y21 == 2 && x21 == 1)   //?�ж�ը���е����
			dz[n][10] = 4000;
			if (z2 == 1 && y21 == 2 && x21 == 3)
			dz[n][10] = 4000;
			if (z3 == 1 && y21 == 4 && x21 == 1)
			dz[n][10] = 4000;
			if (z4 == 1 && y21 == 4 && x21 == 3)
			dz[n][10] = 4000;
			break;
			}
			}*/
		}
	}
}
//  //�������ӱ��Է��Ե�
void shuaxinR0(int m, char cMap[12][5], int dz[26][16], int i1, int j1, int i2, int j2)
{
	int flag = 0, order = 1, n;
	int zong = 1, value, sum1 = 1, sum2 = 1;
	flag = dabenying(0, m, i2, j2, dz);
	if (cMap[i1][j1] <= 'd')
	{
		for (int n = 0; n < 25; n++)
			if (dz[n][12] == i2 && dz[n][13] == j2)
			{
				track[tra] = n;
				tra++;
			}
	}
	for (int xa1 = 0; xa1 < 25; xa1++)
	{
		if (i2 == dz[xa1][12] && j2 == dz[xa1][13])
			bekilled[xa1]++;
	}
	for (n = 0; n < 25; n++)
	{
		if (dz[n][12] == i2 && dz[n][13] == j2)
		{
			if (m == 0)
			{
				for (int i = 0; i < 12; i++)
				{
					if (i == 9)
					{
						continue;
					}
					if (dz[n][i] != 0 && dz[n][i] < 9000)//�������ܵ����Ӹ�������
					{
						zong = dz[25][i];
						for (int n1 = 0; n1 < 25; n1++)
						{
							if (n1 != n)
							{
								dz[n1][i] = (int)(dz[n1][i] + (dz[n1][i] / (zong*1.0 - dz[n][i] + 1)*dz[n][i]));//��������ʰ�Ȩ��������λ��
							}
						}
						dz[n][i] = 0;
					}
				}
				value = 10000 - dz[n][9];
				dz[25][9] -= 10000;
				for (int n1 = 0; n1 < 25; n1++)
				{
					if (n1 != n && dz[n1][9] < 9000)
					{
						dz[n1][9] = (int)(dz[n1][9] - (dz[n1][9] / (dz[25][9] * 1.0 + 1)*value));//��������ʰ�Ȩ��������λ��
					}
				}
				dz[n][9] = 10000;
				cMap[i2][j2] = 'J';
				value = 0;
			}
			if (m>0 && m<8)//��������Ϊ�������ų�
			{
				for (int i = m; i < 12; i++)
				{
					if (i == 9)
					{
						continue;
					}
					sum1 = sum1 + dz[n][i];
					if (sum1 >= 10000)
					{
						sum1 = 10000 - 3000;
					}
					if (dz[n][i] != 0 && dz[n][i] < 9000)//�������ܵ����Ӹ�������
					{
						zong = dz[25][i];
						for (int n1 = 0; n1 < 25; n1++)
						{
							if (n1 != n)
							{
								dz[n1][i] = (int)(dz[n1][i] + (dz[n1][i] / (zong*1.0 - dz[n][i] + 1)*dz[n][i]));//��������ʰ�Ȩ��������λ��
							}
						}
						dz[n][i] = 0;
					}
				}
				for (int i = 0; i <12; i++)
				{
					if ((i >= m && i < 9) || (i >= 10 && i < 12))
					{
						continue;
					}
					value = (int)(dz[n][i] / (12000 * 1.0 - sum1)*sum1);  //�ֵõĸ��ʷ�
					FILE *fp = fopen("2", "a");
					fprintf(fp, "\n�ܷ֣�%d", sum1);
					fprintf(fp, "\n�˴�value������%d", value);
					fclose(fp);
					if (dz[n][i] != 0 && dz[n][i] < 9000)
					{
						zong = dz[25][i];
						for (int n1 = 0; n1 < 25; n1++)
						{
							if (n1 != n)
							{
								dz[n1][i] = (int)(dz[n1][i] - (dz[n1][i] / (zong*1.0 - dz[n][i] + 1)*value));//���Ű�Ȩ����
							}
						}
					}
					dz[n][i] = dz[n][i] + value;
				}
				value = 0;
			}
			/*for (int i = m; i < 10; i++)
			{
			if (dz[n][i] != 0 && dz[n][i] < 9000)
			{
			value = (int)(dz[n][i] / (10000*1.0 - dz[n][10] + 1.0)*dz[n][10]);
			zong = dz[25][i];
			for (int n1 = 0; n1 < 25; n1++)
			{
			if (n1 != n )
			{
			dz[n1][i] = (int)(dz[n1][i] - (dz[n1][i] / (zong*1.0 - dz[n][i] + 1)*value));//���Ű�Ȩ����
			dz[n1][10] = (int)(dz[n1][10] + (dz[n1][i] / (dz[25][10] * 1.0 - dz[n][10] + 1)*dz[n][10]));
			}
			}
			dz[n][i] = dz[n][i] + value;
			}
			}
			dz[n][10] = 0;
			value = 0;*/
		}
	}
}
//�����Ե��Է�����
//�����Ե��Է�����
void shuaxinR1(int m, char cMap[12][5], int dz[26][16], int i1, int j1, int i2, int j2)  //�����Ե��Է�����
{
	int flag = 0, zong = 1, value, sum = 0, n;
	flag = dabenying(1, m, i2, j2, dz);
	for (n = 0; n < 25; n++)
	{
		if (dz[n][12] == i2 && dz[n][13] == j2)
		{
			dz[n][12] = 14;
			if (m < 8 && m >= 0)//��������Ϊ˾�����ų�
			{
				for (int i = 0; i <= m; i++)
				{
					sum = sum + dz[n][i];   //�����������ʻ���
					if (sum >= 10000)
					{
						sum = 10000 - 1500;
					}
					if (dz[n][i] != 0 && dz[n][i] != 10000)//�������ܵ����Ӹ�������
					{
						zong = dz[25][i];
						if (dz[n][i] != 0 && dz[n][i] != 10000)
						{
							for (int n1 = 0; n1 < 25; n1++)
							{
								if (n1 != n && dz[n1][i] < 9000)
								{
									dz[n1][i] = (int)(dz[n1][i] + (dz[n1][i] / (zong*1.0 - dz[n][i] + 1)*dz[n][i]));//��������ʰ�Ȩ��������λ��
								}
							}
							dz[n][i] = 0;                                         //����
						}
					}
				}
				for (int i = m + 1; i <= 8; i++)
				{
					value = (int)(dz[n][i] / (10000 * 1.0 - sum)*sum);  //�ֵõĸ��ʷ�
					if (dz[n][i] != 0 && dz[n][i] != 10000)
					{
						zong = dz[25][i];
						if (dz[n][i] != 0 && dz[n][i] < 9000)
						{
							for (int n1 = 0; n1 < 25; n1++)
							{
								if (n1 != n)
								{
									dz[n1][i] = (int)(dz[n1][i] - (dz[n1][i] / (zong*1.0 - dz[n][i] + 1)*value));//���Ű�Ȩ����
								}
							}
						}
					}
					dz[n][i] = dz[n][i] + value;           //���Ű�Ȩ�ӷ�
				}
				value = 0;
			}
			if (m == 8)//��������Ϊ����
			{
				for (int i = 0, sums = 1; i < 12; i++)
				{
					sums = sums + dz[n][i];
					if (sums >= 10000)
					{
						sums = 10000 - 1500;
					}
					zong = dz[25][i];
					if (dz[n][i] != 0 && dz[n][i] < 9000)
					{
						for (int n1 = 0; n1 < 25; n1++)
						{
							if (n1 != n)
							{
								dz[n1][i] = (int)(dz[n1][i] + (dz[n1][i] / (zong*1.0 - dz[n][i] + 1)*dz[n][i]));//��������ʰ�Ȩ��������λ��
							}
						}
						dz[n][i] = 0;                                                            //����
					}
				}
				for (int i = 0; i < 8; i++)
				{
					value = (int)(dz[n][i] / (10000 * 1.0 - sum - dz[n][i])*sum);  //�ֵõĸ��ʷ�
					if (dz[n][i] != 0 && dz[n][i] != 10000)
					{
						zong = dz[25][i];
						for (int n1 = 0; n1 < 25; n1++)
						{
							if (n1 != n && dz[n1][i] < 9000)
							{
								dz[n1][i] = (int)(dz[n1][i] - (dz[n1][i] / (zong*1.0 - dz[n][i] + 1)*value));//���Ű�Ȩ����
							}
						}
					}
					dz[n][i] = dz[n][i] + value;           //���Ű�Ȩ�ӷ�
				}
				value = 0;
			}
		}
	}
}
//�����ƶ���˫�����Ӷ���
void shuaxinR2(int m, char cMap[12][5], int dz[26][16], int i1, int j1, int i2, int j2)            //�����������
{
	int flag = 0, zong = 1, value = 0, n;
	for (n = 0; n < 25; n++)
	{
		if (dz[n][12] == i2 && dz[n][13] == j2)
		{
			dz[n][12] = 14;
			if (i2 == 0 && j2 == 1)                                        //�������ӽ��з���Ӫ
			{
				for (int i = 0; i < 12; i++)
				{
					if (i < m)
					{
						if (dz[n][i] != 0 && dz[n][i] < 9000)
						{
							value = value + dz[1][i];
							zong = dz[25][i];
							for (int n1 = 0; n1 < 25; n1++)
							{
								if (n1 != n)
								{
									dz[n1][i] = (int)(dz[n1][i] + (dz[n1][i] / (zong*1.0 - dz[n][i] + 1)*dz[n][i]));
								}
							}
							dz[1][i] = 0;
							value = 0;
						}
					}
					else
					{
						if (dz[n][i] != 0)
						{
							zong = dz[25][i];
							if (dz[1][i] != 0)
							{
								for (int n1 = 0; n1 < 25; n1++)
								{
									dz[n1][i] = (int)(dz[n1][i] - (dz[1][i] / (zong*1.0 - dz[1][11] + 1)*dz[1][11]));
								}
							}
							dz[1][i] = (int)(dz[1][i] + (dz[1][i] / (zong*1.0 - dz[1][11] + 1)*dz[1][11]));
						}
					}
				}
				dz[1][11] = 0;
				for (int i = m; i < 12; i++)
				{
					value = 10000 - dz[3][11];
					if (dz[3][i] != 0)
					{
						for (int n1 = 0; n1 < 25; n1++)
						{
							dz[n1][i] = (int)(dz[n1][i] - (dz[3][i] / (1000 - dz[3][11])*value));
						}
						dz[3][i] = 0;
					}
				}
				dz[3][11] = 10000;
				value = 0;
			}
			if (i2 == 0 && j2 == 3)                                        //�������ӽ��з���Ӫ
			{
				for (int i = 0; i < 12; i++)
				{
					if (i < m)
					{
						value = value + dz[1][i];
						zong = dz[25][i];
						for (int n1 = 0; n1 < 25; n1++)
						{
							if (n1 != n && dz[n1][i] < 9000)
							{
								dz[n1][i] = (int)(dz[n1][i] + (dz[n1][i] / (zong*1.0 - dz[n][i] + 1)*dz[n][i]));
							}
						}
						dz[1][i] = 0;
						value = 0;
					}
					else
					{
						zong = dz[25][i];
						if (dz[3][i] != 0)
						{
							for (int n1 = 0; n1 < 25; n1++)
							{
								dz[n1][i] = (int)(dz[n1][i] - (dz[3][i] / (zong*1.0 - dz[3][11] + 1)*dz[3][11]));
							}
						}
						dz[3][i] = (int)(dz[3][i] + (dz[3][i] / (zong*1.0 - dz[3][11] + 1)*dz[3][11]));
					}
				}
				dz[3][11] = 0;
				for (int i = 0; i < 12; i++)
				{
					value = 10000 - dz[1][11];
					if (dz[1][i] != 0)
					{
						for (int n1 = 0; n1 < 25; n1++)
						{
							dz[n1][i] = (int)(dz[n1][i] - (dz[1][i] / (1000 - dz[1][11])*value));
						}
						dz[1][i] = 0;
					}
				}
				dz[1][11] = 10000;
				value = 0;
			}
			if (m >= 0 && m <= 8)
			{
				if (m == 0)
				{
					if (jq == 1)     //�Է�Ϊ˾��
					{
						for (int i = 1; i < 12; i++)
						{
							if (dz[n][i] != 0 || dz[n][i] > 9000)
							{
								zong = dz[25][i];
								for (int n1 = 0; n1 < 25; n1++)
								{
									if (n1 != n)
									{
										dz[n1][i] = (int)(dz[n1][i] + (dz[n1][i] / (zong*1.0 - dz[n][i] + 1)*dz[n][i]));
									}
								}
								dz[n][i] = 0;
							}
						}
						dz[n][0] = 10000;
						for (int n1 = 0; n1 < 25; n1++)
						{
							for (int i = 1; i < 12; i++)
							{
								if (dz[n1][i] != 0 && dz[n1][i] < 9000)
								{
									if (n1 != n)
									{
										dz[n1][i] = (int)(dz[n1][i] + (dz[n1][i] / (10000 * 1.0 - dz[n1][0] + 1)*dz[n1][0]));
										dz[n1][0] = 0;
									}
								}
							}
						}
					}
					else
					{
						for (int i = 1; i < 12; i++)
						{
							if (i == 10)
							{
								continue;
							}
							if (dz[n][i] != 0 && dz[n][i] < 9000)
							{
								zong = dz[25][i];
								for (int n1 = 0; n1 < 25; n1++)
								{
									if (n1 != n)
									{
										dz[n1][i] = (int)(dz[n1][i] + (dz[n1][i] / (zong*1.0 - dz[n][i] + 1)*dz[n][i]));
									}
								}
								dz[n][i] = 0;
							}
						}
						value = 10000 - dz[n][10];
						dz[25][10] -= 10000;
						for (int n1 = 0; n1 < 25; n1++)
						{
							zong = dz[25][10];
							if (n1 != n)
							{
								dz[n1][10] = (int)(dz[n1][10] - (dz[n1][10] / (zong*1.0 + 1)*value));
							}
						}
						dz[n][10] = 10000;
					}
					value = 0;
				}
				else
				{
					for (int i = 0; i < 12; i++)
					{
						if (i == m || i == 10)
						{
							continue;
						}
						if (dz[n][i] != 0 && dz[n][i] < 9000)
						{
							zong = dz[25][i];
							for (int n1 = 0; n1 < 25; n1++)
							{
								if (n1 != n)
								{
									dz[n1][i] = (int)(dz[n1][i] + (dz[n1][i] / (zong*1.0 - dz[n][i] + 1)*dz[n][i]));
								}
							}
							dz[n][i] = 0;
						}
					}
					value = 5000 - dz[n][m];
					for (int n1 = 0; n1 < 25; n1++)
					{
						if (n1 != n)
						{
							dz[n1][m] = (int)(dz[n1][m] - (dz[n1][m] / (dz[25][m] * 1.0 - dz[n][m])*value));
						}
					}
					dz[n][m] = 5000;
					value = 5000 - dz[n][10];
					for (int n1 = 0; n1 < 25; n1++)
					{
						if (n1 != n)
						{
							dz[n1][10] = (int)(dz[n1][10] - (dz[n1][10] / (dz[25][10] * 1.0 - dz[n][10])*value));
						}
					}
					dz[n][10] = 5000;
				}
				value = 0;
			}
		}
	}
}

/* ************************************************************************ */
/* �������ܣ����ݲ��з���ˢ������											*/
/* �ӿڲ�����																*/
/*     char cMap[12][5] ���̾���											*/
/*     char *cInMessage ���Բ��е�GO YXYX R YX����							*/
/*     char *cOutMessage �������е�BESTMOVE YXYX����						*/
/* ************************************************************************ */
void FreshMap(char cMap[12][5], char *cInMessage, char *cOutMessage, int dz[26][16])
{
	int x1, y1;				//���					//x1,y1,x2,y2,result��char�͸�Ϊint�ͣ�ûʲôӰ��
	int x2, y2;				//���
	int result = -1, k, x = 0, m = 0;			//���ӽ��
	int  zong = 1, flag = 0, zs = 0, value = 0;
	//�жϺ����Ƿ��һ���ط��и���
	for (int n = 0; n<25; n++)
	{
		k = 0;
		for (int i = 0; i<12; i++)
		{

			if (dz[n][i]<100)
			{
				if (dz[n][i]<0)
				{
					dz[n][i] = 0;
				}
				k++;
			}
			if (k >= 11)
			{
				for (int i1 = 0; i1 < 12; i1++)
				{
					if (dz[n][i1] > 100 && dz[n][i1] < 11000)
					{
						zong = dz[25][i];
						for (int n1 = 0; n1 < 25; n1++)
						{
							if (n1 != n)
							{
								dz[n1][i1] = (int)(dz[n1][i1] - (dz[n1][i1] / (zong*1.0 - dz[n][i1] + 1)*(10000 - dz[n][i1])));
							}
						}
						dz[n][i1] = 10000;
					}
					else
					{
						zong = dz[25][i];
						for (int n1 = 0; n1 < 25; n1++)
						{
							if (n1 != n)
							{
								dz[n1][i1] = (int)(dz[n1][i1] - (dz[n1][i1] / (zong*1.0 - dz[n][i1] + 1)*dz[n][i1]));
							}
						}
						dz[n][i1] = 0;
					}
				}
			}
		}
	}
	//�ж�����
	for (int i = 0; i<12; i++)
	{
		k = 0;
		for (int n = 0; n < 25; n++)
		{
			if (dz[n][i] >8000)
			{
				k++;
			}
			if (dz[n][i] < 0)
			{
				dz[n][i] = 0;
			}
		}
		if (k <= 3)
		{
			if (i == 0 || i == 1 || i == 11)
			{
				dz[25][i] = 10000;
				zs = 1;
				if (k == zs)
				{
					flag = 1;
				}
			}
			if (i > 5 && i < 10)
			{
				dz[25][i] = 30000;
				zs = 3;
				if (k == zs)
				{
					flag = 1;
				}
			}
			if ((i >= 2 && i <= 5) || i == 10)
			{
				dz[25][i] = 20000;
				zs = 2;
				if (k == zs)
				{
					flag = 1;
				}
			}
			if (flag == 1)
			{
				for (int n = 0; n < 25; n++)
				{
					if (dz[n][i] > 8000)
					{
						for (int i1 = 0; i1 < 12; i1++)
						{
							if (dz[n][i1] != 0)
							{
								zong = dz[25][i1];
								if (i1 != i)
								{
									value = (int)(dz[n][i1] / (zong*1.0 - dz[n][i] + 1)*(10000 - dz[n][i]));
									dz[n][i1] = 0;
								}
								for (int n1 = 0; n1 < 25; n1++)
								{
									if (n1 != n)
									{
										dz[n1][i1] = (int)(dz[n1][i1] + (dz[n1][i1] / (zong*1.0 - dz[n][i1] + 1)*value));
									}
								}
							}
						}
						dz[n][i] = 10000;
					}
				}
			}
		}

	}


	if (cInMessage[0] == 'G')	// GO ָ��
	{
		if (cInMessage[3] >= 'A' && cInMessage[3] <= 'L')																					//x,y���귢���Ի�����Ϊ��ϰ��
		{
			y1 = cInMessage[3] - 'A';
			x1 = cInMessage[4] - '0';
			y2 = cInMessage[5] - 'A';
			x2 = cInMessage[6] - '0';
			result = cInMessage[8] - '0';		//���ӽ��
			y11 = y1;
			x11 = x1;
			y21 = y2;
			x21 = x2;
			if (y21 == 2 && x21 == 1 && y11 < 5)
				z1++;
			if (y21 == 2 && x21 == 3 && y11 < 5)
				z2++;
			if (y21 == 4 && x21 == 1 && y11 < 5)
				z3++;
			if (y21 == 4 && x21 == 3 && y11 < 5)
				z4++;
			if (cInMessage[10] >= 'A' && cInMessage[10] <= 'L') //�Է�˾��ս������ʾ����λ��
			{
				cMap[(cInMessage[10] - 'A')][cInMessage[11] - '0'] = 'L';
				jq++;
				if (cInMessage[11] - '0' == 1)
				{
					dz[1][11] = 10000;
					dz[1][7] = 0;//�˵�Ϊ���죬Ϊ�ų��͵��׵ķ�ֵΪ0
					dz[1][9] = 0;
					dz[3][11] = 0;
					dz[3][7] = 6000;
					dz[3][9] = 4000;
				}
				if (cInMessage[11] - '0' == 3)
				{
					dz[3][11] = 10000;
					dz[1][11] = 0;
					dz[3][7] = 0;
					dz[3][9] = 0;
					dz[1][7] = 6000;
					dz[1][9] = 4000;
				}
			}
			/*/////�жϵ��׵ĸ���///////////
			if (y1<2)
			{
			for (int n = 0; n<25; n++)
			{
			if (dz[n][12] == y1 && dz[n][13] == x1)
			{
			dz[n][12] = y2;
			dz[n][13] = x2;
			for (int i = 0; i<12; i++)
			{
			if (dz[n][i] != 0 && i == 9 && dz[n][i] != 10000)
			{
			for (int n1 = 0; n1<25; n1++)
			{
			if (n1 != n && dz[n1][i]<9000)
			dz[n1][i] = (int)(1.0*dz[n1][i] * (1 + 1.0*dz[n][i] / (30000 - dz[n][i])));
			}
			dz[n][i] = 0;
			}
			}
			zong = 1;
			for (int i = 0; i<9; i++)
			zong = zong + dz[n][i];
			for (int i = 0; i<9; i++)
			{
			souhui(n, i, (int)1.0 * 10000 * dz[n][i] / (zong + 1) - dz[n][i], dz);
			dz[n][i] = 10000 * dz[n][i] / (zong + 1);
			}
			}
			}
			}*/
			switch (result)		//���ݲ�ͬ����޸�����
			{
			case 0:			//�Է����ӱ������Ե�
				Ina_step[0] = 2;
				Ina_step[1] = 1;
				k = cMap[y2][x2] - 'a';  //�յ�Ϊ��������
				shuaxinG0(k, cMap, dz, y1, x1, y2, x2);
				cMap[y1][x1] = '0';
				break;
			case 1:			//�Է��Ե���������
				Ina_step[0] = 2;
				Ina_step[1] = 1;
				k = cMap[y2][x2] - 'a';//�յ�Ϊ�������� k:��������������С
				shuaxinG1(k, cMap, dz, y1, x1, y2, x2);
				cMap[y2][x2] = cMap[y1][x1];
				cMap[y1][x1] = '0';
				break;
			case 2:			//˫�����Ӷ���
				Ina_step[0] = 2;
				Ina_step[1] = 1;
				k = cMap[y2][x2] - 'a';//�յ�Ϊ��������
				shuaxinG2(k, cMap, dz, y1, x1, y2, x2);
				cMap[y1][x1] = '0';
				cMap[y2][x2] = '0';
				break;
			case 3:			//�Է��ƶ����ӡ�����///�� ��Ӫը����������
				Ina_step[1]++;
				shuaxinG3(y1, x1, y2, x2, dz, cMap);
				cMap[y2][x2] = cMap[y1][x1];
				cMap[y1][x1] = '0';
				break;
			}
			FILE *fp;
			fp = fopen("2", "a");
			fprintf(fp, "\n%d,%c,%c,%d,%d,%d,%d,%d\n", result, cMap[y2][x2], cMap[y1][x1], y2, x2, y1, x1, k);
			fclose(fp);
		}
	}
	if (cInMessage[0] == 'R')	// RESULT ָ��
	{
		y1 = cOutMessage[9] - 'A';
		x1 = cOutMessage[10] - '0';
		y2 = cOutMessage[11] - 'A';
		x2 = cOutMessage[12] - '0';
		result = cInMessage[7] - '0';		//������
		if (cInMessage[8] == ' ' && cInMessage[9] >= 'A' && cInMessage[9] <= 'L') //�Է�˾��ս������ʾ����λ��
		{
			cMap[(cInMessage[10] - 'A')][cInMessage[11] - '0'] = 'L';
			jq++;
			if (cInMessage[11] - '0' == 1)
			{
				dz[1][11] = 10000;
				dz[3][11] = 0;
				dz[1][7] = 0;//�˵�Ϊ���죬Ϊ�ų��͵��׵ķ�ֵΪ0
				dz[1][9] = 0;
			}
			if (cInMessage[11] - '0' == 3)
			{
				dz[3][11] = 10000;
				dz[1][11] = 0;
				dz[3][7] = 0;
				dz[3][9] = 0;
			}
		}
		switch (result)		//���ݲ�ͬ����޸�����
		{
		case 0:			//�������ӱ��Է��Ե�
			Ina_step[0] = 1;
			Ina_step[1] = 1;
			k = cMap[y1][x1] - 'a';  //���Ϊ��������
			shuaxinR0(k, cMap, dz, y1, x1, y2, x2);//���ݼ���������ˢ�²²���ʱ�
			cMap[y1][x1] = '0';
			break;
		case 1:			//�����Ե��Է�����
			Ina_step[0] = 1;
			Ina_step[1] = 1;
			k = cMap[y1][x1] - 'a';
			shuaxinR1(k, cMap, dz, y1, x1, y2, x2);
			cMap[y2][x2] = cMap[y1][x1];
			cMap[y1][x1] = '0';
			break;
		case 2:			//˫�����Ӷ���
			Ina_step[0] = 1;
			Ina_step[1] = 1;
			k = cMap[y1][x1] - 'a';
			shuaxinR2(k, cMap, dz, y1, x1, y2, x2);
			cMap[y1][x1] = '0';
			cMap[y2][x2] = '0';
			break;
		case 3:			//�����ƶ�����
			Ina_step[1]++;
			cMap[y2][x2] = cMap[y1][x1];
			cMap[y1][x1] = '0';
			break;
		}
		/*for (int n = 0; n < 25; n++)
		{
		if (dz[n][12] != 14)
		{
		x++;
		}
		}
		if (x <=10)
		{
		for (int n = 0; n < 25; n++)
		{
		m = dz[n][0];
		for (int j = 1; j < 12; j++)
		{
		m = max(m, dz[n][j]);
		}
		for (int i = 0; i < 12; i++)
		{
		if (dz[n][i] == m)
		{
		for (int i1 = 0; i1 < 12; i1++)
		{
		if (i1 != i)
		{
		if (dz[n][i1] != 0 && dz[n][i1] < 9000)
		{
		zong = dz[25][i1];
		for (int n1 = 0; n1 < 25; n1++)
		{
		if (n1 != n)
		{
		dz[n1][i1] = (int)(dz[n1][i1] + (dz[n1][i1] / (zong * 1.0 - dz[n][i1])*dz[n][i1]));
		}
		}
		dz[n][i1] = 0;
		}
		}
		}
		dz[n][i] = 10000;
		continue;
		}
		}
		}
		}*/
		for (int i = 0; i<12; i++)
		{
			dz[25][i] = 0;
			for (int x = 0; x < 25; x++)
			{
				if (dz[x][i] >= 10000 && dz[x][i] <= 15000)
				{
					dz[x][i] = 10000;
				}
				if (dz[x][i] < 0 || dz[x][i]>15000)
				{
					dz[x][i] = 0;
				}
				dz[25][i] = dz[25][i] + dz[x][i];
			}
		}
		/*FILE *fp;
		int p, q;
		fp = fopen("dz", "a");
		for (p = 0; p < 26; p++)
		{
		for (q = 0; q < 16; q++)
		{
		fprintf(fp, "%8d", dz[p][q]);
		}
		fprintf(fp, "\n");
		}
		fprintf(fp, "\n");
		fclose(fp);*/
	}
	
	FILE *abcd = fopen("2", "a");
	fprintf(abcd, "\n�˴�Ϊ���ʱ�\n");
	for (int temp = 0; temp != 26; temp++)
	{
		for (int tt = 0; tt != 14; tt++)
		{
			fprintf(abcd, "%5d  ", dz[temp][tt]);
		}
		fprintf(abcd, "\n");
	}
	fclose(abcd);
}
/* ************************************************************************ */
/* �������ܣ�����INFOָ��,���ز�������										*/
/* �ӿڲ�����																*/
/*     char *cInMessage ���յ�INFO verָ��									*/
/*     char *cOutMessage ��������											*/
/* ************************************************************************ */
void CulInfo(char *cInMessage, char *cVer, char *cOutMessage)
{
	strcpy(cVer, cInMessage + 5);																												//�����û��
	strcpy(cOutMessage, "NAME yuanjiang");
}

/* ************************************************************************ */
/* �������ܣ�����STARTָ��,���ز���											*/
/* �ӿڲ�����																*/
/*     char *cInMessage ���յ�START first time stepsָ��					*/
/*     int *iFirst ����Ȩ[0���У�1����]										*/
/*     int *iTime ����ʱ������(��λ��)[1000,3600]							*/
/*     int *iStep �����ȴ�����(��λ��)[10,31]								*/
/*     char *cOutMessage �����ַ�����										*/
/* ************************************************************************ */
void CulArray(char *cInMessage, int *iFirst, int *iTime, int *iStep, char *cOutMessage)
{
	*iFirst = cInMessage[6] - '0';
	*iTime = cInMessage[8] - '0';
	*iTime = *iTime * 10 + (cInMessage[9] - '0');
	*iTime = *iTime * 10 + (cInMessage[10] - '0');
	*iTime = *iTime * 10 + (cInMessage[11] - '0');
	*iStep = cInMessage[13] - '0';
	*iStep = *iStep * 10 + (cInMessage[14] - '0');
	if (*iFirst == 0)	//����		a˾��,b����,cʦ��,d�ó�,e�ų�,fӪ��,g����,h�ų�,i����,j����kը��,l����   cdgdckhkfiifebejagjihljhg    hegickfkcibefigjajdhdljhg
						//	strcpy(cOutMessage,"ARRAY hcgcgkikgfdfdabejiiejljhh");         chdfckgkdiefabgjjiiejlghh           cdgdckhkfiifebejagjihljhg   cdedckfkfiiegbijajjghlhhg    cdedckfkfiiegbijajjghlhhg
		strcpy(cOutMessage, "ARRAY cgdgckekfiifeibjajjdhlhhg");       //1.    cgdgckfkeiiefgbjajjdhlhhi   2.cgdgckekfiifeibjajjdhlhhg

	else			//����				chefckgkfiidgbjjidjeghhlj     hegickfkcibefigjajdhdljhg

					//	strcpy(cOutMessage,"ARRAY hcgcgkikgfdfadbejiiejljhh");		chdfckgkdiefabijjgiejlghh    chdfckgkdiefabgjjiiejlghh   cdgdhkbkfiifecejagjihljhg
		strcpy(cOutMessage, "ARRAY cgdgckekfiifeibjajjdhlhhg");       //1.       cgdgckfkeiiefgbjajjdhlhhi   2.cgdgckekfiifeibjajjdhlhhg
}
//��Ҫ���ߵ�λ�öԼ�����ɵ���в��ֵ
int weixie(int x, int y, int x1, int y1, int dz[25][16], char cMap[12][5])
{
	int n, score = 0, k, i, j, t, t1 = 0;
	if (cMap[x1][y1] == '0')
		return 0;
	for (n = 0; n<25; n++)//�ڲ²���ʱ����ҵ���Ҫ���ߵ�λ��
	{
		if (dz[n][12] == x1 && dz[n][13] == y1)
			break;
	}
	k = cMap[x][y] - 'a';
	//���з�ֵ����
	if (k >= 0 && k != 10)  //     k==10           Ϊը�����Ȳ�����
	{
		for (i = 0; i<9; i++)//�������ߵ���ķ�ֵ
		{
			if (i<k)
				score = score - dz[n][i];
			else if (i>k)
				score = score + dz[n][i];
			else
				continue;
		}
		if (cMap[x][y] == 'i')
			score = score + dz[n][9];
		else
			score = score - dz[n][9];//���׵ķ�ֵ
	}
	//ͳ�Ƹ������Ƿ�Ϊ������������������
	for (i = 0; i<12; i++)
	{
		for (j = 0; j<5; j++)
		{
			if (cMap[i][j] >= 'a' && cMap[i][j] <= 'i')
			{
				if (i == x && j == y)
					continue;
				else
				{
					t = cMap[i][j] - 'a';
					if (t <= k)   //�Ƚ��������ӵĴ�С
						t1++;  //����
				}
			}
		}
	}
	if (t1<3)//��������Ǽ�������������ȥը���ķ�ֵ
		score = score - dz[n][10];
	return score;
}
int jweixie(int i, int j, int dz[25][16], char cMap[12][5])
{
	int i1, j1;
	int score = 0, score1 = 0;
	if (IsMoveCamp(i, j) == 1)
		score = 0;
	else//����ȡ��Сֵ����Ϊ�������Ϊ����������
	{
		//��ǰ�����ҵ��Լ������ӵ���в����
		//���ڵ�һ�ţ�����ɽ���ǰ�����Ǽ�������
		if (i>0 && !IsAfterHill(i, j) && !IsMyChess(cMap, i - 1, j))
		{
			score1 = weixie(i, j, i - 1, j, dz, cMap);
			if (score1<score)
				score = score1;
			if (i>1 && i<11 && (j == 0 || j == 4))//��������
			{
				for (i1 = i - 1; i1>0; i1--)
				{
					if (cMap[i1][j] == '0')
						continue;
					else if (cMap[i1][j] >= 'A' && cMap[i1][j] <= 'X')
					{
						score1 = weixie(i, j, i1, j, dz, cMap);
						if (score1<score)
							score = score1;
						break;
					}
					else
						break;
				}
			}
		}
		//�������
		if (i<11 && !IsBehindHill(i, j) && !IsMyChess(cMap, i + 1, j))
		{
			score1 = weixie(i, j, i + 1, j, dz, cMap);
			if (score1<score)
				score = score1;
			if (i>0 && i<10 && (j == 0 || j == 4))
			{
				for (i1 = i + 1; i1<11; i1++)
				{
					if (cMap[i1][j] == '0')
						continue;
					else if (cMap[i1][j] >= 'A' && cMap[i1][j] <= 'X')
					{
						score1 = weixie(i, j, i1, j, dz, cMap);
						if (score1<score)
							score = score1;
						break;
					}
					else
						break;
				}
			}
		}
		//��������
		if (j>0 && !IsMyChess(cMap, i, j - 1))
		{
			score1 = weixie(i, j, i, j - 1, dz, cMap);
			if (score1<score)
				score = score1;
			if (j>0 && j<5 && (i == 1 || i == 5 || i == 6 || i == 10))
			{
				for (j1 = j - 1; j1 >= 0; j1--)
				{
					if (cMap[i][j1] == '0')
						continue;
					else if (cMap[i][j1] >= 'A' && cMap[i][j1] <= 'X')
					{
						score1 = weixie(i, j, i, j1, dz, cMap);
						if (score1<score)
							score = score1;
						break;
					}
					else
						break;
				}
			}
		}
		//��������
		if (j<4 && !IsMyChess(cMap, i, j + 1))
		{
			score1 = weixie(i, j, i, j + 1, dz, cMap);
			if (score1<score)
				score = score1;
			if (j >= 0 && j<4 && (i == 1 || i == 5 || i == 6 || i == 10))
			{
				for (j1 = j + 1; j1<5; j1++)
				{
					if (cMap[i][j1] == '0')
						continue;
					else if (cMap[i][j1] >= 'A' && cMap[i][j1] <= 'X')
					{
						score1 = weixie(i, j, i, j1, dz, cMap);
						if (score1<score)
							score = score1;
						break;
					}
					else
						break;
				}
			}
		}
	}
	return score;
}
int Oppnextmove(int i, int j, char cMap[12][5], int allmove[200][2])
{
	int k = 0, i1, j1, num = 0, num1, iSaMove[40][2];
	char cmap[12][5];
	if (IsOppChess(cMap, i, j) && !IsBaseCamp(i, j))
	{
		//����ǰ��:���ڵ�һ��,����ɽ���,ǰ�����Ǽ�������,ǰ������������ռ�����Ӫ
		if (i>0 && !IsAfterHill(i, j) && !IsOppChess(cMap, i - 1, j) && !IsFilledCamp(cMap, i - 1, j))
		{
			allmove[k][0] = i - 1;
			allmove[k][1] = j;
			k++;
			if ((j == 0 || j == 4) && i>0 && i<11)
			{
				for (i1 = i - 1; i1>0; i1--)
				{
					if (cMap[i1][j] == '0')
					{
						allmove[k][0] = i1;
						allmove[k][1] = j;
						k++;
					}
					else if (cMap[i1][j] >= 'a' && cMap[i1][j] <= 'l')
					{
						allmove[k][0] = i1;
						allmove[k][1] = j;
						k++;
						break;
					}
					else break;
				}
			}
		}
		//��������:����������,��಻�Ǽ�������,��಻�Ǳ�ռ�õ���Ӫ
		if (j>0 && !IsOppChess(cMap, i, j - 1) && !IsFilledCamp(cMap, i, j - 1))
		{
			allmove[k][0] = i;
			allmove[k][1] = j - 1;
			k++;
			//�Ƿ���1,5,6,10������
			if (i == 1 || i == 5 || i == 6 || i == 10)
			{
				for (int i1 = j - 1; i1 >= 0; i1--)
				{
					if (cMap[i][i1] == '0')
					{
						allmove[k][0] = i;
						allmove[k][1] = i1;
						k++;
					}
					else if (cMap[i][i1] >= 'a'&&cMap[i][i1] <= 'l')
					{
						allmove[k][0] = i;
						allmove[k][1] = i1;
						k++;
						break;
					}
					else break;
				}
			}
		}
		//��������:����������,�Ҳ಻�Ǽ�������,�Ҳ಻�Ǳ�ռ�õ���Ӫ
		if (j<4 && !IsOppChess(cMap, i, j + 1) && !IsFilledCamp(cMap, i, j + 1))
		{
			allmove[k][0] = i;
			allmove[k][1] = j + 1;
			k++;
			//�Ƿ���1,5,6,10������
			if (i == 1 || i == 5 || i == 6 || i == 10)
			{
				for (int i1 = j + 1; i1<5; i1++)
				{
					if (cMap[i][i1] == '0')
					{
						allmove[k][0] = i;
						allmove[k][1] = i1;
						k++;
					}
					else if (cMap[i][i1] >= 'a'&&cMap[i][i1] <= 'l')
					{
						allmove[k][0] = i;
						allmove[k][1] = i1;
						k++;
						break;
					}
					else break;
				}
			}
		}

		//���Ժ��ƣ��������һ�У��󷽲��Ǽ������ӣ����治����ռ�е���Ӫ
		if (i<11 && !IsBehindHill(i, j) && !IsOppChess(cMap, i + 1, j) && !IsFilledCamp(cMap, i + 1, j))
		{
			allmove[k][0] = i + 1;
			allmove[k][1] = j;

			k++;
			//������������������ƶ����󷽲��Ǽ������ӣ����ǵ�һ�У��������һ��
			if ((j == 0 || j == 4) && i>0 && i<11)
			{
				for (i1 = i + 1; i1<11; i1++)
				{
					if (cMap[i1][j] == '0')
					{
						allmove[k][0] = i1;
						allmove[k][1] = j;

						k++;
					}
					else if (cMap[i1][j] >= 'a' && cMap[i1][j] <= 'l')
					{
						allmove[k][0] = i1;
						allmove[k][1] = j;
						k++;
						break;
					}
					else  break;
				}

			}
		}
		//������ǰ�ƣ���ǰ��������ռ�е���Ӫ�����Ǽ�������
		if ((Iszuoqian(i, j) || IsMoveCamp(i, j)) && !IsOppChess(cMap, i - 1, j - 1) && !IsFilledCamp(cMap, i - 1, j - 1))
		{
			allmove[k][0] = i - 1;
			allmove[k][1] = j - 1;

			k++;
		}
		//��������ƣ���󷽲��Ǽ������ӣ�������ռ�е���Ӫ
		if ((Iszuohou(i, j) || IsMoveCamp(i, j)) && !IsOppChess(cMap, i + 1, j - 1) && !IsFilledCamp(cMap, i + 1, j - 1))
		{
			allmove[k][0] = i + 1;
			allmove[k][1] = j - 1;

			k++;
		}
		//������ǰ�ƣ���ǰ�����Ǽ������ӣ�������ռ�е���Ӫ
		if ((Isyouqian(i, j) || IsMoveCamp(i, j)) && !IsOppChess(cMap, i - 1, j + 1) && !IsFilledCamp(cMap, i - 1, j + 1))
		{
			allmove[k][0] = i - 1;
			allmove[k][1] = j + 1;

			k++;
		}
		//�����Һ��ƣ��Һ󷽲��Ǽ������ӣ�������ռ�е���Ӫ
		if ((Isyouhou(i, j) || IsMoveCamp(i, j)) && !IsOppChess(cMap, i + 1, j + 1) && !IsFilledCamp(cMap, i + 1, j + 1))
		{
			allmove[k][0] = i + 1;
			allmove[k][1] = j + 1;
			k++;
		}
	}

	return k;
}
//����ĳ��λ�õ����ӵ���һ�����������λ��
int nextmove1(int i, int j, char cMap[12][5], int allmove[200][2])
{
	int k = 0, i1, j1, num = 0, num1, iSaMove[40][2];
	char cmap[12][5];
	if (IsMyMovingChess(cMap, i, j) && !IsBaseCamp(i, j))  //�������ڴ�Ӫ�Ŀ��ƶ�����
	{
		//��������
		if (cMap[i][j] == 'i' && IsRailway(i, j))
		{
			iSaMove[0][0] = i;
			iSaMove[0][1] = j;
			for (i1 = 0; i1<12; i1++)
			{
				for (j1 = 0; j1<5; j1++)
					cmap[i1][j1] = cMap[i1][j1];
			}
			num = SapperRail(iSaMove, cmap, i, j, 0);
			for (num1 = 1; num1<num; num1++)
			{
				allmove[k][0] = iSaMove[num1][0];
				allmove[k][1] = iSaMove[num1][1];
				k++;
			}
		}
		//����ǰ��:���ڵ�һ��,����ɽ���,ǰ�����Ǽ�������,ǰ������������ռ�����Ӫ
		if (i>0 && !IsAfterHill(i, j) && !IsMyChess(cMap, i - 1, j) && !IsFilledCamp(cMap, i - 1, j))
		{
			allmove[k][0] = i - 1;
			allmove[k][1] = j;
			k++;
			if ((j == 0 || j == 4) && i>0 && i<11)
			{
				for (i1 = i - 1; i1>0; i1--)
				{
					if (cMap[i1][j] == '0')
					{
						allmove[k][0] = i1;
						allmove[k][1] = j;
						k++;
					}
					else if (cMap[i1][j] >= 'A' && cMap[i1][j] == 'X')
					{
						allmove[k][0] = i1;
						allmove[k][1] = j;
						k++;
						break;
					}
					else break;
				}
			}
		}
		//��������:����������,��಻�Ǽ�������,��಻�Ǳ�ռ�õ���Ӫ
		if (j>0 && !IsMyChess(cMap, i, j - 1) && !IsFilledCamp(cMap, i, j - 1))
		{
			allmove[k][0] = i;
			allmove[k][1] = j - 1;
			k++;
			//�Ƿ���1,5,6,10������
			if (i == 1 || i == 5 || i == 6 || i == 10)
			{
				for (int i1 = j - 1; i1 >= 0; i1--)
				{
					if (cMap[i][i1] == '0')
					{
						allmove[k][0] = i;
						allmove[k][1] = i1;
						k++;
					}
					else if (cMap[i][i1] >= 'A'&&cMap[i][i1] <= 'X')
					{
						allmove[k][0] = i;
						allmove[k][1] = i1;
						k++;
						break;
					}
					else break;
				}
			}
		}
		//��������:����������,�Ҳ಻�Ǽ�������,�Ҳ಻�Ǳ�ռ�õ���Ӫ
		if (j<4 && !IsMyChess(cMap, i, j + 1) && !IsFilledCamp(cMap, i, j + 1))
		{
			allmove[k][0] = i;
			allmove[k][1] = j + 1;
			k++;
			//�Ƿ���1,5,6,10������
			if (i == 1 || i == 5 || i == 6 || i == 10)
			{
				for (int i1 = j + 1; i1<5; i1++)
				{
					if (cMap[i][i1] == '0')
					{
						allmove[k][0] = i;
						allmove[k][1] = i1;
						k++;
					}
					else if (cMap[i][i1] >= 'A'&&cMap[i][i1] <= 'X')
					{
						allmove[k][0] = i;
						allmove[k][1] = i1;
						k++;
						break;
					}
					else break;
				}
			}
		}

		//���Ժ��ƣ��������һ�У��󷽲��Ǽ������ӣ����治����ռ�е���Ӫ
		if (i<11 && !IsBehindHill(i, j) && !IsMyChess(cMap, i + 1, j) && !IsFilledCamp(cMap, i + 1, j))
		{
			allmove[k][0] = i + 1;
			allmove[k][1] = j;

			k++;
			//������������������ƶ����󷽲��Ǽ������ӣ����ǵ�һ�У��������һ��
			if ((j == 0 || j == 4) && i>0 && i<11)
			{
				for (i1 = i + 1; i1<11; i1++)
				{
					if (cMap[i1][j] == '0')
					{
						allmove[k][0] = i1;
						allmove[k][1] = j;

						k++;
					}
					else if (cMap[i1][j] >= 'A' && cMap[i1][j] <= 'X')
					{
						allmove[k][0] = i1;
						allmove[k][1] = j;
						k++;
						break;
					}
					else  break;
				}

			}
		}
		//������ǰ�ƣ���ǰ��������ռ�е���Ӫ�����Ǽ�������
		if ((Iszuoqian(i, j) || IsMoveCamp(i, j)) && !IsMyChess(cMap, i - 1, j - 1) && !IsFilledCamp(cMap, i - 1, j - 1))
		{
			allmove[k][0] = i - 1;
			allmove[k][1] = j - 1;

			k++;
		}
		//��������ƣ���󷽲��Ǽ������ӣ�������ռ�е���Ӫ
		if ((Iszuohou(i, j) || IsMoveCamp(i, j)) && !IsMyChess(cMap, i + 1, j - 1) && !IsFilledCamp(cMap, i + 1, j - 1))
		{
			allmove[k][0] = i + 1;
			allmove[k][1] = j - 1;

			k++;
		}
		//������ǰ�ƣ���ǰ�����Ǽ������ӣ�������ռ�е���Ӫ
		if ((Isyouqian(i, j) || IsMoveCamp(i, j)) && !IsMyChess(cMap, i - 1, j + 1) && !IsFilledCamp(cMap, i - 1, j + 1))
		{
			allmove[k][0] = i - 1;
			allmove[k][1] = j + 1;

			k++;
		}
		//�����Һ��ƣ��Һ󷽲��Ǽ������ӣ�������ռ�е���Ӫ
		if ((Isyouhou(i, j) || IsMoveCamp(i, j)) && !IsMyChess(cMap, i + 1, j + 1) && !IsFilledCamp(cMap, i + 1, j + 1))
		{
			allmove[k][0] = i + 1;
			allmove[k][1] = j + 1;
			k++;
		}
	}
	return k;
}

void mychessdx(char cMap[12][5], char mc[25])   //���ҷ����Ӱ��������Ĵ�С����
{												//�ҵ��ҷ����ӳ���˾����������
	int i = 0, l;
	for (int i2 = 0; i2<12; i2++)  // �Ҽ���ը������Ŀ
	{
		for (int j2 = 0; j2<5; j2++)
			if (cMap[i2][j2] >= 'a' && cMap[i2][j2] <= 'l')
			{
				mc[i] = cMap[i2][j2];
				i++;
				l = i;
			}
	}
	for (i = 0; i<l; i++)
	{
		for (int j = 0; j + i<l - 1; j++)
		{
			if (mc[j]>mc[j + 1])
			{
				char flag = mc[j];
				mc[j] = mc[j + 1];
				mc[j + 1] = flag;
			}
		}
	}
}

void jushipg(char cMap[12][5], int dz[25][16])
{
	if (cMap[11][1] == 'l')    ///���������λ��
	{
		qipanfen[6][0] = 130;
		qipanfen[7][0] = 120;
		qipanfen[7][1] = 600;
		qipanfen[8][0] = 120;
		qipanfen[8][1] = 80;
		qipanfen[9][0] = 120;
		qipanfen[9][1] = 700;
		qipanfen[10][0] = 600;
		qipanfen[10][1] = 200;
	}
	if (cMap[11][3] == 'l')
	{
		qipanfen[6][4] = 130;
		qipanfen[7][4] = 120;
		qipanfen[7][3] = 600;
		qipanfen[8][4] = 120;
		qipanfen[8][3] = 80;
		qipanfen[9][4] = 120;
		qipanfen[9][3] = 700;
		qipanfen[10][4] = 600;
		qipanfen[10][3] = 200;
	}
	if (dz[1][11] == 10000)  //�з������λ��
	{
		qipanfen[0][3] = -10000;
		qipanfen[0][4] = -10000;
		qipanfen[0][1] = 10000;
		qipanfen[0][0] = 600;
		qipanfen[1][0] = 400;
		qipanfen[1][1] = 700;
		qipanfen[2][0] = 300;
		qipanfen[2][1] = 900;
		qipanfen[3][0] = 240;
		qipanfen[3][1] = 100;
		qipanfen[4][0] = 230;
		qipanfen[4][1] = 500;
		qipanfen[5][0] = 220;
	}
	if (dz[3][11] == 10000)
	{
		qipanfen[0][1] = -10000;
		qipanfen[0][0] = -10000;
		qipanfen[0][3] = 10000;
		qipanfen[0][4] = 600;
		qipanfen[1][4] = 400;
		qipanfen[1][3] = 700;
		qipanfen[2][4] = 300;
		qipanfen[2][3] = 900;
		qipanfen[3][4] = 240;
		qipanfen[3][3] = 100;
		qipanfen[4][4] = 230;
		qipanfen[4][3] = 500;
		qipanfen[5][4] = 220;
	}
}
int walei1(char cMap[12][5], int dz[25][16])
{
	int k = 0;
	if (cMap[1][0] == '0' || (cMap[1][0] == 'X' && Judge(1, 0, 9, dz)>5000))
	{
		if (cMap[1][1] == '0' || (cMap[1][1] == 'X' && Judge(1, 1, 9, dz)>5000))
			k = 1;
		if (cMap[0][0] == '0' || (cMap[0][0] == 'X' && Judge(0, 0, 9, dz)>5000))
			k = 1;
	}
	return k;
}
int walei3(char cMap[12][5], int dz[25][16])
{
	int k = 0;
	if (cMap[1][4] == '0' || (cMap[1][4] == 'X' && Judge(1, 4, 9, dz)>5000))
	{
		if (cMap[1][3] == '0' || (cMap[1][3] == 'X' && Judge(1, 3, 9, dz)>5000))
			k = 1;
		if (cMap[0][4] == '0' || (cMap[0][4] == 'X' && Judge(0, 4, 9, dz)>5000))
			k = 1;
	}
	return k;
}
int walei(char cMap[12][5], int dz[25][16])//�жϵз����츽���Ƿ��е���
{
	int k = 0;
	if (dz[1][11]>9000)
	{
		if (cMap[1][0] == '0' || (cMap[1][0] == 'X' && Judge(1, 0, 9, dz)>5000))
		{
			if (cMap[1][1] == '0' || (cMap[1][1] == 'X' && Judge(1, 1, 9, dz)>5000))
				k = 1;
			if (cMap[0][0] == '0' || (cMap[0][0] == 'X' && Judge(0, 0, 9, dz)>5000))
				k = 1;
		}
		if ((cMap[1][4] == '0' || (cMap[1][4] == 'X' && Judge(1, 4, 9, dz)>5000)) && (cMap[1][3] == '0' || (cMap[1][3] == 'X' && Judge(1, 3, 9, dz)>5000)) && (cMap[1][2] == '0' || (cMap[1][2] == 'X' && Judge(1, 2, 9, dz)>5000)) && (cMap[1][1] == '0' || (cMap[1][1] == 'X' && Judge(1, 1, 9, dz)>5000)))
			k = 1;
	}
	else if (dz[3][11]>9000)
	{
		if (cMap[1][4] == '0' || (cMap[1][4] == 'X' && Judge(1, 4, 9, dz)>5000))
		{
			if (cMap[1][4] == '0' || (cMap[1][4] == 'X' && Judge(1, 4, 9, dz)>5000))
				k = 1;
			if (cMap[0][4] == '0' || (cMap[0][4] == 'X' && Judge(0, 4, 9, dz)>5000))
				k = 1;
		}
		if ((cMap[1][0] == '0' || (cMap[1][0] == 'X' && Judge(1, 0, 9, dz)>5000)) && (cMap[1][1] == '0' || (cMap[1][1] == 'X' && Judge(1, 1, 9, dz)>5000)) && (cMap[1][2] == '0' || (cMap[1][2] == 'X' && Judge(1, 2, 9, dz)>5000)) && (cMap[1][3] == '0' || (cMap[1][3] == 'X' && Judge(1, 3, 9, dz)>5000)))
			k = 1;
	}
	else
	{
		if (walei1(cMap, dz) && walei3(cMap, dz))
			k = 1;
		if ((cMap[1][4] == '0' || (cMap[1][4] == 'X' && Judge(1, 4, 9, dz)>5000)) && (cMap[1][3] == '0' || (cMap[1][3] == 'X' && Judge(1, 3, 9, dz)>5000)) && (cMap[1][2] == '0' || (cMap[1][2] == 'X' && Judge(1, 2, 9, dz)>5000)) && (cMap[1][1] == '0' || (cMap[1][1] == 'X' && Judge(1, 1, 9, dz)>5000)))
			k = 1;
		if ((cMap[1][0] == '0' || (cMap[1][0] == 'X' && Judge(1, 0, 9, dz)>5000)) && (cMap[1][1] == '0' || (cMap[1][1] == 'X' && Judge(1, 1, 9, dz)>5000)) && (cMap[1][2] == '0' || (cMap[1][2] == 'X' && Judge(1, 2, 9, dz)>5000)) && (cMap[1][3] == '0' || (cMap[1][3] == 'X' && Judge(1, 3, 9, dz)>5000)))
			k = 1;
	}

	return k;
}

int pinggu(int i, int j, int i1, int j1, int dz[25][16], char cMap[12][5])
{
	int zha = 0;
	char mchess[25];
	int score = 0, weixief = 0, qipan = 0, jweixief = 0, sanyif = 0, teshu = 0, score1 = 0;
	bool sanyi1 = false, sanyi2 = false, sanyi3 = false;
	char cmap[12][5], cmap1[12][5];
	int k, k1, k2, k3, i2, j2;
	int allmove1[200][2], allmove2[200][2];
	int x = 0;
	int i3, j3;
	int flag = 0, flag1, flag2 = 0;
	FILE *fp;
	fp = fopen("1", "a");
	for (i2 = 0; i2 < 12; i2++)
	{
		for (j2 = 0; j2 < 5; j2++)
			cmap[i2][j2] = cMap[i2][j2];
	}
	cmap[i1][j1] = cmap[i][j];
	cmap[i][j] = '0';

	if (dz[1][11] == 0)
		cMap[0][3] = 'L';
	if (dz[3][11] == 0)
		cMap[0][1] = 'L';
	//    ������        ����������������������������������������������������������

	mychessdx(cMap, mchess);
	if (cMap[i][j] <= 'e' || cMap[i][j] == 'k')//�����Ĵ����ó������ӣ���ը������������Ӫ������
	{
		if (cMap[11][1] == 'l' && i1 == 11 && j1 == 3)
			teshu = teshu - 20000;
		if (cMap[11][3] == 'l' && i1 == 11 && j1 == 1)
			teshu = teshu - 20000;
	}
	//fprintf(fp, "\naaaa %d ", teshu);
	//////////////////////////////////////////////////////��������
	if (cMap[11][1] == 'l')
	{
		if (cMap[10][1] == 'X' && i1 == 10 && j1 == 1)
			teshu = teshu + (13 - (cMap[i][j] - 'a')) * 500;
		if (cMap[10][0] == 'X' && cMap[11][0] == '0' && i1 == 10 && j1 == 0)
			teshu = teshu + (13 - (cMap[i][j] - 'a')) * 500;
		if (cMap[10][0] == 'X' && cMap[11][0] == 'j' && Judge(10, 0, 8, dz) > 6000)
			teshu = teshu + (13 - (cMap[i][j] - 'a')) * 500;
	}
	if (cMap[11][3] == 'l')
	{
		if (cMap[10][3] == 'X' && i1 == 10 && j1 == 3)
			teshu = teshu + (13 - (cMap[i][j] - 'a')) * 500;
		if (cMap[10][4] == 'X' && cMap[11][4] == '0' && i1 == 10 && j1 == 4)
			teshu = teshu + (13 - (cMap[i][j] - 'a')) * 500;
		if (cMap[10][4] == 'X' && cMap[11][4] == 'j' && Judge(10, 4, 8, dz) > 6000)
			teshu = teshu + (13 - (cMap[i][j] - 'a')) * 500;
	}
	//fprintf(fp, "\naaaa1 %d ", teshu);
	/////////////////////////////////////////////////////////////////
	//��������
	//
	//��Դ��ӻ���Ľ���
	if (cMap[i][j] == 'k')
	{
		if ((i1 == 11 && j1 == 1) || (i1 == 11 && j1 == 3))
			teshu = teshu - 300000;
		int ia, ib, ix, alnum, almovea[200][2];
		char cmapx[12][5];
		for (ia = 0; ia < 12; ia++)
			for (ib = 0; ib < 12; ib++)
			{
				cmapx[ia][ib] = cMap[ia][ib];

			}
		cmapx[i1][j1] = cmapx[i][j];
		cmapx[i][j] = '0';
		ib = 0;
		ix = 0;
		for (ia = 0; ia < 25; ia++)
		{
			if (bekilled[ia] > ib)
			{
				ib = bekilled[ia];
				ix = ia;
			}
		}
		//һ������
		if (ib > 0 && dz[ix][12] == 1 && dz[ix][13] == 1 && i1 == 1 && j1 == 0 && cMap[i1][j1] == '0')
		{
			teshu = teshu + 8000;
		}
		if (ib > 0 && dz[ix][12] == 1 && dz[ix][13] == 3 && i1 == 1 && j1 == 4 && cMap[i1][j1] == '0')
		{
			teshu = teshu + 8000;
		}
		//��������
		alnum = 0;
		alnum = nextmove1(i1, j1, cmapx, almovea);
		for (ia = 0; ia < alnum; ia++)
		{
			if (ib > 0 && dz[ix][12] == 1 && dz[ix][13] == 1 && almovea[ia][0] == 1 && almovea[ia][1] == 0 && cMap[i1][j1] == '0')
			{
				teshu = teshu + 6000;
			}
			if (ib > 0 && dz[ix][12] == 1 && dz[ix][13] == 3 && almovea[ia][0] == 1 && almovea[ia][1] == 0 && cMap[i1][j1] == '0')
			{
				teshu = teshu + 6000;
			}
		}
	}
	fprintf(fp, "\naaaa2 %d ", teshu);
	//���ڽ���
	if (NumChess(cMap) + NumOppChess(cMap) <= 40)
	{   
		    //�����������죨��ࣩ
		if (cMap[0][1] == 'L')
		{
			int flag1 = 0;
			if (cMap[i][j] <= 'e')
			{
				if (i1 == 1 && j1 == 0 && cMap[1][0] == '0'&&cMap[1][1] == '0')
					teshu = teshu + 7000;
				if (i1 == 2 && j1 == 1 && cMap[2][1] == '0'&&cMap[1][1] == '0')
					teshu = teshu + 7000;
				if (i1 == 1 && j1 == 0 && cMap[1][0] == '0'&&cMap[0][0] == '0')
					teshu = teshu + 7000;
				if (i1 == 1 && j1 == 2 && cMap[1][2] == '0' && (cMap[0][2] == '0' || cMap[1][1] == '0'))
					teshu = teshu + 7000;
			}
			if (flag1 == 0)
			{
				int allmove1[200][2], m1, m2;
				char cmap1[12][5];
				for (m1 = 0; m1 < 12; m1++)
					for (m2 = 0; m2 < 5; m2++)
						cmap1[m1][m2] = cMap[m1][m2];
				cmap1[i1][j1] = cmap1[i][j];
				cmap1[i][j] = '0';
				m2 = nextmove1(i1, j1, cmap1, allmove1);
				int flag2 = 0;
				for (m1 = 0; m1 < m2; m1++)
				{
					if (allmove1[m1][0] == 1 && allmove1[m1][1] == 0 && cMap[1][0] == '0'&&cMap[1][1] == '0'&&flag2==0)
					{
						teshu = teshu + 6000;
						flag2 = 1;
					}
					if (allmove1[m1][0] == 2 && allmove1[m1][1] == 1 && cMap[2][1] == '0'&&cMap[1][1] == '0'&&flag2 == 0)
					{
						teshu = teshu + 6000;
						flag2 = 1;
					}
					if (allmove1[m1][0] == 1 && allmove1[m1][1] == 2 && cMap[1][2] == '0'&&cMap[0][2] == '0'&&flag2 == 0)
					{
						teshu = teshu + 6000;
						flag2 = 1;
					}
					if (allmove1[m1][0] == 1 && allmove1[m1][1] == 2 && cMap[1][2] == '0' && (cMap[0][2] == '0' || cMap[1][1] == '0') && flag2 == 0)
					{
						teshu = teshu + 6000;
						flag2 = 1;
					}
				}
			}
			//ֱ�Ӷ���
			if (i1 == 0 && j1 == 1)
				teshu = teshu + 1000000;
			if (i1 == 1 && j1 == 1)
				teshu = teshu + 800000;
			if (i1 == 0 && j1 == 0)
				teshu = teshu + 600000;
			//******************************************************
			//�Թ�����ʹ��
			if (cMap[i][j] == 'i')
			{
				//һ������
				int flag1 = 0;
				if (cMap[i1][j1] == 'X'&&i1 == 0 && j1 == 0 && Judge(i1, j1, 9, dz) > 4000)
				{
					teshu = teshu + 5000;
					flag1 = 1;
				}
				if (cMap[i1][j1] == 'X'&&i1 == 0 && j1 == 2 && Judge(i1, j1, 9, dz) > 4000)
				{
					teshu = teshu + 5000;
					flag1 = 1;
				}
				if (cMap[i1][j1] == 'X'&&i1 == 1 && j1 == 0 && Judge(i1, j1, 9, dz) > 4000)
				{
					teshu = teshu + 5000;
					flag1 = 1;
				}
				if (cMap[i1][j1] == 'X'&&i1 == 1 && j1 == 1 && Judge(i1, j1, 9, dz) > 4000)
				{
					teshu = teshu + 5000;
					flag1 = 1;
				}
				if (cMap[i1][j1] == 'X'&&i1 == 1 && j1 == 2 && Judge(i1, j1, 9, dz) > 4000)
				{
					teshu = teshu + 5000;
					flag1 = 1;
				}
				//��������
				if (flag1 == 0)
				{
					int allmove1[200][2], m1, m2;
					char cmap1[12][5];
					for (m1 = 0; m1 < 12; m1++)
						for (m2 = 0; m2 < 5; m2++)
							cmap1[m1][m2] = cMap[m1][m2];
					cmap1[i1][j1] = cmap1[i][j];
					cmap1[i][j] = '0';
					m2 = nextmove1(i1, j1, cmap1, allmove1);
					for (m1 = 0; m1 < m2; m1++)
						if (Judge(allmove1[m1][0], allmove1[m1][1], 9, dz) >= 4000 && ((allmove1[m1][0] = 0 || allmove1[m1][0] == 1) && (allmove1[m1][1] >= 0 && allmove1[m1][1] <= 2)))
						{
							teshu = teshu + 4000;
						}

				}
			}
		}
			//�����������죨�Ҳࣩ
		if (cMap[0][3] == 'L')
		{
			if (cMap[i][j] <= 'e')
			{
				int flag1 = 0;
				if (i1 == 1 && j1 == 4 && cMap[1][4] == '0'&&cMap[1][3] == '0')
				{
					teshu = teshu + 7000; flag1 = 1;
				}
				if (i1 == 2 && j1 == 3 && cMap[2][3] == '0'&&cMap[1][3] == '0')
				{
					teshu = teshu + 7000; flag1 = 1;
				}
				if (i1 == 1 && j1 == 4 && cMap[1][4] == '0'&&cMap[0][4] == '0')
				{
					teshu = teshu + 7000; flag1 = 1;
				}
				if (i1 == 1 && j1 == 2 && cMap[1][2] == '0' && (cMap[0][2] == '0' || cMap[1][3] == '0'))
				{
					teshu = teshu + 7000; flag1 = 1;
				}
				if (flag1 == 0)
				{
					int allmove1[200][2], m1, m2;
					char cmap1[12][5];
					for (m1 = 0; m1 < 12; m1++)
						for (m2 = 0; m2 < 5; m2++)
							cmap1[m1][m2] = cMap[m1][m2];
					cmap1[i1][j1] = cmap1[i][j];
					cmap1[i][j] = '0';
					int flag2 = 0;
					m2 = nextmove1(i1, j1, cmap1, allmove1);
					for (m1 = 0; m1 < m2; m1++)
					{
						if (allmove1[m1][0] == 1 && allmove1[m1][1] == 4 && cMap[1][4] == '0'&&cMap[1][3] == '0'&&flag2==0)
						{
							teshu = teshu + 6000;
							flag2 = 1;
							fprintf(fp, "\n3 %d %d", teshu,m1);
						}
						if (allmove1[m1][0] == 2 && allmove1[m1][1] == 3 && cMap[2][3] == '0'&&cMap[1][3] == '0'&&flag2 == 0)
						{
							teshu = teshu + 6000;
							flag2 = 1;
							fprintf(fp, "\n4 %d ", teshu);
						}
						if (allmove1[m1][0] == 1 && allmove1[m1][1] == 4 && cMap[1][4] == '0'&&cMap[0][4] == '0'&&flag2 == 0)
						{
							teshu = teshu + 6000;
							flag2 = 1;
							fprintf(fp, "\n5 %d ", teshu);
						}
						if (allmove1[m1][0] == 1 && allmove1[m1][1] == 2 && cMap[1][2] == '0' && (cMap[0][2] == '0' || cMap[1][3] == '0') && flag2 == 0)
						{
							teshu = teshu + 6000;
							flag2 = 1;
							fprintf(fp, "\n6 %d ", teshu);
						}
					}
				}
			}
			fprintf(fp, "\n2 %d ", teshu);
			//ֱ�Ӷ�
			if (i1 == 0 && j1 == 3)
				teshu = teshu + 1000000;
			if (i1 == 1 && j1 == 3)
				teshu = teshu + 800000;
			if (i1 == 0 && j1 == 4)
				teshu = teshu + 600000;
		
			//******************************************************
			//�Թ�����ʹ��
			if (cMap[i][j] == 'i')
			{
				//һ������
				int flag1 = 0;
				if (cMap[i1][j1] == 'X'&&i1 == 0 && j1 == 4 && Judge(i1, j1, 9, dz) > 4000)
				{
					teshu = teshu + 5000;
					flag1 = 1;
				}
				if (cMap[i1][j1] == 'X'&&i1 == 0 && j1 == 2 && Judge(i1, j1, 9, dz) > 4000)
				{
					teshu = teshu + 5000;
					flag1 = 1;
				}
				if (cMap[i1][j1] == 'X'&&i1 == 1 && j1 == 4 && Judge(i1, j1, 9, dz) > 4000)
				{
					teshu = teshu + 5000;
					flag1 = 1;
				}
				if (cMap[i1][j1] == 'X'&&i1 == 1 && j1 == 3 && Judge(i1, j1, 9, dz) > 4000)
				{
					teshu = teshu + 5000;
					flag1 = 1;
				}
				if (cMap[i1][j1] == 'X'&&i1 == 1 && j1 == 2 && Judge(i1, j1, 9, dz) > 4000)
				{
					teshu = teshu + 5000;
					flag1 = 1;
				}
				//��������
				if (flag1 == 0)
				{
					int allmove1[200][2], m1, m2;
					char cmap1[12][5];
					for (m1 = 0; m1 < 12; m1++)
						for (m2 = 0; m2 < 5; m2++)
							cmap1[m1][m2] = cMap[m1][m2];
					cmap1[i1][j1] = cmap1[i][j];
					cmap1[i][j] = '0';
					m2 = nextmove1(i1, j1, cmap1, allmove1);
					for (m1 = 0; m1 < m2; m1++)
						if (Judge(allmove1[m1][0], allmove1[m1][1], 9, dz) >= 4000 && ((allmove1[m1][0] = 0 || allmove1[m1][0] == 1) && (allmove1[m1][1] >= 2 && allmove1[m1][1] <= 4)))
						{
							teshu = teshu + 4000;
						}

				}
			}
		}
	}
		//******************************************************
//******************************************************
	//1.�ҷ���������ػ�����
	mychessdx(cMap, mchess);
	if (cMap[i][j] == mchess[0])
	{
		if (cMap[i1][j1] == 'X' && Judge(i1, j1, 10, dz) >= 3000)
			teshu = teshu - 5000;
		if (cMap[11][1] == 'l')
		{
			if (cMap[10][2] == mchess[0] || cMap[10][1] == mchess[0] || cMap[10][0] == mchess[0] || cMap[9][2] == mchess[0] || cMap[9][1] == mchess[0] || cMap[9][0] == mchess[0] || cMap[8][0] == mchess[0] || cMap[8][1] == mchess[0])
				flag2 = 1;		//�жϼ��������Ƿ��ڿ��Ա��������λ�� 1�ڡ�0����
			if (i1 == 10 && j1 == 2 && cMap[i1][j1] == 'X')
				teshu = teshu + 5000;
			else if (i1 == 10 && j1 == 1 && cMap[i1][j1] == 'X')
				teshu = teshu + 15000;
			else if ((i1 == 9 || i1 == 8 || i1 == 10) && j1 == 0 && cMap[i1][j1] == 'X')
			{
				for (k1 = i1 - 1; k1 >= 1; k1--)
				{
					if (cMap[k1][j1] == '0')
						continue;
					else if (cMap[k1][j1] == 'X' && Judge(k1, j1, 10, dz) >= 3000)
					{
						flag = 1;
						break;
					}
					else
						break;
				}
				if (flag == 1)
					teshu = teshu - 5000;
				else
					teshu = teshu + 2000;
				if (cMap[10][0] == 'X')
					teshu = teshu + 5000;
			}
			else if (i1 == 8 && j1 == 1 && cMap[i1][j1] == 'X')
				teshu = teshu + 3500;
			else if (i1 == 9 && j1 == 2 && cMap[i1][j1] == 'X')
				teshu = teshu + 3500;
			else if (i1 == 9 && j1 == 1)
				teshu = teshu + 3000;
			else
				teshu = teshu - 2000;
		}
		if (cMap[11][3] == 'l')
		{
			if (cMap[10][2] == mchess[0] || cMap[10][3] == mchess[0] || cMap[10][4] == mchess[0] || cMap[9][2] == mchess[0] || cMap[9][3] == mchess[0] || cMap[9][4] == mchess[0] || cMap[8][3] == mchess[0] || cMap[8][4] == mchess[0])
				flag2 = 1;
			if (i1 == 10 && j1 == 2 && cMap[i1][j1] == 'X')
				teshu = teshu + 5000;
			else if (i1 == 10 && j1 == 3 && cMap[i1][j1] == 'X')
				teshu = teshu + 15000;
			else if (i1 == 9 && j1 == 3)
				teshu = teshu + 3000;
			else if ((i1 == 9 || i1 == 8 || i1 == 10) && j1 == 4 && cMap[i1][j1] == 'X')
			{
				for (k1 = i1 - 1; k1 >= 1; k1--)
				{
					if (cMap[k1][j1] == '0')
						continue;
					else if (cMap[k1][j1] == 'X' && Judge(k1, j1, 10, dz) >= 3000)
					{
						flag = 1;
						break;
					}
					else
						break;
				}
				if (flag == 1)
					teshu = teshu - 5000;
				else
					teshu = teshu + 2000;
				if (cMap[10][4] == 'X')
					teshu = teshu + 5000;

			}
			else if (i1 == 8 && j1 == 3 && cMap[i1][j1] == 'X')
				teshu = teshu + 3500;
			else if (i1 == 9 && j1 == 2 && cMap[i1][j1] == 'X')
				teshu = teshu + 3500;
			else
				teshu = teshu - 2000;
		}
	}

	if (flag2 == 0 && cMap[i][j] == mchess[0])//����������Ӳ��ھ�����Χ���������߹�ȥ
	{
		sanyi1 = false;
		sanyi2 = false;
		sanyi3 = false;
		if (cMap[11][1] == 'l')
		{

			if (i1 == 10 && (j1 == 2 || j1 == 1 || j1 == 0))
			{
				teshu = teshu + 6000;
				sanyi1 = true;
			}
			if (i1 == 9 && j1 == 1)
			{
				teshu = teshu + 6000;
				sanyi1 = true;
			}
		}
		if (cMap[11][3] == 'l')
		{
			if (i1 == 10 && (j1 == 2 || j1 == 3 || j1 == 4))
			{
				teshu = teshu + 6000;
				sanyi1 = true;
			}
			if (i1 == 9 && j1 == 3)
			{
				teshu = teshu + 6000;
				sanyi1 = true;
			}
		}
		if (sanyi1 == false)
		{
			k1 = nextmove1(i1, j1, cmap, allmove1);
			for (k2 = 0; k2<k1; k2++)
			{
				if (cMap[11][1] == 'l')
				{
					if (allmove1[k2][0] == 10 && (allmove1[k2][1] == 2 || allmove1[k2][1] == 1 || allmove1[k2][1] == 0))
					{
						teshu = teshu + 5000;
						sanyi2 = true;
					}
					if (allmove1[k2][0] == 9 && allmove1[k2][1] == 1)
					{
						teshu = teshu + 5000;
						sanyi2 = true;
					}
				}

				if (cMap[11][3] == 'l')
				{
					if (allmove1[k2][0] == 10 && (allmove1[k2][1] == 2 || allmove1[k2][1] == 3 || allmove1[k2][1] == 4))
					{
						teshu = teshu + 4000;
						sanyi2 = true;
					}
					if (allmove1[k2][0] == 9 && allmove1[k2][1] == 3)
					{
						teshu = teshu + 4000;
						sanyi2 = true;
					}
				}
			}
			if (sanyi2 == false)
			{
				for (k2 = 0; k2<k1; k2++)
				{
					cmap[allmove1[k2][0]][allmove1[k2][1]] = cmap[i1][j1];
					cmap[i1][j1] = '0';
					k3 = nextmove1(allmove1[k2][0], allmove1[k2][1], cmap, allmove2);
					for (int k4 = 0; k4<k3; k4++)
					{
						if (cMap[11][1] == 'l')
						{
							if (allmove2[k4][0] == 10 && (allmove2[k4][1] == 2 || allmove2[k4][1] == 1 || allmove2[k4][1] == 0))
							{
								teshu = teshu + 4000;
								sanyi2 = true;
							}
							if (allmove2[k4][0] == 9 && allmove2[k4][1] == 1)
							{
								teshu = teshu + 4000;
								sanyi2 = true;
							}
						}
						if (cMap[11][3] == 'l')
						{
							if (allmove2[k4][0] == 10 && (allmove2[k4][1] == 2 || allmove2[k4][1] == 3 || allmove2[k4][1] == 4))
							{
								teshu = teshu + 4000;
								sanyi2 = true;
							}
							if (allmove2[k4][0] == 9 && allmove2[k4][1] == 3)
							{
								teshu = teshu + 4000;
								sanyi2 = true;
							}
						}
						cmap[i1][j1] = cmap[allmove1[k2][0]][allmove1[k2][1]];
						cmap[allmove1[k2][0]][allmove1[k2][1]] = '0';
					}
				}
			}

		}

	}

	//fprintf(fp, "\naaaa2 %d ", teshu);
	/***********����***************/
	int flage = 0, allmove3[200][2], allmove4[200][2], sanyi4 = false, sanyi5 = false, sanyi6 = false;
	char cmap3[12][5];
	for (i2 = 0; i2<12; i2++)
	{
		for (j2 = 0; j2<5; j2++)
			cmap3[i2][j2] = cMap[i2][j2];
	}
	cmap3[i1][j1] = cmap3[i][j];
	cmap3[i][j] = '0';
	if (cMap[i][j] == mchess[1])
	{

		if ((cMap[i1][j1] == 'X' && Judge(i1, j1, 10, dz) >= 3000)|| (cMap[i1][j1] == 'X'&& Judge(i1, j1, 0, dz) >= 5000))
			teshu = teshu - 5000;
		if (cMap[11][1] == 'l')
		{

			if (cMap[10][2] == mchess[1] || cMap[10][3] == mchess[1] || cMap[10][4] == mchess[1] || cMap[9][2] == mchess[1] || cMap[9][3] == mchess[1] || cMap[9][4] == mchess[1] || cMap[8][4] == mchess[1] || cMap[8][3] == mchess[1])
				flage = 1;		//�жϼ����ڶ��������Ƿ��ڿ����Ҳౣ�������λ�� 1�ڡ�0����
			if (i1 == 10 && j1 == 3 && cMap[i1][j1] == 'X'&&Judge(i1, j1, 0, dz) <= 5000 && Judge(i1, j1, 10, dz) <= 6000)
				teshu = teshu + 6000;
			else if (i1 == 10 && j1 == 4 && cMap[i1][j1] == 'X'&&Judge(i1, j1, 0, dz) <= 5000 && Judge(i1, j1, 10, dz) <= 6000)
				teshu = teshu + 3000;
			else if (i1 == 8 && j1 == 3 && cMap[i1][j1] == 'X'&&Judge(i1, j1, 0, dz) <= 5000 && Judge(i1, j1, 10, dz) <= 6000)
				teshu = teshu + 2200;
			else if (i1 == 8 && j1 == 4 && cMap[i1][j1] == 'X'&&Judge(i1, j1, 0, dz) <= 5000 && Judge(i1, j1, 10, dz) <= 6000)
				teshu = teshu + 2400;
			else if (i1 == 9 && j1 == 4 && cMap[i1][j1] == 'X'&&Judge(i1, j1, 0, dz) <= 5000 && Judge(i1, j1, 10, dz) <= 6000)
				teshu = teshu + 2500;
			else if (i1 == 9 && j1 == 2 && cMap[i1][j1] == 'X'&&Judge(i1, j1, 0, dz) <= 5000 && Judge(i1, j1, 10, dz) <= 6000)
				teshu = teshu + 2500;
			else if (i1 == 9 && j1 == 3 && Judge(i1, j1, 0, dz) <= 5000 && Judge(i1, j1, 10, dz) <= 6000)
				teshu = teshu + 2000;
			else
				teshu = teshu - 1000;
		}
		if (cMap[11][3] == 'l')
		{
			if (cMap[10][2] == mchess[1] || cMap[10][1] == mchess[1] || cMap[10][0] == mchess[1] || cMap[9][2] == mchess[1] || cMap[9][1] == mchess[1] || cMap[9][0] == mchess[1] || cMap[8][1] == mchess[1] || cMap[8][0] == mchess[1])
				flage = 1;
			else if (i1 == 10 && j1 == 1 && cMap[i1][j1] == 'X'&&Judge(i1, j1, 0, dz) <= 5000 && Judge(i1, j1, 10, dz) <= 6000)
				teshu = teshu + 6000;
			else if (i1 == 10 && j1 == 0 && cMap[i1][j1] == 'X'&&Judge(i1, j1, 0, dz) <= 5000 && Judge(i1, j1, 10, dz) <= 6000)
				teshu = teshu + 3000;
			else if (i1 == 9 && j1 == 1 && Judge(i1, j1, 0, dz) <= 5000 && Judge(i1, j1, 10, dz) <= 6000)
				teshu = teshu + 2000;
			else if (i1 == 8 && j1 == 1 && cMap[i1][j1] == 'X'&&Judge(i1, j1, 0, dz) <= 5000 && Judge(i1, j1, 10, dz) <= 6000)
				teshu = teshu + 2500;
			else if (i1 == 8 && j1 == 0 && cMap[i1][j1] == 'X'&&Judge(i1, j1, 0, dz) <= 5000 && Judge(i1, j1, 10, dz) <= 6000)
				teshu = teshu + 2400;
			else if (i1 == 9 && j1 == 0 && cMap[i1][j1] == 'X'&&Judge(i1, j1, 0, dz) <= 5000 && Judge(i1, j1, 10, dz) <= 6000)
				teshu = teshu + 2500;
			else if (i1 == 9 && j1 == 2 && cMap[i1][j1] == 'X'&&Judge(i1, j1, 0, dz) <= 5000 && Judge(i1, j1, 10, dz) <= 6000)
				teshu = teshu + 2500;
			else
				teshu = teshu - 1000;
		}

	}
	if (flage == 0 && cMap[i][j] == mchess[1])//�����ڶ������Ӳ��ھ�����Χ���������߹�ȥ
	{
		sanyi4 = false;
		sanyi5 = false;
		sanyi6 = false;
		if (cMap[11][1] == 'l')
		{

			if (i1 == 10 && (j1 == 3 || j1 == 4))
			{
				teshu = teshu + 5000;
				sanyi4 = true;
			}
			if (i1 == 9 && j1 == 3)
			{
				teshu = teshu + 5000;
				sanyi4 = true;
			}

		}
		if (cMap[11][3] == 'l')
		{
			if (i1 == 10 && (j1 == 1 || j1 == 0))
			{
				teshu = teshu + 5000;
				sanyi4 = true;
			}
			if (i1 == 9 && j1 == 1)
			{
				teshu = teshu + 5000;
				sanyi4 = true;
			}
		}
		if (sanyi4 == false)
		{
			k1 = nextmove1(i1, j1, cmap3, allmove3);
			for (k2 = 0; k2 < k1; k2++)
			{
				if (cMap[11][1] == 'l')
				{
					if (allmove3[k2][0] == 10 && (allmove3[k2][1] == 3 || allmove3[k2][1] == 4))
					{
						teshu = teshu + 4000;
						sanyi5 = true;
					}
					if (allmove3[k2][0] == 9 && allmove3[k2][1] == 3)
					{
						teshu = teshu + 4000;
						sanyi5 = true;
					}
				}

				if (cMap[11][3] == 'l')
				{
					if (allmove3[k2][0] == 10 && (allmove3[k2][1] == 1 || allmove3[k2][1] == 0))
					{
						teshu = teshu + 4000;
						sanyi5 = true;
					}
					if (allmove3[k2][0] == 9 && allmove3[k2][1] == 1)
					{
						teshu = teshu + 4000;
						sanyi5 = true;
					}
				}
			}
			if (sanyi5 == false)
			{
				for (k2 = 0; k2 < k1; k2++)
				{
					cmap3[allmove3[k2][0]][allmove3[k2][1]] = cmap3[i1][j1];
					cmap3[i1][j1] = '0';
					k3 = nextmove1(allmove3[k2][0], allmove3[k2][1], cmap3, allmove4);
					for (int k4 = 0; k4 < k3; k4++)
					{
						if (cMap[11][1] == 'l')
						{
							if (allmove4[k4][0] == 10 && (allmove4[k4][1] == 3 || allmove4[k4][1] == 4))
							{
								teshu = teshu + 3000;
								sanyi5 = true;
							}
							if (allmove4[k4][0] == 9 && allmove4[k4][1] == 3)
							{
								teshu = teshu + 3000;
								sanyi5 = true;
							}
						}
						if (cMap[11][3] == 'l')
						{
							if (allmove4[k4][0] == 10 && (allmove4[k4][1] == 1 || allmove4[k4][1] == 0))
							{
								teshu = teshu + 3000;
								sanyi5 = true;
							}
							if (allmove4[k4][0] == 9 && allmove4[k4][1] == 1)
							{
								teshu = teshu + 3000;
								sanyi5 = true;
							}
						}
						cmap3[i1][j1] = cmap3[allmove4[k2][0]][allmove4[k2][1]];
						cmap3[allmove4[k2][0]][allmove4[k2][1]] = '0';
					}
				}
			}

		}
	}
	/******************************/
	//fprintf(fp, "\naaaa3 %d ", teshu);
	fprintf(fp, "\n Ina_step[0] %d Ina_step[1]%d ", Ina_step[0], Ina_step[1]);
	//��ʮһ��
	if (Ina_step[0] == 2 && Ina_step[1]>12 && Ina_step[1] <= 18)
	{
		if (cMap[i][j] >= 'e' && cMap[i][j]<'i')
		{
			k1 = nextmove1(i1, j1, cmap, allmove1);	//�ж������ϣ��������ڹ���С���ó��������ܷ�������֮�����ӣ�
			for (k2 = 0; k2<k1; k2++)
			{
				if (cmap[allmove1[k2][0]][allmove1[k2][1]] >= 'A' && cmap[allmove1[k2][0]][allmove1[k2][1]] <= 'X')
					flag = 1;
			}
		}
		if (cMap[i1][j1] >= 'A' && cMap[i1][j1] <= 'X')
		{
			if (!IsMoveCamp(i, j) && cMap[i][j] >= 'e' && cMap[i][j]<'i')//����������Ӫ��С���ó������ų������ӡ����ӵķ�ֵ���
			{
				sanyif = 30000;
				sanyif = sanyif + (cMap[i][j] - 'a') * 10;
				sanyi1 = true;
			}
			else if (cMap[i][j] == mchess[0])//����������������ʮһ��������������Ӳ�������ʮһ��
			{
				sanyif = 0;
				sanyi1 = false;
			}
			else if (cMap[i][j] == 'i')
			{
				if (walei(cMap, dz))//�жϹ����Ƿ���Ҫ���ף�����Ҫ�򣬽��С���ʮһ��
				{
					sanyi1 = true;
					sanyif = 40000;                     //////////////////////////////////////////
														//sanyif=sanyif+(cMap[i][j]-'a')*10;
				}
				else
				{
					sanyif = 0;
					sanyi1 = false;
				}
			}
			else if (IsMoveCamp(i, j) && weixie(i, j, i1, j1, dz, cMap)<0)//��������Ӫ������	cMap[i][j]<'d'
			{
				sanyif = 20000;
				sanyif = sanyif + (cMap[i][j] - 'a') * 10;
				sanyi1 = false;
			}
			else if (cMap[i][j] == 'k')//��������ӪС���ó�������	cMap[i][j]<'d'
			{
				sanyif = 20000;
				sanyif = sanyif + (cMap[i][j] - 'a') * 10;
				sanyi1 = false;
			}
			else//���������ų�������
			{
				sanyi1 = true;
				sanyif = 28000;
				if (Judge(i1, j1, 9, dz)>4000)
				{
					sanyif = 20000;
					sanyi1 = false;
				}
				sanyif = sanyif + (cMap[i][j] - 'a') * 10;

			}
			//
		}
		if (sanyi1 == false)//�ڶ�����������
		{
			k1 = nextmove1(i1, j1, cmap, allmove1);
			for (k2 = 0; k2<k1; k2++)
				if (cmap[allmove1[k2][0]][allmove1[k2][1]] >= 'A' && cmap[allmove1[k2][0]][allmove1[k2][1]] <= 'X')
				{
					sanyi2 = true;
					if (cMap[i][j] == mchess[0])//����������������ʮһ��������������Ӳ�������ʮһ��
					{
						sanyif = 0;
						sanyi2 = false;
					}
					else if (cMap[i][j] == 'i')
					{
						if (walei(cMap, dz))//�жϹ����Ƿ���Ҫ���ף�����Ҫ�򣬽��С���ʮһ��
						{
							sanyif = 28000;                   ///////////////////////////////
															  //sanyif=sanyif+(cMap[i][j]-'a')*10;
						}
						else
							sanyif = 0;
					}
					else if (cMap[i][j] == 'k')
					{
						sanyif = 15000;
						sanyif = sanyif + (cMap[i][j] - 'a') * 10;
					}
					else if (cMap[i][j] >= 'e' && cMap[i][j]<'i')
					{
						sanyif = 25000;
						sanyif = sanyif + (cMap[i][j] - 'a') * 10;
					}
					else//���������ų�������
					{
						sanyif = 23000;
						if (Judge(allmove1[k2][0], allmove1[k2][1], 9, dz)>4000)
						{
							sanyif = 15000;
							sanyi2 = false;
						}
						sanyif = sanyif + (cMap[i][j] - 'a') * 10;
					}

				}
			if (sanyi2 == false && flag == 0)				//������������
			{
				for (k2 = 0; k2<k1; k2++)
				{
					cmap[allmove1[k2][0]][allmove1[k2][1]] = cmap[i1][j1];
					cmap[i1][j1] = '0';
					k3 = nextmove1(allmove1[k2][0], allmove1[k2][1], cmap, allmove2);
					for (int k4 = 0; k4<k3; k4++)
						if (cmap[allmove2[k4][0]][allmove2[k4][1]] >= 'A' && cmap[allmove2[k4][0]][allmove2[k4][1]] <= 'X')
						{
							if (cMap[i][j] >= 'e' && cMap[i][j]<'i')
							{
								sanyif = 20000;
								sanyif = sanyif + (cMap[i][j] - 'a') * 10;
							}
							else if (cMap[i][j] == mchess[0])
								sanyif = 0;
							else if (cMap[i][j] == 'i')
							{
								if (walei(cMap, dz))//�жϹ����Ƿ���Ҫ���ף�����Ҫ����С���ʮһ��
								{
									sanyif = 22000;                  //////////////////////////////////////
									sanyif = sanyif + (cMap[i][j] - 'a') * 10;
								}
								else
									sanyif = 0;
							}
							else
							{
								sanyif = 13000;
								sanyif = sanyif + (cMap[i][j] - 'a') * 10;
							}
							sanyi3 = true;

						}
					cmap[i1][j1] = cmap[allmove1[k2][0]][allmove1[k2][1]];
					cmap[allmove1[k2][0]][allmove1[k2][1]] = '0';
				}
			}
		}
		if (NumChess(cMap) < 8 && NumOppChess(cMap) < 8)
			if (cMap[i][j] == 'k')
				sanyif = sanyif + 20000;
		score1 = sanyif + teshu;
	}
	//fprintf(fp, "\naaaa4 %d ", teshu);
	if (Ina_step[0] == 2 && Ina_step[1]>18)
	{
		k1 = nextmove1(i1, j1, cmap, allmove1);
		for (k2 = 0; k2<k1; k2++)
		{
			if ((allmove1[k2][1] == 0 || allmove1[k2][1] == 4) && (allmove1[k2][0]>0 && allmove1[k2][0]<11))
				sanyif = 25000;
		}
		if (i1>0 && i1<11 && (j1 == 0 || j1 == 4))
			sanyif = 35000;
		if ((j == 0 || j == 4) && (i>0 && i<11))
		{
			if (i1 == 1 && (j1 == 0 || j1 == 4))
				sanyif = 45000;
		}

		if (cMap[i1][j1] == 'X')
		{
			sanyif = 60000;
			if (Judge(i1, j1, 9, dz)>3000)
				sanyif = sanyif - 10000;
		}
		if (((i1 == 1 && (j1 == 1 || j1 == 3)) || (i1 == 0 && (j1 == 0 || j1 == 4))) && Judge(i1, j1, 9, dz)<50)
			sanyif = 55000;
		if (cMap[i][j] == 'k')
			sanyif = sanyif - 1000;
		if ((Judge(1, 1, 9, dz)<50 || Judge(0, 0, 9, dz)<50) && j1 == 0)
			sanyif = sanyif + 500;
		if ((Judge(1, 3, 9, dz)<50 || Judge(0, 4, 9, dz)<50) && j1 == 4)
			sanyif = sanyif + 500;
		if (cMap[0][1] == 'L' && i1 == 1 && j1 == 1)
			sanyif = sanyif + 2000;
		if (cMap[0][3] == 'L' && i1 == 1 && j1 == 3)
			sanyif = sanyif + 2000;
		if (cMap[i][j]>mchess[0] && cMap[i][j]<'j')
			sanyif = sanyif + (cMap[i][j] - 'a') * 10;
		if (NumChess(cMap) < 8 && NumOppChess(cMap) < 8)
			if (cMap[i][j] == 'k')
				sanyif = sanyif + 20000;
		score1 = sanyif + teshu;
	}

	if (Ina_step[0] == 1 && Ina_step[1]>12) //�з�����ʮһ�����ж���
	{
		if (cMap[i][j] != mchess[0] && cMap[i1][j1] != 'X')
		{
			for (int m = 0; m<12; m++)
			{
				for (int n = 0; n<5; n++)
				{
					if (Judge(m, n, 9, dz)<5000)
					{
						k1 = Oppnextmove(m, n, cMap, allmove1);
						for (k2 = 0; k2<k1; k2++)
						{
							if (allmove1[k2][0] == i && allmove1[k2][1] == j)
								sanyi1 = true;
						}
					}
				}
			}
			for (int m = 0; m<12; m++)
			{
				for (int n = 0; n<5; n++)
				{
					if (Judge(m, n, 9, dz)<5000)
					{
						k1 = Oppnextmove(m, n, cmap, allmove1);
						for (k2 = 0; k2<k1; k2++)
						{
							if (allmove1[k2][0] == i1 && allmove1[k2][1] == j1)
								sanyi2 = true;
						}
					}
				}
			}
			if (sanyi1 == false && sanyi2 == false)
			{
				if (IsMoveCamp(i1, j1) == 1)
					sanyif = 4000;
				else
					sanyif = 3000;
			}
		}
	}
	//fprintf(fp, "\naaaa5 %d ", teshu);
	jushipg(cMap, dz);    //�ı����̵ķ�ֵ


						  //2.��ֹ����������
	if (cMap[i1][j1] == 'X' && i1<2)                ///////////////////////////////
	{
		if (Ina_step[0] == 2 && Ina_step[1] > 12)  //��ִ��31��
		{
			if (cMap[i][j] < 'e' && Judge(i1, j1, 9, dz)>4000)
				teshu = teshu - 4000;       ///////////////////////////
			if ((cMap[i][j] == 'f' || cMap[i][j] == 'g' || cMap[i][j] == 'h') && Judge(i1, j1, 9, dz) > 4000)
				teshu = teshu - 2000;
		}
		else
		{
			if (cMap[i][j] < 'e' && Judge(i1, j1, 9, dz)>4000)
				teshu = teshu - 6000;       ///////////////////////////
			if ((cMap[i][j] == 'f' || cMap[i][j] == 'g' || cMap[i][j] == 'h') && Judge(i1, j1, 9, dz) > 4000)
				teshu = teshu - 5000;
		}
	}

	//fprintf(fp, "\naaaa6 %d ", teshu);
	//��Ӫ�����ез����ӣ�������Ӫ
	if (IsMoveCamp(i, j) && (cMap[i + 1][j] == 'X' || cMap[i + 1][j + 1] == 'X' || cMap[i + 1][j - 1] == 'X' || cMap[i][j + 1] == 'X' || cMap[i][j - 1] == 'X' || cMap[i - 1][j - 1] == 'X' || cMap[i - 1][j] == 'X' || cMap[i - 1][j + 1] == 'X'))
	{
		if (i == 9 && (j == 1 || j == 3) && cMap[i1][j1] == '0')
			teshu = teshu - 2000;
		else if (i == 8 && j == 2)
			teshu = teshu - 3000;
		else if (cMap[i][j]>'d' && cMap[i1][j1] == 'X')
			teshu = teshu - 2000;
		else if (cMap[i][j] <= 'd' && cMap[i1][j1] == 'X')
			teshu = teshu + 2500;
		else
			teshu = teshu - 1500;
	}
	//fprintf(fp, "\naaaa7 %d ", teshu);
	//����Ӫ�����ез����ӣ���ռ��Ӫ
	if (IsMoveCamp(i1, j1) && (cMap[i1 + 1][j1] == 'X' || cMap[i1 + 1][j1 + 1] == 'X' || cMap[i1 + 1][j1 - 1] == 'X' || cMap[i1][j1 + 1] == 'X' || cMap[i1][j1 - 1] == 'X' || cMap[i1 - 1][j1 - 1] == 'X' || cMap[i1 - 1][j1] == 'X' || cMap[i1 - 1][j1 + 1] == 'X'))
	{
		teshu = teshu + 5000;
	}
	//fprintf(fp, "\naaaa8 %d ", teshu);
	int flag3 = 0, flag4 = 0;
	//3.ը��������ʹ��
	if (cMap[i][j] == 'k')
	{
		/*	if(IsMoveCamp(i,j)!=1 && IsMoveCamp(i1,j1)==1)  //ը������Ӫ
		teshu=teshu+2000;
		if(IsMoveCamp(i,j) && cMap[i1][j1]=='0')  //����ը��
		teshu=teshu-2000;*/
		///ʹ����������ʦ������������ը����
		for (i2 = 0; i2<12; i2++)  // �Ҽ���ը������Ŀ
		{
			for (j2 = 0; j2<5; j2++)
				if (cMap[i2][j2] == 'k')
					zha++;
		}
		//mychessdx(cMap,mchess);   //���ҷŵ����ӵ��������մӴ�С����
		int f = 0;
		for (int m = 0; m<25; m++)  //�жϵз�˾��;����Ƿ�����
		{
			if (dz[m][0] >= 8000 && dz[m][12]>12)
				f++;
			if (dz[m][1] >= 8000 && dz[m][12]>13)
				f++;
		}
		if (zha == 2)
		{
			if (f == 2)//�з�������˾��ȫ������
				if (Judge(i1, j1, 2, dz) + Judge(i1, j1, 1, dz) + Judge(i1, j1, 0, dz) + Judge(i1, j1, 3, dz) >= 9000)  //ը����˾�������ʦ��
					teshu = teshu + 9000;
			if (f == 1 || f == 0)//�з�������˾������һ��
				if (Judge(i1, j1, 2, dz) + Judge(i1, j1, 1, dz) + Judge(i1, j1, 0, dz) >= 9000)  //ը����˾�������ʦ��
					teshu = teshu + 9000;
		}
		if (zha == 1)
		{
			if (Judge(i1, j1, 1, dz) + Judge(i1, j1, 0, dz) + Judge(i1, j1, 2, dz) >= 9000)  //ը����˾�������ʦ��
				teshu = teshu + 9000;
		}
		flag = 0;
		flag1 = 0;
		int k4;
		if (cMap[i1][j1] == '0')
		{
			for (int m = 0; m<12; m++)
			{
				for (int n = 0; n<5; n++)
				{
					if (cMap[m][n] == 'X' && Judge(m, n, 1, dz) + Judge(m, n, 0, dz) + Judge(m, n, 2, dz)<9000)
					{
						k1 = Oppnextmove(m, n, cmap, allmove1);
						for (k2 = 0; k2<k1; k2++)
						{
							if (allmove1[k2][0] == i1 && allmove1[k2][1] == j1)
								flag3 = 1;
						}
					}
				}
			}
			k1 = nextmove1(i1, j1, cmap, allmove1);//�жϼ��������ܷ����������
			for (k2 = 0; k2<k1; k2++)
			{
				if (Judge(allmove1[k2][0], allmove1[k2][1], 1, dz) + Judge(allmove1[k2][0], allmove1[k2][1], 0, dz) + Judge(allmove1[k2][0], allmove1[k2][1], 2, dz) >= 7000)
					flag4 = 1;
			}
			if (flag3 == 0 && flag4 == 1)
				teshu = teshu + 3000;
		}
		flag = 0;
		flag1 = 0;
		for (int m = 0; m<12; m++)
		{
			for (int n = 0; n<5; n++)
			{
				k1 = Oppnextmove(m, n, cMap, allmove1);
				for (k2 = 0; k2<k1; k2++)
				{
					if (allmove1[k2][0] == i && allmove1[k2][1] == j)
						flag = 1;
				}
			}
		}
		for (int m = 0; m<12; m++)
		{
			for (int n = 0; n<5; n++)
			{
				k1 = Oppnextmove(m, n, cmap, allmove1);
				for (k2 = 0; k2<k1; k2++)
				{
					if (allmove1[k2][0] == i1 && allmove1[k2][1] == j1)
						flag1 = 1;
				}
			}
		}
		if (flag == 1 && flag1 == 0)
			teshu = teshu + 1000;
		else
			teshu = teshu - 1000;

	}
	for (i3 = 0; i3<12; i3++)
	{
		for (j3 = 0; j3<5; j3++)
			if (cMap[i3][j3] == 'c')
				x++;
	}
	for (i2 = 0; i2<12; i2++)  // �Ҽ���ը������Ŀ
	{
		for (j2 = 0; j2<5; j2++)
			if (cMap[i2][j2] == 'k')
				zha++;
	}
	//����ʦ��������ը������
	if (cMap[i][j] == 'c' && (x == 2 || x == 1))
	{
		for (i3 = 0; i3<12; i3++)
		{
			for (j3 = 0; j3<5; j3++)
			{
				if (cMap[i3][j3] == 'k')
				{
					k1 = nextmove1(i3, j3, cMap, allmove1);
					for (k2 = 0; k2<k1; k2++)
					{
						if (allmove1[k2][0] == i1 && allmove1[k2][1] == j1)
						{
							if (cMap[i1][j1] == 'X')
								teshu = teshu - 100;
							else if (((j != 0 && j1 == 0) || (j != 4 && j1 == 4)) && cMap[i1][j1] != 'X')
								teshu = teshu + 500;
							else if (((j == 0 && j1 == 0) || (j == 4 && j1 == 4)) && cMap[i1][j1] != 'X')
								teshu = teshu + 1000;
							else
								teshu = teshu + 200;
						}

					}

				}
			}
		}
	}
	if (cMap[i][j] == 'd' && (x == 1 || x == 0))      //�ó���
	{
		for (i3 = 0; i3<12; i3++)
		{
			for (j3 = 0; j3<5; j3++)
			{
				if (cMap[i3][j3] == 'k')
				{
					k1 = nextmove1(i3, j3, cMap, allmove1);
					for (k2 = 0; k2<k1; k2++)
					{
						if (allmove1[k2][0] == i1 && allmove1[k2][1] == j1)
						{
							if (cMap[i1][j1] == 'X')
								teshu = teshu - 100;
							else if (((j != 0 && j1 == 0) || (j != 4 && j1 == 4)) && cMap[i1][j1] != 'X')
								teshu = teshu + 500;
							else if (((j == 0 && j1 == 0) || (j == 4 && j1 == 4)) && cMap[i1][j1] != 'X')
								teshu = teshu + 1000;
							else
								teshu = teshu + 200;
						}
					}

				}
			}
		}
	}
	//fprintf(fp, "\naaaa9 %d ", teshu);
	/************************************************************/
	/************************************************************/
	//����С�Ӷ���
	/*if (cMap[i][j] >= 'd')
	{
		int ff, difang = 0, xa, ya, zonghe = 0, jl, ui, uj, iaa, ibb, fi, opkk, opll[200][2], opf, fl22 = 0, fx, fens = 0;
		for (xa = 0; xa < 12; xa++)
			for (ya = 0; ya < 5; ya++)
			{
				if (cMap[xa][ya] != '0')
					zonghe++;
				if (cMap[xa][ya] == 'X')
					difang++;
			}
		for (ui = 0; ui < 12; ui++)
			for (uj = 0; uj < 5; uj++)
				if (cMap[ui][uj] == 'X')
				{
					fens = 0;
					fi = cMap[i][j] - 'a';
					for (fx = 0; fx <= fi; fx++)
						fens = fens + Judge(ui, uj, fx, dz);
					if (fens > 6000)
						opf = Oppnextmove(ui, uj, cMap, opll); //�з���һ��ģ��
					for (opkk = 0; opkk < opf; opkk++)
					{
						if (opll[opkk][0] == i1 && opll[opkk][1] == j1)   // �з���һ���Ƿ��������ҷ�ը����һ��
							fl22 = 1;
					}
				}
		if (fl22 == 0)
		{
			if (zonghe <= 40 && difang <= 20 && cMap[i][j] >= 'c')
			{
				if (cMap[0][1] == 'L')
				{
					if (cMap[i1][j1] == '0'&&i1 == 0 && j1 == 0)
					{
						teshu = teshu + 4000;
					}
					if (cMap[i1][j1] == '0'&&i1 == 0 && j1 == 2)
					{
						teshu = teshu + 4000;
					}
					if (cMap[i1][j1] == '0'&&i1 == 1 && j1 == 1)
					{
						teshu = teshu + 4000;
					}
					if (cMap[i1][j1] == '0'&&i1 == 1 && j1 == 0 && (cMap[0][0] == '0' || cMap[1][1] == '0'))
					{
						teshu = teshu + 3000;
					}
					if (cMap[i1][j1] == '0'&&i1 == 1 && j1 == 2 && (cMap[0][2] == '0'))
					{
						teshu = teshu + 3000;
					}
				}
				if (cMap[0][3] == 'L')
				{
					if (cMap[i1][j1] == '0'&&i1 == 0 && j1 == 2)
					{
						teshu = teshu + 4000;
					}
					if (cMap[i1][j1] == '0'&&i1 == 0 && j1 == 4)
					{
						teshu = teshu + 4000;
					}
					if (cMap[i1][j1] == '0'&&i1 == 1 && j1 == 3)
					{
						teshu = teshu + 4000;
					}
					if (cMap[i1][j1] == '0'&&i1 == 1 && j1 == 2 && (cMap[0][2] == '0'))
					{
						teshu = teshu + 3000;
					}
					if (cMap[i1][j1] == '0'&&i1 == 1 && j1 == 4 && (cMap[0][4] == '0' || cMap[1][3] == '0'))
					{
						teshu = teshu + 8000;
					}
				}
			}
		}
	}
	fprintf(fp, "\naaaa10 %d ", teshu);
	*/

	//����ը���÷�:ը��׷��ϵͳ
	if (cMap[i][j] == 'k')
	{
		int xa, ya, difang = 0, zonghe = 0, d, q, u, allmove5[200][2], allmove4[200][2], data = 0, allmove3[200][2];
		int iq, opl1[200][2], im, opk, op = 0, almove[200][2], al, ak, fl1 = 0, ia, ib, fl2 = 0, fl3 = 1, fl4 = 0;
		int pl1 = 0;
		char cmapa[12][5], in, jn, cmap2[12][5];
		for (d = 0; d < 12; d++)
			for (q = 0; q < 5; q++)
			{
				if (cMap[d][q] == 'X'&&Judge(d, q, 2, dz) + Judge(d, q, 1, dz) + Judge(d, q, 0, dz) < 6000)
				{
					u = Oppnextmove(d, q, cMap, allmove5);
				}
			}

		for (xa = 0; xa < 12; xa++)
			for (ya = 0; ya < 5; ya++)
			{
				if (cMap[xa][ya] != '0')
					zonghe++;
				if (cMap[xa][ya] == 'X')
					difang++;
			}

		for (in = 0; in < 12; in++)
			for (jn = 0; jn < 5; jn++)
			{
				cmapa[in][jn] = cMap[in][jn];
			}
		cmapa[i1][j1] = cmapa[i][j];
		cmapa[i][j] = '0';
		if (zonghe > 15)
		{
			if (IsMoveCamp(i, j) != 1 && IsMoveCamp(i1, j1) == 1)
				teshu = teshu + 5000;
			//	if(IsMoveCamp(i,j)!=1 && IsMoveCamp(i1,j1)==1&&allmove5[u][0]==i&&allmove5[u][1]==j)  //ը������Ӫ
			//		teshu=teshu+6000;
			for (k1 = 0; k1 < 12; k1++)
				for (k2 = 0; k2 < 5; k2++)
					cmap2[k1][k2] = cMap[k1][k2];
			cmap2[i1][j1] = cmap2[i][j];
			cmap2[i][j] = '0';
			k1 = nextmove1(i1, j1, cmap2, allmove3);
			for (k2 = 0; k2 < k1; k2++)
				if ((IsMoveCamp(i1, j1) != 1) && (IsMoveCamp(allmove3[k2][0], allmove3[k2][1]) == 1) && (allmove5[u][0] != allmove3[k2][0]) && (allmove5[u][1] != allmove3[k2][1]))
					teshu = teshu + 3000;
			if (IsMoveCamp(i, j) || (Judge(i1, j1, 2, dz) + Judge(i1, j1, 1, dz) + Judge(i1, j1, 0, dz) < 8000) && cMap[i1][j1] == 'X')  //����ը��
				teshu = teshu - 5000;
			for (iq = 0; iq <= tra - 1; iq++)//һ��׷��
				if ((i1 == dz[track[iq]][12]) && (j1 == dz[track[iq]][13]))
				{
					teshu = teshu + 22000;
					fl1 = 1;
					break;
				}
			if (fl1 == 0)  //�޷�һ��׷�٣�����ģ�⣬����׷��
			{
				al = nextmove1(i1, j1, cmapa, almove); //�ҷ��ڶ���ģ��
				for (ia = 0; ia < 12; ia++)
					for (ib = 0; ib < 5; ib++)
						if (cMap[ia][ib] == 'X')
						{
							fl3 = 0;
							for (im = 0; im <= tra - 1; im++)
								if ((ia == dz[track[im]][12]) && (ib == dz[track[im]][13]))
								{
									fl3 = 1;
								}
							if (fl3 == 0)
							{
								op = Oppnextmove(ia, ib, cmapa, opl1); //�з���һ��ģ��
								for (opk = 0; opk < op; opk++)
								{
									if (opl1[opk][0] == i1 && opl1[opk][1] == j1)   // �з���һ���Ƿ��������ҷ�ը����һ��
										fl2 = 1;
								}
							}
						}

				if (fl2 == 0)
				{
					for (ak = 0; ak < al; ak++)
						for (iq = 0; iq <= tra - 1; iq++)//һ��׷��
							if ((almove[ak][0] == dz[track[iq]][12]) && (almove[ak][1] == dz[track[iq]][13]))
							{
								teshu = teshu + 9000;
								fl4 = 1;
							}

				}
				//ը����Ӫ
				//****************************************
				//****************************************
				/*if (fl1 == 0 && fl4 == 0)
				{
				if (IsMoveCamp(i, j) != 1 && IsMoveCamp(i1, j1) == 1)  //ը��һ������Ӫ
				{
				teshu = teshu + 3000;
				pl1 = 1;
				}
				if (pl1 == 0&&IsMoveCamp(i, j) != 1)//ը��ģ��������Ӫ
				for (in = 0; in < 12; in++)
				for (jn = 0; jn < 5; jn++)
				{
				cmapa[in][jn] = cMap[in][jn];
				}
				cmapa[i1][j1] = cmapa[i][j];
				cmapa[i][j] = '0';
				al = nextmove1(i1, j1, cmapa, almove);
				for (ia = 0; ia < 12; ia++)
				for (ib = 0; ib < 5; ib++)
				if (cMap[ia][ib] == 'X')
				{
				fl3 = 0;
				for (i = 0; i <= tra - 1; i++)
				if ((ia != dz[track[i]][12]) && (ib != dz[track[i]][13]))
				{
				fl3 = 1;
				}
				if (fl3 == 1)
				op = op + Oppnextmove(ia, ib, cmapa, opl1); //�з���һ��ģ��
				}
				for (opk = 0; opk < op; opk++)
				{
				if (opl1[opk][0] == i1&&opl1[opk][1] == j1)   // �з���һ���Ƿ��������ҷ�ը����һ��
				fl2 = 1;
				}
				if (fl2 == 0)
				{
				for (ak = 0; ak < al; ak++)
				if (IsMoveCamp(almove[ak][0], almove[ak][1]) == 1)
				{
				teshu = teshu + 6000;
				}
				}
				}*/

			}
		}
		else
		{
			for (k1 = 0; k1 < 12; k1++)
				for (k2 = 0; k2 < 5; k2++)
					cmap1[k1][k2] = cMap[k1][k2];
			cmap1[i1][j1] = cmap1[i][j];
			cmap1[i][j] = '0';
			if (cMap[i1][j1] == 'X' && (Judge(i1, j1, 2, dz) + Judge(i1, j1, 1, dz) + Judge(i1, j1, 0, dz) + Judge(i1, j1, 3, dz) + Judge(i1, j1, 4, dz) >= 8000))
			{
				data = 1;
				teshu = teshu + 22000;
			}
			else
			{
				/*	if(cMap[i1][j1]=='X'&&(Judge(i1,j1,2,dz)+Judge(i1,j1,1,dz)+Judge(i1,j1,0,dz)<7000))
				teshu=teshu-1000;*/
				if (data == 0)
				{
					k1 = nextmove1(i1, j1, cmap1, allmove4);
					for (k2 = 0; k2 < k1; k2++)
					{
						if (cmap1[allmove4[k2][0]][allmove4[k2][1]] == 'X' && (Judge(allmove4[k2][0], allmove4[k2][1], 3, dz) + Judge(allmove4[k2][0], allmove4[k2][1], 4, dz) + Judge(allmove4[k2][0], allmove4[k2][1], 2, dz) + Judge(allmove4[k2][0], allmove4[k2][1], 1, dz) + Judge(allmove4[k2][0], allmove4[k2][1], 0, dz) >= 8000) && (allmove5[u][0] != i1) && (allmove5[u][1] != j1))
							teshu = teshu + 9000;
						else
						{
							if (IsMoveCamp(i, j) != 1 && IsMoveCamp(i1, j1) == 1)  //ը������Ӫ
								teshu = teshu + 5000;
							for (k1 = 0; k1 < 12; k1++)
								for (k2 = 0; k2 < 5; k2++)
									cmap2[k1][k2] = cMap[k1][k2];
							cmap2[i1][j1] = cmap2[i][j];
							cmap2[i][j] = '0';
							k1 = nextmove1(i1, j1, cmap2, allmove3);
							for (k2 = 0; k2 < k1; k2++)
								if ((IsMoveCamp(i1, j1) != 1) && (IsMoveCamp(allmove3[k2][0], allmove3[k2][1]) == 1) && (allmove5[u][0] != allmove3[k2][0]) && (allmove5[u][1] != allmove3[k2][1]))
									teshu = teshu + 1000;
							if (IsMoveCamp(i, j) || (Judge(i1, j1, 2, dz) + Judge(i1, j1, 1, dz) + Judge(i1, j1, 0, dz) < 8000) && cMap[i1][j1] == 'X')  //����ը��
								teshu = teshu - 2000;
						}

					}
				}
			}

		}
	}
	//fprintf(fp, "\naaaa11 %d ", teshu);
	/************************************************************/
	/************************************************************/

	//4.��������(����������)		/////////////////////////////////////////////
	flag = 0;
	flag1 = 0;
	flag3 = 0;
	flag4 = 0;
	sanyi1 = false;
	if (cMap[i][j] == 'i')
	{
		flag = walei(cMap, dz);
		if (flag == 0)
		{
			if (Judge(i1, j1, 9, dz) > 4500)   //�����ڵ���
			{
				sanyi1 = true;
				teshu = teshu + 4000;
			}
			if (sanyi1 == false && cMap[i1][j1] == '0')
			{
				for (int m = 0; m < 12; m++)
				{
					for (int n = 0; n < 5; n++)
					{
						k1 = Oppnextmove(m, n, cmap, allmove1);
						for (k2 = 0; k2 < k1; k2++)
						{
							if (allmove1[k2][0] == i1 && allmove1[k2][1] == j1)
								flag3 = 1;
						}
					}
				}
				k1 = nextmove1(i1, j1, cmap, allmove1);
				for (k2 = 0; k2 < k1; k2++)
				{
					if (Judge(allmove1[k2][0], allmove1[k2][1], 9, dz) > 4500)
						flag4 = 1;
				}
				if (flag3 == 0 && flag4 == 1)
					teshu = teshu + 2000;
			}
		}
		if (flag == 1)
		{
			if (Judge(i1, j1, 10, dz) >= 4000)   //������ը��
			{
				sanyi1 = true;
				teshu = teshu + 4000;
			}
			if (sanyi1 == false && cMap[i1][j1] == '0')//һ����������ģ����������
			{
				for (int m = 0; m < 12; m++)
				{
					for (int n = 0; n < 5; n++)
					{
						k1 = Oppnextmove(m, n, cmap, allmove1);
						for (k2 = 0; k2 < k1; k2++)
						{
							if (allmove1[k2][0] == i1 && allmove1[k2][1] == j1)
								flag3 = 1;
						}
					}
				}
				k1 = nextmove1(i1, j1, cmap, allmove1);
				for (k2 = 0; k2 < k1; k2++)
				{
					if (Judge(allmove1[k2][0], allmove1[k2][1], 10, dz) >= 4000)
						flag4 = 1;
				}
				if (flag3 == 0 && flag4 == 1)
					teshu = teshu + 2000;
				if (flag3 == 0)
					teshu = teshu + 2000;
			}
		}
		//���������з�����
		flag = 0;
		for (int m = 0; m < 12; m++)
		{
			for (int n = 0; n < 5; n++)
			{
				k1 = Oppnextmove(m, n, cMap, allmove1);
				for (k2 = 0; k2 < k1; k2++)
				{
					if (allmove1[k2][0] == i && allmove1[k2][1] == j)
						flag = 1;
				}
			}
		}
		for (int m = 0; m < 12; m++)
		{
			for (int n = 0; n < 5; n++)
			{
				k1 = Oppnextmove(m, n, cmap, allmove1);
				for (k2 = 0; k2 < k1; k2++)
				{
					if (allmove1[k2][0] == i1 && allmove1[k2][1] == j1)
						flag1 = 1;
				}
			}
		}
		if (flag == 1 && flag1 == 0)
			teshu = teshu + 1000;
		else
			teshu = teshu - 1000;
		if (IsMoveCamp(i1, j1))
			teshu = teshu + 300;

		//����������������
		if (NumChess(cMap) < 15 && NumOppChess(cMap) < 15)             //��ɱʽ����
		{
			/*char cmap10[12][5];
			for (i2 = 0; i2 < 12; i2++)
			for (j2 = 0; j2 < 5; j2++)
			cmap10[i2][j2] == cMap[i2][j2];
			cmap10[i1][j1] = cmap10[i][j];
			cmap10[i][j] = '0';*/
			FILE *fp;
			fp = fopen("1", "a");
			//fprintf(fp, "\nwwww");
			//fprintf(fp, "\nwwww  %d", Judge(i1, j1, 9, dz));

			int f = 1, f21 = 0, f22 = 0, f23 = 0;
			//fprintf(fp, "\nwwww5  %c %c %c", cMap[9][1], cMap[9][3], mchess[0]);
			if (Judge(i1, j1, 9, dz) > 4000)
				if (cMap[9][1] == mchess[0] || cMap[9][3] == mchess[0])    //�������ؾ���
				{
					teshu = teshu + 20000;
					f = 0;
					//fprintf(fp, "\nwwww1");

				}
			if (cMap[9][1] == mchess[0] || cMap[9][3] == mchess[0])          //�������ؾ���
				if (f == 1)
				{
					//fprintf(fp, "\nwwww22 ");
					k2 = nextmove1(i1, j1, cmap, allmove1);
					//fprintf(fp, "\nwwww33 %d ", k2);
					for (k1 = 0; k1 < k2; k1++)
					{
						//fprintf(fp, "\nwwww22  %d %d %d", allmove1[k1][0], allmove1[k1][1], Judge(allmove1[k1][0], allmove1[k1][1], 9, dz));
						if (Judge(allmove1[k1][0], allmove1[k1][1], 9, dz) > 4000)
						{
							if (f21 == 0)
							{
								teshu = teshu + 10000;
								f21++;
								//fprintf(fp, "\nwww2  %d %d", allmove1[k1][0], allmove1[k1][1]);
							}

						}
					}
				}
			fclose(fp);
		}
	}
	sanyi1 = false;
	flag3 = 0;
	flag = 0;
	if (cMap[i][j]>'e' && cMap[i][j]<'i')
	{
		if (Judge(i1, j1, 10, dz) >= 4000)   //С��������ը��
		{
			sanyi1 = true;
			teshu = teshu + 4000;
		}
		if (sanyi1 == false && cMap[i1][j1] == '0')//һ����������ģ����������
		{
			/*	for(int m=0;m<12;m++)
			{
			for(int n=0;n<5;n++)
			{
			if(weixie(i,j,m,n,dz,cMap)<0)
			{
			k1=Oppnextmove(m,n,cmap,allmove1);
			for(k2=0;k2<k1;k2++)
			{
			if(allmove1[k2][0]==i1 && allmove1[k2][1]==j1)
			flag3=1;
			}
			}
			}
			}*/
			k1 = nextmove1(i1, j1, cmap, allmove1);
			for (k2 = 0; k2<k1; k2++)
			{
				if (Judge(allmove1[k2][0], allmove1[k2][1], 10, dz) >= 4000)
					flag = 1;
			}
		}
		if (flag3 == 0 && flag == 1)
			teshu = teshu + 1500;
	}
	if (i >= 10)
		teshu = teshu - 300;
	if (cMap[11][0] == 'h'&&Judge(10, 0, 8, dz) > 8000)
		if (i == 11 && j == 0 && i1 == 10 && j1 == 0)
			teshu = teshu + 50000;
	if (cMap[11][2] == 'h'&&Judge(10, 2, 8, dz) > 8000)
		if (i == 11 && j == 2 && i1 == 10 && j1 == 2)
			teshu = teshu + 50000;
	//fprintf(fp, "\naaaa12 %d ", teshu);
	//fprintf(fp, "\nsss %d", MyMovingChess(cMap));

	/*if (MyMovingChess(cMap) == 1)
	{
	if (cMap[11][1] == 'l')
	{
	fprintf(fp, "\nsss1 ");
	if (i1 = 10 && j1 == 1)
	{
	teshu = teshu + 2000;
	fprintf(fp, "\nsss2 ");
	}
	}
	if (cMap[11][3] == 'l')
	{
	fprintf(fp, "\nsss3 ");
	if (i1 = 10 && j1 == 3)
	{
	teshu = teshu + 2000;
	fprintf(fp, "\nsss4 ");
	}
	}
	}*/
	/*if (cMap[i1][j1] == '0')
	teshu = teshu + 2000;*/
	//fprintf(fp, "\naaaa13 %d ", teshu);
	fclose(fp);
	weixief = weixie(i, j, i1, j1, dz, cMap) / 10;            /////   ��Ϊ�ͼ����в��ͬ/  //weixief=weixie(i,j,i1,j1,dz,cMap)/5;
	qipan = qipanfen[i1][j1] - qipanfen[i][j];
	jweixief = jweixie(i1, j1, dz, cmap) / 10;
	score = weixief + qipan + jweixief + sanyif + teshu;

	fp = fopen("1", "a");
	fprintf(fp, "\n%s,%d,%s,%d,%s,%d,%s,%d,%s,%d\n%c %d,%d,%d,%d\n", "ֱ����в", weixief, "�����в", jweixief, "��ʮһ����ֵ", sanyif, "�����", teshu, "�ܷ�", score, cMap[i][j], i, j, i1, j1);
	fclose(fp);

	if (Ina_step[0] == 2 && Ina_step[1]>12)
		return score1;
	else
		return score;
}
void CulBestmove(char cMap[12][5], char *cInMessage, char *cOutMessage, int dz[25][16])																	//cInMessage��ȥ������ûʲô����
{
	strcpy(cOutMessage, "BESTMOVE A0A0");
	int move[4];
	int allmove[200][4], iSaMove[40][2];
	int i, j, num, num1, i1, j1, k = 0;
	char cmap[12][5];
	int score1, score = -10000;
	//��ʽ
	if (1)
	{
		//�ҷ����ڵз������Ա�
		if (cMap[0][1] == 'L')
		{
			if (IsMyMovingChess(cMap, 0, 0))
			{
				cOutMessage[9] = 'A';
				cOutMessage[10] = '0';
				cOutMessage[11] = 'A';
				cOutMessage[12] = '1';
				return;
			}
			if (IsMyMovingChess(cMap, 0, 2))
			{
				cOutMessage[9] = 'A';
				cOutMessage[10] = '2';
				cOutMessage[11] = 'A';
				cOutMessage[12] = '1';
				return;
			}
			if (IsMyMovingChess(cMap, 1, 1))
			{
				cOutMessage[9] = 'B';
				cOutMessage[10] = '1';
				cOutMessage[11] = 'A';
				cOutMessage[12] = '1';
				return;
			}
		}
		if (cMap[0][3] == 'L')
		{
			if (IsMyMovingChess(cMap, 0, 4))
			{
				cOutMessage[9] = 'A';
				cOutMessage[10] = '4';
				cOutMessage[11] = 'A';
				cOutMessage[12] = '3';
				return;
			}
			if (IsMyMovingChess(cMap, 0, 2))
			{
				cOutMessage[9] = 'A';
				cOutMessage[10] = '2';
				cOutMessage[11] = 'A';
				cOutMessage[12] = '3';
				return;
			}
			if (IsMyMovingChess(cMap, 1, 3))
			{
				cOutMessage[9] = 'B';
				cOutMessage[10] = '3';
				cOutMessage[11] = 'A';
				cOutMessage[12] = '3';
				return;
			}
		}

		if (cMap[0][0] >= 'e' && cMap[0][0]<'j')
		{
			cOutMessage[9] = 'A';
			cOutMessage[10] = '0';
			cOutMessage[11] = 'A';
			cOutMessage[12] = '1';
			return;
		}
		if (cMap[0][2] >= 'e' && cMap[0][2]<'j')
		{
			cOutMessage[9] = 'A';
			cOutMessage[10] = '2';
			cOutMessage[11] = 'A';
			cOutMessage[12] = '1';
			return;
		}
		if (cMap[1][1] >= 'e' && cMap[1][1]<'j')
		{
			cOutMessage[9] = 'B';
			cOutMessage[10] = '1';
			cOutMessage[11] = 'A';
			cOutMessage[12] = '1';
			return;
		}

		if (cMap[0][4] >= 'e' && cMap[0][4]<'j')
		{
			cOutMessage[9] = 'A';
			cOutMessage[10] = '4';
			cOutMessage[11] = 'A';
			cOutMessage[12] = '3';
			return;
		}
		if (cMap[0][2] >= 'e' && cMap[0][2]<'j')
		{
			cOutMessage[9] = 'A';
			cOutMessage[10] = '2';
			cOutMessage[11] = 'A';
			cOutMessage[12] = '3';
			return;
		}
		if (cMap[1][3] >= 'e' && cMap[1][3]<'j')
		{
			cOutMessage[9] = 'B';
			cOutMessage[10] = '3';
			cOutMessage[11] = 'A';
			cOutMessage[12] = '3';
			return;
		}
	}
	FILE *fp;
	fp = fopen("1", "a");
	for (int m = 0; m<12; m++)
	{
		for (int n = 0; n<5; n++)
		{
			fprintf(fp, "%c ", cMap[m][n]);
		}
		fprintf(fp, "\n");
	}
	fprintf(fp, "\n\n\n%d,%d\n", Ina_step[0], Ina_step[1]);
	for (i = 0; i<25; i++)
	{
		for (j = 0; j<14; j++)
			fprintf(fp, "%5d,", dz[i][j]);
		fprintf(fp, "\n");
	}
	fclose(fp);

	for (i = 0; i<12; i++)
		for (j = 0; j<5; j++)
		{
			if (IsMyMovingChess(cMap, i, j) && !IsBaseCamp(i, j))  //�������ڴ�Ӫ�Ŀ��ƶ�����
			{
				//��������
				if (cMap[i][j] == 'i' && IsRailway(i, j))
				{
					iSaMove[0][0] = i;
					iSaMove[0][1] = j;
					for (i1 = 0; i1<12; i1++)
					{
						for (j1 = 0; j1<5; j1++)
							cmap[i1][j1] = cMap[i1][j1];
					}
					num = SapperRail(iSaMove, cmap, i, j, 0);
					for (num1 = 1; num1<num; num1++)
					{
						allmove[k][0] = i;
						allmove[k][1] = j;
						allmove[k][2] = iSaMove[num1][0];
						allmove[k][3] = iSaMove[num1][1];
						k++;
					}
				}
				//����ǰ��:���ڵ�һ��,����ɽ���,ǰ�����Ǽ�������,ǰ������������ռ�����Ӫ
				if (i>0 && !IsAfterHill(i, j) && !IsMyChess(cMap, i - 1, j) && !IsFilledCamp(cMap, i - 1, j))
				{
					allmove[k][0] = i;
					allmove[k][1] = j;
					allmove[k][2] = i - 1;
					allmove[k][3] = j;
					k++;
					if ((j == 0 || j == 4) && i>0 && i<11)
					{
						for (i1 = i - 1; i1>0; i1--)
						{
							if (cMap[i1][j] == '0')
							{
								allmove[k][0] = i;
								allmove[k][1] = j;
								allmove[k][2] = i1;
								allmove[k][3] = j;
								k++;
							}
							else if (cMap[i1][j] >= 'A' && cMap[i1][j] == 'X')
							{
								allmove[k][0] = i;
								allmove[k][1] = j;
								allmove[k][2] = i1;
								allmove[k][3] = j;
								k++;
								break;
							}
							else break;
						}
					}
				}
				//��������:����������,��಻�Ǽ�������,��಻�Ǳ�ռ�õ���Ӫ
				if (j>0 && !IsMyChess(cMap, i, j - 1) && !IsFilledCamp(cMap, i, j - 1))
				{
					allmove[k][0] = i;
					allmove[k][1] = j;
					allmove[k][2] = i;
					allmove[k][3] = j - 1;
					k++;
					//�Ƿ���1,5,6,10������
					if (i == 1 || i == 5 || i == 6 || i == 10)
					{
						for (int i1 = j - 1; i1 >= 0; i1--)
						{
							if (cMap[i][i1] == '0')
							{
								allmove[k][0] = i;
								allmove[k][1] = j;
								allmove[k][2] = i;
								allmove[k][3] = i1;
								k++;
							}
							else if (cMap[i][i1] >= 'A'&&cMap[i][i1] <= 'X')
							{
								allmove[k][0] = i;
								allmove[k][1] = j;
								allmove[k][2] = i;
								allmove[k][3] = i1;
								k++;
								break;
							}
							else break;
						}
					}
				}
				//��������:����������,�Ҳ಻�Ǽ�������,�Ҳ಻�Ǳ�ռ�õ���Ӫ
				if (j<4 && !IsMyChess(cMap, i, j + 1) && !IsFilledCamp(cMap, i, j + 1))
				{
					allmove[k][0] = i;
					allmove[k][1] = j;
					allmove[k][2] = i;
					allmove[k][3] = j + 1;
					k++;
					//�Ƿ���1,5,6,10������
					if (i == 1 || i == 5 || i == 6 || i == 10)
					{
						for (int i1 = j + 1; i1<5; i1++)
						{
							if (cMap[i][i1] == '0')
							{
								allmove[k][0] = i;
								allmove[k][1] = j;
								allmove[k][2] = i;
								allmove[k][3] = i1;
								k++;
							}
							else if (cMap[i][i1] >= 'A'&&cMap[i][i1] <= 'X')
							{
								allmove[k][0] = i;
								allmove[k][1] = j;
								allmove[k][2] = i;
								allmove[k][3] = i1;
								k++;
								break;
							}
							else break;
						}
					}
				}

				//���Ժ��ƣ��������һ�У��󷽲��Ǽ������ӣ����治����ռ�е���Ӫ
				if (i<11 && !IsBehindHill(i, j) && !IsMyChess(cMap, i + 1, j) && !IsFilledCamp(cMap, i + 1, j))
				{
					allmove[k][0] = i;
					allmove[k][1] = j;
					allmove[k][2] = i + 1;
					allmove[k][3] = j;
					k++;
					//������������������ƶ����󷽲��Ǽ������ӣ����ǵ�һ�У��������һ��
					if ((j == 0 || j == 4) && i>0 && i<11)
					{
						for (i1 = i + 1; i1<11; i1++)
						{
							if (cMap[i1][j] == '0')
							{
								allmove[k][0] = i;
								allmove[k][1] = j;
								allmove[k][2] = i1;
								allmove[k][3] = j;
								k++;
							}
							else if (cMap[i1][j] >= 'A' && cMap[i1][j] <= 'X')
							{
								allmove[k][0] = i;
								allmove[k][1] = j;
								allmove[k][2] = i1;
								allmove[k][3] = j;
								k++;
								break;
							}
							else  break;
						}

					}
				}
				//������ǰ�ƣ���ǰ��������ռ�е���Ӫ�����Ǽ�������
				if ((Iszuoqian(i, j) || IsMoveCamp(i, j)) && !IsMyChess(cMap, i - 1, j - 1) && !IsFilledCamp(cMap, i - 1, j - 1))
				{
					allmove[k][0] = i;
					allmove[k][1] = j;
					allmove[k][2] = i - 1;
					allmove[k][3] = j - 1;
					k++;
				}
				//��������ƣ���󷽲��Ǽ������ӣ�������ռ�е���Ӫ
				if ((Iszuohou(i, j) || IsMoveCamp(i, j)) && !IsMyChess(cMap, i + 1, j - 1) && !IsFilledCamp(cMap, i + 1, j - 1))
				{
					allmove[k][0] = i;
					allmove[k][1] = j;
					allmove[k][2] = i + 1;
					allmove[k][3] = j - 1;
					k++;
				}
				//������ǰ�ƣ���ǰ�����Ǽ������ӣ�������ռ�е���Ӫ
				if ((Isyouqian(i, j) || IsMoveCamp(i, j)) && !IsMyChess(cMap, i - 1, j + 1) && !IsFilledCamp(cMap, i - 1, j + 1))
				{
					allmove[k][0] = i;
					allmove[k][1] = j;
					allmove[k][2] = i - 1;
					allmove[k][3] = j + 1;
					k++;
				}
				//�����Һ��ƣ��Һ󷽲��Ǽ������ӣ�������ռ�е���Ӫ
				if ((Isyouhou(i, j) || IsMoveCamp(i, j)) && !IsMyChess(cMap, i + 1, j + 1) && !IsFilledCamp(cMap, i + 1, j + 1))
				{
					allmove[k][0] = i;
					allmove[k][1] = j;
					allmove[k][2] = i + 1;
					allmove[k][3] = j + 1;
					k++;
				}
			}
		}
	for (i = 0; i<k; i++)
	{
		if ((score1 = pinggu(allmove[i][0], allmove[i][1], allmove[i][2], allmove[i][3], dz, cMap)) >= score)
		{
			if (allmove[i][0] == allmove[i][2] && allmove[i][1] == allmove[i][3])
				continue;
			else
			{
				score = score1;
				move[0] = allmove[i][0];
				move[1] = allmove[i][1];
				move[2] = allmove[i][2];
				move[3] = allmove[i][3];
			}
		}
	}
	cOutMessage[9] = move[0] + 'A';
	cOutMessage[10] = move[1] + '0';
	cOutMessage[11] = move[2] + 'A';
	cOutMessage[12] = move[3] + '0';
	fp = fopen("1", "a");
	fprintf(fp, "\n%d,%d,%d,%d,%d,%d\n", move[0], move[1], move[2], move[3], score1, score);
	//	fprintf(fp,"\n%d\n",zz++);
	fclose(fp);

}
/* ************************************************************************ */
/* �������ܣ����㼺������ŷ�(������Ϊʾ���㷨,�����ѡ�����иĽ��㷨)		*/
/* �ӿڲ�����																*/
/*     char *cMap ���̾���													*/
/*     char *cInMessage ���Բ��е� GO ����									*/
/*     char *cOutMessage �������е� BESTMOVE ����							*/
/* ************************************************************************ */


int main()
{
	char cVer[200];			//Э��汾
	int iFirst;				//����Ȩ[0���У�1����]																							//��֪��iFirst��iTime��iStep��ʲô�ã�������ƽ̨�й�ϵ��
	int iTime;				//����ʱ������(��λ��)[1000,3600]
	int iStep;				//�����ȴ�����(��λ��)[10,31]
	char cInMessage[200];   //����ͨ������
	char cOutMessage[200];  //���ͨ������
	char cIn1[200], cIn2[200];
	char cMap[12][5];		//����
							//   ˾�� ,���� ,ʦ�� ,�ó� ,�ų� ,Ӫ�� ,���� ,�ų� ,���� ,���� ,ը�� ,����     i,j,(��������λ��)
	int dz[26][16] = {
		100  ,100  ,250  ,500  ,500  ,700  ,2000 ,2100 ,400  ,3250 ,100  ,0    ,   0,0,0,0,//A0  10000
		0    ,0    ,0    ,0    ,0    ,0    ,0    ,3000 ,0    ,2000 ,0    ,5000 ,   0,1,0,0,//A1
		100  ,100  ,250  ,500  ,500  ,700  ,2000 ,2100 ,200  ,3250 ,100  ,0    ,   0,2,0,0,//A2
		0    ,0    ,0    ,0    ,0    ,0    ,0    ,3000 ,0    ,2000 ,0    ,5000 ,   0,3,0,0,//A3
		100  ,100  ,250  ,500  ,500  ,700  ,2000 ,2100 ,400  ,3250 ,100  ,0    ,   0,4,0,0,//A4

		500  ,500  ,850  ,700  ,600  ,500  ,600  ,500  ,1000 ,3250 ,1000 ,0    ,   1,0,0,0,//B0
		400  ,400  ,850  ,700  ,600  ,500  ,800  ,600  ,1000 ,3250 ,900  ,0    ,   1,1,0,0,//B1
		400  ,400  ,850  ,700  ,600  ,500  ,800  ,600  ,1000 ,3250 ,900  ,0    ,   1,2,0,0,//B2
		400  ,400  ,850  ,700  ,600  ,500  ,800  ,600  ,1000 ,3250 ,900  ,0    ,   1,3,0,0,//B3
		500  ,500  ,850  ,700  ,600  ,500  ,600  ,500  ,1000 ,3250 ,1000 ,0    ,   1,4,0,0,//B4

		500  ,500  ,1000 ,1000 ,1000 ,1500 ,500  ,500  ,2000 ,0    ,1500 ,0    ,   2,0,0,0,//C0
		500  ,500  ,1000 ,1000 ,1000 ,1500 ,500  ,500  ,2000 ,0    ,1500 ,0    ,   2,2,0,0,//C2
		500  ,500  ,1000 ,1000 ,1000 ,1500 ,500  ,500  ,2000 ,0    ,1500 ,0    ,   2,4,0,0,//C4

		500  ,500  ,1000 ,1000 ,1000 ,1500 ,500  ,500  ,2000 ,0    ,1500 ,0    ,   3,0,0,0,//D0
		500  ,500  ,1000 ,1000 ,1000 ,1500 ,500  ,500  ,2000 ,0    ,1500 ,0    ,   3,1,0,0,//D1
		500  ,500  ,1000 ,1000 ,1000 ,1500 ,500  ,500  ,2000 ,0    ,1500 ,0    ,   3,3,0,0,//D3
		500  ,500  ,1000 ,1000 ,1000 ,1500 ,500  ,500  ,2000 ,0    ,1500 ,0    ,   3,4,0,0,//D4

		500  ,500  ,1000 ,1000 ,1000 ,1500 ,500  ,500  ,2000 ,0    ,1500 ,0    ,   4,0,0,0,//E0
		500  ,500  ,1000 ,1000 ,1000 ,1500 ,500  ,500  ,2000 ,0    ,1500 ,0    ,   4,2,0,0,//E2
		500  ,500  ,1000 ,1000 ,1000 ,1500 ,500  ,500  ,2000 ,0    ,1500 ,0    ,   4,4,0,0,//E4

		500  ,500  ,1000 ,1000 ,1200 ,2800 ,1500 ,1500 ,0    ,0    ,0    ,0    ,   5,0,0,0,//F0
		500  ,500  ,1000 ,1000 ,1000 ,1000 ,1500 ,1500 ,2000 ,0    ,0    ,0    ,   5,1,0,0,//F1
		500  ,500  ,1000 ,1000 ,1100 ,2800 ,1600 ,1500 ,0    ,0    ,0    ,0    ,   5,2,0,0,//F2
		500  ,500  ,1000 ,1000 ,1000 ,1000 ,1500 ,1500 ,2000 ,0    ,0    ,0    ,   5,3,0,0,//F3
		500  ,500  ,1000 ,1000 ,1200 ,2800 ,1500 ,1500 ,0    ,0    ,0    ,0    ,   5,4,0,0,//F4
		10000,10000,20000,20000,20000,20000,30000,30000,30000,30000,20000,10000
	};   //�²����                  10000     22200  27600


		 //cin.gets(a,20)		gets(a)		cin.get(str,size).get();�����get()�������ǰ������Ĳ����ڻ������Ļ��з���
	cin.getline(cInMessage, 200);		//��ȡ���Բ���ϵͳ��ָ�� "GO 0000 0 00"
										//	gets(cInMessage);

	while (cInMessage[0] >= 'A')
	{
		if (strcmp(cIn1, cIn2) == 0) {
			//		printf("han been gone run!\n");
		}
		else {
			//		FILE *fp;
			//		fp=fopen("D:/Debug/ceshi.txt","a");
			//	fprintf(fp,"%s%s\n","����ָ��:",cInMessage);
			switch (cInMessage[0])
			{

			case 'I':								//INFOָ��
				CulInfo(cInMessage, cVer, cOutMessage);
				cout << cOutMessage << endl;			//��"NAME "ָ��ݸ�����ϵͳ
				break;
			case 'S':								//START ָ��
				CulArray(cInMessage, &iFirst, &iTime, &iStep, cOutMessage);
				InitMap(cMap, cOutMessage);
				cout << cOutMessage << endl;
				break;
			case 'G':								//GO ָ��
				FreshMap(cMap, cInMessage, cOutMessage, dz);
				CulBestmove(cMap, cInMessage, cOutMessage, dz);
				cout << cOutMessage << endl;
				break;
			case 'R':								//RESULT ָ��
				FreshMap(cMap, cInMessage, cOutMessage, dz);
				//	cout<<cOutMessage<<endl;
				break;
			case 'E':								//END ָ��
				return 0;
			default:
				return 1;

			}
			//		fprintf(fp,"%s%s\n","����ָ��:",cOutMessage);
			//	fclose(fp);
		}
		strcpy(cIn1, cInMessage);
		//	cin.getline(cInMessage,200);	//��ȡ���Բ���ϵͳ��ָ��"START" �� "RESULT" �� "GO" �� "END"

		while (1) {
			gets(cInMessage);
			if (cInMessage[0] >= 'A') {
				break;
			}
		}
		strcpy(cIn2, cInMessage);
	}
	return 0;
}
