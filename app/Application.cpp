////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project                    Toto|Miam
/// @file                       TotoMiam/Application.cpp
/// @author                     Lucas Brémond <lucas.bremond@gmail.com>
/// @license                    MIT License

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <TotoMiam/StepperMotorController.hpp>

#include <TotoMiam/Application.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace totomiam
{

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

                                Application::Application                    ( )
                                :   wifiEnabled_(true),
                                    wifiActive_(false),
                                    statusTimerEnabled_(true)
{

}

                                Application::~Application                   ( )
{
    this->stop() ;
}

bool                            Application::isActive                       ( ) const
{
    return wifiManager_.isActive() || timeManager_.isActive() || serverManager_.isActive() || taskManager_.isActive() ;
}

void                            Application::start                          ( )
{

    Serial.println("Starting Application...") ;

    // Application storage setup

    applicationStorage_.setup() ;
    applicationStorage_.load() ;

    // Status timer setup

    if (statusTimerEnabled_)
    {

        statusTimer_.initializeMs(1000, std::bind(&Application::onPrintStatus, this)) ; // TBM param

        statusTimer_.start() ;

    }

    // WiFi client setup

    if (!wifiManager_.isActive())
    {

        Serial.println("Starting WiFi Manager...") ;

        wifiManager_.associateApplicationStorage(applicationStorage_) ;

        wifiManager_.setConnectionSuccessHandler(Delegate<void()>(&Application::onWifiConnectionSuccess, this)) ;
        wifiManager_.setConnectionFailureHandler(Delegate<void()>(&Application::onWifiConnectionFailure, this)) ;

        wifiManager_.setMode(WiFiManager::Mode::Station) ;
        // wifiManager_.setMode(WiFiManager::Mode::AccessPoint) ;

        wifiManager_.start() ;

        Serial.println("WiFi Manager has started.") ;

    }

    Serial.println("Application has started.") ;

}

void                            Application::stop                           ( )
{

    Serial.println("Stopping Application...") ;

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

    if (wifiManager_.isActive())
    {
        wifiManager_.stop() ;
    }

    Serial.println("Application has stopped.") ;

}

void                            Application::onPrintStatus                  ( )
{

    Serial.printf("Current time: [%s].\n", Time::Now().toString().c_str()) ;

}

void                            Application::onWifiConnectionSuccess        ( )
{

    Serial.println("WiFi is connected!") ;

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

void                            Application::onWifiConnectionFailure        ( )
{

    Serial.println("WiFi connection has failed.") ;

    if (serverManager_.isActive())
    {
        serverManager_.stop() ;
    }

    if (timeManager_.isActive())
    {
        timeManager_.stop() ;
    }

}

void                            Application::onClockSet                     ( )
{

    Serial.println("Clock has been set.") ;

    // Task manager setup

    if (!taskManager_.isActive())
    {

        serverManager_.associateTaskManager(taskManager_) ;

        taskManager_.associateApplicationStorage(applicationStorage_) ;

        taskManager_.start() ;

    }

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

totomiam::Application           application ;

void                            init                                        ( )
{

    // Set up serial

    Serial.begin(SERIAL_BAUD_RATE) ;
    Serial.systemDebugOutput(true) ;

    // Change CPU frequency to 160 MHz

	// System.setCpuFrequency(eCF_160MHz) ;
	Serial.printf("CPU frequency set to [%d Hz].\n", (int)System.getCpuFrequency()) ;

    // Starting application

    application.start() ;

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
