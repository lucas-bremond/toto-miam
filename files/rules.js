$(document).ready
(
	function ( )
	{

		function updateRules ( )
		{

			$.getJSON
			(
				'/rules',
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

								if (!aRule['type'])
								{
									return ;
								}

								let	row											=		'' ;

								switch (aRule['type'])
								{

									case 'Time':
									{

										row										=		'<tr data-id="' + aRule['id'] + '">'
																				+			'<td>' + aRule['id'] + '</td>'
																				+			'<td>' + aRule['type'] + '</td>'
																				+			'<td>' + aRule['time'] + '</td>'
																				+			'<td>' + (aRule['previous_execution_time'] ? aRule['previous_execution_time'] : '---') + '</td>'
																				+			'<td><button action="delete-rule" type="button" class="btn btn-default"><span class="glyphicon glyphicon-minus"></span></button></td>'
																				+		'</tr>' ;
										break ;

									}

									case 'Interval':
									{

										row										=		'<tr data-id="' + aRule['id'] + '">'
																				+			'<td>' + aRule['id'] + '</td>'
																				+			'<td>' + aRule['type'] + '</td>'
																				+			'<td>' + aRule['interval'] + '</td>'
																				+			'<td>' + (aRule['previous_execution_time'] ? aRule['previous_execution_time'] : '---') + '</td>'
																				+			'<td><button action="delete-rule" type="button" class="btn btn-default"><span class="glyphicon glyphicon-minus"></span></button></td>'
																				+		'</tr>' ;
										break ;

									}

									default:
										break ;

								}

								$('table[name="rules"] tbody').append(row) ;

							}
						) ;

						refresh() ;

					}
					
				}
			) ;

		} ;

		function refresh ( )
		{

			$('button[action="delete-rule"]').click
			(
				function (event)
				{

					let			ruleId											=		$(event.target).closest('tr').data('id') ;

					if (!ruleId)
					{
						return ;
					}

					$.ajax
					(
						{
							url													:		'/rules?id=' + ruleId,
							type												:		'DELETE',
							success												:		function (aResult)
							{
								updateRules() ;
							},
							error												:		function (aResult)
							{

							}
						}
					) ;

				}
			) ;

		} ;

		$('button[action="add-rule"]').click
		(
			function ( )
			{
				
				$('button[action="add-rule"]').prop('disabled', true) ;

				$('button[action="add-rule"]').removeClass('btn-info') ;
				$('button[action="add-rule"]').removeClass('btn-success') ;
				$('button[action="add-rule"]').removeClass('btn-danger') ;
				$('button[action="add-rule"]').addClass('btn-warning') ;

				let 			timeString										=		$('input[name="time"]').val() ;

				if (!timeString)
				{
					return ;
				}

				if (timeString.length != 8)
				{
					return ;
				}

				$.post
				(
					'/rules',
					{
						'type'													:		'Time',
						'time'													:		'2017-01-01 ' + timeString + ' [UTC]'
					},
					function (data)
					{
						
					}
				)
				.done
				(
					function ( )
					{
						$('button[action="add-rule"]').removeClass('btn-warning') ;
						$('button[action="add-rule"]').addClass('btn-success') ;
					}
				)
				.fail
				(
					function ( )
					{
						$('button[action="add-rule"]').removeClass('btn-warning') ;
						$('button[action="add-rule"]').addClass('btn-danger') ;
					}
				)
				.always
				(
					function ( )
					{
						updateRules() ;
						$('button[action="add-rule"]').prop('disabled', false) ;
					}
				) ;

			}
		) ;

		updateVersion() ;
		updateRules() ;
	
		window.setInterval(updateRules, 5000) ;
	
	}
) ;