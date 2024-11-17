//#include <iostream>
//#include <cmath>
//#include <windows.h>
//using namespace std;
//
//class Equation {
//public:
//    virtual void findRoots() const = 0;
//    virtual ~Equation() {}
//};
//
//class LinearEquation : public Equation {
//    double a, b;
//public:
//    LinearEquation(double a, double b) : a(a), b(b) {}
//    void findRoots() const override {
//        if (a != 0)
//            cout << "Корінь: x = " << -b / a << endl;
//        else
//            cout << (b == 0 ? "Безліч розв'язків" : "Немає розв'язків") << endl;
//    }
//};
//
//class QuadraticEquation : public Equation {
//    double a, b, c;
//public:
//    QuadraticEquation(double a, double b, double c) : a(a), b(b), c(c) {}
//    void findRoots() const override {
//        if (a == 0) {
//            LinearEquation(b, c).findRoots();
//            return;
//        }
//        double D = b * b - 4 * a * c;
//        if (D > 0)
//            cout << "Корені: x1 = " << (-b + sqrt(D)) / (2 * a)
//            << ", x2 = " << (-b - sqrt(D)) / (2 * a) << endl;
//        else if (D == 0)
//            cout << "Один корінь: x = " << -b / (2 * a) << endl;
//        else
//            cout << "Немає дійсних коренів" << endl;
//    }
//};
//
//int main() {
//    SetConsoleCP(1251);
//    SetConsoleOutputCP(1251);
//
//    Equation* eq1 = new LinearEquation(2, -4);
//    eq1->findRoots();
//    delete eq1;
//
//    Equation* eq2 = new QuadraticEquation(1, -3, 2);
//    eq2->findRoots();
//    delete eq2;
//
//    return 0;
//}

#include <iostream>
#include <fstream>
#include <vector>
#include <memory>
#include <windows.h>


using namespace std;

class Shape {
public:
    virtual ~Shape() = default;
    virtual void Show() const = 0;
    virtual void Save(ofstream& out) const = 0;
    virtual void Load(ifstream& in) = 0;
};

class Square : public Shape {
private:
    int x, y, side;
public:
    Square(int x = 0, int y = 0, int side = 0) : x(x), y(y), side(side) {}

    void Show() const override {
        cout << "Квадрат: (" << x << ", " << y << "), Сторона = " << side << endl;
    }

    void Save(ofstream& out) const override {
        out << "Square " << x << " " << y << " " << side << endl;
    }

    void Load(ifstream& in) override {
        in >> x >> y >> side;
    }
};

class Rectangle : public Shape {
private:
    int x, y, width, height;
public:
    Rectangle(int x = 0, int y = 0, int width = 0, int height = 0)
        : x(x), y(y), width(width), height(height) {}

    void Show() const override {
        cout << "Прямокутник: (" << x << ", " << y << "), Ширина = " << width << ", Висота = " << height << endl;
    }

    void Save(ofstream& out) const override {
        out << "Rectangle " << x << " " << y << " " << width << " " << height << endl;
    }

    void Load(ifstream& in) override {
        in >> x >> y >> width >> height;
    }
};

class Circle : public Shape {
private:
    int cx, cy, radius;
public:
    Circle(int cx = 0, int cy = 0, int radius = 0) : cx(cx), cy(cy), radius(radius) {}

    void Show() const override {
        cout << "Коло: (" << cx << ", " << cy << "), Радіус = " << radius << endl;
    }

    void Save(ofstream& out) const override {
        out << "Circle " << cx << " " << cy << " " << radius << endl;
    }

    void Load(ifstream& in) override {
        in >> cx >> cy >> radius;
    }
};

void SaveShapes(const vector<shared_ptr<Shape>>& shapes, const string& filename) {
    ofstream out(filename);
    for (const auto& shape : shapes) {
        shape->Save(out);
    }
}

void LoadShapes(vector<shared_ptr<Shape>>& shapes, const string& filename) {
    ifstream in(filename);
    string type;
    while (in >> type) {
        if (type == "Square") {
            auto square = make_shared<Square>();
            square->Load(in);
            shapes.push_back(square);
        }
        else if (type == "Rectangle") {
            auto rectangle = make_shared<Rectangle>();
            rectangle->Load(in);
            shapes.push_back(rectangle);
        }
        else if (type == "Circle") {
            auto circle = make_shared<Circle>();
            circle->Load(in);
            shapes.push_back(circle);
        }
    }
}

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    
    vector<shared_ptr<Shape>> shapes = {
        make_shared<Square>(1, 1, 10),
        make_shared<Rectangle>(2, 2, 20, 10),
        make_shared<Circle>(5, 5, 7)
    };

    SaveShapes(shapes, "shapes.txt");

    vector<shared_ptr<Shape>> loadedShapes;
    LoadShapes(loadedShapes, "shapes.txt");

    for (const auto& shape : loadedShapes) {
        shape->Show();
    }

    return 0;
}






