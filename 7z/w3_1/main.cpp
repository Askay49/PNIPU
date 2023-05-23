#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <grx20.h>
#include <grxkeys.h>

#define N 100

struct TPoint //����� �����
{
	int x, y;							//����������
	int vx, vy;							//������� ��������
	int color;							//����
	TPoint(int ix, int iy, int icolor); //������ ������� �����
	virtual ~TPoint();
	virtual void Draw(int icolor);
	void Show();
	void Hide();
	void MoveXY(int ix, int iy);
	virtual int SizeX();
	virtual int SizeY();
};
struct TBox : public TPoint //����� �������� �������� ������� � ���������� ����� + ����
{
	int w, h; //������ � ������
	TBox(int ix, int iy, int icolor, int iw, int ih);
	virtual ~TBox();
	virtual void Draw(int icolor);
	virtual int SizeX();
	virtual int SizeY();
};
struct TCircle : public TPoint //����� ��� � ���������
{
	int r; //������
	TCircle(int ix, int iy, int icolor, int ir);
	virtual ~TCircle();
	virtual void Draw(int icolor);
	virtual int SizeX();
	virtual int SizeY();
};

TPoint::TPoint(int ix, int iy, int icolor) //����������� (����������� ��� ��������), ������ ������������� �������� ����������
{
	x = ix;
	y = iy;
	vx = rand() % 7 - 3;
	vy = rand() % 7 - 3;
	color = icolor;
}

TPoint::~TPoint() //���������� (����������� ��� ��������)
{
	Hide();
}

void TPoint::Draw(int icolor) //������� ���������
{
	GrPlot(x, y, icolor);
	GrPlot(x + 1, y, icolor);
	GrPlot(x, y + 1, icolor);
	GrPlot(x + 1, y + 1, icolor);
}
int TPoint::SizeX() //������� ������������� ������ �� X
{
	return 1;
}
int TPoint::SizeY() //������� ������������� ������ �� Y
{
	return 1;
}

void TPoint::Show() //������� "��������"
{
	Draw(color);
}

void TPoint::Hide() //������� "������"
{
	Draw(0);
}

void TPoint::MoveXY(int ix, int iy) //������� ��������
{
	Hide(); //������
	x = ix; //�������� ����������
	y = iy;
	Show(); //��������
}

TBox::TBox(int ix, int iy, int icolor, int iw, int ih) : TPoint(ix, iy, icolor) //� ���������� �������� ���� ����� ���
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
int TBox::SizeX()
{
	return w / 2;
}
int TBox::SizeY()
{
	return h / 2;
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
int TCircle::SizeX()
{
	return r;
}
int TCircle::SizeY()
{
	return r;
}
//****************************************************************
//****************************************************************
main()
{
	int number = 0;					//���������� ����� �� ������
	TPoint *obj[N];					//������ �����
	GrSetMode(GR_biggest_graphics); // ������ ����
	srand(time(0));					//����� ������� ��������� �������
	int i;
	int RandSel = rand() % 3; //�������� ������

	GrKeyType key;
	do
	{
		while (!GrKeyPressed()) //����������� ����, ���� �� ������ ������
		{
			GrSleep(1); //��������� ��������

			for (i = 0; i < number; i++) //���� ������������ ������
			{
				if (obj[i]->x + obj[i]->vx - obj[i]->SizeX() < 0 || obj[i]->x + obj[i]->vx + obj[i]->SizeX() > GrMaxX()) //�������� ������ �� ������� ������ �� ��� X
					obj[i]->vx = -obj[i]->vx;																			 //������ ������ �� ���������������
				if (obj[i]->y + obj[i]->vy - obj[i]->SizeY() < 0 || obj[i]->y + obj[i]->vy + obj[i]->SizeY() > GrMaxY()) //�������� ������ �� ������� ������ �� ��� Y
					obj[i]->vy = -obj[i]->vy;																			 //������ ������ �� ���������������

				obj[i]->MoveXY(obj[i]->x + obj[i]->vx, obj[i]->y + obj[i]->vy); //�������
			}
		}
		key = GrKeyRead();
		switch (key) //���������� ������
		{
		case GrKey_Space: //���� ������, ������� ��������� ������
			switch (RandSel)
			{
			case 0:
				obj[number] = new TPoint(GrMaxX() / 2, GrMaxY() / 2, 15);
				break;
			case 1:
				obj[number] = new TBox(GrMaxX() / 2, GrMaxY() / 2, 15, rand() % 70 + 30, rand() % 70 + 30);
				break;
			case 2:
				obj[number] = new TCircle(GrMaxX() / 2, GrMaxY() / 2, 15, rand() % 30 + 20);
			}
			obj[number]->Show();
			RandSel = rand() % 3; //��������� �������� ������
			number++;			  //���������� ����� ������
			break;

		case GrKey_Delete: //���� �����, ������� � �������� �����
			GrClearScreen(0);
			delete obj[number - 1];
			number--;
		}
	} while (key != GrKey_Escape); //���� ����� ESC, ������� �� �����

	for (i = 0; i < N; i++)
	{
		delete obj[i]; //������� ��� ������
	}
}
