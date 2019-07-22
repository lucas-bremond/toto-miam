////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project                    Toto|Miam
/// @file                       TotoMiam/ApplicationStorage.cpp
/// @author                     Lucas Brémond <lucas.bremond@gmail.com>
/// @license                    MIT License

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <TotoMiam/ApplicationStorage.hpp>

#include <ArduinoJson.h>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace totomiam
{

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static bool mounted = false ;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

                                ApplicationStorage::ApplicationStorage      ( )
{

}

bool                            ApplicationStorage::isDefined               ( )
{
    return fileExist(APP_SETTINGS_FILE) ;
}

String                          ApplicationStorage::getSsid                 ( ) const
{
    return ssid_ ;
}

String                          ApplicationStorage::getPassword             ( ) const
{
    return password_ ;
}

void                            ApplicationStorage::setup                   ( )
{

    if (!mounted)
    {

        Serial.println("Mounting File System...") ;

        spiffs_mount() ;

        mounted = true ;

        Serial.println("File System is mounted.") ;

    }

}

void                            ApplicationStorage::load                    ( )
{

    Serial.println("Loading Application Storage...") ;

    if (this->isDefined())
    {

        const size_t size = fileGetSize(APP_SETTINGS_FILE) ;

        char* jsonString = new char[size + 1] ;

        fileGetContent(APP_SETTINGS_FILE, jsonString, size + 1) ;

        DynamicJsonDocument jsonDocument(size) ;

        deserializeJson(jsonDocument, jsonString) ;

        JsonObject network = jsonDocument["network"] ;

        ssid_ = network["ssid"].as<const char*>() ;
        password_ = network["password"].as<const char*>() ;

        delete[] jsonString ;

    }

    Serial.println("Application Storage is loaded.") ;

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
