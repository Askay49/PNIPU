// region comment
// #include <stdio.h>
// #include <stdlib.h>
// #include <time.h>
// #include <grx20.h>
// #include <windows.h>
// #define N 3
// struct TPoint
// {
// 	int x, y, h1;
// 	int color;
// 	TPoint(int ix, int iy, int icolor);
// 	virtual ~TPoint();
// 	virtual void Draw(int icolor);
// 	void Show();
// 	void Hide();
// 	virtual void MoveXY(int y); //int ix, int iy);
// };
// struct TBox : public TPoint
// {
// 	int w, h1, h2, hr;
// 	TBox(int ix, int iy, int icolor, int iw, int ih);
// 	virtual ~TBox();
// 	virtual void Draw(int icolor);
// 	virtual void MoveXY(int y);
// };
// struct TBird : public TPoint
// {
// 	int y, r;
// 	TBird(int ix, int iy, int r, int icolor);
// 	virtual ~TBird();
// 	virtual void Draw(int icolor);
// 	virtual void MoveXY(int y);
// };
// TPoint::TPoint(int ix, int iy, int icolor)
// {
// 	x = ix;
// 	y = iy;
// 	color = icolor;
// }
// TPoint::~TPoint()
// {
// 	Hide();
// }
// void TPoint::Draw(int icolor)
// {
// 	GrPlot(x, y, icolor);
// 	GrPlot(x + 1, y, icolor);
// 	GrPlot(x, y + 1, icolor);
// 	GrPlot(x + 1, y + 1, icolor);
// }
// void TPoint::Show()
// {
// 	Draw(color);
// }
// void TPoint::Hide()
// {
// 	Draw(0);
// }
// void TPoint::MoveXY(int y) //int ix, int iy)
// {
// 	Hide();
// 	// x = x + rand() % 7 - 3; //ix;
// 	// y = y + rand() % 7 - 3; //iy;
// 	Show();
// }
// //****************************************************************
// TBox::TBox(int ix, int iy, int icolor, int iw, int ih) : TPoint(ix, iy, icolor)
// {
// 	w = iw;
// }
// TBox::~TBox()
// {
// 	Hide();
// }
// void TBox::Draw(int icolor)
// {
// 	GrBox(x - w / 2, y - h1, x + w / 2, y, icolor);
// 	GrBox(x - w / 2, y - h2 - GrMaxY() + h2, x + w / 2, y - GrMaxY() + h2, icolor);
// }
// void TBox::MoveXY(int y) //int ix, int iy)
// {
// 	Hide();
// 	x--;
// 	if (x < 0)
// 	{
// 		int hr = 350; //rand() % 150 + 200;
// 		x = GrMaxX();
// 		h1 = hr - rand() % 200 - 75;
// 		h2 = hr - h1;
// 	}
// 	Show();
// }
// TBird::TBird(int ix, int iy, int ir, int icolor) : TPoint(ix, iy, icolor)
// {
// 	y = iy;
// 	r = ir;
// }
// TBird::~TBird()
// {
// 	Hide();
// }
// void TBird::Draw(int icolor)
// {
// 	GrCircle(x, y, r, icolor);
// }
// void TBird::MoveXY(int iy) //int ix, int iy)
// {
// 	Hide();
// 	y += iy;
// 	//y = iy;
// 	Show();
// }
// endregion comment