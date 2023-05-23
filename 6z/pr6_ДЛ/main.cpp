#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <grx20.h>
#include <grxkeys.h>

#define N 100

struct TPoint //����� �����
{
	int x, y;
	int color;
	TPoint(int ix, int iy, int icolor);
	virtual ~TPoint();
	virtual void Draw(int icolor);
	void Show();
	void Hide();
	virtual void MoveXY();
};
struct TBox : public TPoint //��������
{
	int w, h;
	TBox(int ix, int iy, int icolor, int iw, int ih);
	virtual ~TBox();
	virtual void Draw(int icolor);
	virtual void MoveXY();
};
struct TEllipse : public TPoint //������
{
	int xa, ya;
	TEllipse(int ix, int iy, int icolor, int ixa, int iya);
	virtual ~TEllipse();
	virtual void Draw(int icolor);
};
struct TCircle : public TPoint //�����
{
	int r;
	TCircle(int ix, int iy, int icolor, int ir);
	virtual ~TCircle();
	virtual void Draw(int icolor);
	virtual void MoveXY();
};
struct TName : public TPoint // � ���������
{
	int wn, hn;
	TName(int ix, int iy, int icolor, int iwn, int ihn);
	virtual ~TName();
	virtual void Draw(int icolor);
};

TPoint::TPoint(int ix, int iy, int icolor) //����������� �����
{
	x = ix;
	y = iy;
	color = icolor;
}

TPoint::~TPoint() //���������� �����
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

void TPoint::Show() //��������
{
	Draw(color);
}

void TPoint::Hide() //������
{
	Draw(0);
}

void TPoint::MoveXY() // �������� �����
{
	Hide();
	x = x + rand() % 7 - 3; // ix;
	y = y + rand() % 7 - 3; // iy;
	Show();
}
TBox::TBox(int ix, int iy, int icolor, int iw, int ih) : TPoint(ix, iy, icolor) //� ��������� ���� �����, ���������� ������ �������� ����� � ��������
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
void TBox::MoveXY() // ������� �������� ������ ������ � ���� ��� �����������
{
	Hide();
	color = rand() % 15 + 1;

	if (h > 25)
		h -= 3;
	else
		h = h + (rand() % 5 - 2);
	if (w > 25)
		w -= 3;
	else
		w = w + (rand() % 5 - 2);
	x = x + rand() % 7 - 3; // ix;
	y = y + rand() % 7 - 3; // iy;
	Show();
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
void TCircle::MoveXY() // ���� ������ ������ � ���� ��� �����������
{
	Hide();
	color = rand() % 15 + 1;
	if (r > 25)
		r -= 3;
	else
		r = r + (rand() % 5 - 2);
	x = x + rand() % 7 - 3;
	y = y + rand() % 7 - 3;
	Show();
}
//****************************************************************
TEllipse::TEllipse(int ix, int iy, int icolor, int ixa, int iya) : TPoint(ix, iy, icolor)
{
	xa = ixa;
	ya = iya;
}
TEllipse::~TEllipse()
{
	Hide();
}
void TEllipse::Draw(int icolor)
{
	GrEllipse(x, y, xa, ya, icolor);
}
//****************************************************************
TName::TName(int ix, int iy, int icolor, int iwn, int ihn) : TPoint(ix, iy, icolor)
{
	wn = iwn;
	hn = ihn;
}
TName::~TName()
{
	Hide();
}
void TName::Draw(int icolor) //������� ��������� ���������
{
	GrLine(x, y, x + wn * 2, y, icolor); //����� �
	GrEllipseArc(x + wn, y, wn / 2, hn, 0, 1800, GR_ARC_STYLE_OPEN, icolor);

	GrEllipseArc(x + wn * 4, y, wn / 2, hn, 0, 1800, GR_ARC_STYLE_OPEN, icolor);
}

main()
{
	TPoint *obj[N];					//����� ��������
	GrSetMode(GR_default_graphics); // ������ ����
	srand(time(0));
	int i;
	int RandSel = 4;		//���������� ������ ������
	for (i = 0; i < N; i++) //���� ����������� �������� ������
	{
		switch (RandSel)
		{
		case 0:
			obj[i] = new TPoint(GrMaxX() / 2, GrMaxY() / 2, rand() % 15 + 1);
			break;
		case 1:
			obj[i] = new TBox(GrMaxX() / 2, GrMaxY() / 2, rand() % 15 + 1, rand() % 20, rand() % 20);
			break;
		case 2:
			obj[i] = new TCircle(GrMaxX() / 2, GrMaxY() / 2, rand() % 15 + 1, rand() % 20);
			break;
		case 3:
			obj[i] = new TEllipse(GrMaxX() / 2, GrMaxY() / 2, rand() % 15 + 1, rand() % 30, rand() % 30);
			break;
		case 4:
			obj[i] = new TName(GrMaxX() / 3, GrMaxY() / 3, rand() % 15 + 1, rand() % 40 + 20, rand() % 40 + 20);
		}
		obj[i]->Show();
		RandSel = rand() % 4; //��������� ����������, ����� ����� ������ ����
	}
	GrKeyType key;
	do
	{
		while (!GrKeyPressed()) //���� �� ������ ������� ���������
		{
			GrSleep(5); //��������� ��������
			for (i = 0; i < N; i++)
			{
				obj[i]->MoveXY(); // ������� ������ ������
			}
		}

		key = GrKeyRead();
	} while (key != GrKey_Escape); //���� ����� ESC �������

	for (i = 0; i < N; i++) //������� ��� �������
	{
		delete obj[i];
	}
}
