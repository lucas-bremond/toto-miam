////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project                    Toto|Miam
/// @file                       TotoMiam/Task.hpp
/// @author                     Lucas Brémond <lucas.bremond@gmail.com>
/// @license                    MIT License

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef __TotoMiam_Task__
#define __TotoMiam_Task__

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <SmingCore.h>

#include <TotoMiam/Time.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace totomiam
{

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class Task
{

    public:

        enum class Status
        {

            Undefined,
            Pending,
            Executing,
            Completed,
            Failed

        } ;

                                Task                                        (   const   uint&                       anId,
                                                                                const   Time&                       anExecutionTime,
                                                                                const   Duration&                   aDuration                                   =   Duration::Seconds(3),
                                                                                const   uint&                       aRuleId                                     =   0,
                                                                                const   Task::Status&               aStatus                                     =   Task::Status::Pending ) ;

        bool                    isDefined                                   ( ) const ;
        bool                    isRuleDefined                               ( ) const ;

        uint                    getId                                       ( ) const ;
        Task::Status            getStatus                                   ( ) const ;
        Time                    getExecutionTime                            ( ) const ;
        Duration                getDuration                                 ( ) const ;
        uint                    getRuleId                                   ( ) const ;

        void                    setStatus                                   (   const   Task::Status&               aStatus                                     ) ;

        void                    execute                                     ( ) ;

        static Task             Undefined                                   ( ) ;

        static String           StringFromStatus                            (   const   Task::Status&               aStatus                                     ) ;

    private:

        uint                    id_ ;
        Task::Status            status_ ;
        Time                    executionTime_ ;
        Duration                duration_ ;

        uint                    ruleId_ ;

} ;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
