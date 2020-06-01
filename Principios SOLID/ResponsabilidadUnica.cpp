#include<iostream>
#include<string>

using namespace std;

/********************ICAR ABSTRACT CLASS*********************/

class ICar {
	public:
		~ICar(){};
		virtual std::string getCarMark() = 0 ;
};

/********************CAR CLASS*********************/

class Car : public ICar{
	
	private:
		std::string m_mark;
		
	public:
		Car(std::string mark);
		~Car(){};

		std::string getCarMark();
};

Car::Car(std::string mark){
	m_mark = mark;
}

std::string Car::getCarMark(){
	return m_mark;
}

/********************ICARDB ABSTRACT CLASS*********************/

class ICarDB{
	public:
		~ICarDB(){};
		virtual void saveCarDB(ICar* car) = 0 ;
		virtual void deleteCarDB(ICar* car) = 0 ;
};

/********************CARDB CLASS*********************/

class CarDB : public ICarDB{
	public:
		CarDB(){};
		~CarDB(){};
		void saveCarDB(ICar* car);
		void deleteCarDB(ICar* car);
};

void CarDB::saveCarDB(ICar* car){
	std::cout<< "Car: "<<car->getCarMark()<< " saved from DB."<<std::endl;
}

void CarDB::deleteCarDB(ICar* car){
	std::cout<< "Car: "<<car->getCarMark()<< " deleted from DB."<<std::endl;
}

void printMark(ICar* car){
	std::cout<<"The mark of the car is: "<<car->getCarMark()<<std::endl;
}

int main (){
	
	ICar *car1 = new Car("Audi");
    ICar *car2 = new Car("Toyota");

    printMark(car1);
    printMark(car2);

    ICarDB *carDB = new CarDB();

    carDB->saveCarDB(car1);
    carDB->saveCarDB(car2);

    carDB->deleteCarDB(car1);
		
	return 0;
}
