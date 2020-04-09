#include "pch.h"
#include "CErrorMessage.h"

using namespace std;

string CErrorMessage::GetErrorMessage() const
{
	return m_message;
}

void CErrorMessage::PrintErrorMessage() const
{
	cout << m_message;
}