<?php 
require_once 'conexion.php';

function agregar(){

	$con=conectar();

	$consulta=consulta($con,"id","CervezaTable");
	$tipo="'".$_POST['agregar']."'";
	
	$birras=mysqli_fetch_array($consulta, MYSQLI_NUM);

	if(!($insert=mysqli_query($con,"INSERT INTO CervezaTable(Tipo) VALUES('$tipo')"))){
			echo "Error:". mysqli_error($con);
			exit();
	}

	$query=mysqli_query($con,"SELECT id FROM CervezaTable WHERE Tipo='$tipo'");
	
	$birras=mysqli_fetch_array($query, MYSQLI_NUM);

	
	$last_id=$birras[0];
	

	$listas= "<option value";//='$last_id'>$tipo</option>";

	cerrar($con);
	return $listas;
}

echo json_encode(agregar());
//agregar();