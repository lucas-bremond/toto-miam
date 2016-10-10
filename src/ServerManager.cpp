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

		serverPtr_->setDefaultHandler(HttpPathDelegate(&ServerManager::onStatus, this)) ;

		serverPtr_->addPath("/status", HttpPathDelegate(&ServerManager::onStatus, this)) ;
		serverPtr_->addPath("/current_time", HttpPathDelegate(&ServerManager::onCurrentTime, this)) ;
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

void							ServerManager::onStatus						(			HttpRequest&				aRequest,
																						HttpResponse&				aResponse							)
{

	if (aRequest.getRequestMethod() == RequestMethod::GET)
	{

		JsonObjectStream* 		JSONStream										=		new JsonObjectStream() ;

		JsonObject&				JSONObject										=		JSONStream->getRoot() ;
	
		JSONObject["status"]													=		(bool)true ;

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

// void onIndex(HttpRequest &request, HttpResponse &response)
// {
// 	TemplateFileStream *tmpl = new TemplateFileStream("index.html");
// 	auto &vars = tmpl->variables();
// 	//vars["counter"] = String(counter);
// 	response.sendTemplate(tmpl); // this template object will be deleted automatically
// }

// void onFile(HttpRequest &request, HttpResponse &response)
// {
// 	String file = request.getPath();
// 	if (file[0] == '/')
// 		file = file.substring(1);

// 	if (file[0] == '.')
// 		response.forbidden();
// 	else
// 	{
// 		response.setCache(86400, true); // It's important to use cache for better performance.
// 		response.sendFile(file);
// 	}
// }

// void onAjaxInput(HttpRequest &request, HttpResponse &response)
// {
// 	JsonObjectStream* stream = new JsonObjectStream();
// 	JsonObject& json = stream->getRoot();
// 	json["status"] = (bool)true;

// 	String stringKey = "StringKey";
// 	String stringValue = "StringValue";

// 	json[stringKey] = stringValue;

//     for( int i = 0; i < 11; i++)
//     {
//         char buff[3];
//         itoa(i, buff, 10);
//         String desiredString = "sensor_";
//         desiredString += buff;
//         json[desiredString] = desiredString;
//     }


// 	JsonObject& gpio = json.createNestedObject("gpio");
// 	for (int i = 0; i < countInputs; i++)
// 		gpio[namesInput[i].c_str()] = digitalRead(inputs[i]);

// 	response.sendJsonObject(stream);
// }