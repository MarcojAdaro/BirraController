 $(document).ready(function(){	
	
	url = document.URL;
  	var res = url.split("=");
	
	$("h2:eq(1)").html(" "+res[1])	
 
	
	
	$.ajax({
      	type: 'POST',
      	dataType: "json",
      	url: 'php/Temp.php',
      	data : {'modo':"read",'fermentador':res[1]}
    	})
    	.done(function(modo){
    		for (var i=0;i<4;i++) {
    			$('textarea:eq('+i+')').html(modo[i])
    		}
    		
	 		if(modo[4]=='1'){
	 			$("#cocinar").prop('disabled', true); 			
	 			}
	 		else $("#cocinar").prop('disabled', false);
    	}) 
		.fail(function(modo){
			alert("Fallo")
		})	
		 


	$(".Suma").on('click',function(){
		var id = $(this).parent().next().children().attr("id");
		var tactual= $(this).parent().next().children().html();
		var sumar=1 ,tmax;
	
		if(id.substr(0,3) == "Min"){// Sabiendo el id de la temperatura que vamos a cambiar
			var tmax = $("#Max"+id.substr(3)).html() // Extramos la temperatura correspondiente al mismo modo, asi obtenemos// Siempre la temperatura min y max ya sea de maduracion como fermentacion	
			var tmin = tactual
			if(++tmin >= tmax)
				sumar=0								
		}


		//$(this).parent().next().children().empty();
		if(sumar)
			if(parseInt(tactual)>8)
				$(this).parent().next().children().html(parseInt(tactual)+1);
			else 
				$(this).parent().next().children().html("0"+(parseInt(tactual)+1));
	});

	$(".Resta").on('click',function(){
		var id = $(this).parent().prev().children().attr("id");
		var tactual= $(this).parent().prev().children().html();
		var sumar=1;

		if(id.substr(0,3) == "Max"){// Sabiendo el id de la temperatura que vamos a cambiar
			var tmin = $("#Min"+id.substr(3)).html() // Extramos la temperatura correspondiente al mismo modo, asi obtenemos// Siempre la temperatura min y max ya sea de maduracion como fermentacion	
			var tmax = tactual
			if(tmin >= --tmax)
				sumar=0								
		}

		if(sumar)
			if(parseInt(tactual)>10)
				$(this).parent().prev().children().html(parseInt(tactual)-1);	
			else
				$(this).parent().prev().children().html("0"+(parseInt(tactual)-1));	
	});
	
	$("#cocinar").on('click',function () {
				
		VTemp= ($('textarea:eq(0)').html())+","+($('textarea:eq(1)').html())+","+($('textarea:eq(2)').html())+","+($('textarea:eq(3)').html())+",1";
	
		$.ajax({
      	type: 'POST',
      	dataType: "json",
      	url: 'php/Temp.php',
      	data : {'modo':"Set",'temp':VTemp,'fermentador':res[1]}
    	})
    	.done(function(){
	 		$("#cocinar").prop('disabled', false);
	 		window.history.back();
    	}) 
		.fail(function(){
			alert("Fallo la coccion")
		})
})
	$("#Cancelar").on('click',function () {
		
			$.ajax({
      	type: 'POST',
      	dataType: "json",
      	url: 'php/Temp.php',
      	data : {'modo':"Cancelar",'fermentador':res[1]}
    	})
    	.done(function(){
	 		alert("Cancelado")
	 		$("#cocinar").prop('disabled', false);
    	}) 
		.fail(function(){
			alert("Fallo")
		})		
		
		
		})

});