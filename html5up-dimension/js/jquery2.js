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

    var tipo = $('#listas option:selected').text();
    $.ajax({
      type: 'POST',
      dataType: "json",
      url: 'php/cargar_birra.php',
      data: {'tipo': tipo}
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
      alert('Hubo un errror al cargar la base de datos')
    })
  })

$('#Editar').on('click',function(){
    $('#Cocinadas').removeAttr("readonly");
    $('#Ultima').removeAttr("readonly");
    $('#TempMaxF').removeAttr("readonly");;
    $('#TempMinF').removeAttr("readonly");
    $('#TempMaxM').removeAttr("readonly");
    $('#TempMinM').removeAttr("readonly");
    $('#Inercia').removeAttr("readonly");
    $('#Litros').removeAttr("readonly");
    $('#Tiempo').removeAttr("readonly");
    $('#Confirmar').prop('disabled', false);
})

$('#Confirmar').on('click',function(){
    $('#Cocinadas').attr("readonly","readonly");
    $('#Ultima').attr("readonly","readonly");
    $('#TempMaxF').attr("readonly","readonly");
    $('#TempMinF').attr("readonly","readonly");
    $('#TempMaxM').attr("readonly","readonly");
    $('#TempMinM').attr("readonly","readonly");
    $('#Inercia').attr("readonly","readonly");
    $('#Litros').attr("readonly","readonly");
    $('#Tiempo').attr("readonly","readonly");
    $('#Confirmar').prop('disabled', true);

    var Cocinadas= $('#Cocinadas').val();
    var Ultima = $('#Ultima').val();
    var TempMaxF = $('#TempMaxF').val();
    var TempMinF = $('#TempMinF').val();
    var TempMaxM = $('#TempMaxM').val();
    var TempMinM = $('#TempMinM').val();
    var Inercia = $('#Inercia').val();
    var Litros = $('#Litros').val();
    var Tiempo = $('#Tiempo').val();
    var tipo = $('#listas option:selected').text();

    $.ajax({
      type: 'POST',
      dataType: "json",
      url: 'php/update.php',
      data: {'tipo':tipo,'Cocinadas':Cocinadas,'Ultima':Ultima,'TempMaxF':TempMaxF,'TempMinF':TempMinF,'TempMaxM':TempMaxM, 'TempMinM':TempMinM, 'Inercia':Inercia, 'Litros':Litros, 'Tiempo':Tiempo }
    })
    .done(function(){
      alert("Se editaron correctamente los datos");
    })

    .fail(function(){
      alert('Error al Editar: Vuelva a intentarlo con valores diferentes')
    })
})

$('#Agregar').on('click',function(){
	var add=prompt("Ingrese la Cerveza ");

	$.ajax({
    type: 'POST',
    dataType: "json",
    url: 'php/agregar.php',
    data: {'add': add}
  })
  .done(function(){
    location.reload();
  })
  .fail(function(){
    alert('Hubo un errror al cargar las listas_rep')
  })

})
