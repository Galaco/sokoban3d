#include "vec3.h"

Vec3::Vec3(){
	x = 0;
	y = 0;
	z = 0;
}

Vec3::Vec3(glm::vec3 v){
	x = v.x;
	y = v.y;
	z = v.z;
}

Vec3::Vec3(float v) {
	x = v;
	y = v;
	z = v;
}

Vec3::Vec3(float x1, float y1, float z1){
	x = x1;
	y = y1;
	z = z1;
}

Vec3::~Vec3(){

}

void Vec3::set(float newX, float newY, float newZ){
	x = newX;
	y = newY;
	z = newZ;
}

Vec3 Vec3::operator- (const Vec3& b) const {
	Vec3 v;
	v.x = x - b.x;
	v.y = y - b.y;
	v.z = z - b.z;

	return v;
}
Vec3 Vec3::operator+ (const Vec3& b) const {
	Vec3 v;
	v.x = x + b.x;
	v.y = y + b.y;
	v.z = z + b.z;

	return v;
}

Vec3& Vec3::operator+= (const Vec3& b) {
	x += b.x;
	y += b.y;
	z += b.z;

	return *this;
}
Vec3& Vec3::operator-= (const Vec3& b) { 
	x -= b.x;
	y -= b.y;
	z -= b.z;

	return *this;
}

Vec3 Vec3::operator* (float n) const {
	Vec3 v;
	v.x = x * n;
	v.y = y * n;
	v.z = z * n;

	return v;
}

Vec3 Vec3::operator* (float n) {
	Vec3 v;
	v.x = x * n;
	v.y = y * n;
	v.z = z * n;

	return v;
}

Vec3 Vec3::operator/ (float n) const {
	Vec3 v;
	v.x = x / n;
	v.y = y / n;
	v.z = z / n;

	return v;
}

Vec3& Vec3::operator*= (float n) {
	x *= n;
	y *= n;
	z *= n;

	return *this;
}

Vec3& Vec3::operator/= (float n) {
	x /= n;
	y /= n;
	z /= n;

	return *this;
}

Vec3 Vec3::operator* (const Vec3& b)  {
	Vec3 v;
	v = cross(b);

	return v;
}
Vec3& Vec3::operator*= (const Vec3& b)  {
	x *= b.x;
	y *= b.y;
	z *= b.z;

	return *this;
}

Vec3 Vec3::operator= (const Vec3& b) {
	x = b.x;
	y = b.y;
	z = b.z;
	return *this;
}

Vec3 Vec3::operator= (const float b) {
	x = b;
	y = b;
	z = b;
	return *this;
}

Vec3 Vec3::operator-() const {
	Vec3 v;
	v.x = -x;
	v.y = -y;
	v.z = -z;
	return v;
}

bool Vec3::operator== (const Vec3& b) {
	if(x == b.x && y == b.y && z == b.z){
		return true;
	} else {
		return false;
	}
}

bool Vec3::operator!= (const Vec3& b){
	if(x != b.x || y != b.y || z != b.z){
		return true;
	} else {
		return false;
	}
}

float& Vec3::operator[](unsigned int index){
	switch(index){
	case 0:
		return x; break;
	case 1:
		return y; break;
	case 2: 
		return z; break;
	default:
		return x; break;
	}
}

Vec3::operator glm::vec3() const{
	glm::vec3 v;
	v.x = x;
	v.y = y;
	v.z = z;

	return v;
}
Vec3::operator glm::vec4() const{
	glm::vec4 v;
	v.x = x;
	v.y = y;
	v.z = z;

	return v;
}

Vec3 Vec3::cross(const Vec3& b) {
	Vec3 v;
	v.x = y * b.z - z * b.y;
	v.y = z * b.x - x * b.z;
	v.z = x * b.y - y * b.x;

	return v;
}

float Vec3::dot(const Vec3& b) const {
	return (x*b.x + y*b.y + z*b.z);
}