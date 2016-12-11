////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///
///	This file is part of the TotoMiam library.
///
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

///	@file 						TotoMiam/TimeManager.cpp
///	@author 					Lucas Bremond <lucas@axelspace.com>
///	@date 						9 Oct 2016

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <TotoMiam/TimeManager.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace TotoMiam
{

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

								TimeManager::TimeManager					( )
								:	NTPServer_("pool.ntp.org"),
									pollingInterval_(30),
									NTPClient_(nullptr)
{

	// // Option 1
	// // Use this option if you want to have full control of NtpTime client
	// // Default : no automatic NTP requests sent, no automatic update of SystemTime
	// // Default : NTP_DEFAULT_SERVER and NTP_DEFAULT_AUTO_UPDATE_INTERVAL from ntpclient.h

	// // NtpClient ntpClient(onNtpReceive);

	// // Option 2
	// // Use this option if you want control but other server/timeout options
	// // Default : use server as defined in call, no automatic update of SystemTime
	// // Default : automatic NTP request at myRequestInterval seconds
	// // Default : if myRequestInterval == 0 -> no automatic NTP request

	// // NtpClient ntpClient ("my_ntp_server", myRequestInterval, onNtpReceive);

	// // Option 3
	// // Use this option if you want to start wit autorefresh and autosystemupdate
	// // No further callback from ntpClient
	// // NtpClient ntpClient("pool.ntp.org", 30);

	// // Option 4
	// // only create pointer and initialize on onWifiConnectionSuccess
	// // NtpClient *ntpClient;

	// //	ntpClient.setAutoQueryInterval(60);
	// //	ntpClient.setAutoQuery(true);
	// //  ntpClient.setAutoUpdateSystemClock(true);
	// 	// Request to update time now. 
	// 	// Otherwise the set interval will pass before time
	// 	// is updated.
	// //	ntpClient.requestTime();

}

bool							TimeManager::isActive						( ) const
{
	return (NTPClient_ != nullptr) ;
}

void							TimeManager::start							( )
{

	// Serial.println("Starting Time Manager...") ;

	if (this->isActive())
	{
		this->stop() ;
	}

	if (true) // TBR
	{

		NTPClient_																=		new NtpClient(NTPServer_, pollingInterval_, NtpTimeResultDelegate(&TimeManager::onNtpReceive, this)) ;
	
	} else {

		clockSetHandler_() ;

	}

	// Serial.println("Starting Time Manager [OK]") ;

}

void							TimeManager::stop							( )
{

	// Serial.println("Stopping Time Manager...") ;

	if (!this->isActive())
	{
		return ;
	}

	delete NTPClient_ ;

	NTPClient_																	=		nullptr ;

	// Serial.println("Stopping Time Manager [OK]") ;

}

void							TimeManager::setClockSetHandler				(		Delegate<void()>				aDelegate							)
{
	clockSetHandler_															=		aDelegate ;
}

void							TimeManager::onNtpReceive					(			NtpClient&					aNTPClient,
																						time_t						aNTPTime							)
{

	SystemClock.setTime(aNTPTime, TimeZone::eTZ_UTC) ;

	Serial.print("TimeManager Callback Time_t = ");
	Serial.print(aNTPTime) ;
	Serial.print("Time = ");
	Serial.println(SystemClock.getSystemTimeString());

	if (clockSetHandler_)
	{
		clockSetHandler_() ;
	}

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////