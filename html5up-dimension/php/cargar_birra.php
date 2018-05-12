<?php 
require_once 'conexion.php';

function getInfo(){
	$campos=array('Cocinadas','Ultima','TempMaxF','TempMinF','TempMaxM','TempMinM','Inercia','Litros','Tiempo');
	$tipo="'".$_POST['tipo']."'";
	$prueba=array();
	$i=2;
	
	//$prueba['Cocinadas']="$tipo";
	$conexion= conectar();
	
	$consulta= "SELECT * FROM CervezaTable WHERE id=".$tipo;
	if (!($resultado=mysqli_query($conexion, $consulta)))
		echo "Error:". mysqli_error($conexion);
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