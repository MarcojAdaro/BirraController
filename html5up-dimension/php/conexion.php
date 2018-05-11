<?php 

function conectar(){

/*
$servername= "localhost";
$username= "root";
$password= "birra";
$namebase= "CervezasBase";
*/
$conexion = mysqli_connect("localhost", "root", "birra", "CervezasBase");
if(!$conexion){
	echo "Error: No se pudo conectar a MySQL.";
	
	exit;
}

//myqli_query($conexion,"SELECT * FROM 'CervezasTable'");
return $conexion;
}

function cerrar($conexion){
	mysqli_close($conexion); 
	}


	//conectar();

?>