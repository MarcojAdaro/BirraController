<?php 
require_once 'conexion.php';

function getInfo(){
	$campos=array('Cocinadas','Ultima','TempMaxF','TempMinF','TempMaxM','TempMinM','Inercia','Litros','Tiempo');
	$tipo="'".$_POST['tipo']."'";
	$prueba=array();
	$i=2;
	
	//$prueba['Cocinadas']="$tipo";
	$conexion= conectar();
	
	$resultado=consulta($conexion,"","CervezaTable","id",$tipo);
	//if($resultado= msqli_query ($conexion, $consulta))
	$fila= mysqli_fetch_array($resultado, MYSQLI_NUM);
	//echo ($fila[1]);

	foreach ($campos as $campo) {

		$prueba[$campo]=$fila[$i];
		$i++;
		}
	
	
	cerrar($conexion);
	return $prueba;
}


echo  json_encode(getInfo());
//getInfo();