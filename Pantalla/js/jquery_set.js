 $(document).ready(function(){	
	
	url = document.URL;
  	var res = url.split("=");

  	$("h2").append(" "+res[1])

	$(".Suma").on('click',function(){
		
		var tempMax= $(this).parent().next().children().html();
		$(this).parent().next().children().empty();
		
		if(parseInt(tempMax)>8)
			$(this).parent().next().children().html(parseInt(tempMax)+1);
		else 
			$(this).parent().next().children().html("0"+(parseInt(tempMax)+1));
	});

	$(".Resta").on('click',function(){
		
		var tempMin= $(this).parent().prev().children().html();
		
		if(parseInt(tempMin)>10)
			$(this).parent().prev().children().html(parseInt(tempMin)-1);	
		else
			$(this).parent().prev().children().html("0"+(parseInt(tempMin)-1));	
	});
	
	$("#cocinar").on('click',function () {
				
		VTemp= ($('textarea:eq(0)').html())+","+($('textarea:eq(1)').html())+","+($('textarea:eq(2)').html())+","+($('textarea:eq(3)').html());
	
		$.ajax({
      	type: 'POST',
      	dataType: "json",
      	url: 'php/Temp.php',
      	data : {'modo':"Set",'temp':VTemp,'fermentador':res[1]}
    	})
    	.done(function(){
	 		alert("Exito!!: Estamos cocinando")
    	}) 
		.fail(function(){
			alert("Fallo la coccion")
		})
	
	})


});