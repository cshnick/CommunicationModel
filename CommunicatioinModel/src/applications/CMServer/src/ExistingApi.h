/*
 * ExistingApi.h
 *
 *  Created on: 14 апр. 2016 г.
 *      Author: ilia
 */

#ifndef NET_SAMPLES_RESTSERVER_SRC_EXISTINGAPI_H_
#define NET_SAMPLES_RESTSERVER_SRC_EXISTINGAPI_H_

#include <memory>

#include "Poco/Net/HTTPRequestHandler.h"
#include "Poco/Net/HTTPRequestHandlerFactory.h"
#include "Poco/Net/HTTPServerRequest.h"

class ExistingApiHandlerFactory : public Poco::Net::HTTPRequestHandlerFactory {
	Poco::Net::HTTPRequestHandler* createRequestHandler(const Poco::Net::HTTPServerRequest& request) override;
};

class ExistingApiRequestHandlerPrivate;
class ExistingApiRequestHandler : public Poco::Net::HTTPRequestHandler {
	friend class ExistingApiRequestHandlerPrivate;
public:
	ExistingApiRequestHandler();
	void handleRequest(Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response) override;

private:
	std::unique_ptr<ExistingApiRequestHandlerPrivate> d;
};

#endif /* NET_SAMPLES_RESTSERVER_SRC_EXISTINGAPI_H_ */
