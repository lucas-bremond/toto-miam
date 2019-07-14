////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project                    Toto|Miam
/// @file                       TotoMiam/CalendarDate.hpp
/// @author                     Lucas Brémond <lucas.bremond@gmail.com>
/// @license                    MIT License

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef __TotoMiam_CalendarDate__
#define __TotoMiam_CalendarDate__

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <SmingCore/SmingCore.h>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace totomiam
{

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class Time ;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class CalendarDate
{

    public:

        enum class Format
        {

            Undefined,
            DateTime,
            Date,
            Time

        } ;

                                CalendarDate                                (   const   uint16_t&                   aYear,
                                                                                const   uint8_t&                    aMonth,
                                                                                const   uint8_t&                    aDay,
                                                                                const   uint8_t&                    anHourCount,
                                                                                const   uint8_t&                    aMinuteCount,
                                                                                const   uint8_t&                    aSecondCount                                ) ;

        bool                    operator ==                                 (   const   CalendarDate&               aCalendarDate                               ) const ;
        bool                    operator !=                                 (   const   CalendarDate&               aCalendarDate                               ) const ;

        bool                    isDefined                                   ( ) const ;

        uint16_t                getYear                                     ( ) const ;
        uint8_t                 getMonth                                    ( ) const ;
        uint8_t                 getDay                                      ( ) const ;
        uint8_t                 getHours                                    ( ) const ;
        uint8_t                 getMinutes                                  ( ) const ;
        uint8_t                 getSeconds                                  ( ) const ;

        String                  toString                                    (   const   CalendarDate::Format&       aFormat                                     =        CalendarDate::Format::DateTime ) const ;

        void                    setYear                                     (   const   uint16_t&                   aYearCount                                  ) ;
        void                    setMonth                                    (   const   uint8_t&                    aMonthCount                                 ) ;
        void                    setDay                                      (   const   uint8_t&                    aDayCount                                   ) ;
        void                    setHours                                    (   const   uint8_t&                    aHourCount                                  ) ;
        void                    setMinutes                                  (   const   uint8_t&                    aMinuteCount                                ) ;
        void                    setSeconds                                  (   const   uint8_t&                    aSecondCount                                ) ;

        static CalendarDate     Undefined                                   ( ) ;

        static CalendarDate     Time                                        (   const   totomiam::Time&             aTime                                       ) ;

        static CalendarDate     Parse                                       (   const   String&                     aString                                     ) ;

    private:

        uint16_t                year_ ;
        uint8_t                 month_ ;
        uint8_t                 day_ ;
        uint8_t                 hours_ ;
        uint8_t                 minutes_ ;
        uint8_t                 seconds_ ;

                                CalendarDate                                ( ) ;

} ;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
