<?php 

function conectar(){


	$servername= "localhost";
	$username= "root";
	$password= "birra";
	$namebase= "CervezasBase";

	$conexion = mysqli_connect($servername, $username, $password,$namebase);

	if(!$conexion){
		echo "Error: No se pudo conectar a MySQL.";
		
		exit;	
	}

	return $conexion;
}

function cerrar($conexion){
	mysqli_close($conexion); 
}

function consulta($conexion,$filtro,$nomTabla,$campo,$busqueda){

	if($filtro=="")$filtro="*";

	$consulta= "SELECT ".$filtro." FROM ".$nomTabla;
	if($campo!= "") $consulta.=" WHERE ".$campo."=".$busqueda;

	//$consulta= "SELECT * FROM CervezaTable WHERE id='2'";

	if (!($resultado=mysqli_query($conexion, $consulta)))
		echo "Error:". mysqli_error($conexion);

	return $resultado;
}


	//conectar();

?>