#ifndef VECTOR_H
#define VECTOR_H

//define Vector class
class Vector{
private:
	double x;
	double y;

public:
	Vector (void) {}
	Vector (double, double);
	void set (double, double);
	void normalize ();
	double dot (Vector);
	Vector add (Vector);
	Vector operator+ (Vector);
	Vector subtract (Vector);
	Vector operator- (Vector);
	Vector mult (Vector);
	Vector operator* (Vector);
	Vector scalar_mult (double);
	Vector operator* (double);
	Vector scalar_divide (double);
	Vector operator/ (double);
	double sum_components (void);
	double length (void);
};

#endif
