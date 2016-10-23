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

	Serial.println("Starting Server Manager...") ;

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
		serverPtr_->addPath("/current_time", HttpPathDelegate(&ServerManager::onCurrentTime, this)) ;
		serverPtr_->addPath("/rule", HttpPathDelegate(&ServerManager::onRule, this)) ;
		serverPtr_->addPath("/task", HttpPathDelegate(&ServerManager::onTask, this)) ;

		Serial.println(WifiStation.getIP()) ;

	}

	Serial.println("Starting Server Manager [OK]") ;

}

void							ServerManager::stop							( )
{

	Serial.println("Stopping Server Manager...") ;

	if (!this->isActive())
	{
		return ;
	}

	delete serverPtr_ ;

	serverPtr_																	=		nullptr ;

	Serial.println("Stopping Server Manager [OK]") ;

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

	if (aRequest.getRequestMethod() == RequestMethod::GET)
	{

		JsonObjectStream* 		JSONStream										=		new JsonObjectStream() ;

		JsonObject&				JSONObject										=		JSONStream->getRoot() ;
	
		JSONObject["status"]													=		(bool)true ;
		JSONObject["version"]													=		(String)Version::Current().getString() ;

		aResponse.sendJsonObject(JSONStream) ;

	} else {

		aResponse.badRequest() ;

	}

}

void							ServerManager::onCurrentTime				(			HttpRequest&				aRequest,
																						HttpResponse&				aResponse							)
{

	if (aRequest.getRequestMethod() == RequestMethod::GET)
	{

		JsonObjectStream* 		JSONStream										=		new JsonObjectStream() ;

		JsonObject&				JSONObject										=		JSONStream->getRoot() ;
	
		JSONObject["time"]														=		(String)Time::Now().getString() ;

		aResponse.sendJsonObject(JSONStream) ;

	} else {

		aResponse.badRequest() ;

	}

}

void							ServerManager::onRule						(			HttpRequest&				aRequest,
																						HttpResponse&				aResponse							)
{

	if (!taskManagerPtr_)
	{
		return aResponse.notFound() ;
	}

	if (aRequest.getRequestMethod() == RequestMethod::GET)
	{

		JsonObjectStream* 		JSONStream										=		new JsonObjectStream() ;

		JsonObject&				JSONObject										=		JSONStream->getRoot() ;

		String					idString										=		aRequest.getQueryParameter("id", "") ;
		
		if (idString == "")
		{

			JsonArray&			ruleArray										=		JSONObject.createNestedArray("rules") ;

			for (uint idx = 0; idx < taskManagerPtr_->accessRules().size(); ++idx)
			{

				const Rule&		rule 											=		taskManagerPtr_->accessRules().elementAt(idx) ;

				JsonObject&		ruleObject										=		ruleArray.createNestedObject() ;

				ruleObject["id"]												=		(int)rule.getId() ;
				ruleObject["type"]												=		(String)Rule::getStringOfType(rule.getType()) ;

				switch (rule.getType())
				{

					case Rule::Type::Time:
						ruleObject["time"]										=		(String)rule.getTime().getString() ;
						break ;

					case Rule::Type::Interval:
						ruleObject["interval"]									=		(String)rule.getInterval().getString() ;
						break ;

					default:
						// Do nothing...
						break ;

				}

				ruleObject["previous_execution_time"]							=		(String)rule.getPreviousExecutionTime().getString() ;

			}
			
		} else {

			uint				id 												=		idString.toInt() ;

			if (id == 0)
			{
				return aResponse.badRequest() ;
			}

			if (taskManagerPtr_->hasRuleWithId(id))
			{

				const Rule&		rule 											=		taskManagerPtr_->accessRuleWithId(id) ;

				JSONObject["id"]												=		(int)rule.getId() ;
				JSONObject["type"]												=		(String)Rule::getStringOfType(rule.getType()) ;

				switch (rule.getType())
				{

					case Rule::Type::Time:
						JSONObject["time"]										=		(String)rule.getTime().getString() ;
						break ;

					case Rule::Type::Interval:
						JSONObject["interval"]									=		(String)rule.getInterval().getString() ;
						break ;

					default:
						// Do nothing...
						break ;

				}

				JSONObject["previous_execution_time"]							=		(String)rule.getPreviousExecutionTime().getString() ;

			}

		}

		aResponse.sendJsonObject(JSONStream) ;

	} else if (aRequest.getRequestMethod() == RequestMethod::POST) {

		String					idString										=		aRequest.getPostParameter("id", "") ;

		uint					id 												=		0 ;

		if (idString != "")
		{

			id 																	=		idString.toInt() ;
			
			if (id == 0)
			{
				return aResponse.badRequest() ;
			}

		} else {

			id 																	=		taskManagerPtr_->getNextRuleId() ;

		}

		// TBI

		// String					executionTimeString								=		aRequest.getPostParameter("execution_time", "") ;

		// if (executionTimeString != "")
		// {

		// 	Time 				executionTime 									=		Time::Parse(executionTimeString) ;

		// 	if (!executionTime.isDefined())
		// 	{
		// 		return aResponse.badRequest() ;
		// 	}

		// 	if (!taskManagerPtr_->addRule(Rule(id, executionTime)))
		// 	{
		// 		return aResponse.badRequest() ;
		// 	}
			
		// } else {

		// 	if (!taskManagerPtr_->addImmediateRule())
		// 	{
		// 		return aResponse.badRequest() ;
		// 	}

		// }

	} else if (aRequest.getRequestMethod() == RequestMethod::DELETE) {

		String					idString										=		aRequest.getQueryParameter("id", "") ;
		
		if (idString == "")
		{
			return aResponse.badRequest() ;
		}

		uint					id 												=		idString.toInt() ;

		if (id == 0)
		{
			return aResponse.badRequest() ;
		}

		if (!taskManagerPtr_->removeRuleWithId(id))
		{
			return aResponse.badRequest() ;
		}

	} else {

		aResponse.badRequest() ;

	}

}

void							ServerManager::onTask						(			HttpRequest&				aRequest,
																						HttpResponse&				aResponse							)
{

	if (!taskManagerPtr_)
	{
		return aResponse.notFound() ;
	}

	if (aRequest.getRequestMethod() == RequestMethod::GET)
	{

		JsonObjectStream* 		JSONStream										=		new JsonObjectStream() ;

		JsonObject&				JSONObject										=		JSONStream->getRoot() ;

		String					idString										=		aRequest.getQueryParameter("id", "") ;
		
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
			
		} else {

			uint				id 												=		idString.toInt() ;

			if (id == 0)
			{
				return aResponse.badRequest() ;
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

	} else if (aRequest.getRequestMethod() == RequestMethod::POST) {

		String					idString										=		aRequest.getPostParameter("id", "") ;

		uint					id 												=		0 ;

		if (idString != "")
		{

			id 																	=		idString.toInt() ;
			
			if (id == 0)
			{
				return aResponse.badRequest() ;
			}

		} else {

			id 																	=		taskManagerPtr_->getNextTaskId() ;

		}

		String					executionTimeString								=		aRequest.getPostParameter("execution_time", "") ;

		if (executionTimeString != "")
		{

			Time 				executionTime 									=		Time::Parse(executionTimeString) ;

			if (!executionTime.isDefined())
			{
				return aResponse.badRequest() ;
			}

			if (!taskManagerPtr_->addTask(Task(id, executionTime)))
			{
				return aResponse.badRequest() ;
			}
			
		} else {

			if (!taskManagerPtr_->addImmediateTask())
			{
				return aResponse.badRequest() ;
			}

		}

	} else if (aRequest.getRequestMethod() == RequestMethod::DELETE) {

		String					idString										=		aRequest.getQueryParameter("id", "") ;
		
		if (idString == "")
		{
			return aResponse.badRequest() ;
		}

		uint					id 												=		idString.toInt() ;

		if (id == 0)
		{
			return aResponse.badRequest() ;
		}

		if (!taskManagerPtr_->removeTaskWithId(id))
		{
			return aResponse.badRequest() ;
		}

	} else {

		aResponse.badRequest() ;

	}

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////