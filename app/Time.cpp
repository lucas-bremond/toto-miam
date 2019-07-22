////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project                    Toto|Miam
/// @file                       TotoMiam/Time.cpp
/// @author                     Lucas Brémond <lucas.bremond@gmail.com>
/// @license                    MIT License

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <TotoMiam/CalendarDate.hpp>

#include <TotoMiam/Time.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace totomiam
{

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool                            Time::operator ==                           (   const   Time&                       aTime                                       ) const
{
    return timestamp_ == aTime.timestamp_ ;
}

bool                            Time::operator !=                           (   const   Time&                       aTime                                       ) const
{
    return timestamp_ != aTime.timestamp_ ;
}

bool                            Time::operator <=                           (   const   Time&                       aTime                                       ) const
{
    return timestamp_ <= aTime.timestamp_ ;
}

bool                            Time::operator <                            (   const   Time&                       aTime                                       ) const
{
    return timestamp_ < aTime.timestamp_ ;
}

bool                            Time::operator >=                           (   const   Time&                       aTime                                       ) const
{
    return timestamp_ >= aTime.timestamp_ ;
}

bool                            Time::operator >                            (   const   Time&                       aTime                                       ) const
{
    return timestamp_ > aTime.timestamp_ ;
}

Time                            Time::operator +                            (   const   Duration&                   aDuration                                   ) const
{

    if (this->isDefined())
    {

        Time time(*this) ;

        time.timestamp_ += aDuration.getSeconds() ;

        return time ;

    }

    return Time::Undefined() ;

}

bool                            Time::isDefined                             ( ) const
{
    return timestamp_ > 0 ;
}

time_t                          Time::getUnixTime                           ( ) const
{
    return timestamp_ ;
}

String                          Time::toString                              ( ) const
{
    return CalendarDate::Time(*this).toString() ;
}

Time                            Time::Undefined                             ( )
{

    Time time ;

    time.timestamp_ = 0 ;

    return time ;

}

Time                            Time::Now                                   ( )
{
    return Time::Unix(SystemClock.now(TimeZone::eTZ_UTC)) ;
}

Time                            Time::Unix                                  (   const   time_t&                     aTimestamp                                  )
{

    Time time ;

    time.timestamp_ = aTimestamp ;

    return time ;

}

Time                            Time::CalendarDate                          (   const   totomiam::CalendarDate&     aCalendarDate                               )
{

    return Time::Unix(DateTime::toUnixTime(aCalendarDate.getSeconds(),
                                           aCalendarDate.getMinutes(),
                                           aCalendarDate.getHours(),
                                           aCalendarDate.getDay(),
                                           aCalendarDate.getMonth() - 1,
                                           aCalendarDate.getYear())) ;

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

                                Time::Time                                  ( )
                                :   timestamp_(0)
{

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
