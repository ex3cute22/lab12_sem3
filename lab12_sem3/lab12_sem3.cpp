#include <iostream>
#include <stdlib.h>
#include <locale>
#include <Windows.h>
#include <conio.h>
#include <locale.h>
#define fflush while (getchar() != '\n')
#define AMOUNTCAR 3 
using namespace std;

class Transport {
public:
    virtual void Buy() = 0;
    virtual void Drive() = 0;
};

class AirTransport: public Transport{
protected:
    string name;
    int numberOfPassengers;
public:
    AirTransport() {
        name = "";
    }
    AirTransport(string name) {
        this->name = name;
        numberOfPassengers = 0;
    }
    AirTransport(string name, int numberOfPassengers) {
        this->name = name;
        this->numberOfPassengers = numberOfPassengers;
    }
    void Buy() override {
        cout << "Пилот купил " + name  + " (Кол-во пассажиров: " << numberOfPassengers << ")"<< endl;
    }
    void Drive() override {
        cout << "Пилот полетел на " + name << endl << endl;
    }
    virtual void Display() {
        cout << "Название транспорта: " + name << endl;
    }
    virtual void Read() {
        cout << "Введите название транспорта" << endl;
        cin >> name;
    }
    AirTransport& operator=(const AirTransport& a) {
        name = a.name;
        numberOfPassengers = a.numberOfPassengers;
        return *this;
    }
};

class LandTransport : public Transport{
    protected : string name = " ";
    public:
        LandTransport() {
            name = " ";
        }
        LandTransport(string name) {
            this->name = name;
        }
        void Buy() override{
            cout << "Водитель купил " + name<< endl;
        }
        void Drive() override{
            cout << "Водитель поехал на " + name << endl << endl;
        }
        virtual void Display() {
            cout << "Название транспорта: " + name << endl;
        }
        virtual void Read() {
            cout << "Введите название транспорта" << endl;  
            cin >> name;
        }
        //Перегрузка оператора присваивания
        LandTransport& operator=(const LandTransport& a) {
            name = a.name;
            return *this;
        }
        friend std::ostream& operator<<(std::ostream& os, const LandTransport& a)
        {
            os << a.name << endl;
            return os;
        }
};

class Moto : public LandTransport {
    string name;
    int year;
    int price;

public :
    Moto() : LandTransport("Мотоцикл"){
        name = " ";
        year = 0;
        price = 0;
    }
    Moto(string name, int year, int price) : LandTransport("Мотоцикл " + name) {
        this->name = name;
        this->year = year;
        this->price = price;
    }
    void Read() override {
        LandTransport::Read();
        cout << "Марка: ";
        cin >> name;
        cout << "Год: ";
        cin >> year;
        cout << "Цена: ";
        cin >> price;
    }
    
    void Display() override{
        LandTransport::Display();
        cout << "Марка: " << name << "\tГод: " << year << "\tЦена: " << price << endl;
    }
    friend std::ostream& operator<<(std::ostream& os, const Moto& a)
    {
        cout << (LandTransport)a;
        cout << "Мотоцикл " << a.name << " " << a.year << " года стоит " << a.price << " руб." << endl;
        return os;
    }
};

class Plane : public AirTransport {
protected:
    string name;
    int numberOfPassengers;
    int MaxHeight;
public:
    Plane() : AirTransport("Самолёт") {
        name = "";
        numberOfPassengers = 0;
        MaxHeight = 0;
    }
    Plane(string name, int numberOfPassengers, int MaxHeight) : AirTransport("Самолёт " + name, numberOfPassengers) {
        this->name = name;
        this->numberOfPassengers = numberOfPassengers;
        this->MaxHeight = MaxHeight;
    }
    void Read() override {
        AirTransport::Read();
        cout << "Название: ";
        cin >> name;
        cout << "Кол-во пассажиров: ";
        cin >> numberOfPassengers;
        cout << "Максимальная высота: ";
        cin >> MaxHeight;
    }
    void Display() override {
        AirTransport::Display();
        cout << "Название: " << name << "\tКол-во пассажиров: " << numberOfPassengers << " \tМаксимальная высота: " << MaxHeight << endl;
    }
};

class Car : public LandTransport {
protected:
    string marka; //Марка
    string model; //Модель
    float engine; //Объём двигателя
    int power; //Кол-во л.с.
    string transmission; //Коробка передач
    string color; //Цвет машины
    int year; //Год автомобиля
    int price; //Цена
    static int count;
    string* people; //владельцы
    int countPeople; //кол-во владельцев
public:
    //Конструктор без параметров
    Car() : LandTransport("Автомобиль"){
        marka = " ";
        model = " ";
        engine = 0;
        power = 0;
        transmission = " ";
        color = " ";
        year = 0;
        price = 0;
        countPeople = 0;
        count++;
    }
    //Конструктор с одним параметром
    Car(string _marka) : LandTransport("Автомобиль " + _marka) {
        marka = " ";
        marka = _marka;
        model = " ";
        engine = 0;
        power = 0;
        transmission = " ";
        color = " ";
        year = 0;
        price = 0;
        countPeople = 0;
        count++;
    }
    //Конструктор со всеми параметрами
    Car(string _marka, string _model, float _engine, int _power, string _transmission, string _color, int _year, int _price, int _countPeople, string* _people) : LandTransport("Автомобиль " + _marka) {
        marka = " ";
        model = " ";
        marka = _marka;
        model = _model;
        engine = _engine;
        power = _power;
        transmission = " ";
        color = " ";
        transmission = _transmission;
        color = _color;
        year = _year;
        price = _price;
        countPeople = _countPeople;
        //Динамический обьект
        people = new string[countPeople];
        for (int i = 0; i < countPeople; i++) {
            people[i] = _people[i];
        }
        count++;
    }

    //Деструктор
    ~Car() {
        Car::RemoveItem();
    }
    void Read() override{
        LandTransport::Read();
        printf("Введите марку машины: ");
        cin >> marka;
        printf("Введите модель машины: ");
        cin >> model;
        printf("Введите объём двигателя: ");
        scanf_s("%f", &engine);
        fflush;
        printf("Введите кол-во л.с.: ");
        scanf_s("%d", &power);
        fflush;
        printf("Введите тип трансмиссии(коробка передач): ");
        cin >> transmission;
        printf("Введите цвет автомобиля: ");
        cin >> color;
        printf("Введите год автомобиля: ");
        scanf_s("%d", &year);
        fflush;
        printf("Введите цену за данный автомобиль: ");
        scanf_s("%d", &price);
        fflush;
        printf("\n");
    }
    void Display() override{
        LandTransport::Display();
        if (marka != " ")cout << marka << endl;
        if (model != " ") cout << model << endl;
        if (engine != 0) cout << engine << endl;
        if (power != 0)cout << power << endl;
        if (transmission != " ")cout << transmission << endl;
        if (color != " ")cout << color << endl;
        if (year != 0)cout << year << endl;
        if (price != 0)cout << price << endl;
        if (countPeople != 0) {
            for (int i = 0; i < countPeople; i++)
                cout << people[i] << " ";
        }
        cout << endl << endl;

    }
    void Add(Car object) {
        int sum = price + object.price;
        if (sum > 350000) {
            marka = "Ferrari"; model = "F430"; engine = 5.0; power = 440; transmission = "Автомат", color = "Красный", year = 2018; price = 350000;
        }
        else if (sum > 250000) {
            marka = "Nissan"; model = "Skyline"; engine = 3.0; power = 270; transmission = "Автомат", color = "Серебристый", year = 2004; price = 250000;
        }
        else if (sum > 150000) {
            marka = "ВАЗ"; model = "2101"; engine = 1.0; power = 60; transmission = "Механика", color = "Красный", year = 1988; price = 150000;
        }
        else {
            marka = "ЗАЗ"; model = "966"; engine = 0.8; power = 40; transmission = "Механика", color = "Синий", year = 1966; price = 0;
        }
    }
    void Sale(int& _balance) {
        _balance += price;
    }
    void Paint() {
        string newColor;
        cout << "\nСтарый цвет: " << color << "\tНовый цвет: ";
        cin >> newColor;
        color = newColor;
    }
    int* getPrice() {
        return &price;
    }
    int setPrice(int* price) {
        return *price;
    }
    int* getPower() {
        return &power;
    }
    int& setPower(int* power) {
        return *power;
    }

    //Дружественная функция
    friend int getYear(Car& CAR);
    //Перегрузка операторов '+', '++'
    Car& operator++(); // версия префикс
    Car operator++(int); // версия постфикс

    static void RemoveItem() {
        count--;
    }

    static int infoCount() {
        return count;
    }
    //Car& operator= (const Car& a)
    //{
    //    marka = " ";
    //    model = " ";
    //    marka = a.marka;
    //    model = a.model;
    //    engine = a.engine;
    //    power = a.power;
    //    transmission = " ";
    //    color = " ";
    //    transmission = a.transmission;
    //    color = a.color;
    //    year = a.year;
    //    price = a.price;
    //    countPeople = a.countPeople;
    //    people = new string[countPeople];
    //    for (int i = 0; i < countPeople; i++) {
    //        people[i] = a.people[i];
    //    }
    //    return *this;
    //}
    void showRate() {
        //Защищенный блок
        try {
            if (price <= 0) throw price; //Инициализация исключения
            cout << year * 200 / price;
        }
        //Перехват исключения
        catch (int price) {
            cout << "Цена автомобиля " << price << ", меньше или равно 0" << endl;
        }
    }
};

Car& Car::operator++() {
    power++;
    return *this;
}

Car Car::operator++(int) {
    engine++;
    return *this;
}

Car operator+(Car& a, Car& b) {
    Car c = a;
    c.Add(b);
    return c;
}

int getYear(Car& CAR) {
    return CAR.year;
}

int Car::count = 0;

class Driver {
public:
    Driver() {
        cout << "Человек получил водительское удостоверение\n" << endl << endl;
    }
    void ToDrive(Transport* transport) {
        transport->Drive();
    }
    void ToBuy(Transport* transport) {
        transport->Buy();
    }
};



int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    setlocale(LC_ALL, "Rus");
    system("color 70");
    system("mode con cols=160 lines=65");

    string peoples[2] = { "Vova", "Petya" };

    Car toyota("Toyota", "Camry", 2.0, 180, "Автомат", "Серебристый", 1998, 150000, 2, peoples);
    toyota.Display();
    Car bmw("BMW", "X5", 3.6, 220, "Автомат", "Синий", 2012, 350000, 2, peoples);
    bmw.Display();
    Moto bmx("BMX", 2020, 120000);
    bmx.Display();
    Plane boing("Боинг", 120, 11000);
    boing.Display();
    Driver Ilya;
    Ilya.ToBuy(&boing);
    Ilya.ToDrive(&boing);

    Ilya.ToBuy(&bmx);
    Ilya.ToDrive(&bmx);

    Ilya.ToBuy(&toyota);
    Ilya.ToDrive(&toyota);

    Ilya.ToBuy(&bmw);
    Ilya.ToDrive(&bmw);

    LandTransport a;
    a = bmx;

    cout << bmx;

    cout << a;
}