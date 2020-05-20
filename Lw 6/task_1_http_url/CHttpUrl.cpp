#include "CHttpUrl.h"
#include "CUrlParsingError.h"
#include <algorithm>
#include <regex>
#include <string>

using namespace std;

CHttpUrl::CHttpUrl(string const& url)
{
	regex ex("([\\w]*)://([^/ :]+)(:([0-9]{1,5}))?(/[\\S]*)?");
	cmatch what;
	string protocol, domain, port;

	if (regex_match(url.c_str(), what, ex))
	{
		protocol = string(what[1]);
		domain = string(what[2]);
		m_document = string(what[5]);
		port = string(what[4]);

		m_protocol = StringToProtocol(protocol);
		m_domain = !domain.empty() ? domain : throw CUrlParsingError("ERROR: wrong url\nURL must consist of protocol://domain:port/documen\n");
		m_port = StringToUnsignedShort(port, m_protocol);
	}
	else
	{
		throw CUrlParsingError("ERROR: wrong url\nURL must consist of protocol://domain:port/documen\n");
	}
}

//CHttpUrl::CHttpUrl(string const& domain, string const& document, Protocol protocol = Protocol::HTTP)
//{}
//
//CHttpUrl::CHttpUrl(string const& domain, string const& document, Protocol protocol, int port)
//{}

Protocol StringToProtocol(string& inpString)
{
	transform(inpString.begin(), inpString.end(), inpString.begin(), ::tolower);
	Protocol protocol;

	if (inpString == "https")
	{
		protocol = Protocol::HTTPS;
	}
	else if (inpString == "http")
	{
		protocol = Protocol::HTTP;
	}
	else
	{
		throw CUrlParsingError("ERROR: wrong protocol value: use http or https protocol\n");
	}

	return protocol;
}

unsigned short StringToUnsignedShort(string& port, Protocol protocol)
{
	if (port.empty())
	{
		return protocol == Protocol::HTTP ? 80 : 443;
	}
	else
	{
		try
		{
			int p = static_cast<int>(strtoul(port.c_str(), NULL, 10));

			return CheckPortRange(p);
		}
		catch (CUrlParsingError error)
		{
			throw error;
		}
	}
}

unsigned short CheckPortRange(const int port)
{
	if (port < 1 || port > USHRT_MAX)
	{
		throw CUrlParsingError("ERROR: wrong port\nPort must be in the range of 1 to 65535\n");
	}

	return (unsigned short)port;
}

string CHttpUrl::GetDomain() const
{
	return m_domain;
}

string CHttpUrl::GetDocument() const
{
	return m_document;
}

Protocol CHttpUrl::GetProtocol() const
{
	return m_protocol;
}

unsigned short CHttpUrl::GetPort() const
{
	return m_port;
}

void CHttpUrl::AppendProperties(std::ostream& strm) const
{
	strm << "\n\tDomain: " << GetDomain()
		 << "\n\tDocument: " << GetDocument()
		 << "\n\tProtocol: " << ConvertProtocolToString(GetProtocol())
		 << "\n\tPort: " << ConvertPortToString(GetPort());
}

string CHttpUrl::GetUrl() const
{
	ostringstream strm;
	strm << ConvertProtocolToString(m_protocol) + "://" + m_domain + m_document;
	AppendProperties(strm);

	return strm.str();
}

string ConvertProtocolToString(const Protocol protocol)
{
	return protocol == Protocol::HTTP ? "http" : "https";
}

string ConvertPortToString(unsigned short port)
{
	return to_string(port);
}