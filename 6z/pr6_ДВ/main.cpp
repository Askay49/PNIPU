#include <stdio.h>
#include <stdlib.h>
#include <time.h>	 //для рандомной функции
#include <grx20.h>	 //графика
#include <grxkeys.h> //клавиши

#define N 100 //максимальное количество объектов

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
struct TBox : public TPoint //квадраты наследуют от точки большую часть + то что в них
{
	int w, h;
	TBox(int ix, int iy, int icolor, int iw, int ih);
	virtual ~TBox();
	virtual void Draw(int icolor);
	virtual void MoveXY();
};
struct TEllipse : public TPoint //квадраты наследуют от точки большую часть + то что в них
{
	int xa, ya;
	TEllipse(int ix, int iy, int icolor, int ixa, int iya);
	virtual ~TEllipse();
	virtual void Draw(int icolor);
};
struct TCircle : public TPoint // тоже самое с кругами
{
	int r;
	TCircle(int ix, int iy, int icolor, int ir);
	virtual ~TCircle();
	virtual void Draw(int icolor);
	virtual void MoveXY();
};
struct TName : public TPoint // структура инициалов
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

void TPoint::Show() //функция "показать"
{
	Draw(color);
}

void TPoint::Hide() //функция "спрятать" (отрисовывает черным)
{
	Draw(0);
}

void TPoint::MoveXY() //функция перемещения
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
void TBox::Draw(int icolor) //рисовалка квадрата
{
	GrBox(x - w / 2, y - h / 2, x + (w - w / 2), y + (h - h / 2), icolor);
}
void TBox::MoveXY() //движение квадрата с заменой цвета и размера
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
TCircle::TCircle(int ix, int iy, int icolor, int ir) : TPoint(ix, iy, icolor) //конструктор
{
	r = ir;
}
TCircle::~TCircle() //деструктор
{
	Hide();
}
void TCircle::Draw(int icolor) //рисовалка
{

	GrCircle(x, y, r, icolor);
}
void TCircle::MoveXY() // движение круга с рандомным цветом и размером
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
TEllipse::TEllipse(int ix, int iy, int icolor, int ixa, int iya) : TPoint(ix, iy, icolor) //кароче дальше тоже самое
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
void TName::Draw(int icolor) //отрисовка инициалов
{
	GrLine(x, y, x + wn * 2, y, icolor);
	GrEllipseArc(x + wn, y, wn / 2, hn / 2, 0, 1800, GR_ARC_STYLE_OPEN, icolor);

	GrEllipseArc(x + 100, y, wn / 2, hn / 4, 2700, 900, GR_ARC_STYLE_OPEN, icolor); //В
	GrEllipseArc(x + 100, y + hn / 2, wn / 2, hn / 4, 2700, 900, GR_ARC_STYLE_OPEN, icolor);
	GrLine(x + 100, y - hn / 4, x + 100, y + hn * 0.75, icolor);
}

main()
{
	TPoint *obj[N];					// создаем массив объектов
	GrSetMode(GR_default_graphics); //размер окна
	srand(time(0));					//точка отсчета рандома
	int i;
	int RandSel = 4;		//селектор фигуры
	for (i = 0; i < N; i++) //заполнение массива и отрисовка рандомными фигурами
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
			obj[i] = new TName(GrMaxX() / 2, GrMaxY() / 2, rand() % 15 + 1, rand() % 40 + 20, rand() % 40 + 20);
		}
		obj[i]->Show();
		RandSel = rand() % 5;
	}
	GrKeyType key;
	do
	{
		while (!GrKeyPressed()) //пока не наживаються клавиши...
		{
			GrSleep(5);				//ждем немного
			for (i = 0; i < N; i++) //двигаем каждую фигуру
			{
				obj[i]->MoveXY();
			}
		}

		key = GrKeyRead();
	} while (key != GrKey_Escape); //выходим если нажат ESC

	for (i = 0; i < N; i++) //удаляем все фигуры
	{
		delete obj[i];
	}
}
