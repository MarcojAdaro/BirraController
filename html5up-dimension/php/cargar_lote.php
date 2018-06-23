<?php 
require_once 'conexion.php';

function getLote(){
	$tipo="'".$_POST['tipo']."'";
	$conexion= conectar();
	$i=1;
	$j=0;
	$listas = '<option value="0">Elige una opción</option>';
	$resultado=consulta($conexion,"Lote","CervezaTable as c,Lotes as l","Tipo",$tipo);
	
	$lote= mysqli_fetch_array($resultado, MYSQLI_NUM);
	
	do{
		$listas .= "<option value='$i'>$lote[$j]</option>";
		$i++;
		$lote=mysqli_fetch_array($resultado, MYSQLI_NUM);
	}while($lote[$j]!="");
	
	
	cerrar($conexion);
	return $listas;
}
echo json_encode(getLote());