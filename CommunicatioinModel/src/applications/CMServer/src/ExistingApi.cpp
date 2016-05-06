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
#include "Poco/Logger.h"
#include "Poco/JSON/Parser.h"
#include "Poco/JSON/Stringifier.h"
#include "Poco/Net/HTTPServerResponse.h"

#include "ncconsolestorage.hpp"

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
template<typename T = string>
using DynMap = std::map<T, Poco::Dynamic::Var>;

class ExistingApiRequestHandlerPrivate {
	friend class ExistingApiRequestHandler;
public:
	ExistingApiRequestHandlerPrivate(ExistingApiRequestHandler *q)
	: q(q) {}
	~ExistingApiRequestHandlerPrivate() {}

	void handleRequest(HTTPServerRequest& request, HTTPServerResponse& response) {
		try {
			string uri = request.getURI();
			string method = request.getMethod();

			Logger::get("main").information("Requested from %s, method %s", uri, method);
			for (RMFContainer &rmf : rthMap) {
				regex rx(rmf.regex);
				if (regex_match(uri, rx) && rmf.method == method) {
					if (rmf.fn) {
						rmf.fn(request, response);
					}
				}
			}

			response.setStatusAndReason(HTTPResponse::HTTP_OK);
			response.setContentType("application/json");
		} catch (const std::exception &e) {
			Logger::get("main").critical(e.what());
		}
	}

	void handleTest(HTTPServerRequest& request, HTTPServerResponse& response) {
		Logger::get("main").information("Within request test");
	}

private:
	ExistingApiRequestHandler *q;

	static RegexToHandlerVec rthMap;
};

RegexToHandlerVec ExistingApiRequestHandlerPrivate::rthMap  = {
	{".*/status", HTTPRequest::HTTP_GET, [] (HTTPServerRequest& request, HTTPServerResponse& response) {
		    Logger::get("main").information("Status match");
			ostream &os = response.send();
			os << "";
		}
	},

	{".*/register", HTTPRequest::HTTP_POST, [] (HTTPServerRequest& request, HTTPServerResponse& response) {
			Logger::get("main").information("Register match");
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
			Logger::get("main").information("lsserver DEL");
			ostream &os = response.send();
			os << "";
		}
	},

	{".*/lsserver", HTTPRequest::HTTP_POST, [] (HTTPServerRequest& request, HTTPServerResponse& response) {
			Logger::get("main").information("lsserver POST");
			ostream &os = response.send();
			os << "";
		}
	},

	{".*/lsserver", HTTPRequest::HTTP_GET, [] (HTTPServerRequest& request, HTTPServerResponse& response) {
			Logger::get("main").information("lsserver GET");
			ostream &os = response.send();
			os << "";
		}
	},

	{".*/postcreds", HTTPRequest::HTTP_POST, [] (HTTPServerRequest& request, HTTPServerResponse& response) {
		using namespace litesql;
		using namespace ncconsole;

		try {
			NCConsoleStorage db("sqlite3", "database=nconsole.db");
			if (db.needsUpgrade()) db.upgrade();

			string gname1("Gr1"), gname2("Gr2");
			DeviceGroup dg1(db), dg2(db);
			auto ds1 = select<DeviceGroup>(db, DeviceGroup::Uniquename == gname1);
			if (!ds1.count()) {
				dg1.uniquename = gname1;
				dg1.update();
			} else dg1 = ds1.one();

			auto ds2 = select<DeviceGroup>(db, DeviceGroup::Uniquename == gname2);
			if (!ds2.count()) {
				dg2.uniquename = gname2;
				dg2.update();
			} else dg2 = ds2.one();

			string dname1("Dev1"), dname2("Dev2");
			Device d1(db), d2(db);
			auto dsd1 = select<Device>(db, Device::Uniquename == dname1);
			if (!dsd1.count()) {
				d1.uniquename = dname1;
				d1.update();
			} else d1 = dsd1.one();

			auto dsd2 = select<Device>(db, Device::Uniquename == dname2);
			if (!dsd2.count()) {
				d2.uniquename = dname2;
				d2.update();
			} else d2 = dsd2.one();

			if (!dg1.devices().get(Device::Id == d1.id).count()) {
				dg1.devices().link(d1);
			}
			if (!d2.groups().get().count()) {
				d2.groups().link(dg1);
			}

			if (!select<Credential>(db, Credential::Authname == "teterevand").count()) {
				Credential teterev(db);

				teterev.authname = "teterevand";
				teterev.username = "Teterev Andrey";
				teterev.update();
			}

		} catch (const exception &e) {
			Logger::get("main").critical(e.what());
		}

		Logger::get("main").information("postcreds POST");
		ostream &os = response.send();
		os << "";
	}
	},

//	{"", HTTPRequest::HTTP_GET, &ExistingApiRequestHandlerPrivate::handleTest},

	{".*/echo", HTTPRequest::HTTP_GET, [] (HTTPServerRequest& request, HTTPServerResponse& response) {
		using namespace Poco::JSON;
		using namespace Poco::Dynamic;

		try {
			Var json_var = Parser().parse(request.get("json", "{}"));
			Object::Ptr root = json_var.extract<Object::Ptr>();
			auto username = root->getValue<string>("username");
			Logger::get("main").information("Username (template method): %s", username);
			DynamicStruct root_obj = *root;
			string username_easy = root_obj["username"];
			Logger::get("main").information("Username (easy way): %s", username_easy);

			stringstream ss;
			Stringifier::stringify(json_var, ss);
			Logger::get("main").information("Stringified: %s", ss.str());
			Stringifier::stringify(json_var, response.send());
		} catch (std::exception &e) {
			response.send() << "{\"Error\", \" Invalid json argument\"}" << endl;
		}
	}
	},

	{".*/groups", HTTPRequest::HTTP_POST, [] (HTTPServerRequest& request, HTTPServerResponse& response) {
		using namespace Poco::JSON;
		using namespace Poco::Dynamic;
		using namespace litesql;
		using namespace ncconsole;

		try {
			Object::Ptr root_obj = Parser().parse(request.get("json", "{}")).extract<Object::Ptr>();
			DynamicStruct root_struct = *root_obj;
			string method = root_struct["method"];
			Logger::get("main").information("Requested function: %s", method);

			NCConsoleStorage db("sqlite3", "database=nconsole.db");
			db.verbose = true;
			if (db.needsUpgrade()) db.upgrade();

			Object returnobj;
			if (method == "add") {
				string groupname = root_struct["params"]["name"];

				bool exists = select<DeviceGroup>(db, DeviceGroup::Uniquename == groupname).count();
				if (!exists) {
					DeviceGroup gr(db);
					gr.uniquename = groupname;
					gr.name = groupname;
					gr.update();
					returnobj.set("status", "ok");
					returnobj.set("reason", "");
					returnobj.set("value", (int)gr.id);
				} else {
					returnobj.set("status", "Rejected");
					returnobj.set("reason", "Db exists");
					returnobj.set("value", 0);
				}
			} else if (method == "rename") {
				int id = root_struct["params"]["id"];
				bool exists = select<DeviceGroup>(db, DeviceGroup::Id == id).count();
				if (exists) {
					string newname = root_struct["params"]["newname"];
					bool newexists = select<DeviceGroup>(db, DeviceGroup::Name == newname).count();
					if (!newexists) {
						DeviceGroup gr = select<DeviceGroup>(db, DeviceGroup::Id == id).one();
						gr.uniquename = newname;
						gr.name = newname;
						gr.update();
						returnobj.set("status", "Ok");
						returnobj.set("reason", "");
						returnobj.set("value", "");
					} else {
						returnobj.set("status", "Rejected");
						returnobj.set("reason", "Db newname exists");
						returnobj.set("value", "");
					}
				} else {
					returnobj.set("status", "Rejected");
					returnobj.set("reason", "Db missed");
					returnobj.set("value", "");
				}
			} else if (method == "delete") {
				int id = root_struct["params"]["id"];
				bool exists = select<DeviceGroup>(db, DeviceGroup::Id == id).count();
				if (exists) {
					DeviceGroup gr = select<DeviceGroup>(db, DeviceGroup::Id == id).one();
					gr.del();
					gr.update();
					returnobj.set("status", "Ok");
					returnobj.set("reason", "");
					returnobj.set("value", "");
				} else {
					returnobj.set("status", "Rejected");
					returnobj.set("reason", "Db missed");
					returnobj.set("value", "");
				}
			}

			root_obj->set("return", returnobj);
			root_obj->stringify(response.send());

			stringstream ss; request.write(ss);
			Logger::get("main").information("Incoming request: %s", ss.str());
		} catch (std::exception &e) {
			Logger::get("main").critical("Exception: %s", string(e.what()));
			response.send() << "{\"Error\", \" Invalid json argument\"}" << endl;
		}
	}
	},

	{".*/groups", HTTPRequest::HTTP_GET, [] (HTTPServerRequest& request, HTTPServerResponse& response) {
		using namespace Poco::JSON;
		using namespace Poco::Dynamic;
		using namespace litesql;
		using namespace ncconsole;

		try {
			Object::Ptr root_obj = Parser().parse(request.get("json", "{}")).extract<Object::Ptr>();
			DynamicStruct root_struct = *root_obj;
			string method = root_struct["method"];
			Logger::get("main").information("Requested function: %s", method);

			NCConsoleStorage db("sqlite3", "database=nconsole.db");
			db.verbose = true;
			if (db.needsUpgrade()) db.upgrade();

			auto convertGroup = [] (const DeviceGroup &gr) {
				Object groupObject;
				groupObject.set(gr.id.name(), (int)gr.id);
				groupObject.set(gr.uniquename.name(), (string)gr.uniquename);
				groupObject.set(gr.name.name(), (string)gr.name);

				return groupObject;
			};

			Object returnobj;
			if (method == "get") {
				if (root_struct["params"].isString()) { //Empty params
					auto ds = select<DeviceGroup>(db);
					if (ds.count()) {
						auto groups = ds.all();
						JSON::Array arr;
						for (const DeviceGroup &gr: groups) {
							arr.add(convertGroup(gr));
						}
						returnobj.set("status", "Ok");
						returnobj.set("reason", "");
						returnobj.set("value", arr);
					} else {
						returnobj.set("status", "Rejected");
						returnobj.set("reason", "Db missing");
						returnobj.set("value", "");
					}
				} else {
					int id = root_struct["params"]["id"];
					auto ds = select<DeviceGroup>(db, DeviceGroup::Id == id);
					if (ds.count()) {
						DeviceGroup gr = ds.one();
						Object retvalue = convertGroup(gr);
						returnobj.set("status", "Ok");
						returnobj.set("reason", "");
						returnobj.set("value", retvalue);
					} else {
						returnobj.set("status", "Rejected");
						returnobj.set("reason", "Db missing");
						returnobj.set("value", "");
					}
				}
			}

			root_obj->set("return", returnobj);
			root_obj->stringify(response.send());

			stringstream ss; request.write(ss);
			Logger::get("main").information("Incoming request: %s", ss.str());
		} catch (std::exception &e) {
			Logger::get("main").critical("Exception: %s", string(e.what()));
			response.send() << "{\"Error\", \" Invalid json argument\"}" << endl;
		}
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


