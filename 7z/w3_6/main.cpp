#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <grx20.h>
#include <grxkeys.h>
#include <math.h>

#define N 100

struct TPoint
{
	bool state;
	float x, y;
	float vx, vy;
	int color;
	TPoint(float ix, float iy, int icolor);
	virtual ~TPoint();
	virtual void Draw(int icolor);
	void Show();
	void Hide();
	void MoveXY(int ix, int iy);
};
struct TBox : public TPoint
{
	int w, h;
	TBox(int ix, int iy, int icolor, int iw, int ih);
	virtual ~TBox();
	virtual void Draw(int icolor);
};
struct TCircle : public TPoint
{
	int r;
	TCircle(int ix, int iy, int icolor, int ir);
	virtual ~TCircle();
	virtual void Draw(int icolor);
};

TPoint::TPoint(float ix, float iy, int icolor)
{
	state = 0;
	x = ix;
	y = iy;
	vx = rand() % 7 - 3;
	vy = rand() % 7 - 3;
	color = icolor;
}

TPoint::~TPoint()
{
	Hide();
}

void TPoint::Draw(int icolor)
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

void TPoint::MoveXY(int ix, int iy)
{
	Hide();
	x = ix;
	y = iy;
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
	int number = 0;					//���������� �����
	TPoint *obj[N];					//������ �����
	GrSetMode(GR_biggest_graphics); // ������ ����
	srand(time(0));					//����� ������� �������
	int i;
	int RandSel = rand() % 3; //�������� �����

	GrKeyType key;
	do
	{
		while (!GrKeyPressed())
		{
			GrSleep(5);
			for (i = 0; i < number; i++) //������� �����
			{

				if (obj[i]->y - obj[i]->vy > GrMaxY()) //���� �� ��������� ����� ������ ����� �� ��� ������������ �� � �������� �����������
				{
					obj[i]->vy = obj[i]->vy * 0.5;
					obj[i]->vy = -obj[i]->vy;
				}

				if (obj[i]->x + obj[i]->vx > GrMaxX()) //���� ������ �� ������ ������� �������� �����������
				{
					obj[i]->vx = obj[i]->vx * 0.5;
					obj[i]->vx = -obj[i]->vx;
				}

				if (obj[i]->x + obj[i]->vx < 0) //����� �������, ������ �����������
				{
					obj[i]->vx = obj[i]->vx * 0.5;
					obj[i]->vx = -obj[i]->vx;
				}

				obj[i]->vy -= 0.1;		//��������� ��������� ������ �������� �� Y, ���� ���� �������
				if (obj[i]->state == 0) //���� ��������� 0 �� ��������� ������� ��� ������
					obj[i]->MoveXY(obj[i]->x + obj[i]->vx, obj[i]->y - obj[i]->vy);
				else if (obj[i]->state == 1) //���� ��������� 1, ����������� �����
					obj[i]->MoveXY(obj[i]->x, obj[i]->y - 1);

				if (obj[i]->y > GrMaxY() - 20 && fabs(obj[i]->vy) < 0.1) //���� �������� ���������� +-, ������ ���������� 1
					obj[i]->state = 1;
				if (obj[i]->state == 1 && obj[i]->y < GrMaxY() / 2) //���� ��������� 1 � �� ���� ������ ������ ������� ��������� 0 � ������ ������ �� Y ���������
				{
					obj[i]->state = 0;
					obj[i]->vy = rand() % 5;
					obj[i]->color = rand() % 14 + 1;
				}
			}
		}
		key = GrKeyRead();
		switch (key)
		{
		case GrKey_Space: //�� ������ �������� �����
			switch (RandSel)
			{
			case 0:
				obj[number] = new TPoint(GrMaxX() / 2, GrMaxY() / 2, 15);
				break;
			case 1:
				obj[number] = new TBox(GrMaxX() / 2, GrMaxY() / 2, 15, rand() % 20, rand() % 20);
				break;
			case 2:
				obj[number] = new TCircle(GrMaxX() / 2, GrMaxY() / 2, 15, rand() % 20);
			}
			obj[number]->Show();
			RandSel = rand() % 3;
			number++;
			break;

		case GrKey_Delete: //�� ����� �������� �����
			GrClearScreen(0);
			delete obj[number - 1];
			number--;
		}
	} while (key != GrKey_Escape); //�� ������ �������

	for (i = 0; i < N; i++) //������� �������
	{
		delete obj[i];
	}
}
