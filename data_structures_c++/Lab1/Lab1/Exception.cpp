/*******************************************************************
*
* Date created: April 2nd, 2024
*
* File Author: Zaelfenn Sandow
*
* File name: Exception.cpp
*
* File purpose: Defines the functions for the exception class.
*
*
*******************************************************************/

#include "Exception.h"

Exception::Exception() : m_msg(nullptr)														//default constructor
{}

Exception::Exception(const char* msg) : m_msg(nullptr)												//value constructor
{
	if (msg != nullptr) {
		m_msg = new char[strlen(msg) + 1];						//if the passed in value is not empty, create a new char * with the same length, plus one for null terminated string
		for (int i = 0; msg[i] != '\0'; ++i)					//copy the characters from the passed in string to the member string one by one
			m_msg[i] = msg[i];
	}
}

Exception::Exception(const Exception& copy)	: m_msg(nullptr) 								//copy constructor
{
	if (copy.m_msg != nullptr) {
		m_msg = new char[strlen(copy.m_msg) + 1];						//if the passed in value is not empty, create a new char * with the same length, plus one for null terminated string
		strcpy(m_msg, copy.m_msg);										//copy the string over
	}
}

Exception::Exception(Exception&& copy) noexcept: m_msg(copy.m_msg)								//move constructor
{
	copy.m_msg = nullptr;
}


Exception::~Exception()														//destructor
{
	if (m_msg != nullptr) {				//if there is a message
		delete[] m_msg;					//delete the message
		m_msg = nullptr;				//set to nullptr
	}
}

Exception& Exception::operator = (const Exception& rhs)						//copy assignment operatore
{
	if (rhs.m_msg != nullptr) {
		m_msg = new char[strlen(rhs.m_msg) + 1];						//if the passed in value is not empty, create a new char * with the same length, plus one for null terminated string
		strcpy(m_msg, rhs.m_msg);										//copy the string over
	}
	return *this;
}

Exception& Exception::operator = (Exception&& rhs)	noexcept						//move assignment operator
{
	if (rhs.m_msg != nullptr) {
		m_msg = rhs.m_msg;												//change pointer location
		rhs.m_msg = nullptr;											//stop pointing 
	}

	return *this;
}

const char* Exception::getMsg()												//getter for m_msg
{
	return m_msg;
}

void Exception::setMsg(const char* msg)										//setter for m_msg
{
	if (msg != nullptr)
	{
		m_msg = new char[strlen(msg) + 1];						//if the passed in value is not empty, create a new char * with the same length, plus one for null terminated string
		strcpy(m_msg, msg);										//copy the string over
	}
	else if (m_msg != nullptr)
	{
		delete[] m_msg;											//if a null is passed in, make sure that data is non existent
		m_msg = nullptr;
	}
}


ostream& operator << (ostream& stream, const Exception& except)					//stream operator
{
	if (except.m_msg != nullptr) //if there is data
		stream << except.m_msg; //input the data
	else
		stream << ""; //otherwise input a null string
	return stream;

}
