////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project                    Toto|Miam
/// @file                       TotoMiam/StepperMotorController.cpp
/// @author                     Lucas Brémond <lucas.bremond@gmail.com>
/// @license                    MIT License

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <TotoMiam/Configuration.hpp>

#include <TotoMiam/StepperMotorCore.hpp>

#include <TotoMiam/StepperMotorController.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace totomiam
{

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

                                StepperMotorController::StepperMotorController ( const  StepperMotor::Mode&         aMode,
                                                                                const   StepperMotor::Pinout&       aPinout                                     )
                                :   inputRadius_(1.5), // TBM param
                                    outputRadius_(4.0), // TBM param
                                    stepsPerRotation_(4096), // TBM param
                                    mode_(aMode),
                                    pinout_(aPinout)
{
    // stepperMotorCore.addChannel(*this) ;
}

                                StepperMotorController::~StepperMotorController ( )
{
    // stepperMotorCore.removeChannel(*this) ;
}

bool                            StepperMotorController::isDefined           ( ) const
{
    return mode_ != StepperMotor::Mode::Undefined ;
}

bool                            StepperMotorController::isBusy              ( ) const
{
    return stepperMotorCore.isChannelBusy(*this) ;
}

double                          StepperMotorController::getInputRadius      ( ) const
{
    return inputRadius_ ;
}

double                          StepperMotorController::getOutputRadius     ( ) const
{
    return outputRadius_ ;
}

uint                            StepperMotorController::getStepsPerRotation ( ) const
{
    return stepsPerRotation_ ;
}

StepperMotor::Mode              StepperMotorController::getMode             ( ) const
{
    return mode_ ;
}

StepperMotor::Pinout            StepperMotorController::getPinout           ( ) const
{
    return pinout_ ;
}

void                            StepperMotorController::rotate              (   const   Angle&                      anAngle                                     )
{

    if (!this->isDefined())
    {
        return ;
    }

    if (this->isBusy())
    {
        return ;
    }

    Serial.println("Stepper Motor Controller is rotating [" + anAngle.toString() + "]...") ;

    stepperMotorCore.rotate(anAngle, *this) ;

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
