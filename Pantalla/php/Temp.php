<?php

//$_POST['modo']
//$_POST['fermentador']=1;
$linea = ($_POST['fermentador'] -1)*14;
$posicion =12;

switch($_POST['modo']) {
case"Update":
	echo Update();
	break;
case "Set":
	echo json_encode(setTemp());
	break;
case "Cancelar":
	echo json_encode(CanTemp());
	break;
case "read":
	echo json_encode(ReadTemp());
	break;
	case "Fer_Mad":
	echo json_encode(Fer_Mad());
	break;
}

function Update() {
global $linea;
if (!$fp= fopen("Temperatura.txt","r")){
	echo "no abrio";
}
fseek($fp,($_POST['fermentador'] -1)*6);
$tmp= fread($fp,5);
fclose($fp);

return $tmp;


}

function setTemp() {
global $linea;
if (!$fp= fopen("Parametros.txt","r+")){
	echo "no abrio";
}
fseek($fp,$linea);

$tmp=fwrite($fp, $_POST['temp'], 13);

//$tmp= fread($fp,512);
fclose($fp);

//return $tmp;
}

function CanTemp(){
	global $linea,$posicion;
	if (!$fp= fopen("Parametros.txt","r+")){
		echo "no abrio";
	}
	
	fseek($fp,$linea+$posicion);

	$tmp=fwrite($fp, "0", 1);	

	//$tmp= fread($fp,512);
	fclose($fp);

}


function ReadTemp(){

	global $linea,$posicion;
	
	if (!$fp= fopen("Parametros.txt","r")){
		echo "no abrio";
	}
	fseek($fp,$linea);

	$tmp=fread($fp,13);
	
	$p = explode(",", $tmp);
	
	fclose($fp);

	return $p;
}
function Fer_Mad(){

	global $linea,$posicion;
	
	if (!$fp= fopen("Parametros.txt","r+")){
		echo "no abrio";
	}
	fseek($fp,$linea+15);
	if($_POST['fer_mad'] == "Fermentar") {
		fwrite($fp,",0",2);
	}else {
		fwrite($fp,",1",2);
		}
	
	fclose($fp);

}