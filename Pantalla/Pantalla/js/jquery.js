 $(document).ready(function(){
    alert(params['ferm'])
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
<<<<<<< HEAD
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
=======
      url: 'php/updateTemp.php',
    })
    .done(function(temp){
    	$('#temperatura').html(temp+"ºC")
    })
    .fail(function(){
      alert("Fallamos")


    })

}
>>>>>>> a1935f068a33534f90335cc9cea8c9e97a322d4f
