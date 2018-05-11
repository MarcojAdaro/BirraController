<?php 
require_once 'conexion.php';

function getInfo(){
	$campos=array('Cocinadas','Ultima','TempMaxF','TempMinF','TempMaxM','TempMinM','Inercia','Litros','Tiempo');
	$tipo="'".$_POST['tipo']."'";
	$conexion= conectar();
	
	$consulta= "SELECT * FROM CervezasTable WHERE Tipo='APA'";//.$tipo;
	if (!($resultado=mysqli_query($conexion, $consulta)))
		echo "Error:". mysqli_error($conexion);
	//if($resultado= msqli_query ($conexion, $consulta))
	$fila= mysqli_fetch_array($resultado, MYSQLI_NUM);
	//echo ($fila[1]);
	$i=2;
	
	$prueba=array();

	foreach ($campos as $campo) {

		$prueba[$campo]=$fila[$i];
		$i++;
		}
	
	
	cerrar($conexion);
	return $prueba;
}

echo  json_encode(getInfo());
//getInfo();