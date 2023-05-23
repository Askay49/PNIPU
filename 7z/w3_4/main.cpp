#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <grx20.h>
#include <grxkeys.h>

#define N 100

struct TPoint //класс точки
{
	int x, y;	//координаты
	int vx, vy; //вектора скорости
	int color;	//цвет
	TPoint(int ix, int iy, int icolor);
	virtual ~TPoint(); //различные функции
	virtual void Draw(int icolor);
	void Show();
	void Hide();
	void MoveXY(int ix, int iy);
};
struct TBox : public TPoint //класс квадрата наследует переменные и функции от точки + свои
{
	int w, h; //ширина высота
	TBox(int ix, int iy, int icolor, int iw, int ih);
	virtual ~TBox();
	virtual void Draw(int icolor);
};
struct TCircle : public TPoint //также как с квадратом
{
	int r; //радиус
	TCircle(int ix, int iy, int icolor, int ir);
	virtual ~TCircle();
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

TPoint::~TPoint() //деструктор точки (выполняется при удалении)
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

TBox::TBox(int ix, int iy, int icolor, int iw, int ih) : TPoint(ix, iy, icolor) //с остальными фигурами точно такие же функции для них
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
	int number = 0;					//номер фигуры
	TPoint *obj[N];					//массив объектов
	GrSetMode(GR_biggest_graphics); // размер окна
	srand(time(0));					//точка отсчета рандома
	bool state = 0;					//переменная состояния объектов
	int i;
	int RandSel = rand() % 3; //селектор фигуры
	int count = 0;			  //счетчик

	GrKeyType key;
	do
	{
		while (!GrKeyPressed())
		{
			GrSleep(5); //небольшая задержка
			if (state)	//если состояние ==1
			{
				count = 0;					 //обнуляем счетчик
				for (i = 0; i < number; i++) //и в цикле проверяем все ли фигуры пришли в нужную точку (считаем сколько их пришло)
				{
					if (obj[i]->x < GrMaxX() / 2 + 10 && obj[i]->x > GrMaxX() / 2 - 10 && obj[i]->y > GrMaxY() / 2 - 10 && obj[i]->y < GrMaxY() / 2 + 10)
					{
						count++;
					}
				}

				if (count == number) //если все фигуры пришли в нужную точку
				{
					state = 0; //меняем состояние на 0
				}
			}

			for (i = 0; i < number; i++) //цикл движения фигур
			{
				if (state == 0) //если состояние 0
				{
					obj[i]->vx = rand() % 15 - 7; //случайно меняем вектора
					obj[i]->vy = rand() % 15 - 7;
				}
				else
				{
					obj[i]->vx = (GrMaxX() / 2 - obj[i]->x) / 10; //если состояние 1, вектора в центр экрана
					obj[i]->vy = (GrMaxY() / 2 - obj[i]->y) / 10;
				}

				obj[i]->MoveXY(obj[i]->x + obj[i]->vx, obj[i]->y + obj[i]->vy); //двигаем фигуру на вектора выше посчитанные
			}
			if (rand() % 100 == 50) //в случайные моменты времени меняем состояние на 1
				state = 1;
		}
		key = GrKeyRead();
		switch (key)
		{
		case GrKey_Space: //если нажат пробел создаем новую фигуру
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
			RandSel = rand() % 3; //обновляем селектор фигуры
			number++;			  //и прибавляем количество фигур
			break;

		case GrKey_Delete:			//если нажат делит
			GrClearScreen(0);		//чистим экран
			delete obj[number - 1]; //удаляем последний объект
			number--;				//и вычитаем номер фигуры
			break;
		case GrKey_F1: //на F1 мы можем сами поменять состояние фигур
			state = !state;
		}
	} while (key != GrKey_Escape); //если нажат ESC

	for (i = 0; i < N; i++) //удаляем все объекты
	{
		delete obj[i];
	}
}
