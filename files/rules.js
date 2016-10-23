$(document).ready
(
	function ()
	{
	
		(
			function worker ()
			{
				$.getJSON
				(
					'/rule',
					function (data)
					{
						
						// console.log(data) ;

						$('table[name="rules"] tbody').empty() ;

						if (data && data["rules"])
						{

							$.each
							(
								data["rules"],
								function (aKey, aRule)
								{

									// console.log(aRule) ;

									let row = '<tr><td>' + aRule['id'] + '</td><td>' + aRule['type'] + '</td><td>' + aRule['previous_execution_time'] + '</td></tr>' ;

									$('table[name="rules"] tbody').append(row) ;

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