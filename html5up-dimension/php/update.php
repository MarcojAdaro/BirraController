<?php 
require_once 'conexion.php';

function update(){
	
	$campos=array("Cant_Cocinadas","Ultima_vez","TempFmax","TempFmin","TempMmax","TempMmin","Inercia","Litros","Tiempo_Estimado");

	$values=array('Cocinadas','Ultima','TempMaxF','TempMinF','TempMaxM','TempMinM','Inercia','Litros','Tiempo');
	
	$con=conectar();
	$tipo="'".$_POST['tipo']."'";

	$consulta=consulta($con,"","CervezaTable","id",$tipo);
	$filas= mysqli_fetch_array($consulta, MYSQLI_BOTH);
	
	$i=2;
	foreach ($values as $value) {

		if($_POST[$value]!= $filas[$i]){
			mysqli_query($con,"UPDATE CervezaTable SET ".$campos[$i-2]."='".$_POST[$value]."' WHERE id=".$tipo);
		}
		$i++;
	}
}

echo json_encode(update());
