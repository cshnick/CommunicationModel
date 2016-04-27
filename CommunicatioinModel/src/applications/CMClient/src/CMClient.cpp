//
// httpget.cpp
//
// $Id: //poco/1.4/Net/samples/httpget/src/httpget.cpp#3 $
//
// This sample demonstrates the HTTPClientSession and the HTTPCredentials classes.
//
// Copyright (c) 2005-2012, Applied Informatics Software Engineering GmbH.
// and Contributors.
//
// SPDX-License-Identifier:	BSL-1.0
//

#include "Poco/Net/HTTPClientSession.h"
#include "Poco/Net/HTTPServerRequest.h"
#include "Poco/Net/HTTPRequest.h"
#include "Poco/Net/HTTPResponse.h"
#include <Poco/Net/HTTPCredentials.h>
#include "Poco/StreamCopier.h"
#include "Poco/NullStream.h"
#include "Poco/Path.h"
#include "Poco/URI.h"
#include "Poco/Exception.h"
#include "Poco/Logger.h"
#include "Poco/FileChannel.h"
#include "Poco/Channel.h"
#include "Poco/SplitterChannel.h"
#include "Poco/ConsoleChannel.h"
#include "Poco/FileChannel.h"
#include "Poco/PatternFormatter.h"
#include "Poco/FormattingChannel.h"
#include <iostream>
#include <sstream>

#include <thread>
#include <mutex>
#include <map>

using namespace std;
using namespace Poco;
using namespace Poco::Net;

//namespace {

mutex s_mutex;
constexpr const char* localhost = "localhost";
constexpr const int defaultport = 9990;

//} //anoo

using RMJContainer = struct {
	string resource;
	string method;
	string json;
};
using RegexToHandlerVec = vector<RMJContainer>;

RegexToHandlerVec g_requests {
	{"/status", HTTPRequest::HTTP_GET,
		"{\"state\" : 0,"
		"\"lasterror\": \"cannot connect to remote server\","
		"\"fingerprint\": \"x234xcv435\","
		"\"version_nr\": 100,"
		"\"succ_conn\": 100"
		"}"
	},

	{"/register", HTTPRequest::HTTP_POST,
		"{\"userIdentity\" : \"a@b.com\","
		"\"password\": \"1\","
		"\"serverName\": \"serverName\""
		"}"
	},

	{"/lsserver", HTTPRequest::HTTP_DELETE, "{}"},

	{"/lsserver", HTTPRequest::HTTP_POST,
		"{\"name\" : \"aserverName\"}"
	},

	{"/lsserver", HTTPRequest::HTTP_GET, "{}"},

	{"/postcreds", HTTPRequest::HTTP_POST, "{}"}
};

bool doRequest(const RMJContainer &rmj) {
	stringstream ss;
	ss << "http://" << localhost << ":" << defaultport;
	string prefix = ss.str();
	URI uri(prefix + rmj.resource);

	std::string username;
	std::string password;
	Poco::Net::HTTPCredentials::extractCredentials(uri, username, password);
	Poco::Net::HTTPCredentials credentials(username, password);

	HTTPClientSession session(uri.getHost(), uri.getPort());
	HTTPRequest request(rmj.method, rmj.resource, HTTPMessage::HTTP_1_1);

	request.add("json", rmj.json);
	stringstream reqss;
	request.write(reqss);
	Logger::get("main").information("Request: %s", reqss.str().c_str());

	HTTPResponse response;

	session.sendRequest(request);
	std::istream& rs = session.receiveResponse(response);
	std::cout << response.getStatus() << " " << response.getReason() << std::endl;
	lock_guard<mutex> guard(mutex);
	if (response.getStatus() != Poco::Net::HTTPResponse::HTTP_UNAUTHORIZED) {

		StreamCopier::copyStream(rs, std::cout);
		return true;
	} else {
		Poco::NullOutputStream null;
		string buffer;
		StreamCopier::copyToString(rs, buffer);
		return false;
	}
	return false;
}

int main(int argc, char** argv)
{
	try {
		const int threadNum = 1;
		Poco::AutoPtr<SplitterChannel> splitterch(new SplitterChannel());
		Poco::AutoPtr<ConsoleChannel> consolech(new ConsoleChannel);
		Poco::AutoPtr<FileChannel> filech(new FileChannel("RESTClient.log"));
		splitterch->addChannel(consolech);
		splitterch->addChannel(filech);

		Poco::AutoPtr<Formatter> formatter(new PatternFormatter("%d-%m-%Y %H:%M:%S %s: %t"));
		Poco::AutoPtr<Channel> formattingChannel(new FormattingChannel(formatter, splitterch));

		Logger::create("main", formattingChannel);

//		for (const RMJContainer &rmj : g_requests) {
//			doRequest(rmj);
//		}

		RMJContainer postcreds {"/postcreds", HTTPRequest::HTTP_POST, "{\"username\": \"test\"}"};
		doRequest(postcreds);

	} catch (const exception &e) {
		Logger::get("main").critical(e.what());
	}

	return 0;
}
