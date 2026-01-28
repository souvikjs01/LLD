/**
 * ISP : Better to have many client specific interface than a large interface
 *                                or
 * You can not foced a class to implement a method that it is not satisfy
 */

#include<iostream>

using namespace std;

// Not following ISP
class Shape {
public:
    virtual double area() = 0;
    virtual double volume() = 0;
};

class Cube : public Shape {
private:
    double side;
public:
    Cube(double side) {
        this->side = side;
    }

    double area() override {
        return 6 * side * side;
    }
    double volume() override {
        return side * side * side;
    }
};

class Square : public Shape {
private:
    double side;

public:
    Square(double side) {
        this->side = side;
    }

    double area() override {
        return side*side;
    }
    double volume() override {
        throw logic_error("Square does not support volume");
    }
};

class Rectangle : public Shape {
private:
    double length;
    double height;
public:
    Rectangle(double length, double height) {
        this->length = length;
        this->height = height;
    }

    double area() override {
        return length * height;
    }
    double volume() override {
        throw logic_error("Rectangle does not support volume");
    }
};

int main() {
    Shape* sqr = new Square(5.0);
    Shape* rect = new Rectangle(8, 4);
    Shape* cube = new Cube(5);

    cout << "Square area: " << sqr->area() << endl;
    // cout << "Square volume: " << sqr->volume() << endl;
    cout << "Rectangle area: " << rect->area() << endl;
    // cout << "Rectangle volume: " << rect->volume() << endl;
    cout << "Cube area: " << cube->area() << endl;
    cout << "Cube volume: " << cube->volume() << endl;

    try{
        cout << "Square volume: " << sqr->volume() << endl;
    } catch(logic_error& e) {
        cout << "Exception " << e.what() << endl;
    }
    
    
    return 0;
}