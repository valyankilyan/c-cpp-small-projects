#include <iostream>

#include "../include/line.h"
#include "../include/point.h"
using namespace std;

int main() {
    Point p1 = Point(1, 2);
    Point p2 = Point(0, 0);
    // cin >> p2;

    cout << "p1 = " << p1 << endl;
    cout << "p2 = " << p2 << endl;

    cout << endl;
    cout << p1 << " + " << p2 << " = " << p1 + p2 << endl;
    cout << p1 << " - " << p2 << " = " << p1 - p2 << endl;
    cout << p1 << " * " << 10 << " = " << p1 * 10 << endl;
    cout << p1 << " / " << 10 << " = " << p1 / 10 << endl;

    Point p3 = p1;
    cout << "p3 = " << p3 << endl;
    p3 += p1;
    cout << "p3+= p1 = " << p3 << endl;
    p3 -= p1;
    cout << "p3-= p1 = " << p3 << endl;
    p3 /= 2;
    cout << "p3/= 2 = " << p3 << endl;
    p3 *= 2;
    cout << "p3*=2 = " << p3 << endl;

    cout << "p1 == p3 = " << (p1 == p3) << endl;
    cout << "p1 != p2 = " << (p1 != p2) << endl;

    cout << "p1 = " << p1 << endl;
    cout << "p2 = " << p2 << endl;
    cout << "p3 = " << p3 << endl;

    cout << "p1 -> p2 = " << p1.vector_lenght(p2) << endl;

    Line l = Line();
    l.push_back(p1);
    l.push_back(p2);
    l.push_back(p3);

    cout << "printtin line from previous points: " << l << endl;

    Line* line = new Line();

    int n = 5;
    for (int i = 0; i < n; i++) {
        Point np = Point(i, i);
        line->push_back(np);
    }

    cout << endl
         << "line: " << *line << endl;
    line->delete_point(3);
    cout << "line after delete(3): " << *line << endl;
    line->add_point(2, Point(2, 10));
    cout << "line after addition point 2, 10 on 2nd place: " << *line << endl;
    line->set_point(2, Point(10, 2));
    cout << "line after settin 2nd point to 10, 2: " << *line << endl;


    Line* new_line = new Line(line);
    cout << *new_line << endl;
    line->pop_back();
    cout << *new_line << endl;

    // for (int i = n; i > 0 ; i--) {
    //     Point np = Point(i, i);
    //     cline->push_back(np);
    // }

    // cout << "line = " << *line << endl;
    // cout << "cline = " << *cline << endl;

    // cout << "trying to make an array\n";

    // Line** line_array = new Line*[2];
    // line_array[0] = line;
    // line_array[1] = cline;
    // cout << *line_array[0] << endl << *line_array[1] << endl;
    // cout << line_array[0]->perimeter() << " " << line_array[1]->perimeter() << endl;

    // cout << "cline before deleting: " << *cline << endl;
    // cline->delete_point(3);
    // cout << "cline after deleting third point: " << *cline << endl;
    // cline->set_point(2, Point(1, 1));
    // cout << *cline << endl;

    // delete p1;
    // delete p2;
}