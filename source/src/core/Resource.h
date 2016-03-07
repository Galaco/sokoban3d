/*********************************************************************
Project: Dissertation
Author: Josh Martin

Name: Resource
Description: Abstract class that should never really be instantiated
			 itself. All type of resources inherit from this. A 
			 resource in this case is defined a class that has intial
			 setup, but after that its data is simply used by other 
			 classes
*********************************************************************/
#ifndef RESOURCE_H
#define RESOURCE_H


class Resource
{
public:
	Resource(){};
	~Resource(){};
};
#endif