/*
 * ExistingApi.cpp
 *
 *  Created on: 14 апр. 2016 г.
 *      Author: ilia
 */

#include "ExistingApi.h"

#include <vector>
#include <functional>
#include <regex>

#include "Poco/URI.h"
#include "Poco/JSON/Parser.h"
#include "Poco/Net/HTTPServerResponse.h"

using namespace Poco;
using namespace Poco::Net;
using namespace std;

HTTPRequestHandler* ExistingApiHandlerFactory::createRequestHandler(const Poco::Net::HTTPServerRequest& request) {
	return new ExistingApiRequestHandler;
}

using RequestSourceHandlerFunc = function<void(HTTPServerRequest&, HTTPServerResponse&)>;
using RMFContainer = struct {
	string regex;
	string method;
	RequestSourceHandlerFunc fn;
};
using RegexToHandlerVec = vector<RMFContainer>;

class ExistingApiRequestHandlerPrivate {
	friend class ExistingApiRequestHandler;
public:
	ExistingApiRequestHandlerPrivate(ExistingApiRequestHandler *q)
	: q(q) {}
	~ExistingApiRequestHandlerPrivate() {}

	void handleRequest(HTTPServerRequest& request, HTTPServerResponse& response) {
		string uri = request.getURI();
		string method = request.getMethod();
		for (RMFContainer &rmf : rthMap) {
			regex rx(rmf.regex);
			if (regex_match(uri, rx) && rmf.method == method) {
				if (rmf.fn) {
					rmf.fn(request, response);
				}
			}
		}

		string  json = request["json"];
		JSON::Parser parser;
		Dynamic::Var json_obj = parser.parse(json); //Throw error if can't parse
		response.setStatusAndReason(HTTPResponse::HTTP_OK);
		response.setContentType("application/json");
	}

private:
	ExistingApiRequestHandler *q;

	static RegexToHandlerVec rthMap;
};

RegexToHandlerVec ExistingApiRequestHandlerPrivate::rthMap  = {
	{".*/status", HTTPRequest::HTTP_GET, [] (HTTPServerRequest& request, HTTPServerResponse& response) {
			cout << "Status match" << std::endl;
			ostream &os = response.send();
			os << "";
		}
	},

	{".*/register", HTTPRequest::HTTP_POST, [] (HTTPServerRequest& request, HTTPServerResponse& response) {
			cout << "Register match" << std::endl;
			ostream &os = response.send();
			os << "{\n" <<
					"\t\"name\" : \"Licensing Server Name\",\n" <<
					"\t\"createdGmt\" : 1439473893849,\n" <<
					"\t\"status\": \"ACTIVE\"\n" <<
					"\t\"lastActivityGmt\" : 1439473893849,\n" <<
					"}" << endl;
		}
	},

	{".*/lsserver", HTTPRequest::HTTP_DELETE, [] (HTTPServerRequest& request, HTTPServerResponse& response) {
			cout << "lsserver DEL" << std::endl;
			ostream &os = response.send();
			os << "";
		}
	},

	{".*/lsserver", HTTPRequest::HTTP_POST, [] (HTTPServerRequest& request, HTTPServerResponse& response) {
			cout << "lsserver POST" << std::endl;
			ostream &os = response.send();
			os << "";
		}
	},

	{".*/lsserver", HTTPRequest::HTTP_GET, [] (HTTPServerRequest& request, HTTPServerResponse& response) {
			cout << "lsserver GET" << std::endl;
			ostream &os = response.send();
			os << "";
		}
	},

	{"theex", "GET",  nullptr}
};


ExistingApiRequestHandler::ExistingApiRequestHandler()
	: d(new ExistingApiRequestHandlerPrivate(this)) {

}
void ExistingApiRequestHandler::handleRequest(HTTPServerRequest& request, HTTPServerResponse& response) {
	d->handleRequest(request, response);
}


