 $(document).ready(function(){
   var refreshId = setInterval(refrescarTablaEstadoSala, 30000);
   $("#boton").on('click',function(){
   		alert("Puto2");
   });

   $.ajaxSetup({ cache: false });
 });


 function refrescarTablaEstadoSala() {
  alert("Puto");
  $("#temperatura").empty();	
  //$("#temperatura").html("puto");

  $.ajax({
      type: 'POST',
      dataType: "json",
      url: 'php/serial.py',
    })
    .done(function(listas_rep){
    	$('#temperatura').html(listas_rep)
    })
}