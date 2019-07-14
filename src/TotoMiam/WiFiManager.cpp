////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project                    Toto|Miam
/// @file                       TotoMiam/WiFiManager.cpp
/// @author                     Lucas Brémond <lucas.bremond@gmail.com>
/// @license                    MIT License

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <TotoMiam/ApplicationStorage.hpp>

#include <TotoMiam/WiFiManager.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace totomiam
{

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

                                WiFiManager::WiFiManager                    ( )
                                :   mode_(WiFiManager::Mode::Station),
                                    ssid_(""),
                                    password_(""),
                                    active_(false),
                                    applicationStoragePtr_(nullptr)
{

}

bool                            WiFiManager::isActive                       ( ) const
{
    return active_ ;
}

WiFiManager::Mode                WiFiManager::getMode                       ( ) const
{
    return mode_ ;
}

void                            WiFiManager::setMode                        (   const   WiFiManager::Mode&          aMode                                       )
{
    mode_ = aMode ;
}

void                            WiFiManager::start                          ( )
{

    if (this->isActive())
    {
        this->stop() ;
    }

    active_ = true ;

    WifiStation.enable(mode_ == WiFiManager::Mode::Station) ;
    WifiAccessPoint.enable(mode_ == WiFiManager::Mode::AccessPoint) ;

    if (mode_ == WiFiManager::Mode::Station)
    {

        if ((applicationStoragePtr_ != nullptr) && applicationStoragePtr_->isDefined())
        {

            ssid_ = applicationStoragePtr_->accessSSID() ;
            password_ = applicationStoragePtr_->accessPassword() ;

        }

        WifiStation.config(ssid_, password_) ;

        WifiEvents.onStationGotIP(StationGotIPDelegate(&WiFiManager::onConnectionSuccess, this)) ;
        WifiEvents.onStationDisconnect(StationDisconnectDelegate(&WiFiManager::onConnectionFailure, this)) ;

    }

    if (mode_ == WiFiManager::Mode::AccessPoint)
    {
        connectionSuccessHandler_() ;
    }

}

void                            WiFiManager::stop                           ( )
{

    if (!this->isActive())
    {
        return ;
    }

    if (mode_ == WiFiManager::Mode::Station)
    {
        WifiStation.enable(false) ;
    }

    if (mode_ == WiFiManager::Mode::AccessPoint)
    {
        WifiAccessPoint.enable(false) ;
    }

    active_ = false ;

}

void                            WiFiManager::associateApplicationStorage    (           ApplicationStorage&         anApplicationStorage                        )
{
    applicationStoragePtr_ = &anApplicationStorage ;
}

void                            WiFiManager::setConnectionSuccessHandler    (           Delegate<void()>            aDelegate                                   )
{
    connectionSuccessHandler_ = aDelegate ;
}

void                            WiFiManager::setConnectionFailureHandler    (           Delegate<void()>            aDelegate                                   )
{
    connectionFailureHandler_ = aDelegate ;
}

void                            WiFiManager::startmDNS                      ( )
{

    // struct mdns_info*            info                                            =        (struct mdns_info*)os_zalloc(sizeof(struct mdns_info)) ;

    // info->host_name                                                                =        (char*) "totomiam" ;
    // info->ipAddr                                                                =        WifiStation.getIP() ;
    // info->server_name                                                            =        (char*) "Sming" ;
    // info->server_port                                                            =        80 ;
    // info->txt_data[0]                                                            =        (char*) "version = now" ;

    // espconn_mdns_init(info) ;

}

void                            WiFiManager::onConnectionSuccess            (           IPAddress                   anIPAddress,
                                                                                        IPAddress                   aMask,
                                                                                        IPAddress                   aGateway                                    )
{

    if (!active_)
    {
        return ;
    }

    Serial.println("Connection to WiFi is successful!") ;

    Serial.println("IP: " + anIPAddress.toString()) ;
    Serial.println("Mask: " + aMask.toString()) ;
    Serial.println("Gateway: " + aGateway.toString()) ;

    this->startmDNS() ;

    if (connectionSuccessHandler_)
    {
        connectionSuccessHandler_() ;
    }

}

void                            WiFiManager::onConnectionFailure            (           String                      aSsid,
                                                                                        uint8_t                     aSsidLength,
                                                                                        uint8_t                     *bssid,
                                                                                        uint8_t                     aReason                                     )
{

    if (!active_)
    {
        return ;
    }

    Serial.println("Connection to WiFi has failed!") ;

    Serial.println("SSID: " + aSsid) ;
    Serial.println("Reason: " + aReason) ;

    if (mode_ == WiFiManager::Mode::Station)
    {

        // Retry connection

        WifiEvents.onStationGotIP(StationGotIPDelegate(&WiFiManager::onConnectionSuccess, this)) ;
        WifiEvents.onStationDisconnect(StationDisconnectDelegate(&WiFiManager::onConnectionFailure, this)) ;

        if (connectionFailureHandler_)
        {
            connectionFailureHandler_() ;
        }

    }

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
