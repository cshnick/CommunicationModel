//
// HTTPFormServer.cpp
//
// $Id: //poco/Main/Net/samples/HTTPFormServer/src/HTTPFormServer.cpp#5 $
//
// This sample demonstrates the HTTPServer and HTMLForm classes.
//
// Copyright (c) 2006, Applied Informatics Software Engineering GmbH.
// and Contributors.
//
// SPDX-License-Identifier:	BSL-1.0
//

#include "ExistingApi.h"

#include "Poco/Net/HTTPServer.h"
#include "Poco/Net/HTTPRequestHandler.h"
#include "Poco/Net/HTTPRequestHandlerFactory.h"
#include "Poco/Net/HTTPServerParams.h"
#include "Poco/Net/HTTPServerRequest.h"
#include "Poco/Net/HTTPServerResponse.h"
#include "Poco/Net/HTTPServerParams.h"
#include "Poco/Net/HTMLForm.h"
#include "Poco/Net/PartHandler.h"
#include "Poco/Net/MessageHeader.h"
#include "Poco/Net/ServerSocket.h"
#include "Poco/Net/SecureServerSocket.h"
#include "Poco/Net/SecureStreamSocket.h"
#include "Poco/CountingStream.h"
#include "Poco/NullStream.h"
#include "Poco/StreamCopier.h"
#include "Poco/Exception.h"
#include "Poco/Util/ServerApplication.h"
#include "Poco/Util/Option.h"
#include "Poco/Util/OptionSet.h"
#include "Poco/Util/HelpFormatter.h"
#include "Poco/Logger.h"
#include "Poco/ConsoleChannel.h"
#include "Poco/SplitterChannel.h"
#include "Poco/FormattingChannel.h"
#include "Poco/FileChannel.h"
#include "Poco/PatternFormatter.h"
#include <iostream>
#include <memory>

using Poco::Net::ServerSocket;
using Poco::Net::SecureServerSocket;
using Poco::Net::SecureStreamSocket;
using Poco::Net::HTTPRequestHandler;
using Poco::Net::HTTPRequestHandlerFactory;
using Poco::Net::HTTPServer;
using Poco::Net::HTTPServerRequest;
using Poco::Net::HTTPServerResponse;
using Poco::Net::HTTPServerParams;
using Poco::Net::MessageHeader;
using Poco::Net::HTMLForm;
using Poco::Net::NameValueCollection;
using Poco::Util::ServerApplication;
using Poco::Util::Application;
using Poco::Util::Option;
using Poco::Util::OptionSet;
using Poco::Util::HelpFormatter;
using Poco::CountingInputStream;
using Poco::NullOutputStream;
using Poco::StreamCopier;
using Poco::Channel;
using Poco::ConsoleChannel;
using Poco::FileChannel;
using Poco::SplitterChannel;
using Poco::Formatter;
using Poco::FormattingChannel;
using Poco::PatternFormatter;
using Poco::Logger;

class CMServer: public Poco::Util::ServerApplication {
public:
	CMServer()
		:_helpRequested(false) {}
	~CMServer() {}

protected:
	void initialize(Application& self) {
		loadConfiguration(); // load default configuration files, if present
		ServerApplication::initialize(self);
	}

	void uninitialize() {
		ServerApplication::uninitialize();
	}

	void defineOptions(OptionSet& options) {
		ServerApplication::defineOptions(options);

		options.addOption(
				Option("help", "h",	"display help information on command line arguments")
				.required(false)
				.repeatable(false));
	}

	void handleOption(const std::string& name, const std::string& value) {
		ServerApplication::handleOption(name, value);

		if (name == "help")
			_helpRequested = true;
	}

	void displayHelp() {
		HelpFormatter helpFormatter(options());
		helpFormatter.setCommand(commandName());
		helpFormatter.setUsage("OPTIONS");
		helpFormatter.setHeader("A web server that shows how to work with HTML forms.");
		helpFormatter.format(std::cout);
	}

	int main(const std::vector<std::string>& args) {
		if (_helpRequested) {
			displayHelp();
		} else {
			Poco::AutoPtr<SplitterChannel> splitterch(new SplitterChannel());
			Poco::AutoPtr<ConsoleChannel> consolech(new ConsoleChannel);
			Poco::AutoPtr<FileChannel> filech(new FileChannel("RESTServer.log"));
			splitterch->addChannel(consolech);
			splitterch->addChannel(filech);

			Poco::AutoPtr<Formatter> formatter(new PatternFormatter("%d-%m-%Y %H:%M:%S %s: %t"));
			Poco::AutoPtr<Channel> formattingChannel(new FormattingChannel(formatter, splitterch));

			Logger::create("main", formattingChannel);

			Logger::get("main").information("Starting CMServer...");
			unsigned short port = (unsigned short) config().getInt("CMServer.port", 9443);

			SecureServerSocket svs(port);
			HTTPServer srv(new ExistingApiHandlerFactory, svs, new HTTPServerParams);
			// start the HTTPServer
			srv.start();
			waitForTerminationRequest();
			srv.stop();
		}
		return Application::EXIT_OK;
	}

private:
	bool _helpRequested;
};

int main(int argc, char** argv) {

	CMServer app;
	return app.run(argc, argv);
}
