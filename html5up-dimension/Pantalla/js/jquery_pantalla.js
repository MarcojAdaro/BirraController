 $(document).ready(function(){

  url = document.URL;
  var res = url.split("=");
  //alert(res[1])
  $("h3").append(" "+res[1])

   var refreshId = setInterval(refrescarTablaEstadoSala, 30000);
   $("#boton").on('click',function(){
   		window.location.href = "SetTemp.html?ferm="+res[1];
   });

 });


 function refrescarTablaEstadoSala() {

  $("#temperatura").empty();	

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