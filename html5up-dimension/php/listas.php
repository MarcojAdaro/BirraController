<?php 
require_once 'conexion.php';

function getBirra(){

	$con=conectar();
	
	$consulta=consulta($con,"Tipo","CervezaTable");
	$listas = '<option value="0">Elige una opción</option>';
	$birras=mysqli_fetch_array($consulta, MYSQLI_NUM);
	$i=1;
	$j=0;
	do{
		$listas .= "<option value='$i'>$birras[$j]</option>";
		$i++;
		$birras=mysqli_fetch_array($consulta, MYSQLI_NUM);
	}while($birras[$j]!="");
	
	cerrar($conexion);
	return $listas;
}

echo getBirra();
//getBirra();