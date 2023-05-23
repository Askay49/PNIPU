#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <grx20.h>
#include <grxkeys.h>

#define N 100

struct TPoint //класс точки
{
	int x, y;	//координаты
	int vx, vy; //вектора
	int s;		//определяет расстояние до объекта
	int color;	//цвет
	TPoint(int ix, int iy, int icolor);
	virtual ~TPoint();			   //деструктор
	virtual void Draw(int icolor); //отрисовка
	void Show();				   //показать объект
	void Hide();				   //спрятать объект
	void MoveXY(int ix, int iy);   //движение
};
struct TBox : public TPoint //класс квадрата наследует переменные и функции от точки
{
	int w, h; //ширина, высота
	TBox(int ix, int iy, int icolor, int iw, int ih);
	virtual ~TBox();			   //свой деструктор
	virtual void Draw(int icolor); //своя отрисвока
};
struct TCircle : public TPoint //круг
{
	int r; //радиус
	TCircle(int ix, int iy, int icolor, int ir);
	virtual ~TCircle();
	virtual void Draw(int icolor);
};

TPoint::TPoint(int ix, int iy, int icolor) //конструктор
{
	x = ix;
	y = iy;
	vx = rand() % 7 - 3; //случайные вектора и s
	vy = rand() % 7 - 3;
	s = rand() % 60 + 15;
	color = icolor;
}

TPoint::~TPoint()
{
	Hide(); //при удалении спрятать
}

void TPoint::Draw(int icolor)
{
	GrPlot(x, y, icolor); //точка состоит из 4 пикселей
	GrPlot(x + 1, y, icolor);
	GrPlot(x, y + 1, icolor);
	GrPlot(x + 1, y + 1, icolor);
}

void TPoint::Show()
{
	Draw(color); //отрисовка своим цветом
}

void TPoint::Hide()
{
	Draw(0); //отрисовка черным
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
	GrBox(x - w / 2, y - h / 2, x + (w - w / 2), y + (h - h / 2), icolor); // квадрат собственно
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
	int number = 1;					//количество элементов
	TPoint *obj[N];					//массив объектов
	GrSetMode(GR_biggest_graphics); // размер окна
	srand(time(0));					//точка отсчета рандомной функции
	int i;
	int RandSel = rand() % 3;								 //селектор объекта
	obj[0] = new TCircle(GrMaxX() / 2, GrMaxY() / 2, 10, 2); // создание основной фигуры
	obj[0]->Show();											 //показать ее

	GrKeyType key;
	do
	{
		while (!GrKeyPressed()) //пока не нажата клавиша
		{
			GrSleep(5);																						  //задержка
			obj[0]->MoveXY(obj[0]->x + obj[0]->vx + rand() % 7 - 3, obj[0]->y + obj[0]->vy + rand() % 7 - 3); //рандомное перемещение зеленой окружности
			if (obj[0]->x < 0)																				  //условия выхода за границу экрана и перемещение в другой конец экрана
				obj[0]->x = GrMaxX();
			if (obj[0]->y < 0)
				obj[0]->y = GrMaxY();
			if (obj[0]->x > GrMaxX())
				obj[0]->x = 0;
			if (obj[0]->y > GrMaxY())
				obj[0]->y = 0;

			for (i = 1; i < number; i++) //цикл по объектам
			{
				obj[i]->vx = (obj[0]->x - obj[i]->x) / obj[i]->s + rand() % 7 - 3; //задание векторов к зеленой окружности
				obj[i]->vy = (obj[0]->y - obj[i]->y) / obj[i]->s + rand() % 7 - 3;
				obj[i]->MoveXY(obj[i]->x + obj[i]->vx, obj[i]->y + obj[i]->vy); //перемещение по векторам
			}
		}
		key = GrKeyRead();
		switch (key) //обработка клавиш
		{
		case GrKey_Space: //по пробелу создать случайную фигуру
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

		case GrKey_Delete: // по делиту удалить случайную фигуру
			GrClearScreen(0);
			delete obj[number - 1];
			number--;
		}
	} while (key != GrKey_Escape); //по ESC выйти

	for (i = 0; i < N; i++) //цикл удаляющий все объекты
	{
		delete obj[i];
	}
}
