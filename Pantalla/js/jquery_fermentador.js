  url = document.URL;
  var res = url.split("=");
  //alert(res[1]) 555 
  $("h1:eq(0)").append(" "+res[1]) 
 
 $(document).ready(function(){
  var refreshId = setInterval(refrescarTablaEstadoSala, 30000);
  $.ajax({
    type: 'POST',
    dataType: "json",
    url: 'php/Temp.php',
    data : {'modo':"read",'fermentador':res[1]}
  })
  .done(function(modo){
     
    if(modo[4]=='1'){
      refrescarTablaEstadoSala()
      refreshId = setInterval(refrescarTablaEstadoSala, 30000);

    }
    else{
      clearInterval(refreshId);
      $('#temperatura').html("OFF")
    }
    
  }) 
  .fail(function(modo){
    alert("Fallo")
  })  


  Fer_Mad();




  $("#boton").on('click',function(){
   	window.location.href = "SetTemp.html?ferm="+res[1];
  });


  $("#modo").on('click',function(){
	
    var fer_mad =$("#modo").html()

  		$.ajax({
        type: 'POST',
        dataType: "text",
        url: 'php/Temp.php',
        data : {'modo':"Fer_Mad",'fermentador':res[1],'fer_mad': fer_mad}
      })
      .done(function(temp){
        Fer_Mad()
      })
      .fail(function(){
        alert("Fallamos")
      })
	});


 
 });

 function refrescarTablaEstadoSala() {

  $("#temperatura").empty();	

  $.ajax({
      type: 'POST',
      dataType: "text",
      url: 'php/Temp.php',
      data : {'modo':"Update",'fermentador':res[1]}
    })
    .done(function(temp){
    	$('#temperatura').html(temp+"ºC")
    })
    .fail(function(){
      alert("Fallamos")
    })

  }

function Fer_Mad(){


  $.ajax({
        type: 'POST',
        dataType: "text",
        url: 'php/Temp.php',
        data : {'modo':"Read_Status",'fermentador':res[1]}
      })
      .done(function(FerMad){
        $("h1").eq(0).html(FerMad+" "+res[1]);
         if (FerMad=="Fermentando") {
            $("#modo").html("Madurar")
        }else {
            $("#modo").html("Fermentar")      
        }
      })
      .fail(function(){
        alert("Fallamos")
      })

}