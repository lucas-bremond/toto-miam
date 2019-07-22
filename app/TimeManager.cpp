////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project                    Toto|Miam
/// @file                       TotoMiam/TimeManager.cpp
/// @author                     Lucas Brémond <lucas.bremond@gmail.com>
/// @license                    MIT License

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <TotoMiam/TimeManager.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace totomiam
{

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

                                TimeManager::TimeManager                    ( )
                                :   ntpServerUrl_("pool.ntp.org"),
                                    pollingInterval_(30),
                                    ntpClient_(nullptr)
{

    // Set timezone hourly difference to UTC

    // SystemClock.setTimeZone(2);

}

bool                            TimeManager::isActive                       ( ) const
{
    return ntpClient_ != nullptr ;
}

void                            TimeManager::start                          ( )
{

    if (this->isActive())
    {
        this->stop() ;
    }

    Serial.println("Starting Time Manager...") ;

    ntpClient_ = new NtpClient(ntpServerUrl_, pollingInterval_, NtpTimeResultDelegate(&TimeManager::onNtpReceive, this)) ;

    Serial.println("Time Manager has started.") ;

}

void                            TimeManager::stop                           ( )
{

    if (!this->isActive())
    {
        return ;
    }

    Serial.println("Stopping Time Manager...") ;

    delete ntpClient_ ;

    ntpClient_ = nullptr ;

    Serial.println("Time Manager has stopped.") ;

}

void                            TimeManager::setClockSetHandler             (           Delegate<void()>            aDelegate                                   )
{
    clockSetHandler_ = aDelegate ;
}

void                            TimeManager::onNtpReceive                   (           NtpClient&                  aNtpClient,
                                                                                        time_t                      aNtpTime                                    )
{

    SystemClock.setTime(aNtpTime, TimeZone::eTZ_UTC) ;

    if (clockSetHandler_)
    {
        clockSetHandler_() ;
    }

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
