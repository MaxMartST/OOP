#include "CErrorMessage.h"

#include <iostream>

using namespace std;

string CErrorMessage::GetErrorMessage() const
{
	return m_message;
}