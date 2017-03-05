$(document).ready
(
	function ()
	{

		updateVersion() ;
	
		(
			function worker ()
			{
				$.getJSON
				(
					'/tasks',
					function (data)
					{
						
						// console.log(data) ;

						$('table[name="tasks"] tbody').empty() ;

						if (data && data["tasks"])
						{

							$.each
							(
								data["tasks"],
								function (aKey, aTask)
								{

									// console.log(aTask) ;

									let row = '<tr><td>' + aTask['id'] + '</td><td>' + aTask['status'] + '</td><td>' + aTask['execution_time'] + '</td></tr>' ;

									$('table[name="tasks"] tbody').append(row) ;

								}
							) ;

						}
						
						setTimeout(worker, 5000) ;

					}
				) ;
			}
		)() ;
	
	}
) ;