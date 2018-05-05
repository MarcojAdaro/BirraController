$(document).ready(function(){

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
    $.ajax({
      type: 'POST',
      url: 'php/cargar_birra.php',
      data: {'id': id}
    })
    .done(function(listas_rep){
      $('#Cocinadas').val(listas_rep)
    })
    .fail(function(){
      alert('Hubo un errror al cargar los vídeos')
    })
  })