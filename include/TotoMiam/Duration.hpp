////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project                    Toto|Miam
/// @file                       TotoMiam/Duration.hpp
/// @author                     Lucas Brémond <lucas.bremond@gmail.com>
/// @license                    MIT License

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef __TotoMiam_Duration__
#define __TotoMiam_Duration__

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <SmingCore.h>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace totomiam
{

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class Time ;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class Duration
{

    public:

        bool                    operator ==                                 (   const   Duration&                   aDuration                                   ) const ;
        bool                    operator !=                                 (   const   Duration&                   aDuration                                   ) const ;
        bool                    operator <=                                 (   const   Duration&                   aDuration                                   ) const ;
        bool                    operator <                                  (   const   Duration&                   aDuration                                   ) const ;
        bool                    operator >=                                 (   const   Duration&                   aDuration                                   ) const ;
        bool                    operator >                                  (   const   Duration&                   aDuration                                   ) const ;

        bool                    isDefined                                   ( ) const ;

        int                     getSeconds                                  ( ) const ;
        String                  toString                                    ( ) const ;

        static Duration         Undefined                                   ( ) ;

        static Duration         Zero                                        ( ) ;

        static Duration         Seconds                                     (     const     int&                    aSecondCount                                ) ;
        static Duration         Minutes                                     (     const     int&                    aMinuteCount                                ) ;

        static Duration         Between                                     (   const   Time&                       aFirstTime,
                                                                                const   Time&                       aSecondTime                                 ) ;

    private:

        bool                    defined_ ;
        int                     duration_ ;

                                Duration                                    ( ) ;

} ;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
