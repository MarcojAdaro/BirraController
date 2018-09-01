 $(document).ready(function(){
   var refreshId = setInterval(refrescarTablaEstadoSala, 30000);
   $("#boton").on('click',function(){
   });

   $.ajaxSetup({ cache: false });
 });


 function refrescarTablaEstadoSala() {

  $("#temperatura").empty();	
  //$("#temperatura").html("puto");

  $.ajax({
      type: 'POST',
      dataType: "text",
      url: 'php/updateTemp.php',
    })
    .done(function(temp){
    	$('#temperatura').html(temp+"ºC")
    })
    .fail(function(){
      alert("Fallamos")


    })

}