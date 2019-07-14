////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project                    Toto|Miam
/// @file                       TotoMiam/Task.cpp
/// @author                     Lucas Brémond <lucas.bremond@gmail.com>
/// @license                    MIT License

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <TotoMiam/Configuration.hpp>
#include <TotoMiam/StepperMotorController.hpp>

#include <TotoMiam/Task.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace totomiam
{

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

                                Task::Task                                  (   const   uint&                       anId,
                                                                                const   Time&                       anExecutionTime,
                                                                                const   Duration&                   aDuration,
                                                                                const   uint&                       aRuleId,
                                                                                const   Task::Status&               aStatus                                     )
                                :   id_(anId),
                                    status_(aStatus),
                                    executionTime_(anExecutionTime),
                                    duration_(aDuration),
                                    ruleId_(aRuleId)
{

}

bool                            Task::isDefined                             ( ) const
{
    return status_ != Task::Status::Undefined ;
}

bool                            Task::isRuleDefined                         ( ) const
{
    return ruleId_ > 0 ;
}

uint                            Task::getId                                 ( ) const
{
    return id_ ;
}

Task::Status                    Task::getStatus                             ( ) const
{
    return status_ ;
}

Time                            Task::getExecutionTime                      ( ) const
{
    return executionTime_ ;
}

Duration                        Task::getDuration                           ( ) const
{
    return duration_ ;
}

uint                            Task::getRuleId                             ( ) const
{
    return ruleId_ ;
}

void                            Task::setStatus                             (   const   Task::Status&               aStatus                                     )
{
    status_ = aStatus ;
}

void                            Task::execute                               ( )
{

    Serial.printf("Executing Task [%d]...\n", id_) ;

    if (Duration::Between(executionTime_, Time::Now()) <= Duration::Minutes(1))
    {

        status_ = Task::Status::Executing ;

        StepperMotorController stepperMotorController = { D0, D1, D2, D3 } ;

        stepperMotorController.rotate(Angle::Degrees(-90.0)) ;

        // stepperMotorControllerPtr_ = new StepperMotorController(D0, D1, D2, D3) ; // TBM param

        // Serial.println("Servo...") ;

        // ServoChannel* servoChannelPtr_ = new(ServoChannel) ;

        // servoChannelPtr_->attach(2) ;

        // Serial.println("Servo !") ;

        status_ = Task::Status::Completed ;

        // LED

        // digitalWrite(PIN_LED, HIGH) ;

        // delay(3000) ;

        // digitalWrite(PIN_LED, LOW) ;

        // digitalWrite(PIN_LED, state);

        // Motor

        // Revert state

        // state = !state ;

        // status_ = Task::Status::Completed ;

        // motorMaxCount_ = task.getDuration().getSeconds() * 1000 / motorTimerLoopMs_ ;

        // currentTaskPtr_ = task ;

        Serial.printf("Task [%d] has been executed.\n", id_) ;

    }
    else
    {

        Serial.printf("Task [%d] execution has failed.\n", id_) ;

        status_ = Task::Status::Failed ;

    }

}

Task                            Task::Undefined                             ( )
{
    return { 0, Time::Undefined(), Duration::Zero(), 0, Task::Status::Undefined } ;
}

String                          Task::StringFromStatus                      (   const   Task::Status&               aStatus                                     )
{

    switch (aStatus)
    {

        case Task::Status::Undefined:
            return "Undefined" ;

        case Task::Status::Pending:
            return "Pending" ;

        case Task::Status::Executing:
            return "Executing" ;

        case Task::Status::Completed:
            return "Completed" ;

        case Task::Status::Failed:
            return "Failed" ;

    }

    return "Error" ;

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
