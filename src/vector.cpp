#include <../include/vector.h>
#include <cmath>

//constructor
Vector::Vector (double x, double y){
	set(x, y);
}

//set method
void Vector::set (double x, double y){
	this -> x = x;
	this -> y = y;
}

//normalizes v
void Vector::normalize (){
	double length = sqrt(x * x +y * y);
	x /= length;
	y /= length;
}

//computes dot product of caller and v
double Vector::dot (Vector v){
	return x * v.x + y * v.y;
}

//computes sum of caller and v
Vector Vector::add (Vector v){
	Vector rv;
	rv.x = x + v.x;
	rv.y = y + v.y;
	return rv;
}

//overloads operator +
Vector Vector::operator+ (Vector v){
	return this -> add(v);
}

//computes difference of caller and v
Vector Vector::subtract (Vector v){
	Vector rv;
	rv.x = x - v.x;
	rv.y = y - v.y;
	return rv;
}

//overloads operator -
Vector Vector::operator- (Vector v){
	return this -> subtract(v);
}

//computes product of caller and v
Vector Vector::mult (Vector v){
	Vector rv;
	rv.x = x * v.x;
	rv.y = y * v.y;
	return rv;
}

//overloads operator *
Vector Vector::operator* (Vector v){
	return this -> mult(v);
}

//computes product of caller and scalar s
Vector Vector::scalar_mult (double s){
	Vector rv;
	rv.x = x * s;
	rv.y = y * s;
	return rv;
}

//overloads operator *
Vector Vector::operator* (double s){
	return this -> scalar_mult(s);
}

//computes quotient of caller and scalar s
Vector Vector::scalar_divide (double s){
	Vector rv;
	rv.x = x / s;
	rv.y = y / s;
	return rv;
}

//overloads operator /
Vector Vector::operator/ (double s){
	return this -> scalar_divide(s);
}

//computes sum of components of caller
double Vector::sum_components (void){
	return this -> x + this -> y;
}

//computes length of caller
double Vector::length (void){
	return sqrt(x * x + y * y);
}
