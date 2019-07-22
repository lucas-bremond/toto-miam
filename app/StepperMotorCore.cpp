////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project                    Toto|Miam
/// @file                       TotoMiam/StepperMotorCore.cpp
/// @author                     Lucas Brémond <lucas.bremond@gmail.com>
/// @license                    MIT License

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <TotoMiam/Configuration.hpp>
#include <TotoMiam/StepperMotorController.hpp>

#include <TotoMiam/StepperMotorCore.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace totomiam
{

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// [TBI] add multi-channel support

const byte phases[] = { 1, 3, 2, 6, 4, 12, 8, 9 } ;

HardwareTimer* hardwareTimerPtr = nullptr ;

StepperMotor::Pinout pinout ;

bool started = false ;
bool reverse = false ;

int phase ;
int steps ;
int dir ;
int i ;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void IRAM_ATTR                  setup                                       (   const   StepperMotor::Pinout&       aPinout,
                                                                                const   int                         aStepCount                                  ) ;

void IRAM_ATTR                  tearDown                                    ( ) ;

void IRAM_ATTR                  activatePins                                ( ) ;

void IRAM_ATTR                  deactivatePins                              ( ) ;

void IRAM_ATTR                  writePins                                   (   const   int&                        aBitmap                                     ) ;

void IRAM_ATTR                  hardwareLoop                                ( ) ;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void IRAM_ATTR                  setup                                       (   const   StepperMotor::Pinout&       aPinout,
                                                                                const   int                         aStepCount                                  )
{

    started = true ;

    ETS_INTR_LOCK() ;

	// getPins();
	// calcTiming();

	ETS_INTR_UNLOCK() ;

    pinout = aPinout ;

    i = 0 ;
	steps = aStepCount ;
	dir = (steps > 0) - (steps < 0) ;
    steps *= dir ;
    reverse = false ;

    Serial.printf("Steps: [%d].\n", steps) ;
    Serial.printf("Direction: [%d].\n", dir) ;

    activatePins() ;

    hardwareTimerPtr->initializeUs(100000, hardwareLoop) ;

	hardwareTimerPtr->startOnce() ;

}

void IRAM_ATTR                  tearDown                                    ( )
{

    writePins(0) ;

    deactivatePins() ;

    phase = 0 ;
    steps = 0 ;
    dir = 0 ;
    i = 0 ;

    started = false ;
    reverse = false ;

}

void IRAM_ATTR                  activatePins                                ( )
{

    pinMode(pinout.pin_A, OUTPUT) ;
	pinMode(pinout.pin_B, OUTPUT) ;
	pinMode(pinout.pin_C, OUTPUT) ;
	pinMode(pinout.pin_D, OUTPUT) ;

}

void IRAM_ATTR                  deactivatePins                              ( )
{

    pinMode(pinout.pin_A, INPUT) ;
    pinMode(pinout.pin_B, INPUT) ;
    pinMode(pinout.pin_C, INPUT) ;
    pinMode(pinout.pin_D, INPUT) ;

}

void IRAM_ATTR                  writePins                                   (   const   int&                        aBitmap                                     )
{

    const bool state_A = aBitmap & 8 ? HIGH : LOW ;
    const bool state_B = aBitmap & 4 ? HIGH : LOW ;
    const bool state_C = aBitmap & 2 ? HIGH : LOW ;
    const bool state_D = aBitmap & 1 ? HIGH : LOW ;

    // Serial.print(state_A) ;
    // Serial.print(", ") ;
    // Serial.print(state_B) ;
    // Serial.print(", ") ;
    // Serial.print(state_C) ;
    // Serial.print(", ") ;
    // Serial.print(state_D) ;
    // Serial.print("\n") ;

    digitalWrite(pinout.pin_A, state_A) ;
    digitalWrite(pinout.pin_B, state_B) ;
    digitalWrite(pinout.pin_C, state_C) ;
    digitalWrite(pinout.pin_D, state_D) ;

}

void IRAM_ATTR                  hardwareLoop                                ( )
{

    if (!started)
    {
        return ;
    }

    // Serial.printf("StepperMotorCore :: hardwareLoop -> [i = %d]\n", i) ;

    hardwareTimerPtr->setIntervalUs(2000) ;
    // hardwareTimerPtr->setIntervalMs(2000) ;

    hardwareTimerPtr->startOnce() ;

    if (i <= steps)
    {

        writePins(phases[phase]) ;

        phase = (8 + phase + dir) % 8 ;

        i++ ;

    }
    else
    {

        if (!reverse)
        {

            i = 0 ;
            phase = 0 ;
            dir = -dir ;

            reverse = true ;

        }
        else
        {

            hardwareTimerPtr->stop() ;

            tearDown() ;

        }

    }

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

                                StepperMotorCore::StepperMotorCore          ( )
{

    hardwareTimerPtr = &hardwareTimer_ ;

}

                                StepperMotorCore::~StepperMotorCore         ( )
{

    channels_.removeAllElements() ;

    if (started)
    {

        hardwareTimer_.stop() ;

        hardwareTimerPtr = nullptr ;

        started = false ;

    }

}

bool                            StepperMotorCore::hasChannel                (           StepperMotorController&     aStepperMotorController                     ) const
{
    return channels_.contains(&aStepperMotorController) ;
}

bool                            StepperMotorCore::isChannelBusy             (   const   StepperMotorController&     aStepperMotorController                     ) const
{
    return started ; // TBM
}

void                            StepperMotorCore::start                     ( )
{

    // Serial.println("StepperMotorCore :: start...") ;

    // if (!started)
    // {

    //     started                                                                    =        true ;

    //     hardwareTimer.initializeUs(2000, hardwareLoop) ;

    //     hardwareTimer.startOnce() ;

    // }

    // Serial.println("StepperMotorCore :: start [OK]") ;

}

void                            StepperMotorCore::stop                      ( )
{

}

void                            StepperMotorCore::addChannel                (               StepperMotorController& aStepperMotorController                     )
{

    // Serial.println("StepperMotorCore :: addChannel...") ;

    // if ((channels_.size() < maxChannelCount) && (!this->hasChannel(aStepperMotorController)))
    // {

    //     channels_.add(&aStepperMotorController) ;

    // }

    // Serial.println("StepperMotorCore :: addChannel [OK]") ;

}

void                            StepperMotorCore::removeChannel             (               StepperMotorController& aStepperMotorController                     )
{

    // Serial.println("StepperMotorCore :: removingChannel...") ;

    // if (channels_.removeElement(&aStepperMotorController))
    // {

    //     ETS_INTR_LOCK() ;

    //     // getPins();
    //     // calcTiming();

    //     ETS_INTR_UNLOCK() ;

    //     if (channels_.size() == 0)
    //     {

    //         if (started)
    //         {

    //             started = false ;

    //             hardwareTimer.stop() ;

    //         }

    //     }

    // }

    // Serial.println("StepperMotorCore :: removingChannel [OK]") ;

}

void                            StepperMotorCore::rotate                    (   const   Angle&                      anAngle,
                                                                                        StepperMotorController&     aStepperMotorController                     )
{

    if (started)
    {
        return ;
    }

    Serial.println("Start rotating Stepper Motor [" + anAngle.toString() + "]...") ;

    const double inputRadius = aStepperMotorController.getInputRadius() ;
    const double outputRadius = aStepperMotorController.getOutputRadius() ;
    const uint stepsPerRotation = aStepperMotorController.getStepsPerRotation() ;

    const int steps = anAngle.getRevolutions() * outputRadius / inputRadius * stepsPerRotation ;

    setup(aStepperMotorController.getPinout(), steps) ;

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

StepperMotorCore                stepperMotorCore ;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
