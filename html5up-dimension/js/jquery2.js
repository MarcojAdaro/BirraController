$(document).ready(function(){
alert("prueba");
  $.ajax({
    type: 'POST',
    url: 'php/listas.php'
  })
  .done(function(listas_rep){
    $('#listas').html(listas_rep)
  })
  .fail(function(){
    alert('Hubo un errror al cargar las listas_rep')
  })
})

$('#listas').on('change', function(){

    var id = $('#lista').val()
    var i=0;
    $.ajax({
      type: 'POST',
      dataType: "json",
      url: 'php/cargar_birra.php',
      data: {'id': id}
    })
    .done(function(listas_rep){
      $('#Cocinadas').val(listas_rep.Cocinadas);
      $('#Ultima').val(listas_rep.Ultima);
      $('#TempMaxF').val(listas_rep.TempMaxF);
      $('#TempMinF').val(listas_rep.TempMinF);
      $('#TempMaxM').val(listas_rep.TempMaxM);
      $('#TempMinM').val(listas_rep.TempMinM);
      $('#Inercia').val(listas_rep.Inercia);
      $('#Litros').val(listas_rep.Litros);
      $('#Tiempo').val(listas_rep.Tiempo);

      
    })
    .fail(function(){
      alert('Hubo un errror al cargar los vídeos')
    })
  })
