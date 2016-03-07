/*********************************************************************
Project: Dissertation
Author: Josh Martin

Name: Vector 3D
Description: Exists as a middle man between math libraries and their
lua-bound versions
*********************************************************************/
#ifndef VEC3_H
#define VEC3_H

#include <math.h>
#include <glm/glm.hpp>

class Vec3{
public:
	Vec3();
	Vec3(glm::vec3);
	Vec3(float);
	Vec3(float, float, float);
	~Vec3();

	void set(float newX, float newY, float newZ);

	Vec3 operator- (const Vec3&) const;	
	Vec3 operator+ (const Vec3&) const;	

	Vec3& operator+= (const Vec3& v);	
	Vec3& operator-= (const Vec3& v);

	Vec3 operator* (float);
	Vec3 operator* (float n) const;
	Vec3 operator/ (float n) const;
	Vec3& operator*= (float);
	Vec3& operator/= (float);

	Vec3 operator* (const Vec3& v);
	Vec3& operator*= (const Vec3& v);

	Vec3 operator= (const Vec3&);
	Vec3 operator= (const float);
	Vec3 operator- () const; 

	bool operator== (const Vec3&);
	bool operator!= (const Vec3&);
	float& operator[](unsigned int);

	operator glm::vec3() const;
	operator glm::vec4() const;


	float dot(const Vec3&) const;
	Vec3 cross(const Vec3&);

	//base variables (public)
	float x, y, z;
private:

};
#endif;