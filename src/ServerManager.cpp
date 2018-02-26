////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///
///	This file is part of the TotoMiam library.
///
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

///	@file 						TotoMiam/ServerManager.cpp
///	@author 					Lucas Bremond <lucas@axelspace.com>
///	@date 						9 Oct 2016

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <TotoMiam/ServerManager.hpp>
#include <TotoMiam/Version.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace TotoMiam
{

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

typedef Delegate<void(HttpRequest&, HttpResponse&)> HttpPathDelegate ;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

								ServerManager::ServerManager				( )
								:	port_(80),
									serverPtr_(nullptr),
									taskManagerPtr_(nullptr)
{

}

bool							ServerManager::isActive						( ) const
{
	return (serverPtr_ != nullptr) ;
}

void							ServerManager::start						( )
{

	if (this->isActive())
	{
		this->stop() ;
	}

	serverPtr_																	=		new HttpServer() ;

	if (serverPtr_ != nullptr)
	{

		serverPtr_->listen(port_) ;

		serverPtr_->setDefaultHandler(HttpPathDelegate(&ServerManager::onFile, this)) ;

		serverPtr_->addPath("/", HttpPathDelegate(&ServerManager::onIndex, this)) ;
		serverPtr_->addPath("/status", HttpPathDelegate(&ServerManager::onStatus, this)) ;
		serverPtr_->addPath("/time", HttpPathDelegate(&ServerManager::onTime, this)) ;
		serverPtr_->addPath("/rules", HttpPathDelegate(&ServerManager::onRules, this)) ;
		serverPtr_->addPath("/tasks", HttpPathDelegate(&ServerManager::onTasks, this)) ;

	}

}

void							ServerManager::stop							( )
{

	if (!this->isActive())
	{
		return ;
	}

	delete serverPtr_ ;

	serverPtr_																	=		nullptr ;

}

void							ServerManager::associateTaskManager			(			TaskManager&				aTaskManager						)
{
	taskManagerPtr_																=		&aTaskManager ;
}

void							ServerManager::onIndex						(			HttpRequest&				aRequest,
																						HttpResponse&				aResponse							)
{

	aResponse.setCache(86400, true) ;

	aResponse.sendFile("index.html") ;

}

void							ServerManager::onFile						(			HttpRequest&				aRequest,
																						HttpResponse&				aResponse							)
{
	
	String						file											=		aRequest.getPath() ;

	if (file[0] == '/')
	{
		file 																	=		file.substring(1) ;
	}

	if (file[0] == '.')
	{
		aResponse.forbidden() ;
	}
	else
	{
	
		aResponse.setCache(86400, true) ;
		aResponse.sendFile(file) ;
	
	}

}

void							ServerManager::onStatus						(			HttpRequest&				aRequest,
																						HttpResponse&				aResponse							)
{

	if (aRequest.method == HTTP_GET)
	{

		JsonObjectStream* 		JSONStream										=		new JsonObjectStream() ;

		JsonObject&				JSONObject										=		JSONStream->getRoot() ;
	
		JSONObject["status"]													=		(bool)true ;
		JSONObject["version"]													=		(String)Version::Current().getString() ;

		aResponse.sendJsonObject(JSONStream) ;

	}
	else
	{
		aResponse.code = HTTP_STATUS_FORBIDDEN ;
	}

}

void							ServerManager::onTime				(			HttpRequest&				aRequest,
																						HttpResponse&				aResponse							)
{

	if (aRequest.method == HTTP_GET)
	{

		JsonObjectStream* 		JSONStream										=		new JsonObjectStream() ;

		JsonObject&				JSONObject										=		JSONStream->getRoot() ;
	
		JSONObject["time"]														=		(String)Time::Now().getString() ;

		aResponse.sendJsonObject(JSONStream) ;

	}
	else
	{
		aResponse.code = HTTP_STATUS_FORBIDDEN ;
	}

}

void							ServerManager::onRules						(			HttpRequest&				aRequest,
																						HttpResponse&				aResponse							)
{

	if (!taskManagerPtr_)
	{
		return aResponse.notFound() ;
	}

	if (aRequest.method == HTTP_GET)
	{

		JsonObjectStream* 		JSONStream										=		new JsonObjectStream() ;

		JsonObject&				JSONObject										=		JSONStream->getRoot() ;

		String					idString										=		aRequest.getQueryParameter("id") ;
		
		if (idString == "")
		{

			JsonArray&			ruleArray										=		JSONObject.createNestedArray("rules") ;

			for (uint idx = 0; idx < taskManagerPtr_->accessRules().size(); ++idx)
			{

				const Rule&		rule 											=		taskManagerPtr_->accessRules().elementAt(idx) ;

				JsonObject&		ruleObject										=		ruleArray.createNestedObject() ;

				ruleObject["id"]												=		(int)rule.getId() ;
				ruleObject["type"]												=		(String)Rule::StringFromType(rule.getType()) ;

				switch (rule.getType())
				{

					case Rule::Type::Time:
						ruleObject["time"]										=		(String)rule.getTime().getString(CalendarDate::Format::Time) ;
						break ;

					case Rule::Type::Interval:
						ruleObject["interval"]									=		(String)rule.getInterval().getString() ;
						break ;

					default:
						// Do nothing...
						break ;

				}

				if (rule.getPreviousExecutionTime().isDefined())
				{
					ruleObject["previous_execution_time"]						=		(String)CalendarDate::Time(rule.getPreviousExecutionTime()).getString(CalendarDate::Format::DateTime) ;
				}

			}
			
		}
		else
		{

			uint				id 												=		idString.toInt() ;

			if (id == 0)
			{
				
				aResponse.code = HTTP_STATUS_FORBIDDEN ;
				
				return ;

			}

			if (taskManagerPtr_->hasRuleWithId(id))
			{

				const Rule&		rule 											=		taskManagerPtr_->accessRuleWithId(id) ;

				JSONObject["id"]												=		(int)rule.getId() ;
				JSONObject["type"]												=		(String)Rule::StringFromType(rule.getType()) ;

				switch (rule.getType())
				{

					case Rule::Type::Time:
						JSONObject["time"]										=		(String)rule.getTime().getString(CalendarDate::Format::Time) ;
						break ;

					case Rule::Type::Interval:
						JSONObject["interval"]									=		(String)rule.getInterval().getString() ;
						break ;

					default:
						// Do nothing...
						break ;

				}

				if (rule.getPreviousExecutionTime().isDefined())
				{
					JSONObject["previous_execution_time"]						=		(String)CalendarDate::Time(rule.getPreviousExecutionTime()).getString(CalendarDate::Format::DateTime) ;
				}

			}

		}

		aResponse.sendJsonObject(JSONStream) ;

	}
	else if (aRequest.method == HTTP_POST)
	{

		String					idString										=		aRequest.getPostParameter("id") ;

		uint					id 												=		0 ;

		if (idString != "")
		{

			id 																	=		idString.toInt() ;
			
			if (id == 0)
			{
				
				aResponse.code = HTTP_STATUS_FORBIDDEN ;
				
				return ;

			}

		}
		else
		{
			id 																	=		taskManagerPtr_->getNextRuleId() ;
		}

		String					ruleTypeString									=		aRequest.getPostParameter("type") ;

		if (ruleTypeString != "")
		{

			Rule::Type			ruleType 										=		Rule::TypeFromString(ruleTypeString) ;

			switch (ruleType)
			{

				case Rule::Type::Time:
				{

					String		calendarDateString								=		aRequest.getPostParameter("time") ;

					Serial.println(calendarDateString) ;

					if (calendarDateString == "")
					{
						
						aResponse.code = HTTP_STATUS_FORBIDDEN ;
						
						return ;

					}

					CalendarDate calendarDate 									=		CalendarDate::Parse(calendarDateString) ;

					Serial.println(calendarDate.getString()) ;

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
				// 	break ;
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

		String					ruleIdString									=		aRequest.getQueryParameter("id") ;

		if (ruleIdString == "")
		{
			
			aResponse.code = HTTP_STATUS_FORBIDDEN ;
			
			return ;

		}

		uint					ruleId											=		ruleIdString.toInt() ;

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

void							ServerManager::onTasks						(			HttpRequest&				aRequest,
																						HttpResponse&				aResponse							)
{

	if (!taskManagerPtr_)
	{
		return aResponse.notFound() ;
	}

	if (aRequest.method == HTTP_GET)
	{

		JsonObjectStream* 		JSONStream										=		new JsonObjectStream() ;

		JsonObject&				JSONObject										=		JSONStream->getRoot() ;

		String					idString										=		aRequest.getQueryParameter("id") ;
		
		if (idString == "")
		{

			JsonArray&			taskArray										=		JSONObject.createNestedArray("tasks") ;

			for (uint idx = 0; idx < taskManagerPtr_->accessTasks().size(); ++idx)
			{

				const Task&		task 											=		taskManagerPtr_->accessTasks().elementAt(idx) ;

				JsonObject&		taskObject										=		taskArray.createNestedObject() ;

				taskObject["id"]												=		(int)task.getId() ;
				taskObject["status"]											=		(String)Task::getStringOfStatus(task.getStatus()) ;
				taskObject["execution_time"]									=		(String)task.getExecutionTime().getString() ;

				if (task.isRuleDefined())
				{
					taskObject["rule_id"]										=		(int)task.getRuleId() ;
				}

			}
			
		}
		else
		{

			uint				id 												=		idString.toInt() ;

			if (id == 0)
			{
				
				aResponse.code = HTTP_STATUS_FORBIDDEN ;
				
				return ;

			}

			if (taskManagerPtr_->hasTaskWithId(id))
			{

				const Task&		task 											=		taskManagerPtr_->accessTaskWithId(id) ;

				JSONObject["id"]												=		(int)task.getId() ;
				JSONObject["status"]											=		(String)Task::getStringOfStatus(task.getStatus()) ;
				JSONObject["execution_time"]									=		(String)task.getExecutionTime().getString() ;

				if (task.isRuleDefined())
				{
					JSONObject["rule_id"]										=		(int)task.getRuleId() ;
				}

			}

		}

		aResponse.sendJsonObject(JSONStream) ;

	}
	else if (aRequest.method == HTTP_POST)
	{

		String					idString										=		aRequest.getPostParameter("id") ;

		uint					id 												=		0 ;

		if (idString != "")
		{

			id 																	=		idString.toInt() ;
			
			if (id == 0)
			{
				
				aResponse.code = HTTP_STATUS_FORBIDDEN ;
				
				return ;

			}

		}
		else
		{
			id 																	=		taskManagerPtr_->getNextTaskId() ;
		}

		String					executionTimeString								=		aRequest.getPostParameter("execution_time") ;

		if (executionTimeString != "")
		{

			Time 				executionTime 									=		Time::CalendarDate(CalendarDate::Parse(executionTimeString)) ;

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

		String					taskIdString									=		aRequest.getQueryParameter("id") ;
		
		if (taskIdString == "")
		{
			
			aResponse.code = HTTP_STATUS_FORBIDDEN ;
			
			return ;

		}

		uint					taskId											=		taskIdString.toInt() ;

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

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////