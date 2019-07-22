////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project                    Toto|Miam
/// @file                       TotoMiam/Duration.cpp
/// @author                     Lucas Brémond <lucas.bremond@gmail.com>
/// @license                    MIT License

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <TotoMiam/Time.hpp>
#include <TotoMiam/Duration.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace totomiam
{

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool                            Duration::operator ==                       (   const   Duration&                   aDuration                                   ) const
{
    return duration_ == aDuration.duration_ ;
}

bool                            Duration::operator !=                       (   const   Duration&                   aDuration                                   ) const
{
    return duration_ != aDuration.duration_ ;
}

bool                            Duration::operator <=                       (   const   Duration&                   aDuration                                   ) const
{
    return duration_ <= aDuration.duration_ ;
}

bool                            Duration::operator <                        (   const   Duration&                   aDuration                                   ) const
{
    return duration_ < aDuration.duration_ ;
}

bool                            Duration::operator >=                       (   const   Duration&                   aDuration                                   ) const
{
    return duration_ >= aDuration.duration_ ;
}

bool                            Duration::operator >                        (   const   Duration&                   aDuration                                   ) const
{
    return duration_ > aDuration.duration_ ;
}

bool                            Duration::isDefined                         ( ) const
{
    return defined_ ;
}

int                             Duration::getSeconds                        ( ) const
{
    return duration_ ;
}

String                          Duration::toString                          ( ) const
{
    return String(duration_) + String(" [sec]") ;
}

Duration                        Duration::Undefined                         ( )
{

    Duration duration ;

    duration.defined_ = false ;
    duration.duration_ = 0 ;

    return duration ;

}

Duration                        Duration::Zero                              ( )
{

    Duration duration ;

    duration.defined_ = true ;
    duration.duration_ = 0 ;

    return duration ;

}

Duration                        Duration::Seconds                           (   const   int&                        aSecondCount                                )
{

    Duration duration ;

    duration.defined_ = true ;
    duration.duration_ = aSecondCount ;

    return duration ;

}

Duration                        Duration::Minutes                           (   const   int&                        aMinuteCount                                )
{

    Duration duration ;

    duration.defined_ = true ;
    duration.duration_ = aMinuteCount * 60 ;

    return duration ;

}

Duration                        Duration::Between                           (   const   Time&                       aFirstTime,
                                                                                const   Time&                       aSecondTime                                 )
{

    Duration duration ;

    duration.defined_ = true ;
    duration.duration_ = aSecondTime.getUnixTime() - aFirstTime.getUnixTime() ;

    return duration ;

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

                                Duration::Duration                          ( )
                                :   defined_(false),
                                    duration_(0)
{

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
