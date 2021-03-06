////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project                    Toto|Miam
/// @file                       TotoMiam/Angle.cpp
/// @author                     Lucas Brémond <lucas.bremond@gmail.com>
/// @license                    MIT License

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <TotoMiam/Angle.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace totomiam
{

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool                            Angle::operator ==                          (   const   Angle&                      anAngle                                     ) const
{
    return defined_ && anAngle.defined_ && (degrees_ == anAngle.degrees_) ;
}

bool                            Angle::operator !=                          (   const   Angle&                      anAngle                                     ) const
{
    return defined_ && anAngle.defined_ && (degrees_ != anAngle.degrees_) ;
}

bool                            Angle::operator <=                          (   const   Angle&                      anAngle                                     ) const
{
    return defined_ && anAngle.defined_ && (degrees_ <= anAngle.degrees_) ;
}

bool                            Angle::operator <                           (   const   Angle&                      anAngle                                     ) const
{
    return defined_ && anAngle.defined_ && (degrees_ < anAngle.degrees_) ;
}

bool                            Angle::operator >=                          (   const   Angle&                      anAngle                                     ) const
{
    return defined_ && anAngle.defined_ && (degrees_ >= anAngle.degrees_) ;
}

bool                            Angle::operator >                           (   const   Angle&                      anAngle                                     ) const
{
    return defined_ && anAngle.defined_ && (degrees_ > anAngle.degrees_) ;
}

Angle                           Angle::operator +                           (   const   Angle&                      anAngle                                     ) const
{

    Angle angle ;

    angle.defined_ = defined_ && anAngle.defined_ ;
    angle.degrees_ = angle.defined_ ? (degrees_ + anAngle.degrees_) : 0.0 ;

    return angle ;

}

Angle                           Angle::operator -                           (   const   Angle&                      anAngle                                     ) const
{

    Angle angle ;

    angle.defined_ = defined_ && anAngle.defined_ ;
    angle.degrees_ = angle.defined_ ? (degrees_ - anAngle.degrees_) : 0.0 ;

    return angle ;

}

bool                            Angle::isDefined                            ( ) const
{
    return defined_ ;
}

bool                            Angle::isZero                               ( ) const
{
    return defined_ && (degrees_ == 0.0) ;
}

float                           Angle::getDegrees                           ( ) const
{
    return degrees_ ;
}

float                           Angle::getRadians                           ( ) const
{
    return degrees_ * PI / 180.0 ;
}

float                           Angle::getRevolutions                       ( ) const
{
    return degrees_ / 360.0 ;
}

String                          Angle::toString                             ( ) const
{
    return String(degrees_) + " [deg]" ;
}

Angle                           Angle::Undefined                            ( )
{

    Angle angle ;

    angle.defined_ = false ;
    angle.degrees_ = 0.0 ;

    return angle ;

}

Angle                           Angle::Zero                                 ( )
{

    Angle angle ;

    angle.defined_ = true ;
    angle.degrees_ = 0.0 ;

    return angle ;

}

Angle                           Angle::Degrees                              (   const   float&                      aValue                                      )
{

    Angle angle ;

    angle.defined_ = true ;
    angle.degrees_ = aValue ;

    return angle ;

}

Angle                           Angle::Radians                              (   const   float&                      aValue                                      )
{

    Angle angle ;

    angle.defined_ = true ;
    angle.degrees_ = aValue * 180.0 / PI ;

    return angle ;

}

Angle                           Angle::Revolutions                          (   const   float&                      aValue                                      )
{

    Angle angle ;

    angle.defined_ = true ;
    angle.degrees_ = aValue * 360.0 ;

    return angle ;

}

Angle                           Angle::Parse                                (   const   String&                     aString                                     )
{

    // 180.0 [deg]
    // 1.0 [rad]
    // 3 [rev]

    const int indexOfOpeningBracket = aString.indexOf('[') ;
    const int indexOfClosingBracket = aString.indexOf(']') ;

    if ((indexOfOpeningBracket > 1) && (indexOfClosingBracket == aString.length() - 1) && ((indexOfOpeningBracket + 1) < indexOfClosingBracket))
    {

        const float value = aString.substring(0, indexOfOpeningBracket - 2).toFloat() ;
        const String unit = aString.substring(indexOfOpeningBracket + 1, indexOfClosingBracket - 1) ;

        if (unit == "deg")
        {
            return Angle::Degrees(value) ;
        }
        else if (unit == "rad")
        {
            return Angle::Radians(value) ;
        }
        else if (unit == "rev")
        {
            return Angle::Revolutions(value) ;
        }
        else
        {
            return Angle::Undefined() ;
        }

    }

    return Angle::Undefined() ;

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

                                Angle::Angle                                ( )
                                :   defined_(false),
                                    degrees_(0.0)
{

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
