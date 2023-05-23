#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <grx20.h>
#include <grxkeys.h>

#define N 100

struct TPoint //класс точки
{
	int x, y;							//координаты
	int vx, vy;							//вектора скорости
	int color;							//цвет
	TPoint(int ix, int iy, int icolor); //функции различные, дальше они описаны
	virtual ~TPoint();
	virtual void Draw(int icolor);
	void Show();
	void Hide();
	void MoveXY(int ix, int iy);
};
struct TBox : public TPoint //класс квадрата наследует переменные и функции точки + свои
{
	int w, h; //ширина, высота
	TBox(int ix, int iy, int icolor, int iw, int ih);
	virtual ~TBox();
	virtual void Draw(int icolor);
};
struct TCircle : public TPoint //тоже самое что с квадратом
{
	int r; //радиус
	TCircle(int ix, int iy, int icolor, int ir);
	virtual ~TCircle();
	virtual void Draw(int icolor);
};
struct TCursor : public TCircle //прицел наследует от круга
{
	TCursor(int ix, int iy, int icolor, int ir);
	virtual ~TCursor();
	virtual void Draw(int icolor);
};

TPoint::TPoint(int ix, int iy, int icolor) //конструктор точки (выполняется при создании)
{
	x = ix;
	y = iy;
	vx = rand() % 7 - 3;
	vy = rand() % 7 - 3;
	color = icolor;
}

TPoint::~TPoint() //деструктор точки(выполняется при удалении)
{
	Hide();
}

void TPoint::Draw(int icolor) //функция отрисовки точки (4 пикселя)
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

void TPoint::Hide() //функция "скрыть"
{
	Draw(0);
}

void TPoint::MoveXY(int ix, int iy) //функция движения
{
	Hide();
	x = ix;
	y = iy;
	Show();
}

TBox::TBox(int ix, int iy, int icolor, int iw, int ih) : TPoint(ix, iy, icolor) //также как с точкой дальше для остальных фигур
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
TCursor::TCursor(int ix, int iy, int icolor, int ir) : TCircle(ix, iy, icolor, ir)
{
	r = ir;
}
TCircle::~TCircle()
{
	Hide();
}
TCursor::~TCursor()
{
	Hide();
}
void TCircle::Draw(int icolor)
{

	GrCircle(x, y, r, icolor);
}
void TCursor::Draw(int icolor)
{
	GrCircle(x, y, r, icolor);
	GrLine(x + r, y, x + r + 10, y, icolor);
	GrLine(x - r, y, x - r - 10, y, icolor);
	GrLine(x, y - r, x, y - r - 10, icolor);
	GrLine(x, y + r, x, y + r + 10, icolor);
}
//****************************************************************
//****************************************************************
main()
{
	int number = 0;					//количество объектов
	TPoint *obj[N];					//массив объектов
	GrSetMode(GR_biggest_graphics); // размер окна
	srand(time(0));					//точка отсчета рандома
	int i;
	int RandSel = rand() % 3;										   //селектор объектов
	TCursor *cursor = new TCursor(GrMaxX() / 2, GrMaxY() / 2, 10, 20); //объект прицела
	cursor->Show();													   //показать прицел

	GrKeyType key;
	do
	{
		while (!GrKeyPressed()) //пока не нажата какая либо клавиша...
		{
			GrSleep(5); //ждем

			for (i = 0; i < number; i++) //движение всех объектов и перемещение их в другой конец экрана, если они ушли за границу экрана
			{
				obj[i]->MoveXY(obj[i]->x + obj[i]->vx, obj[i]->y + obj[i]->vy);
				if (obj[i]->x < 0)//если вышел за левую границу экрана
					obj[i]->x = GrMaxX();
				if (obj[i]->y < 0)//верхнюю
					obj[i]->y = GrMaxY();
				if (obj[i]->x > GrMaxX())//правую
					obj[i]->x = 0;
				if (obj[i]->y > GrMaxY())//левую
					obj[i]->y = 0;
			}
		}
		key = GrKeyRead();
		switch (key) //если нажата клавиша смотрит какая и выполняет то что нужно под заданую клавишу
		{
		case GrKey_F1: // F1 - создает объект рандомный
			switch (RandSel)
			{
			case 0:
				obj[number] = new TPoint(GrMaxX() / 2, GrMaxY() / 2, 15);//точка
				break;
			case 1:
				obj[number] = new TBox(GrMaxX() / 2, GrMaxY() / 2, 15, rand() % 20, rand() % 20);//квадрат
				break;
			case 2:
				obj[number] = new TCircle(GrMaxX() / 2, GrMaxY() / 2, 15, rand() % 20);//круг
			}
			obj[number]->Show();
			RandSel = rand() % 3;//случайное значение от 0 до 2
			number++;//прибавить номер
			break;
		case GrKey_Space: // пробел - удаляет объект если он внутри прицела и смещает массив объектов на 1, чтобы не было пустого объекта
			for (i = 0; i < number; i++)
			{
				if (obj[i]->x < cursor->x + cursor->r && obj[i]->x > cursor->x - cursor->r && obj[i]->y > cursor->y - cursor->r && obj[i]->y > cursor->y - cursor->r)
				{//условие если внутри прицела 
					obj[i]->Hide();//скрыть
					delete obj[i];//удалить
					for (int j = i; i < number; i++)
					{
						obj[j] = obj[j + 1];//смещает объекты в массиве
					}
					number--;//вычитает номер
				}
			}
			break;
		case GrKey_Up: //стрелочки перемещают прицел вверх
			cursor->MoveXY(cursor->x, cursor->y - 10);
			break;
		case GrKey_Down: //вниз
			cursor->MoveXY(cursor->x, cursor->y + 10);
			break;
		case GrKey_Left: //влево
			cursor->MoveXY(cursor->x - 10, cursor->y);
			break;
		case GrKey_Right: //вправо
			cursor->MoveXY(cursor->x + 10, cursor->y);
			break;
		case GrKey_Delete: //делит - удаляет последний созданный объект
			obj[number - 1]->Hide();
			delete obj[number - 1];
			number--;
		}
	} while (key != GrKey_Escape); //если эскейп, выходим

	for (i = 0; i < N; i++) //удаляем все объекты
	{
		delete obj[i];
	}
}
