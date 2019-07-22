////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project                    Toto|Miam
/// @file                       TotoMiam/CalendarDate.cpp
/// @author                     Lucas Brémond <lucas.bremond@gmail.com>
/// @license                    MIT License

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <TotoMiam/Time.hpp>

#include <TotoMiam/CalendarDate.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace totomiam
{

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

                                CalendarDate::CalendarDate                  (   const   uint16_t&                   aYear,
                                                                                const   uint8_t&                    aMonth,
                                                                                const   uint8_t&                    aDay,
                                                                                const   uint8_t&                    anHourCount,
                                                                                const   uint8_t&                    aMinuteCount,
                                                                                const   uint8_t&                    aSecondCount                                )
                                :   year_(aYear),
                                    month_(aMonth),
                                    day_(aDay),
                                    hours_(anHourCount),
                                    minutes_(aMinuteCount),
                                    seconds_(aSecondCount)
{

}

bool                            CalendarDate::operator ==                   (   const   CalendarDate&               aCalendarDate                               ) const
{

    return (year_ == aCalendarDate.year_)
        && (month_ == aCalendarDate.month_)
        && (day_ == aCalendarDate.day_)
        && (hours_ == aCalendarDate.hours_)
        && (minutes_ == aCalendarDate.minutes_)
        && (seconds_ == aCalendarDate.seconds_) ;

}

bool                            CalendarDate::operator !=                   (   const   CalendarDate&               aCalendarDate                               ) const
{

    return (year_ != aCalendarDate.year_)
        || (month_ != aCalendarDate.month_)
        || (day_ != aCalendarDate.day_)
        || (hours_ != aCalendarDate.hours_)
        || (minutes_ != aCalendarDate.minutes_)
        || (seconds_ != aCalendarDate.seconds_) ;

}

bool                            CalendarDate::isDefined                     ( ) const
{

    return (year_ != 0)
        || (month_ != 0)
        || (day_ != 0)
        || (hours_ != 0)
        || (minutes_ != 0)
        || (seconds_ != 0) ;

}

uint16_t                        CalendarDate::getYear                       ( ) const
{
    return year_ ;
}

uint8_t                         CalendarDate::getMonth                      ( ) const
{
    return month_ ;
}

uint8_t                         CalendarDate::getDay                        ( ) const
{
    return day_ ;
}

uint8_t                         CalendarDate::getHours                      ( ) const
{
    return hours_ ;
}

uint8_t                         CalendarDate::getMinutes                    ( ) const
{
    return minutes_ ;
}

uint8_t                         CalendarDate::getSeconds                    ( ) const
{
    return seconds_ ;
}

String                          CalendarDate::toString                      (   const   CalendarDate::Format&       aFormat                                     ) const
{

    // 2000-01-01 00:00:00 [UTC]

    switch (aFormat)
    {

        case CalendarDate::Format::DateTime:
        {

            char buffer[25] ;

            sprintf(buffer, "%04d-%02d-%02d %02d:%02d:%02d [UTC]", year_, month_, day_, hours_, minutes_, seconds_) ;

            return { buffer } ;

        }

        case CalendarDate::Format::Date:
        {

            char buffer[10] ;

            sprintf(buffer, "%04d-%02d-%02d", year_, month_, day_) ;

            return { buffer } ;

        }

        case CalendarDate::Format::Time:
        {

            char buffer[14] ;

            sprintf(buffer, "%02d:%02d:%02d [UTC]", hours_, minutes_, seconds_) ;

            return { buffer } ;

        }

        default:
            break ;

    }

    return "" ;

}

void                            CalendarDate::setYear                       (   const   uint16_t&                   aYearCount                                  )
{
    year_ = aYearCount ;
}

void                            CalendarDate::setMonth                      (   const   uint8_t&                    aMonthCount                                 )
{
    month_ = aMonthCount ;
}

void                            CalendarDate::setDay                        (   const   uint8_t&                    aDayCount                                   )
{
    day_ = aDayCount ;
}

void                            CalendarDate::setHours                      (   const   uint8_t&                    aHourCount                                  )
{
    hours_ = aHourCount ;
}

void                            CalendarDate::setMinutes                    (   const   uint8_t&                    aMinuteCount                                )
{
    minutes_ = aMinuteCount ;
}

void                            CalendarDate::setSeconds                    (   const   uint8_t&                    aSecondCount                                )
{
    seconds_ = aSecondCount ;
}

CalendarDate                    CalendarDate::Undefined                     ( )
{
    return { 0, 0, 0, 0, 0, 0 } ;
}

CalendarDate                    CalendarDate::Time                          (   const   totomiam::Time&             aTime                                       )
{

    CalendarDate calendarDate ;

    uint8_t weekDay = 0 ;

    DateTime::fromUnixTime(aTime.getUnixTime(),
                           &calendarDate.seconds_,
                           &calendarDate.minutes_,
                           &calendarDate.hours_,
                           &calendarDate.day_,
                           &weekDay,
                           &calendarDate.month_,
                           &calendarDate.year_) ;

    calendarDate.month_++ ;

    if ((calendarDate.year_ < 1970) || (calendarDate.year_ > 2050))
    {
        return CalendarDate::Undefined() ;
    }

    if ((calendarDate.month_ < 1) || (calendarDate.month_ > 12))
    {
        return CalendarDate::Undefined() ;
    }

    if ((calendarDate.day_ < 1) || (calendarDate.day_ > 31))
    {
        return CalendarDate::Undefined() ;
    }

    if ((calendarDate.hours_ < 0) || (calendarDate.hours_ > 24))
    {
        return CalendarDate::Undefined() ;
    }

    if ((calendarDate.minutes_ < 0) || (calendarDate.minutes_ > 60))
    {
        return CalendarDate::Undefined() ;
    }

    if ((calendarDate.seconds_ < 0) || (calendarDate.seconds_ > 60))
    {
        return CalendarDate::Undefined() ;
    }

    return calendarDate ;

}

CalendarDate                    CalendarDate::Parse                         (   const   String&                     aString                                     )
{

    // Serial.println("CalendarDate::Parse") ;

    // YYYY-MM-DD hh:mm:ss [UTC]

    if (aString.length() != 25)
    {
        return CalendarDate::Undefined() ;
    }

    const uint16_t year = aString.substring(0, 4).toInt() ;
    const uint8_t month = aString.substring(5, 7).toInt() ;
    const uint8_t day = aString.substring(8, 10).toInt() ;

    const uint8_t hours = aString.substring(11, 13).toInt() ;
    const uint8_t minutes = aString.substring(14, 16).toInt() ;
    const uint8_t seconds = aString.substring(17, 19).toInt() ;

    const String timeScale = aString.substring(20, 25) ;

    // Serial.println(aString) ;
    // Serial.println(year) ;
    // Serial.println(month) ;
    // Serial.println(day) ;
    // Serial.println(hours) ;
    // Serial.println(minutes) ;
    // Serial.println(seconds) ;
    // Serial.println(timeScale) ;

    if ((year < 1970) || (year > 2050))
    {
        return CalendarDate::Undefined() ;
    }

    if ((month < 1) || (month > 12))
    {
        return CalendarDate::Undefined() ;
    }

    if ((day < 1) || (day > 31))
    {
        return CalendarDate::Undefined() ;
    }

    if (hours > 24)
    {
        return CalendarDate::Undefined() ;
    }

    if (minutes > 60)
    {
        return CalendarDate::Undefined() ;
    }

    if (seconds > 60)
    {
        return CalendarDate::Undefined() ;
    }

    if (timeScale != "[UTC]")
    {
        return CalendarDate::Undefined() ;
    }

    return { year, month, day, hours, minutes, seconds } ;

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

                                CalendarDate::CalendarDate                  ( )
                                :   year_(0),
                                    month_(0),
                                    day_(0),
                                    hours_(0),
                                    minutes_(0),
                                    seconds_(0)
{

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
