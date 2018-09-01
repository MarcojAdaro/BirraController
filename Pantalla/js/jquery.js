 $(document).ready(function(){
   var refreshId = setInterval(refrescarTablaEstadoSala, 30000);
   $("#boton").on('click',function(){
   		alert("Puto2");
   });

   $.ajaxSetup({ cache: false });
 });


 function refrescarTablaEstadoSala() {

  $("#temperatura").empty();	
  //$("#temperatura").html("puto");

  $.ajax({
      type: 'POST',
      dataType: "text",
      url: 'php/prueba.py',
    })
    .done(function(listas_rep){
	alert(listas_rep)
    	$('#temperatura').html(listas_rep)
    }) 
	.fail(function(){
		alert("fallamos")
});
}
