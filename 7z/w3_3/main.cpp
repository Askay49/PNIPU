#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <grx20.h>
#include <grxkeys.h>
#include <math.h>

#define N 100

struct TPoint //����� �����
{
	int x, y;
	float a, s;
	float va, vs;
	int count, r_time;
	int color;
	TPoint(int ix, int iy, int icolor);
	virtual ~TPoint();
	virtual void Draw(int icolor);
	void Show();
	void Hide();
	void MoveXY();
};
struct TBox : public TPoint //��������
{
	int w, h;
	TBox(int ix, int iy, int icolor, int iw, int ih);
	virtual ~TBox();
	virtual void Draw(int icolor);
};
struct TCircle : public TPoint //�����
{
	int r;
	TCircle(int ix, int iy, int icolor, int ir);
	virtual ~TCircle();
	virtual void Draw(int icolor);
};

TPoint::TPoint(int ix, int iy, int icolor) //����������� ����� (����������� ��� ��������)
{
	x = ix;
	y = iy;
	a = 0;
	s = 0;
	va = 0.01;
	vs = 0.1;
	count = 0;
	r_time = rand() % 10;
	color = icolor;
}

TPoint::~TPoint() //����������( ����������� ��� ��������)
{
	Hide();
}

void TPoint::Draw(int icolor) //��������� �����
{
	GrPlot(x, y, icolor);
	GrPlot(x + 1, y, icolor);
	GrPlot(x, y + 1, icolor);
	GrPlot(x + 1, y + 1, icolor);
}

void TPoint::Show()
{
	Draw(color);
}

void TPoint::Hide()
{
	Draw(0);
}

void TPoint::MoveXY() //�������� �����
{
	Hide();
	if (s + vs > GrMaxY()/2) //���� �� ��������� ����� ������ �� ����� ������ �����������
	{
		va = -va;
		vs = -vs;
	}
	a += va; //���������� � ������� �������
	s += vs;
	x = floor(GrMaxX() / 2 + s * cos(a)); //������ ������� ��������� (����� �������� � ����� ����, ��� ��� ��� ���������)
	y = floor(GrMaxY() / 2 - s * sin(a));
	count++;
	if (count == r_time) //� ��������� ������� �������� ��������
	{
		if (r_time % 2)
		{
			va += 0.2 / r_time;
			vs += 0.2 / r_time;
		}
		else
		{
			va -= 0.2 / r_time;
			vs -= 0.2 / r_time;
		}
		if (va > 0.2)
			va -= 0.1;
		count = 0;
		r_time = rand() % 10;
	}

	Show();
}

TBox::TBox(int ix, int iy, int icolor, int iw, int ih) : TPoint(ix, iy, icolor)
{
	w = iw;
	h = ih;
}
TBox::~TBox()
{
	Hide();
}
void TBox::Draw(int icolor)
{
	GrBox(x - w / 2, y - h / 2, x + (w - w / 2), y + (h - h / 2), icolor);
}
//****************************************************************
TCircle::TCircle(int ix, int iy, int icolor, int ir) : TPoint(ix, iy, icolor)
{
	r = ir;
}
TCircle::~TCircle()
{
	Hide();
}
void TCircle::Draw(int icolor)
{

	GrCircle(x, y, r, icolor);
}
//****************************************************************
//****************************************************************

main()
{
	int number = 0;					//���������� ���������� �����
	TPoint *obj[N];					//������ �����
	GrSetMode(GR_biggest_graphics); // ������ ����
	srand(time(0));
	int i;
	int RandSel = rand() % 3; //�������� ������

	GrKeyType key;
	do
	{
		while (!GrKeyPressed())
		{
			GrSleep(5);
			for (i = 0; i < number; i++) //���������� ������ ������
			{
				obj[i]->MoveXY();
			}
		}
		key = GrKeyRead();
		switch (key)
		{
		case GrKey_Space: //���� ������ ������ ��������� ��������� ������
			switch (RandSel)
			{
			case 0:
				obj[number] = new TPoint(GrMaxX() / 2, GrMaxY() / 2, 15);
				break;
			case 1:
				obj[number] = new TBox(GrMaxX() / 2, GrMaxY() / 2, 15, rand() % 15 + 10, rand() % 15 + 10);
				break;
			case 2:
				obj[number] = new TCircle(GrMaxX() / 2, GrMaxY() / 2, 15, rand() % 15 + 10);
			}
			obj[number]->Show();
			RandSel = rand() % 3;
			number++; //� ���������� ������� �����
			break;

		case GrKey_Delete: //���� ����� ����� ������� ������
			GrClearScreen(0);
			delete obj[number];
			number--; //� ��������� �������
		}
	} while (key != GrKey_Escape); //���� ������ ESC ������� �� �����

	for (i = 0; i < N; i++) //������� �������
	{
		delete obj[i];
	}
}
