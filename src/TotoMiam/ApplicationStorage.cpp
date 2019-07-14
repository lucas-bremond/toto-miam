////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project                    Toto|Miam
/// @file                       TotoMiam/ApplicationStorage.cpp
/// @author                     Lucas Brémond <lucas.bremond@gmail.com>
/// @license                    MIT License

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <TotoMiam/ApplicationStorage.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace totomiam
{

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

                                ApplicationStorage::ApplicationStorage      ( )
{

}

bool                            ApplicationStorage::isDefined               ( )
{
    return fileExist(APP_SETTINGS_FILE) ;
}

const String&                   ApplicationStorage::accessSSID              ( ) const
{
    return ssid_ ;
}

const String&                   ApplicationStorage::accessPassword          ( ) const
{
    return password_ ;
}

void                            ApplicationStorage::load                    ( )
{

    // Serial.println("Loading application storage...") ;

    if (this->isDefined())
    {

        DynamicJsonBuffer jsonBuffer ;

        const int size = fileGetSize(APP_SETTINGS_FILE) ;

        char* jsonString = new char[size + 1] ;

        fileGetContent(APP_SETTINGS_FILE, jsonString, size + 1) ;

        JsonObject& root = jsonBuffer.parseObject(jsonString) ;

        JsonObject& network = root["network"] ;

        ssid_ = network["ssid"].asString() ;
        password_ = network["password"].asString() ;

        delete[] jsonString ;

    }

    // Serial.println("Loading application storage [OK]") ;

}

void                            ApplicationStorage::save                    ( )
{

    // DynamicJsonBuffer jsonBuffer ;

    // JsonObject& root = jsonBuffer.createObject() ;

    // JsonObject& network = jsonBuffer.createObject() ;

    // root["network"] = network ;

    // network["ssid"] = ssid_.c_str() ;
    // network["password"] = password_.c_str() ;

    // // TODO: add direct file stream writing

    // String rootString ;

    // root.printTo(rootString) ;

    // fileSetContent(APP_SETTINGS_FILE, rootString) ;

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
