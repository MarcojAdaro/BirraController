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
				
		VTemp= ($('textarea:eq(0)').html())+","+($('textarea:eq(1)').html())+","+($('textarea:eq(2)').html())+","+($('textarea:eq(3)').html())+",1";
	
		$.ajax({
      	type: 'POST',
      	dataType: "json",
      	url: 'php/Temp.php',
      	data : {'modo':"Set",'temp':VTemp,'fermentador':res[1]}
    	})
    	.done(function(){
	 		alert("Exito!!: Estamos cocinando")
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