////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project                    Toto|Miam
/// @file                       TotoMiam/ServerManager.cpp
/// @author                     Lucas Brémond <lucas.bremond@gmail.com>
/// @license                    MIT License

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <TotoMiam/ServerManager.hpp>
#include <TotoMiam/Version.hpp>

#include <JsonObjectStream.h>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace totomiam
{

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

typedef Delegate<void(HttpRequest&, HttpResponse&)> HttpPathDelegate ;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

                                ServerManager::ServerManager                (   const   uint                        aPort                                       )
                                :   port_(aPort),
                                    serverPtr_(nullptr),
                                    taskManagerPtr_(nullptr)
{

}

bool                            ServerManager::isActive                     ( ) const
{
    return serverPtr_ != nullptr ;
}

void                            ServerManager::start                        ( )
{

    if (this->isActive())
    {
        this->stop() ;
    }

    serverPtr_ = new HttpServer() ;

    if (serverPtr_ != nullptr)
    {

        serverPtr_->listen(port_) ;

        serverPtr_->paths.setDefault(HttpPathDelegate(&ServerManager::onFile, this)) ;

        serverPtr_->paths.set("/", HttpPathDelegate(&ServerManager::onIndex, this)) ;
        serverPtr_->paths.set("/status", HttpPathDelegate(&ServerManager::onStatus, this)) ;
        serverPtr_->paths.set("/time", HttpPathDelegate(&ServerManager::onTime, this)) ;
        serverPtr_->paths.set("/rules", HttpPathDelegate(&ServerManager::onRules, this)) ;
        serverPtr_->paths.set("/tasks", HttpPathDelegate(&ServerManager::onTasks, this)) ;

    }

}

void                            ServerManager::stop                         ( )
{

    if (!this->isActive())
    {
        return ;
    }

    delete serverPtr_ ;

    serverPtr_ = nullptr ;

}

void                            ServerManager::associateTaskManager         (           TaskManager&                aTaskManager                                )
{
    taskManagerPtr_ = &aTaskManager ;
}

void                            ServerManager::onIndex                      (           HttpRequest&                aRequest,
                                                                                        HttpResponse&               aResponse                                   )
{

    aResponse.setCache(86400, true) ;

    aResponse.sendFile("index.html") ;

}

void                            ServerManager::onFile                        (          HttpRequest&                aRequest,
                                                                                        HttpResponse&               aResponse                                   )
{

    String file = aRequest.uri.Path ;

    if (file[0] == '/')
    {
        file = file.substring(1) ;
    }

    if (file[0] == '.')
    {
        aResponse.code = HTTP_STATUS_FORBIDDEN ;
    }
    else
    {

        aResponse.setCache(86400, true) ;
        aResponse.sendFile(file) ;

    }

}

void                            ServerManager::onStatus                     (           HttpRequest&                aRequest,
                                                                                        HttpResponse&               aResponse                                   )
{

    if (aRequest.method == HTTP_GET)
    {

        JsonObjectStream* jsonStream = new JsonObjectStream() ;

        JsonObject jsonObject = jsonStream->getRoot() ;

        jsonObject["status"] = (bool)true ;
        jsonObject["version"] = (String)Version::Current().toString() ;

        aResponse.sendDataStream(jsonStream, MIME_JSON) ;

    }
    else
    {
        aResponse.code = HTTP_STATUS_FORBIDDEN ;
    }

}

void                            ServerManager::onTime                       (           HttpRequest&                aRequest,
                                                                                        HttpResponse&               aResponse                                   )
{

    if (aRequest.method == HTTP_GET)
    {

        JsonObjectStream* jsonStream = new JsonObjectStream() ;

        JsonObject jsonObject = jsonStream->getRoot() ;

        jsonObject["time"] = (String)Time::Now().toString() ;

        aResponse.sendDataStream(jsonStream, MIME_JSON) ;

    }
    else
    {
        aResponse.code = HTTP_STATUS_FORBIDDEN ;
    }

}

void                            ServerManager::onRules                      (           HttpRequest&                aRequest,
                                                                                        HttpResponse&               aResponse                                   )
{

    if (!taskManagerPtr_)
    {

        aResponse.code = HTTP_STATUS_NOT_FOUND ;

        return ;

    }

    if (aRequest.method == HTTP_GET)
    {

        JsonObjectStream* jsonStream = new JsonObjectStream() ;

        JsonObject jsonObject = jsonStream->getRoot() ;

        const String idString = aRequest.getQueryParameter("id") ;

        if (idString == "")
        {

            JsonArray ruleArray = jsonObject.createNestedArray("rules") ;

            for (uint idx = 0; idx < taskManagerPtr_->accessRules().size(); ++idx)
            {

                const Rule& rule = taskManagerPtr_->accessRules().elementAt(idx) ;

                JsonObject ruleObject = ruleArray.createNestedObject() ;

                ruleObject["id"] = (int)rule.getId() ;
                ruleObject["type"] = (String)Rule::StringFromType(rule.getType()) ;

                switch (rule.getType())
                {

                    case Rule::Type::Time:
                        ruleObject["time"] = (String)rule.getTime().toString(CalendarDate::Format::Time) ;
                        break ;

                    case Rule::Type::Interval:
                        ruleObject["interval"] = (String)rule.getInterval().toString() ;
                        break ;

                    default:
                        // Do nothing...
                        break ;

                }

                if (rule.getPreviousExecutionTime().isDefined())
                {
                    ruleObject["previous_execution_time"] = (String)CalendarDate::Time(rule.getPreviousExecutionTime()).toString(CalendarDate::Format::DateTime) ;
                }

            }

        }
        else
        {

            const uint id = idString.toInt() ;

            if (id == 0)
            {

                aResponse.code = HTTP_STATUS_FORBIDDEN ;

                return ;

            }

            if (taskManagerPtr_->hasRuleWithId(id))
            {

                const Rule& rule = taskManagerPtr_->accessRuleWithId(id) ;

                jsonObject["id"] = (int)rule.getId() ;
                jsonObject["type"] = (String)Rule::StringFromType(rule.getType()) ;

                switch (rule.getType())
                {

                    case Rule::Type::Time:
                        jsonObject["time"] = (String)rule.getTime().toString(CalendarDate::Format::Time) ;
                        break ;

                    case Rule::Type::Interval:
                        jsonObject["interval"] = (String)rule.getInterval().toString() ;
                        break ;

                    default:
                        // Do nothing...
                        break ;

                }

                if (rule.getPreviousExecutionTime().isDefined())
                {
                    jsonObject["previous_execution_time"] = (String)CalendarDate::Time(rule.getPreviousExecutionTime()).toString(CalendarDate::Format::DateTime) ;
                }

            }

        }

        aResponse.sendDataStream(jsonStream, MIME_JSON) ;

    }
    else if (aRequest.method == HTTP_POST)
    {

        const String idString = aRequest.getPostParameter("id") ;

        uint id = 0 ;

        if (idString != "")
        {

            id = idString.toInt() ;

            if (id == 0)
            {

                aResponse.code = HTTP_STATUS_FORBIDDEN ;

                return ;

            }

        }
        else
        {
            id = taskManagerPtr_->getNextRuleId() ;
        }

        const String ruleTypeString = aRequest.getPostParameter("type") ;

        if (ruleTypeString != "")
        {

            const Rule::Type ruleType = Rule::TypeFromString(ruleTypeString) ;

            switch (ruleType)
            {

                case Rule::Type::Time:
                {

                    const String calendarDateString = aRequest.getPostParameter("time") ;

                    Serial.println(calendarDateString) ;

                    if (calendarDateString == "")
                    {

                        aResponse.code = HTTP_STATUS_FORBIDDEN ;

                        return ;

                    }

                    const CalendarDate calendarDate = CalendarDate::Parse(calendarDateString) ;

                    Serial.println(calendarDate.toString()) ;

                    if (!calendarDate.isDefined())
                    {

                        aResponse.code = HTTP_STATUS_FORBIDDEN ;

                        return ;

                    }

                    if (!taskManagerPtr_->addRule(Rule::AtTime(id, calendarDate)))
                    {

                        aResponse.code = HTTP_STATUS_FORBIDDEN ;

                        return ;

                    }

                    break ;

                }

                // case Rule::Type::Interval: // TBI
                // {
                //     break ;
                // }

                default:

                    aResponse.code = HTTP_STATUS_FORBIDDEN ;

                    return ;


            }

        }
        else
        {

            aResponse.code = HTTP_STATUS_FORBIDDEN ;

            return ;

        }

    }
    else if (aRequest.method == HTTP_DELETE)
    {

        const String ruleIdString = aRequest.getQueryParameter("id") ;

        if (ruleIdString == "")
        {

            aResponse.code = HTTP_STATUS_FORBIDDEN ;

            return ;

        }

        const uint ruleId = ruleIdString.toInt() ;

        if (ruleId == 0)
        {

            aResponse.code = HTTP_STATUS_FORBIDDEN ;

            return ;

        }

        if (!taskManagerPtr_->removeRuleWithId(ruleId))
        {

            aResponse.code = HTTP_STATUS_FORBIDDEN ;

            return ;

        }

    }
    else
    {
        aResponse.code = HTTP_STATUS_FORBIDDEN ;
    }

}

void                            ServerManager::onTasks                        (         HttpRequest&                aRequest,
                                                                                        HttpResponse&               aResponse                                   )
{

    if (!taskManagerPtr_)
    {

        aResponse.code = HTTP_STATUS_NOT_FOUND ;

        return ;

    }

    if (aRequest.method == HTTP_GET)
    {

        JsonObjectStream* jsonStream = new JsonObjectStream() ;

        JsonObject jsonObject = jsonStream->getRoot() ;

        const String idString = aRequest.getQueryParameter("id") ;

        if (idString == "")
        {

            JsonArray taskArray = jsonObject.createNestedArray("tasks") ;

            for (uint idx = 0; idx < taskManagerPtr_->accessTasks().size(); ++idx)
            {

                const Task& task = taskManagerPtr_->accessTasks().elementAt(idx) ;

                JsonObject taskObject = taskArray.createNestedObject() ;

                taskObject["id"] = (int)task.getId() ;
                taskObject["status"] = (String)Task::StringFromStatus(task.getStatus()) ;
                taskObject["execution_time"] = (String)task.getExecutionTime().toString() ;

                if (task.isRuleDefined())
                {
                    taskObject["rule_id"] = (int)task.getRuleId() ;
                }

            }

        }
        else
        {

            const uint id = idString.toInt() ;

            if (id == 0)
            {

                aResponse.code = HTTP_STATUS_FORBIDDEN ;

                return ;

            }

            if (taskManagerPtr_->hasTaskWithId(id))
            {

                const Task& task = taskManagerPtr_->accessTaskWithId(id) ;

                jsonObject["id"] = (int)task.getId() ;
                jsonObject["status"] = (String)Task::StringFromStatus(task.getStatus()) ;
                jsonObject["execution_time"] = (String)task.getExecutionTime().toString() ;

                if (task.isRuleDefined())
                {
                    jsonObject["rule_id"] = (int)task.getRuleId() ;
                }

            }

        }

        aResponse.sendDataStream(jsonStream, MIME_JSON) ;

    }
    else if (aRequest.method == HTTP_POST)
    {

        const String idString = aRequest.getPostParameter("id") ;

        uint id = 0 ;

        if (idString != "")
        {

            id = idString.toInt() ;

            if (id == 0)
            {

                aResponse.code = HTTP_STATUS_FORBIDDEN ;

                return ;

            }

        }
        else
        {
            id = taskManagerPtr_->getNextTaskId() ;
        }

        const String executionTimeString = aRequest.getPostParameter("execution_time") ;

        if (executionTimeString != "")
        {

            const Time executionTime = Time::CalendarDate(CalendarDate::Parse(executionTimeString)) ;

            if (!executionTime.isDefined())
            {

                aResponse.code = HTTP_STATUS_FORBIDDEN ;

                return ;

            }

            if (!taskManagerPtr_->addTask(Task(id, executionTime)))
            {

                aResponse.code = HTTP_STATUS_FORBIDDEN ;

                return ;

            }

        }
        else
        {

            if (!taskManagerPtr_->addImmediateTask())
            {

                aResponse.code = HTTP_STATUS_FORBIDDEN ;

                return ;

            }

        }

    }
    else if (aRequest.method == HTTP_DELETE)
    {

        const String taskIdString = aRequest.getQueryParameter("id") ;

        if (taskIdString == "")
        {

            aResponse.code = HTTP_STATUS_FORBIDDEN ;

            return ;

        }

        const uint taskId = taskIdString.toInt() ;

        if (taskId == 0)
        {

            aResponse.code = HTTP_STATUS_FORBIDDEN ;

            return ;

        }

        if (!taskManagerPtr_->removeTaskWithId(taskId))
        {

            aResponse.code = HTTP_STATUS_FORBIDDEN ;

            return ;

        }

    }
    else
    {
        aResponse.code = HTTP_STATUS_FORBIDDEN ;
    }

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
