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
	
		$query=mysqli_query($con,"SELECT id FROM CervezaTable WHERE Tipo=$tipo");
	
		$birras=mysqli_fetch_array($query, MYSQLI_NUM);

	}
	
	$last_id['birra']=$birras[0];
	
	return $last_id;

}

echo json_encode(agregar());
//agregar();