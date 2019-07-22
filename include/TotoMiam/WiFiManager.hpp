////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project                    Toto|Miam
/// @file                       TotoMiam/WiFiManager.hpp
/// @author                     Lucas Brémond <lucas.bremond@gmail.com>
/// @license                    MIT License

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef __TotoMiam_WiFiManager__
#define __TotoMiam_WiFiManager__

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <SmingCore.h>

#include <TotoMiam/ApplicationStorage.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace totomiam
{

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class WiFiManager
{

    public:

        enum class Mode
        {

            Station,
            AccessPoint

        } ;

                                WiFiManager                                 ( ) ;

        bool                    isActive                                    ( ) const ;

        WiFiManager::Mode       getMode                                     ( ) const ;

        void                    setMode                                     (   const   WiFiManager::Mode&          aMode                                       ) ;

        void                    start                                       ( ) ;
        void                    stop                                        ( ) ;

        void                    associateApplicationStorage                 (           ApplicationStorage&         anApplicationStorage                        ) ;

        void                    setConnectionSuccessHandler                 (           Delegate<void()>            aDelegate                                   ) ;
        void                    setConnectionFailureHandler                 (           Delegate<void()>            aDelegate                                   ) ;

        static String           getModeFromString                           (   const   String&                     aString                                     ) ;

    private:

        WiFiManager::Mode       mode_ ;

        String                  ssid_ ;
        String                  password_ ;

        bool                    active_ ;

        ApplicationStorage*     applicationStoragePtr_ ;

        Delegate<void()>        connectionSuccessHandler_ ;
        Delegate<void()>        connectionFailureHandler_ ;

        void                    startmDNS                                   ( ) ;

        void                    onConnectionSuccess                         (           IPAddress                   anIPAddress,
                                                                                        IPAddress                   aMask,
                                                                                        IPAddress                   aGateway                                    ) ;

        void                    onConnectionFailure                         (           String                      aSsid,
                                                                                        uint8_t                     aSsidLength,
                                                                                        uint8_t                     *bssid,
                                                                                        uint8_t                     aReason                                     ) ;

} ;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
