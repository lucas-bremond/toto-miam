////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project                    Toto|Miam
/// @file                       TotoMiam/Rule.hpp
/// @author                     Lucas Brémond <lucas.bremond@gmail.com>
/// @license                    MIT License

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef __TotoMiam_Rule__
#define __TotoMiam_Rule__

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <SmingCore/SmingCore.h>

#include <TotoMiam/Time.hpp>
#include <TotoMiam/CalendarDate.hpp>
#include <TotoMiam/Duration.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace totomiam
{

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class Rule
{

    public:

        enum class Type
        {

            Undefined,
            Time,
            Interval

        } ;

        bool                    isDefined                                   ( ) const ;

        uint                    getId                                       ( ) const ;
        Rule::Type              getType                                     ( ) const ;
        CalendarDate            getTime                                     ( ) const ;
        Duration                getInterval                                 ( ) const ;
        Duration                getTaskDuration                             ( ) const ;
        Time                    getPreviousExecutionTime                    ( ) const ;
        Time                    getNextExecutionTime                        ( ) const ;

        void                    resetExecutionTime                          (   const   Time&                       aTime                                       ) ;

        static Rule             AtTime                                      (   const   uint&                       anId,
                                                                                const   CalendarDate&               aCalendarDate,
                                                                                const   Duration&                   aTaskDuration                               =    Duration::Seconds(3) ) ;

        static Rule             AtInterval                                  (   const   uint&                       anId,
                                                                                const   Duration&                   anInterval,
                                                                                const   Duration&                   aTaskDuration                               =    Duration::Seconds(3) ) ;

        static Rule::Type       TypeFromString                              (   const   String&                     aString                                     ) ;
        static String           StringFromType                              (   const   Rule::Type&                 aType                                       ) ;

    private:

        uint                    id_ ;
        Rule::Type              type_ ;

        CalendarDate            time_ ;
        Duration                interval_ ;
        Duration                taskDuration_ ;

        Time                    previousExecutionTime_ ;
        mutable Time            nextExecutionTime_ ;

                                Rule                                        ( ) ;

} ;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
