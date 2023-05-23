#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <grx20.h>
#include <grxkeys.h>

#define N 100

struct TPoint //����� �����
{
	int x, y;	//����������
	int vx, vy; //������� ��������
	int color;	//����
	TPoint(int ix, int iy, int icolor);
	virtual ~TPoint(); //��������� �������
	virtual void Draw(int icolor);
	void Show();
	void Hide();
	void MoveXY(int ix, int iy);
};
struct TBox : public TPoint //����� �������� ��������� ���������� � ������� �� ����� + ����
{
	int w, h; //������ ������
	TBox(int ix, int iy, int icolor, int iw, int ih);
	virtual ~TBox();
	virtual void Draw(int icolor);
};
struct TCircle : public TPoint //����� ��� � ���������
{
	int r; //������
	TCircle(int ix, int iy, int icolor, int ir);
	virtual ~TCircle();
	virtual void Draw(int icolor);
};

TPoint::TPoint(int ix, int iy, int icolor) //����������� ����� (����������� ��� ��������)
{
	x = ix;
	y = iy;
	vx = rand() % 7 - 3;
	vy = rand() % 7 - 3;
	color = icolor;
}

TPoint::~TPoint() //���������� ����� (����������� ��� ��������)
{
	Hide();
}

void TPoint::Draw(int icolor) //������� ��������� ����� (4 �������)
{
	GrPlot(x, y, icolor);
	GrPlot(x + 1, y, icolor);
	GrPlot(x, y + 1, icolor);
	GrPlot(x + 1, y + 1, icolor);
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
	Hide();
	x = ix;
	y = iy;
	Show();
}

TBox::TBox(int ix, int iy, int icolor, int iw, int ih) : TPoint(ix, iy, icolor) //� ���������� �������� ����� ����� �� ������� ��� ���
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
	int number = 0;					//����� ������
	TPoint *obj[N];					//������ ��������
	GrSetMode(GR_biggest_graphics); // ������ ����
	srand(time(0));					//����� ������� �������
	bool state = 0;					//���������� ��������� ��������
	int i;
	int RandSel = rand() % 3; //�������� ������
	int count = 0;			  //�������

	GrKeyType key;
	do
	{
		while (!GrKeyPressed())
		{
			GrSleep(5); //��������� ��������
			if (state)	//���� ��������� ==1
			{
				count = 0;					 //�������� �������
				for (i = 0; i < number; i++) //� � ����� ��������� ��� �� ������ ������ � ������ ����� (������� ������� �� ������)
				{
					if (obj[i]->x < GrMaxX() / 2 + 10 && obj[i]->x > GrMaxX() / 2 - 10 && obj[i]->y > GrMaxY() / 2 - 10 && obj[i]->y < GrMaxY() / 2 + 10)
					{
						count++;
					}
				}

				if (count == number) //���� ��� ������ ������ � ������ �����
				{
					state = 0; //������ ��������� �� 0
				}
			}

			for (i = 0; i < number; i++) //���� �������� �����
			{
				if (state == 0) //���� ��������� 0
				{
					obj[i]->vx = rand() % 15 - 7; //�������� ������ �������
					obj[i]->vy = rand() % 15 - 7;
				}
				else
				{
					obj[i]->vx = (GrMaxX() / 2 - obj[i]->x) / 10; //���� ��������� 1, ������� � ����� ������
					obj[i]->vy = (GrMaxY() / 2 - obj[i]->y) / 10;
				}

				obj[i]->MoveXY(obj[i]->x + obj[i]->vx, obj[i]->y + obj[i]->vy); //������� ������ �� ������� ���� �����������
			}
			if (rand() % 100 == 50) //� ��������� ������� ������� ������ ��������� �� 1
				state = 1;
		}
		key = GrKeyRead();
		switch (key)
		{
		case GrKey_Space: //���� ����� ������ ������� ����� ������
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
			RandSel = rand() % 3; //��������� �������� ������
			number++;			  //� ���������� ���������� �����
			break;

		case GrKey_Delete:			//���� ����� �����
			GrClearScreen(0);		//������ �����
			delete obj[number - 1]; //������� ��������� ������
			number--;				//� �������� ����� ������
			break;
		case GrKey_F1: //�� F1 �� ����� ���� �������� ��������� �����
			state = !state;
		}
	} while (key != GrKey_Escape); //���� ����� ESC

	for (i = 0; i < N; i++) //������� ��� �������
	{
		delete obj[i];
	}
}
