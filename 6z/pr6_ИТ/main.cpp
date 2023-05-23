#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <grx20.h>
#include <grxkeys.h>

#define N 100 //количество фигур

struct TPoint //структура точки
{
	int x, y;
	int color;
	TPoint(int ix, int iy, int icolor);
	virtual ~TPoint();
	virtual void Draw(int icolor);
	void Show();
	void Hide();
	virtual void MoveXY(); // int ix, int iy);
};
struct TBox : public TPoint //структура квадрата наследует от точки
{
	int w, h;
	TBox(int ix, int iy, int icolor, int iw, int ih);
	virtual ~TBox();
	virtual void Draw(int icolor);
	virtual void MoveXY();
};
struct TEllipse : public TPoint //тоже самое с элипсом
{
	int xa, ya;
	TEllipse(int ix, int iy, int icolor, int ixa, int iya);
	virtual ~TEllipse();
	virtual void Draw(int icolor);
};
struct TCircle : public TPoint //и кругами
{
	int r;
	TCircle(int ix, int iy, int icolor, int ir);
	virtual ~TCircle();
	virtual void Draw(int icolor);
	virtual void MoveXY();
};
struct TName : public TPoint //и инициалами
{
	int wn, hn;
	TName(int ix, int iy, int icolor, int iwn, int ihn);
	virtual ~TName();
	virtual void Draw(int icolor);
};

TPoint::TPoint(int ix, int iy, int icolor) //конструктор точки
{
	x = ix;
	y = iy;
	color = icolor;
}

TPoint::~TPoint() //деструктор точки
{
	Hide();
}

void TPoint::Draw(int icolor) //функция отрисовки точки
{
	GrPlot(x, y, icolor);
	GrPlot(x + 1, y, icolor);
	GrPlot(x, y + 1, icolor);
	GrPlot(x + 1, y + 1, icolor);
}

void TPoint::Show() //функция "показать, отрисовывает фигуру"
{
	Draw(color);
}

void TPoint::Hide() //"спрятать" отрисовывает фигуру черным
{
	Draw(0);
}

void TPoint::MoveXY() // функция движения точки
{
	Hide();
	x = x + rand() % 7 - 3; // ix;
	y = y + rand() % 7 - 3; // iy;
	Show();
}
TBox::TBox(int ix, int iy, int icolor, int iw, int ih) : TPoint(ix, iy, icolor) //конструктор квадрата
{
	w = iw;
	h = ih;
}
TBox::~TBox() //деструктор квадрата
{
	Hide();
}
void TBox::Draw(int icolor) //ну кароче все как с точкой...
{
	GrBox(x - w / 2, y - h / 2, x + (w - w / 2), y + (h - h / 2), icolor);
}
void TBox::MoveXY() // у квадрата своя функция движения с рандомным изменением размера и цвета
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
void TCircle::MoveXY() // у круга также рандомно меняеться цвет и размер при движении
{
	Hide();
	color = rand() % 15 + 1;
	if (r > 25)
		r -= 3;
	else
		r = r + (rand() % 5 - 2);
	x = x + rand() % 7 - 3; // ix;
	y = y + rand() % 7 - 3; // iy;
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
void TName::Draw(int icolor) //функция отрисовки букв
{
	GrEllipseArc(x, y - hn / 2, wn / 2, hn, 1800, 3600, GR_ARC_STYLE_OPEN, icolor);
	GrLine(x + wn / 2, y - hn / 2, x + wn / 2, y + hn / 2, icolor); // И

	GrLine(x - wn / 2 + 70, y - hn / 2, x + wn / 2 + 70, y - hn / 2, icolor); //Т
	GrLine(x + 70, y - hn / 2, x + 70, y + hn / 2, icolor);
}

main()
{
	TPoint *obj[N];					//массив фигур
	GrSetMode(GR_default_graphics); //размер окна приложения
	srand(time(0));					//точка отсчета рандома
	int i;
	int RandSel = 4;		//переменная выбора фигуры
	for (i = 0; i < N; i++) //цикл создания случайных фигур
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
		obj[i]->Show();		  //показать созданную фигуру
		RandSel = rand() % 4; //обновляем случайное число
	}
	GrKeyType key;
	do
	{
		while (!GrKeyPressed()) //пока не нажата клавиша
		{
			GrSleep(5);				//небольшая задержка
			for (i = 0; i < N; i++) //цикл движения всех фигур
			{
				obj[i]->MoveXY();
			}
		}

		key = GrKeyRead();
	} while (key != GrKey_Escape); //пока не нажат ESC

	for (i = 0; i < N; i++) //цикл удаления всех фигур
	{
		delete obj[i];
	}
}
