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
	TPoint(int ix, int iy, int icolor); //дальше функции точки
	virtual ~TPoint();
	virtual void Draw(int icolor);
	void Show();
	void Hide();
	void MoveXY(int ix, int iy);
	virtual int SizeX();
	virtual int SizeY();
};
struct TBox : public TPoint //класс квадрата наслеует функции и переменные точки + свои
{
	int w, h; //ширина и высота
	TBox(int ix, int iy, int icolor, int iw, int ih);
	virtual ~TBox();
	virtual void Draw(int icolor);
	virtual int SizeX();
	virtual int SizeY();
};
struct TCircle : public TPoint //также как с квадратом
{
	int r; //радиус
	TCircle(int ix, int iy, int icolor, int ir);
	virtual ~TCircle();
	virtual void Draw(int icolor);
	virtual int SizeX();
	virtual int SizeY();
};

TPoint::TPoint(int ix, int iy, int icolor) //конструктор (выполняется при создании), просто присваиваются значения переменным
{
	x = ix;
	y = iy;
	vx = rand() % 7 - 3;
	vy = rand() % 7 - 3;
	color = icolor;
}

TPoint::~TPoint() //деструктор (выполняется при удалении)
{
	Hide();
}

void TPoint::Draw(int icolor) //функция отрисовки
{
	GrPlot(x, y, icolor);
	GrPlot(x + 1, y, icolor);
	GrPlot(x, y + 1, icolor);
	GrPlot(x + 1, y + 1, icolor);
}
int TPoint::SizeX() //функция расчитывающая размер по X
{
	return 1;
}
int TPoint::SizeY() //функция расчитывающая размер по Y
{
	return 1;
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
	Hide(); //скрыть
	x = ix; //изменить координаты
	y = iy;
	Show(); //показать
}

TBox::TBox(int ix, int iy, int icolor, int iw, int ih) : TPoint(ix, iy, icolor) //с остальными фигурами тоже самое все
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
	int number = 0;					//количество фигур на экране
	TPoint *obj[N];					//массив фигур
	GrSetMode(GR_biggest_graphics); // размер окна
	srand(time(0));					//точка отсчета рандомной функции
	int i;
	int RandSel = rand() % 3; //селектор фигуры

	GrKeyType key;
	do
	{
		while (!GrKeyPressed()) //бесконечный цикл, пока не нажата кнопка
		{
			GrSleep(1); //небольшая задержка

			for (i = 0; i < number; i++) //цикл перемещающий фигуры
			{
				if (obj[i]->x + obj[i]->vx - obj[i]->SizeX() < 0 || obj[i]->x + obj[i]->vx + obj[i]->SizeX() > GrMaxX()) //проверка выхода за границы экрана по оси X
					obj[i]->vx = -obj[i]->vx;																			 //меняем вектор на противоположный
				if (obj[i]->y + obj[i]->vy - obj[i]->SizeY() < 0 || obj[i]->y + obj[i]->vy + obj[i]->SizeY() > GrMaxY()) //проверка выхода за границы экрана по оси Y
					obj[i]->vy = -obj[i]->vy;																			 //меняем вектор на противоположный

				obj[i]->MoveXY(obj[i]->x + obj[i]->vx, obj[i]->y + obj[i]->vy); //двигаем
			}
		}
		key = GrKeyRead();
		switch (key) //обработчик кнопок
		{
		case GrKey_Space: //если пробел, создаем случайную фигуру
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
			RandSel = rand() % 3; //обновляем селектор фигуры
			number++;			  //прибавляем номер фигуры
			break;

		case GrKey_Delete: //если делит, удаляем и вычитаем номер
			GrClearScreen(0);
			delete obj[number - 1];
			number--;
		}
	} while (key != GrKey_Escape); //если нажат ESC, выходим из цикла

	for (i = 0; i < N; i++)
	{
		delete obj[i]; //удаляем все фигуры
	}
}
