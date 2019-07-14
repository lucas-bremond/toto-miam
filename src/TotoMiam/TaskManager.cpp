////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project                    Toto|Miam
/// @file                       TotoMiam/TaskManager.cpp
/// @author                     Lucas Brémond <lucas.bremond@gmail.com>
/// @license                    MIT License

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <TotoMiam/Configuration.hpp>
#include <TotoMiam/Duration.hpp>

#include <TotoMiam/TaskManager.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace totomiam
{

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

                                TaskManager::TaskManager                    ( )
                                :   active_(false),
                                    applicationStoragePtr_(nullptr),
                                    ruleCountLimit_(10),
                                    taskCountLimit_(10),
                                    currentTaskPtr_(nullptr)
{

}

bool                            TaskManager::isActive                       ( ) const
{
    return active_ ;
}

void                            TaskManager::start                          ( )
{

    if (this->isActive())
    {
        this->stop() ;
    }

    Serial.println("Starting Task Manager...") ;

    active_ = true ;

    this->load() ;

    this->addRule(Rule::AtTime(1, CalendarDate(2016, 12, 11, 20, 30, 0), Duration::Seconds(60))) ;
    this->addRule(Rule::AtTime(2, CalendarDate(2016, 12, 11, 7, 30, 0), Duration::Seconds(60))) ;

    timer_.initializeMs(1000, std::bind(&TaskManager::onManage, this)) ; // TBM param

    timer_.start() ;

    Serial.println("Task Manager has started.") ;

}

void                            TaskManager::stop                           ( )
{

    if (!this->isActive())
    {
        return ;
    }

    Serial.println("Stopping Task Manager...") ;

    timer_.stop() ;

    active_ = false ;

    Serial.println("Task Manager has stopped.") ;

}

void                            TaskManager::associateApplicationStorage    (           ApplicationStorage&         anApplicationStorage                        )
{
    applicationStoragePtr_ = &anApplicationStorage ;
}

bool                            TaskManager::hasRuleWithId                  (   const    uint&                      aRuleId                                     ) const
{

    for (uint idx = 0; idx < rules_.size(); ++idx)
    {

        const Rule& rule = rules_[idx] ;

        if (rule.getId() == aRuleId)
        {
            return true ;
        }

    }

    return false ;

}

bool                            TaskManager::hasTaskWithId                  (   const   uint&                       aTaskId                                     ) const
{

    for (uint idx = 0; idx < tasks_.size(); ++idx)
    {

        const Task& task = tasks_[idx] ;

        if (task.getId() == aTaskId)
        {
            return true ;
        }

    }

    return false ;

}

const Rule&                     TaskManager::accessRuleWithId               (   const   uint&                       aRuleId                                     ) const
{

    for (uint idx = 0; idx < rules_.size(); ++idx)
    {

        const Rule& rule = rules_[idx] ;

        if (rule.getId() == aRuleId)
        {
            return rule ;
        }

    }

}

const Task&                     TaskManager::accessTaskWithId               (   const   uint&                       aTaskId                                     ) const
{

    for (uint idx = 0; idx < tasks_.size(); ++idx)
    {

        const Task& task = tasks_[idx] ;

        if (task.getId() == aTaskId)
        {
            return task ;
        }

    }

}

const Vector<Rule>&             TaskManager::accessRules                    ( ) const
{
    return rules_ ;
}

const Vector<Task>&             TaskManager::accessTasks                    ( ) const
{
    return tasks_ ;
}

uint                            TaskManager::getNextRuleId                  ( ) const
{

    uint nextRuleId = 1 ;

    for (uint idx = 0; idx < rules_.size(); ++idx)
    {

        const uint ruleId = rules_[idx].getId() ;

        if (nextRuleId <= ruleId)
        {
            nextRuleId = ruleId + 1 ;
        }

    }

    return nextRuleId ;

}

uint                            TaskManager::getNextTaskId                  ( ) const
{

    uint nextTaskId = 1 ;

    for (uint idx = 0; idx < tasks_.size(); ++idx)
    {

        const uint taskId = tasks_[idx].getId() ;

        if (nextTaskId <= taskId)
        {
            nextTaskId = taskId + 1 ;
        }

    }

    return nextTaskId ;

}

bool                            TaskManager::addRule                        (   const   Rule&                       aRule                                       )
{

    Serial.printf("Adding Rule [%d]...\n", aRule.getId()) ;

    for (uint idx = 0; idx < rules_.size(); ++idx)
    {

        if (rules_[idx].getId() == aRule.getId())
        {

            Serial.printf("Rule [%d] is already added.\n", aRule.getId()) ;

            return false ;

        }

    }

    if (rules_.size() < ruleCountLimit_)
    {

        rules_.addElement(aRule) ;

        this->save() ;

        Serial.printf("Rule [%d] added.\n", aRule.getId()) ;

        return true ;

    }

    Serial.printf("Cannot add Rule [%d]\n.", aRule.getId()) ;

    return false ;

}

bool                            TaskManager::addTask                        (   const   Task&                       aTask                                       )
{

    Serial.printf("Adding Task [%d]...\n", aTask.getId()) ;

    for (uint idx = 0; idx < tasks_.size(); ++idx)
    {

        if (tasks_[idx].getId() == aTask.getId())
        {

            Serial.printf("Task [%d] is already added.\n", aTask.getId()) ;

            return false ;

        }

    }

    if (tasks_.size() >= taskCountLimit_)
    {

        for (uint idx = 0; idx < tasks_.size(); ++idx)
        {

            const Task& task = tasks_[idx] ;

            if (task.getStatus() != Task::Status::Pending)
            {

                tasks_.removeElementAt(idx) ;

                break ;

            }

        }

    }

    if (tasks_.size() < taskCountLimit_)
    {

        tasks_.addElement(aTask) ;

        this->save() ;

        Serial.printf("Task [%d] added.\n", aTask.getId()) ;

        return true ;

    }

    Serial.printf("Cannot add Task [%d]\n.", aTask.getId()) ;

    return false ;

}

bool                            TaskManager::removeRuleWithId               (   const   uint&                       aRuleId                                     )
{

    Serial.printf("Removing Rule [%d]...\n", aRuleId) ;

    for (uint idx = 0; idx < rules_.size(); ++idx)
    {

        const Rule& rule = rules_[idx] ;

        if (rule.getId() == aRuleId)
        {

            rules_.removeElementAt(idx) ;

            this->save() ;

            Serial.printf("Removed Rule [%d].\n", aRuleId) ;

            return true ;

        }

    }

    Serial.printf("No Rule [%d] found...\n", aRuleId) ;

    return false ;

}

bool                            TaskManager::removeTaskWithId               (   const   uint&                       aTaskId                                     )
{

    Serial.printf("Removing Task [%d]...\n", aTaskId) ;

    for (uint idx = 0; idx < tasks_.size(); ++idx)
    {

        const Task& task = tasks_[idx] ;

        if (task.getId() == aTaskId)
        {

            tasks_.removeElementAt(idx) ;

            this->save() ;

            Serial.printf("Removed Task [%d].\n", aTaskId) ;

            return true ;

        }

    }

    Serial.printf("No Task [%d] found...\n", aTaskId) ;

    return false ;

}

bool                            TaskManager::addImmediateTask                ( )
{

    Serial.println("Adding immediate Task...") ;

    return this->addTask(Task(this->getNextTaskId(), Time::Now())) ;

}

void                            TaskManager::load                           ( )
{

    if ((applicationStoragePtr_ != nullptr) && applicationStoragePtr_->isDefined())
    {

        // TBC...

    }

}

void                            TaskManager::save                           ( )
{

    if ((applicationStoragePtr_ != nullptr) && applicationStoragePtr_->isDefined())
    {

        // TBC...

    }

}

void                            TaskManager::onManage                        ( )
{

    Serial.println("Managing Tasks...") ;

    const Time currentTime = Time::Now() ;

    // Executing tasks

    for (size_t idx = 0; idx < tasks_.size(); ++idx)
    {

        Task& task = tasks_[idx] ;

        Serial.print("Task [") ;
        Serial.print(task.getId()) ;
        Serial.print("] status is [") ;
        Serial.print(Task::StringFromStatus(task.getStatus())) ;
        Serial.println("].") ;

        if (task.getStatus() == Task::Status::Pending)
        {

            if (task.getExecutionTime() <= currentTime)
            {

                task.execute() ;

                this->save() ;

                return ;

            }

        }

    }

    // Cheking rules

    for (size_t idx = 0; idx < rules_.size(); ++idx)
    {

        Rule& rule = rules_[idx] ;

        bool hasCorrespondingPendingTask = false ;

        for (uint idx = 0; idx < tasks_.size(); ++idx)
        {

            Task& task = tasks_[idx] ;

            if (task.isRuleDefined() && (task.getRuleId() == rule.getId()) && (task.getStatus() == Task::Status::Pending))
            {

                hasCorrespondingPendingTask = true ;

                break ;

            }

        }

        if (!hasCorrespondingPendingTask)
        {

            // Adding task...

            this->addTask(Task(this->getNextTaskId(), rule.getNextExecutionTime(), rule.getTaskDuration(), rule.getId())) ;

            rule.resetExecutionTime(rule.getNextExecutionTime()) ;

            this->save() ;

            return ;

        }

    }

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
