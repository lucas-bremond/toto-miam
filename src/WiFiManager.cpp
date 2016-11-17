////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///
///	This file is part of the TotoMiam library.
///
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

///	@file 						TotoMiam/WiFiManager.cpp
///	@author 					Lucas Bremond <lucas@axelspace.com>
///	@date 						9 Oct 2016

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <TotoMiam/applicationStorage.hpp>

#include <TotoMiam/WiFiManager.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace TotoMiam
{

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

								WiFiManager::WiFiManager					( )
								:	SSID_(""),
									password_(""),
									active_(false),
									applicationStoragePtr_(nullptr)
{

}

bool							WiFiManager::isActive						( ) const
{
	return active_ ;
}

void							WiFiManager::start							( )
{

	Serial.println("Starting WiFi Manager...") ;

	if (this->isActive())
	{
		this->stop() ;
	}

	if ((applicationStoragePtr_ != nullptr) && applicationStoragePtr_->isDefined())
	{

		SSID_																	=		applicationStoragePtr_->accessSSID() ;
		password_																=		applicationStoragePtr_->accessPassword() ;

		Serial.println("SSID = " + SSID_) ;
	
	} else {

		return ;

	}

	active_																		=		true ;

	WifiStation.enable(true) ;
	WifiStation.config(SSID_, password_) ;

	WifiStation.waitConnection(Delegate<void()>(&WiFiManager::onConnectionSuccess, this), 30, Delegate<void()>(&WiFiManager::onConnectionFailure, this)) ; // TBM param

	WifiAccessPoint.enable(false) ;

	Serial.println("Starting WiFi Manager [OK]") ;

}

void							WiFiManager::stop							( )
{

	Serial.println("Stopping WiFi Manager...") ;

	if (!this->isActive())
	{
		return ;
	}

	WifiStation.enable(false) ;

	active_																		=		false ;

	Serial.println("Stopping WiFi Manager [OK]") ;

}

void							WiFiManager::associateApplicationStorage	(			ApplicationStorage&			anApplicationStorage				)
{
	applicationStoragePtr_														=		&anApplicationStorage ;
}

void							WiFiManager::setConnectionSuccessHandler	(			Delegate<void()>			aDelegate							)
{
	connectionSuccessHandler_													=		aDelegate ;	
}

void							WiFiManager::setConnectionFailureHandler	(			Delegate<void()>			aDelegate							)
{
	connectionFailureHandler_													=		aDelegate ;	
}

void							WiFiManager::startmDNS						( )
{

	Serial.println("Starting mDNS...") ;

	struct mdns_info*			info											=		(struct mdns_info*)os_zalloc(sizeof(struct mdns_info)) ;
	
	info->host_name																=		(char*) "totomiam" ;
	info->ipAddr																=		WifiStation.getIP() ;
	info->server_name															=		(char*) "Sming" ;
	info->server_port															=		80 ;
	info->txt_data[0]															=		(char*) "version = now" ;

	espconn_mdns_init(info) ;

	Serial.println("Starting mDNS [OK]") ;

}

void							WiFiManager::onConnectionSuccess			( )
{

	Serial.println("WiFi connection successful...") ;

	if (!active_)
	{
		return ;
	}

	this->startmDNS() ;

	if (connectionSuccessHandler_)
	{
		connectionSuccessHandler_() ;
	}

}

void							WiFiManager::onConnectionFailure			( )
{

	Serial.println("WiFi connection failed...") ;

	if (!active_)
	{
		return ;
	}

	// Retry connection

	WifiStation.waitConnection(Delegate<void()>(&WiFiManager::onConnectionSuccess, this), 10, Delegate<void()>(&WiFiManager::onConnectionFailure, this)) ; // TBM param

	if (connectionFailureHandler_)
	{
		connectionFailureHandler_() ;
	}

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////