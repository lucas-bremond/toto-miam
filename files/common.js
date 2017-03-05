function updateVersion ( )
{

	$.getJSON
	(
		'/status',
		function (data)
		{
			
			console.log(data) ;

			$('span[name="version"]').html(data['version']) ;
			
		}
	) ;

}