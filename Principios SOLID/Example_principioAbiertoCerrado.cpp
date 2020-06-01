#include<iostream>
#include<string>

/********************ICAR ABSTRACT CLASS*********************/

class ICar {
	public:
		~ICar(){};
		virtual std::string getCarMark() = 0 ;
		virtual int carMediumPrice() = 0;
};

/********************CAR CLASS*********************/

class Toyota : public ICar {
	public:
		Toyota(std::string mark, int price);
		~Toyota(){};
		std::string getCarMark();
		int carMediumPrice();
	
	private:
		std::string m_mark;
		int m_price = 0 ;
};

Toyota::Toyota(std::string mark, int price){
	m_mark = mark;
	m_price = price;
}

std::string Toyota::getCarMark(){
	return m_mark;
}

int Toyota::carMediumPrice(){
	return m_price;
}

class Audi : public ICar{
	public:
		Audi(std::string mark, int prince);
		std::string getCarMark();
		int carMediumPrice();
	
	private:
		std::string m_mark;
		int m_price = 0 ;
};

Audi::Audi(std::string mark, int price){
	m_mark = mark;
	m_price = price;
}

std::string Audi::getCarMark(){
	return m_mark;
}

int Audi::carMediumPrice(){
	return m_price;
}

void print(ICar* car){
	std::cout<<"The mark of the car is: "<<car->getCarMark()<< " and price is: "<<car->carMediumPrice()<<std::endl;
}

int main(){
	
	ICar* audi = new Audi("Audi tt", 40000);
	ICar* toyota = new Toyota("Toyota Hilux", 25000);
	
	print(audi);
	print(toyota);
	
	delete audi;
	delete toyota;
	
	return 0;
}
