////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///
///	This file is part of the TotoMiam library.
///
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

///	@file 						TotoMiam/Application.cpp
///	@author 					Lucas Bremond <lucas@axelspace.com>
///	@date 						9 Oct 2016

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <TotoMiam/StepperMotorController.hpp>

#include <TotoMiam/Application.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace TotoMiam
{

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

								Application::Application					( )
								:	wifiEnabled_(true),
									wifiActive_(false),
									statusTimerEnabled_(false)
{

}

								Application::~Application					( )
{
	this->stop() ;
}

bool							Application::isActive						( ) const
{
	return wifiManager_.isActive() || timeManager_.isActive() || serverManager_.isActive() || taskManager_.isActive() ;
}

void							Application::start							( )
{

	// Application storage setup

	applicationStorage_.load() ;

	// Serial setup

	Serial.begin(SERIAL_BAUD_RATE) ;
	Serial.systemDebugOutput(true) ;
	
	// set timezone hourly difference to UTC
	// SystemClock.setTimeZone(2);

	Serial.println("Starting...");

	// Status timer setup

	if (statusTimerEnabled_)
	{

		statusTimer_.initializeMs(1000, Delegate<void()>(&Application::onPrintStatus, this)) ; // TBM param
		
		statusTimer_.start() ;
	
	}

	// WiFi client setup

	if (!wifiManager_.isActive())
	{

		wifiManager_.associateApplicationStorage(applicationStorage_) ;

		wifiManager_.setConnectionSuccessHandler(Delegate<void()>(&Application::onWifiConnectionSuccess, this)) ;
		wifiManager_.setConnectionFailureHandler(Delegate<void()>(&Application::onWifiConnectionFailure, this)) ;

		wifiManager_.setMode(WiFiManager::Mode::Station) ;
		// wifiManager_.setMode(WiFiManager::Mode::AccessPoint) ;
		
		wifiManager_.start() ;

	}

}

void							Application::stop							( )
{

	if (taskManager_.isActive())
	{
		taskManager_.stop() ;
	}

	if (serverManager_.isActive())
	{
		serverManager_.stop() ;
	}

	if (timeManager_.isActive())
	{
		timeManager_.stop() ;
	}

	// WiFi client stop

	if (wifiManager_.isActive())
	{
		wifiManager_.stop() ;
	}

}

void							Application::onPrintStatus					( )
{

	if (!statusTimerEnabled_)
	{
		return ;
	}

}

void							Application::onWifiConnectionSuccess		( )
{

	// Server manager setup

	if (!serverManager_.isActive())
	{
		serverManager_.start() ;
	}

	// Time manager setup

	if (!timeManager_.isActive())
	{

		timeManager_.setClockSetHandler(Delegate<void()>(&Application::onClockSet, this)) ;
		
		timeManager_.start() ;

	}

}

void							Application::onWifiConnectionFailure		( )
{

	if (serverManager_.isActive())
	{
		serverManager_.stop() ;
	}

	if (timeManager_.isActive())
	{
		timeManager_.stop() ;
	}

}

void							Application::onClockSet						( )
{

	// Task manager setup

	if (!taskManager_.isActive())
	{

		serverManager_.associateTaskManager(taskManager_) ;

		taskManager_.associateApplicationStorage(applicationStorage_) ;
		
		taskManager_.start() ;

	}

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

TotoMiam::Application			application ;

void							init										( )
{

	// System.setCpuFrequency(eCF_80MHz) ;

	// File system setup

	spiffs_mount() ;

	// Starting application

	application.start() ;

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////