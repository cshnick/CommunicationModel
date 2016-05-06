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

#include "Poco/Net/HTTPSClientSession.h"
#include "Poco/Net/HTTPServerRequest.h"
#include "Poco/Net/HTTPRequest.h"
#include "Poco/Net/HTTPResponse.h"
#include "Poco/Net/HTTPCredentials.h"
#include "Poco/Net/ConsoleCertificateHandler.h"
#include "Poco/Net/SSLManager.h"
#include "Poco/Net/HTTPSStreamFactory.h"
#include "Poco/Net/KeyConsoleHandler.h"
#include "Poco/Net/ConsoleCertificateHandler.h"
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
#include "Poco/Util/Application.h"
#include "Poco/JSON/Object.h"
#include "Poco/JSON/Parser.h"
#include <iostream>
#include <sstream>

#include <thread>
#include <mutex>
#include <map>

using namespace std;
using namespace Poco;
using namespace Poco::Net;
using namespace Poco::Dynamic;
using namespace Poco::JSON;

mutex s_mutex;
constexpr const char* protocol  = "https";
constexpr const char* localhost = "localhost";
constexpr const int defaultport = 9443;

using RMJContainer = struct {
	string resource;
	string method;
	Poco::JSON::Object json;
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

class SSLInitializer {
public:
	SSLInitializer() {Poco::Net::initializeSSL();}
	~SSLInitializer() {Poco::Net::uninitializeSSL();}
};

class CMClient: public Poco::Util::Application {
public:
	template<typename T = string>
	using DynMap = std::map<T, Var>;
	using ResponseCallback = std::function<void(HTTPResponse&, istream&)>;

	CMClient() {}

protected:
	void initialize(Application& self) {
		loadConfiguration(); // load default configuration files, if present
		Application::initialize(self);
		createUriPrefix();
	}

	void uninitialize() {
		Application::uninitialize();
	}

	void defineOptions(Poco::Util::OptionSet &opts) {
		Application::defineOptions(opts);
		opts.addOption(Poco::Util::Option("Help", "h", "Display help")
		.required(false)
		.repeatable(false)
		);
	}

	void handleHelp(const std::string& name, const std::string& value) {
		cout << "" << "Help" << endl;
	}

	void getGroups() {
		string resource = "/groups";
		string method = HTTPRequest::HTTP_GET;

		Poco::JSON::Object obj;
		obj.set("type", "request");
		obj.set("path", ",/groups");
		obj.set("method", "get");
		obj.set("params", "");

		RMJContainer c {resource, method, obj};
		sendData(c, [this] (const HTTPResponse &response, istream &istr) {
			stringstream ss; response.write(ss);
			Application::logger().information("Response: %s", trim(ss.str()));
			ss.str(""); ss.clear(); StreamCopier::copyStream(istr, ss);
			Application::logger().information("Response body: %s", trim(ss.str()));
		});
	}

	void getGroup(int groupId) {
		string resource = "/groups";
		string method = HTTPRequest::HTTP_GET;

		Poco::JSON::Object obj;
		obj.set("type", "request");
		obj.set("path", ",groups");
		obj.set("method", "get");
		obj.set("params", Struct<string>(DynMap<string>{
			{"id", groupId}
		}));

		RMJContainer c {resource, method, obj};
		sendData(c, [this] (const HTTPResponse &response, istream &istr) {
			stringstream ss; response.write(ss);
			Application::logger().information("Response: %s", trim(ss.str()));
			ss.str(""); ss.clear(); StreamCopier::copyStream(istr, ss);
			Application::logger().information("Response body: %s", trim(ss.str()));
		});
	}

	int addGroup(const string &groupname) {
		string resource = "/groups";
		string method = HTTPRequest::HTTP_POST;
		int id = -1;

		Poco::JSON::Object obj, params;
		obj.set("type", "request");
		obj.set("path", ",/groups");
		obj.set("method", "add");
			params.set("name", groupname);
		obj.set("params", params);

		RMJContainer c {resource, method, obj};
		sendData(c, [this, &id] (const HTTPResponse &response, istream &istr) {
			stringstream ss; response.write(ss);
			Application::logger().information("Response: %s", trim(ss.str()));
			ss.str(""); ss.clear(); StreamCopier::copyStream(istr, ss);
			Application::logger().information("Response body: %s", trim(ss.str()));
			DynamicStruct root_obj = *(Parser().parse(ss.str()).extract<Object::Ptr>());
			if (root_obj["return"]["status"] == "ok") {
				id = root_obj["return"]["value"];
			}
		});

		printf("");
		return id;
	}

	void renameGroup(int groupId, const string &newname) {
		string resource = "/groups";
		string method = HTTPRequest::HTTP_POST;

		Poco::JSON::Object obj, params;
		obj.set("type", "request");
		obj.set("path", ",/groups");
		obj.set("method", "rename");
			params.set("id", groupId);
			params.set("newname", newname);
		obj.set("params", params);

		RMJContainer c {resource, method, obj};
		sendData(c, [this] (const HTTPResponse &response, istream &istr) {
			stringstream ss; response.write(ss);
			Application::logger().information("Response: %s", trim(ss.str()));
			ss.str(""); ss.clear(); StreamCopier::copyStream(istr, ss);
			Application::logger().information("Response body: %s", trim(ss.str()));
		});
	}


	void deleteGroup(int groupId) {
		string resource = "/groups";
		string method = HTTPRequest::HTTP_POST;

		Poco::JSON::Object obj, params;
		obj.set("type", "request");
		obj.set("path", ",/groups");
		obj.set("method", "delete");
			params.set("id", groupId);
		obj.set("params", params);

		RMJContainer c {resource, method, obj};
		sendData(c, [this] (const HTTPResponse &response, istream &istr) {
			stringstream ss; response.write(ss);
			Application::logger().information("Response: %s", trim(ss.str()));
			ss.str(""); ss.clear(); StreamCopier::copyStream(istr, ss);
			Application::logger().information("Response body: %s", trim(ss.str()));
		});
	}

	void sendData(const RMJContainer &data, ResponseCallback callback) {
		lock_guard<mutex> guard(mutex);

		URI uri(m_uriprefix + data.resource);
		HTTPSClientSession session(uri.getHost(), uri.getPort());

		HTTPRequest request(data.method, data.resource, HTTPMessage::HTTP_1_1);

		stringstream ss; data.json.stringify(ss);
		request.add("json", ss.str());

		HTTPResponse response;
		ostream &ostr = session.sendRequest(request);
		std::istream& rs = session.receiveResponse(response);
		callback(response, rs);
	}

	int main(const vector<string> &args) {
		try {
			Poco::AutoPtr<SplitterChannel> splitterch(new SplitterChannel());
			Poco::AutoPtr<ConsoleChannel> consolech(new ConsoleChannel);
			Poco::AutoPtr<FileChannel> filech(new FileChannel("RESTClient.log"));
			splitterch->addChannel(consolech);
			splitterch->addChannel(filech);

			Poco::AutoPtr<Formatter> formatter(new PatternFormatter("%d-%m-%Y %H:%M:%S %s: %t"));
			Poco::AutoPtr<Channel> formattingChannel(new FormattingChannel(formatter, splitterch));

			Application::logger().setChannel(formattingChannel);

			SSLInitializer raii_ssl;

			string groupname = "Group0";
			string grouprename = "Group100";
			int id = addGroup(groupname);
			if (id == -1) {
				Application::logger().information("Can't add group: %s", groupname);
				return Application::EXIT_OK;
			}
			renameGroup(id, grouprename);
			getGroups();
//			getGroup(0);
			deleteGroup(id);

		} catch (const exception &e) {
			Application::logger().critical(e.what());
			return Application::EXIT_SOFTWARE;
		}

		return Application::EXIT_OK;
	}

private:
	void createUriPrefix() {
		string protocol = config().getString("CMClient.protocol", "https");
		string host = config().getString("CMClient.host", "localhost");
		unsigned short port = (unsigned short) config().getInt("CMClient.port", 9443);

		stringstream ss;
		ss << protocol << "://" << host << ":" << port;
		m_uriprefix = ss.str();
	}
	string trim(const string& str) {
	    size_t first = str.find_first_not_of('\n');
	    size_t last = str.find_last_not_of('\n');
	    return str.substr(first, (last-first + 1));
	}

private:
	string m_uriprefix;
};

POCO_APP_MAIN(CMClient)
