<?php 
require_once 'conexion.php';

function getInfo(){
	$campos=array('Cocinadas','Ultima','TempMaxF','TempMinF','TempMaxM','TempMinM','Inercia','Litros','Tiempo');
	$tipo="'".$_POST['tipo']."'";
	$conexion= conectar();
	$i=2;
	$prueba=array();
	
	$consulta= "SELECT * FROM CervezasTable WHERE id=".$tipo;
	if (!($resultado=mysqli_query($conexion, $consulta)))
		echo "Error:". mysqli_error($conexion);

	$fila= mysqli_fetch_array($resultado, MYSQLI_NUM);
	
	foreach ($campos as $campo) {

		$prueba[$campo]=$fila[$i];
		$i++;
		}
	cerrar($conexion);
	return $prueba;
}
echo  json_encode(getInfo());
