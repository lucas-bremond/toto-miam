////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project                    Toto|Miam
/// @file                       TotoMiam/Angle.hpp
/// @author                     Lucas Brémond <lucas.bremond@gmail.com>
/// @license                    MIT License

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef __TotoMiam_Angle__
#define __TotoMiam_Angle__

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <SmingCore.h>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace totomiam
{

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class Angle
{

    public:

        bool                    operator ==                                 (   const   Angle&                      anAngle                                     ) const ;
        bool                    operator !=                                 (   const   Angle&                      anAngle                                     ) const ;
        bool                    operator <=                                 (   const   Angle&                      anAngle                                     ) const ;
        bool                    operator <                                  (   const   Angle&                      anAngle                                     ) const ;
        bool                    operator >=                                 (   const   Angle&                      anAngle                                     ) const ;
        bool                    operator >                                  (   const   Angle&                      anAngle                                     ) const ;

        Angle                   operator +                                  (   const   Angle&                      anAngle                                     ) const ;
        Angle                   operator -                                  (   const   Angle&                      anAngle                                     ) const ;

        bool                    isDefined                                   ( ) const ;
        bool                    isZero                                      ( ) const ;

        float                   getDegrees                                  ( ) const ;
        float                   getRadians                                  ( ) const ;
        float                   getRevolutions                              ( ) const ;

        String                  toString                                    ( ) const ;

        static Angle            Undefined                                   ( ) ;

        static Angle            Zero                                        ( ) ;

        static Angle            Degrees                                     (   const   float&                      aValue                                      ) ;
        static Angle            Radians                                     (   const   float&                      aValue                                      ) ;
        static Angle            Revolutions                                 (   const   float&                      aValue                                      ) ;

        static Angle            Parse                                       (   const   String&                     aString                                     ) ;

    private:

        bool                    defined_ ;
        float                   degrees_ ;

                                Angle                                       ( ) ;

} ;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
