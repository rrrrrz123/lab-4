#include <iostream>
#include <vector>
#include <list>
#include <fstream>
#include <string>
#include <algorithm>
#include <iterator>
using namespace std;
class Car
{
    string model;
    vector <double> fuel;
    int velocity;
    int power;
public:
    Car() {
        model = "Unknown";
        fuel = {0.0, 0.0, 0.0};
        velocity = 0;
        power = 0;
    }
    Car(string m, vector<double> f, int v, int p) : model(m), fuel(f), velocity(v), power(p) {}
    //конструкторы копирования, перемещения и операторы присваивания писать не нужно
    //в классе нет указателей и динамической памяти, а string и vector сами правильно копируются и чистят память

    //перегрузка оператора < для сортировки list::sort() без параметров
    bool operator<(const Car& other) const {
        return fuel[2] < other.fuel[2];
    }

    //перегрузка оператора вывода в поток <<
    friend ostream& operator<<(ostream& os, const Car& car) {
        os << "Model: " << car.model
           << ", fuel: " << car.fuel[0] << "/" << car.fuel[1] << "/" << car.fuel[2]
           << ", speed: " << car.velocity
           << ", power: " << car.power;
        return os;
    }
};
int main() {
    //файлы для чтения и записи
    ifstream fin("input.txt");
    ofstream fout("output.txt");

    if (!fin.is_open() || !fout.is_open()) {
        cout << "error opening files" << endl;
        return 1;
    }

    list<Car> carList;
    string m;
    double f1, f2, f3;
    int v, p;
    while (fin >> m >> f1 >> f2 >> f3 >> v >> p) {
        vector<double> tempFuel = {f1, f2, f3};
        Car tempCar(m, tempFuel, v, p);
        carList.push_back(tempCar);
    }
    fout << "Original List\n";
    for (const Car& car : carList) {
        fout << car << endl;
    }
    fout << endl;

    //копирование списка в вектор
    vector<Car> carVector;
    copy(carList.begin(), carList.end(), back_inserter(carVector));
    //сортировка списка методом sort() без параметров
    carList.sort();
    //вывод отсортированного списка в файл
    fout << "Sorted List\n";
    for (const Car& car : carList) {
        fout << car << endl;
    }
    fout << endl;
    //вывод скопированного вектора в файл
    fout << "Copied Vector\n";
    for (const Car& car : carVector) {
        fout << car << endl;
    }
    fout << endl;
    cout << "Data saved to output.txt" << endl;


    fin.close();
    fout.close();

    return 0;
}