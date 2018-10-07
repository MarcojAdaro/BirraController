 $(document).ready(function(){

    url = document.URL;
    url = String(url.match(/\?+.+/));
    url = url.replace("?", "");

    alert(url)
   var refreshId = setInterval(refrescarTablaEstadoSala, 30000);
   $("#boton").on('click',function(){
   });

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
      u
	
	/*
      rl: 'php/updateTemp.php',
    })
    .done(function(temp){
    	$('#temperatura').html(temp+"ºC")
    })
    .fail(function(){
      alert("Fallamos")


    })*/

}

