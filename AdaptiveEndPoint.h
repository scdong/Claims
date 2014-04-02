/*
 * AdaptiveActor.h
 *
 *  Created on: Aug 8, 2013
 *      Author: wangli
 */

#ifndef ADAPTIVEENDPOINT_H_
#define ADAPTIVEENDPOINT_H_
#include <Theron/Theron.h>
#include <string>
#include "Message.h"
#include "Logging.h"
class AdaptiveEndPoint:public Theron::EndPoint {
public:
	AdaptiveEndPoint(const char* name, std::string ip, std::string port);

	virtual ~AdaptiveEndPoint();
//	static AdaptiveEndPoint* getInstance();
private:
	bool SayHelloToCoordinator(std::string ip,std::string port);
	int GetCoordinatorEndPointPort();
	bool WaitForReadySignalFromCoordinator();
	bool ConnectToCoordinateEndPoint(int port);
	bool ConnectToRemoteEndPoint(std::string location);
protected:
	Theron::Framework *framework;
	Logging* logging_;
private:
	Theron::Actor* connectionActor;
	int socket_coor;
	std::string ip_coor;

	/**
	 * The Actor which receive the node states from the coordinator
	 */
	friend class ConnectionActor;
//////////////////////////////////////////////////
	class ConnectionActor:public Theron::Actor{
	public:
		ConnectionActor(AdaptiveEndPoint*,const char* Name);
	private:
		void ReceiveNodeStatus256(const Message256 &message, const Theron::Address from);
	private:
		AdaptiveEndPoint* AEP;
	};
};

#endif /* ADAPTIVEACTOR_H_ */
