#include <bits/stdc++.h>
#include <graphics.h>

const int NR = 5;

class Point
{
    const char *_name;
    int _dim;
    int *_comp;

public:
        Point ();
        Point (const char*, int, ...);
        ~Point ();
        friend std::ostream& operator << (std::ostream&, const Point&);
        float dist (const Point&);
        friend float operator * (const Point&, const Point&); // produs scalar, presupunem ca A si B sunt vectori
        void drawPoint (); // 2D
        void drawLine (const Point&);
};

Point :: Point (): _dim(0) // sa fie, nu prea are sens totusi
{
    char *nothing = (char*) malloc (_dim * sizeof(char));
    *nothing = '\0';

    memcpy ((char*)(&_name), (char*)(&nothing), sizeof(nothing));

    int *_comp = (int*) malloc (_dim * sizeof(int));
    *_comp = 0;
};

Point :: Point (const char* name, int dim, ...)
{
    memcpy ((char*)(&_name), (char*)(&name), sizeof(name));
    _dim = dim;

    _comp = (int*) calloc (dim, sizeof(int));

    va_list lp;
    va_start (lp, dim);

    for (int i = 0; i < dim; ++i)
        _comp[i] = va_arg (lp, int);

    va_end(lp);
}

Point :: ~Point ()
{
    _dim = 0;
    delete[] _name;
    delete[] _comp;
}

float operator * (const Point &localP1, const Point &localP2)
{
    float dotProduct = 0;

    if (localP1._dim != localP2._dim)
        return dotProduct;

    for (int i = 0; i < localP1._dim; ++i)
        dotProduct += localP1._comp[i] * localP2._comp[i];

    return dotProduct;
}

float Point :: dist (const Point &localP)
{
    float distance = 0;

    if (_dim != localP._dim)
        return distance;

    for (int i = 0; i < _dim; ++i)
        distance += (_comp[i] - localP._comp[i]) * (_comp[i] - localP._comp[i]);

    distance = sqrt (distance);

    return distance;
}

std::ostream& operator << (std::ostream &out, const Point &localP)
{
    if (!localP._dim)
        return out;

    out << localP._name << "(";

    for (int i = 0; i < localP._dim - 1; ++i)
        out << localP._comp[i] << ", ";

    out << localP._comp[localP._dim - 1] << ")";

    return out;
}

void Point :: drawPoint ()
{
    if (_dim != 2)
        return;

    auto newX = [] (int _arg) -> decltype(_arg) {
        return getmaxx() / 2 + NR * _arg;
    };

    auto newY = [] (int _arg) -> decltype(_arg) {
        return getmaxy() / 2 - NR * _arg;
    };

    circle (newX(_comp[0]), newY(_comp[1]), 2);
    outtextxy (newX(_comp[0]) - 17, newY(_comp[1]) - 8, (char*)(_name));
}

void Point :: drawLine (const Point& localP)
{
    if (_dim != 2 || localP._dim != 2)
        return;

    auto newX = [] (int _arg) -> decltype(_arg) {
        return getmaxx() / 2 + NR * _arg;
    };

    auto newY = [] (int _arg) -> decltype(_arg) {
        return getmaxy() / 2 - NR * _arg;
    };

    line (newX(_comp[0]), newY(_comp[1]), newX(localP._comp[0]), newY(localP._comp[1]));
}

void drawFunction (std::function<int(int)> f, bool val, ...)
{
    auto newX = [] (int _arg) -> decltype(_arg) {
        return getmaxx() / 2 + NR * _arg;
    };

    auto newY = [] (int _arg) -> decltype(_arg) {
        return getmaxy() / 2 - NR * _arg;
    };

    va_list lp;
    va_start (lp, val);

    int inf = -getmaxx()/2;
    int sup = -inf;

    if (val)
    {
        inf = va_arg (lp, int);
        sup = va_arg(lp, int);
    }

    va_end (lp);

    for (int i = inf; i <= sup; i++)
    {
        Point localP ("", 2, i, (int) f(i));
        localP.drawPoint();

        if (i != inf)
        {
            Point auxP ("", 2, i-1, (int) f(i-1));
            localP.drawLine(auxP);
        }
    }
}

auto startGraphic = []()
{
    int gd = DETECT, gm;
    initgraph(&gd, &gm, "C:\\TC\\BGI");

    outtextxy (10, 10, "Geometrie computationala");

    line (0, getmaxy()/2, getmaxx(), getmaxy()/2);
    line (getmaxx()/2, 0, getmaxx()/2, getmaxy());

    outtextxy (getmaxx()/2 + 5, 0, "x");
    outtextxy (getmaxx() - 15, getmaxy()/2 - 18, "y");
    circle (getmaxx()/2, getmaxy()/2, 3);
};

auto stopGraphic = []()
{
    std::cout << "\nApasati o tasta pentru a opri: ";
    char tasta;
    std::cin >> tasta;

    closegraph();
};

int main ()
{
    startGraphic ();

    Point A ("A", 2, 0, 5);
    A.drawPoint();

    Point B ("B", 2, 5, 0);
    B.drawPoint();

    Point C ("C", 2, 0, -5);
    C.drawPoint();

    Point D ("D", 2, -5, 0);
    D.drawPoint();

    A.drawLine (B);
    B.drawLine (C);
    C.drawLine (D);
    D.drawLine (A);

    drawFunction ([](int x) -> decltype(x) {
        return x*x;
    }, false);

    drawFunction ([](int x) -> decltype(x) {
        return -x*x;
    }, false);

    stopGraphic ();
    return 0;
}
