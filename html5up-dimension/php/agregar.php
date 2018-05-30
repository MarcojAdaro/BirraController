<?php 
require_once 'conexion.php';

function agregar(){

	$con=conectar();

	$consulta=consulta($con,"id","CervezaTable");
	
	
	$birras=mysqli_fetch_array($consulta, MYSQLI_NUM);

	if($_POST['add']!="")
	{	
		$tipo="'".$_POST['add']."'";
		if(!($insert=mysqli_query($con,"INSERT INTO CervezaTable(Tipo) VALUES($tipo)"))){
				echo "Error:". mysqli_error($con);
				exit();
		}
	}
	cerrar($con);
	return "Se agrego con Exito";// NO sirve pero tiene qe estar
}

echo json_encode(agregar());
//agregar();