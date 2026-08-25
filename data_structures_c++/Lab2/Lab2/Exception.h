/*******************************************************************
*
* Date created: April 2nd, 2024
*
* File Author: Zaelfenn Sandow
*
* File name: Exception.h
*
* File purpose: Declare the functions for the exception class. 
*
*
*******************************************************************/


#pragma once
#include <ostream>
using std::ostream;
class Exception {
	public:
		Exception();															//default constructor
		Exception(const char* msg);													//value constructor
		Exception(const Exception& copy);										//copy constructor
		Exception(Exception&& copy)noexcept;											//move constructor
			
		~Exception();															//destructor
				
		Exception& operator = (const Exception& copy);							//copy assignment operator
		Exception& operator = (Exception&& copy)noexcept;								//move assignment operator

		const char* getMsg();													//getter for m_msg
		void setMsg(const char* msg);											//setter for m_msg

		friend ostream& operator << (ostream& stream, const Exception& except);	//stream operator
	private:
		char* m_msg;
};