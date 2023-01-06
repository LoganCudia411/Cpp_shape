#ifndef SHAPE_H_
#define SHAPE_H_

#include<iostream>
#include<cmath>
#include<string>
#include<algorithm>
#include<list>
#include<fstream>
#include <iomanip>    

using namespace std;

//partners: cudia2
//This program utilizes inhertance and derived classes to create 4 classes, rectangle, circle, spehre, and RectPrism, 
//from a base class called shape. We are able to calulcate the volume and area by retrieving shape speific data from an input file. 

//Base class
//Please implement Shape's member functions
//constructor, getName()
class Shape{
public:
	//Base class' constructor should be called in derived classes'
	//constructor to initizlize Shape's private variable 
  	Shape(string name) {
		name_=name;
	}
	
  	string getName() {
		return name_;
	}
	
  	virtual double getArea() const = 0;
  	virtual double getVolume() const = 0;
	
private:
  string name_;


};

//Rectangle
//Please implement the member functions of Rectangle:
//constructor, getArea(), getVolume(), operator+, operator-

template <class T>//templating the class allows us to pass different data types for the parameters of our functions
class Rectangle : public Shape{
public:
  	Rectangle<T>(T width = 0, T length = 0):Shape("Rectangle") {//constructor:initialize with paranmeters of function
	width_=width;
	length_=length;
	}
	
  	double getArea() const {//area of one rectangle object
		return width_*length_;
	}
	
  	double getVolume() const {
		return 0;
	}
	
	Rectangle<T> operator + (const Rectangle<T>& rec) {
		return Rectangle(width_+rec.width_, length_+rec.length_);
	}
	
	Rectangle<T> operator - (const Rectangle<T>& rec) {
		return Rectangle(fmax(0,width_-rec.width_), fmax(0,length_-rec.length_));
	} 
	
	T getWidth() const { 
		return width_;
	}
	
	T getLength() const { 
		return length_;
	}
private:
	T width_;
    T length_;

};

//Circle
//Please implement the member functions of Circle:
//constructor, getArea(), getVolume(), operator+, operator-
//@@Insert your code here

class Circle : public Shape{
public:
  	Circle(double radius):Shape("Circle") {
		radius_=radius;
	}
	
  	double getArea() const{
		return pow(radius_,2)*M_PI;
	}
	
 	double getVolume() const{
		return 0;
	}
	
  	Circle operator + (const Circle& cir){
		return Circle(radius_+cir.radius_);
	}
	
	Circle operator - (const Circle& cir){
		return Circle(radius_-cir.radius_);
	} 

	double getRadius() const { 
		return radius_;
	}
	
private:
	double radius_;

};



//Sphere
//Please implement the member functions of Sphere:
//constructor, getArea(), getVolume(), operator+, operator-
//@@Insert your code here

class Sphere : public Shape{
public:
  	Sphere(double radius):Shape("Sphere") {
		radius_=radius;
	}

  	double getVolume() const {
		return (4.0/3.0)*M_PI*pow(radius_,3);
	}	
	
  	double getArea() const {
		return 4.0*M_PI*pow(radius_,2);
	}

	Sphere operator + (const Sphere& sph) {//construct new shape w/ added private variables
		return Sphere(radius_+sph.radius_);
	}

	Sphere operator - (const Sphere& sph) {//construct new shape w/ subtracted private variables
		return Sphere(radius_-sph.radius_);
	} 
	
	double getRadius() const {
		return radius_;
	}

private:
	double radius_;

};

//Rectprism
//Please implement the member functions of RectPrism:
//constructor, getArea(), getVolume(), operator+, operator-
//@@Insert your code here
class RectPrism : public Shape{
public:
  	RectPrism(double width, double length, double height):Shape("RectPrism") {
		width_=width;
		length_=length;
		height_=height;
	}
	
  	double getVolume() const {
		return length_*width_*height_;
	}
  	
	double getArea() const {
		return 2*(length_*width_+length_*height_+width_*height_);
	}
	
	RectPrism operator + (const RectPrism& rectp){//construct new shape w/ added private variables
		return RectPrism(width_+rectp.width_, length_+rectp.length_, height_+rectp.height_);
	}
	
	RectPrism operator - (const RectPrism& rectp){//construct new shape w/ subtracted private variables
		return RectPrism(width_-rectp.width_, length_-rectp.length_, height_-rectp.height_);
	}	
	
	double getWidth() const { 
		return width_;
	}
	
	double getLength() const { 
		return length_;
	}
	
	double getHeight() const { 
		return height_;
	}
  
private:
  	double length_;
  	double width_;
  	double height_;

};

// Read shapes from test.txt and initialize the objects
// Return a vector of pointers that points to the objects 
static list<Shape*> CreateShapes(char* file_name) {
	//@@Insert your code here
	
	//read from file
	int total_shapes;
	//open file and put total amount of shapes into variable
	ifstream ifs(file_name, std::ifstream::in);
  	ifs >> total_shapes;
	//create variables to get read dimensions of particular shapes
	double a,b,c;
	int i;//iterator
	std::list<Shape*> returnList;
	Shape* CurrShape;
	string temp;
	for(i=0; i<total_shapes; i++){//iteratively read from the file and put info into vector
		ifs>>temp;//read from file then put string into temp
	//check what string is put into temp, then call ifs to get dimensions according to each type of 
    	if(temp == "Circle"){
      		ifs>>a;
      		CurrShape = new Circle(a);

    	}else if(temp== "Rectangle"){
      		ifs>>a>>b;
			CurrShape = new Rectangle<double>(a,b);//defaul T type equal to double

	  	}else if(temp == "Sphere"){
      		ifs>>a;
      		CurrShape = new Sphere(a);

    	}else if(temp == "RectPrism"){
      		ifs>>a>>b>>c;
      		CurrShape = new RectPrism(a,b,c);
    	}
		returnList.push_back(CurrShape);//push elements into the back of the list 
	}

	ifs.close();//close the file
	return returnList;
}

// call getArea() of each object 
// return the max area
static double MaxArea(list<Shape*> shapes){
	double max_area = 0;
	//@@Insert your code here
	list<Shape*>::iterator it;
	for(it=shapes.begin(); it!=shapes.end();it++){//iterate through list
		if((*it)->getArea()>max_area){
			max_area=(*it)->getArea();
		}
	}
	return max_area;
}

// call getVolume() of each object 
// return the max volume
static double MaxVolume(list<Shape*> shapes){
	double max_volume = 0;
	//@@Insert your code here
	list<Shape*>::iterator it2;
	for(it2=shapes.begin();it2!=shapes.end(); it2++){//use iterator to go through the list
		if((*it2)->getVolume()>max_volume){//dereference iterator then use the access operator through shape pointer
			max_volume=(*it2)->getVolume();//call virtural function
		}
	}
	return max_volume;
}
#endif

