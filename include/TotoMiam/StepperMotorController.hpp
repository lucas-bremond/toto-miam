////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project                    Toto|Miam
/// @file                       TotoMiam/StepperMotorController.hpp
/// @author                     Lucas Brémond <lucas.bremond@gmail.com>
/// @license                    MIT License

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef __TotoMiam_StepperMotorController__
#define __TotoMiam_StepperMotorController__

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <TotoMiam/StepperMotor.hpp>
#include <TotoMiam/Angle.hpp>

#include <SmingCore.h>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace totomiam
{

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @brief                      Stepper motor controller class
///
/// @note                       Reference: https://github.com/bdargham/BYJ48-Stepper/blob/master/Stepper%20Driver.ino

class StepperMotorController
{

    public:

                                StepperMotorController                      (   const   StepperMotor::Mode&         aMode,
                                                                                const   StepperMotor::Pinout&       aPinout                                     ) ;

                                ~StepperMotorController                     ( ) ;

        bool                    isDefined                                   ( ) const ;
        bool                    isBusy                                      ( ) const ;

        double                  getInputRadius                              ( ) const ;
        double                  getOutputRadius                             ( ) const ;
        uint                    getStepsPerRotation                         ( ) const ;

        StepperMotor::Mode      getMode                                     ( ) const ;
        StepperMotor::Pinout    getPinout                                   ( ) const ;

        void                    rotate                                      (   const   Angle&                      anAngle                                     ) ;

    private:

        double                  inputRadius_ ;
        double                  outputRadius_ ;

        uint                    stepsPerRotation_ ;

        StepperMotor::Mode      mode_ ;
        StepperMotor::Pinout    pinout_ ;

} ;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
