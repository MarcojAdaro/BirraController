<?php 
require_once 'conexion.php';

function eliminar(){

	$con=conectar();

	$tipo="'".$_POST['del']."'";
	if(!($insert=mysqli_query($con,"DELETE FROM CervezaTable WHERE Tipo=$tipo"))){
			echo "Error:". mysqli_error($con);
			exit();
	}
	cerrar($con);
	return "Se elimino con Exito";// NO sirve pero tiene qe estar
}

echo json_encode(eliminar());