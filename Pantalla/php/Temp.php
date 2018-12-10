<?php

//$_POST['modo']
//$_POST['fermentador']=1;
$linea = ($_POST['fermentador'] -1)*16;
$posicion = 12;
$cantFerm = 4;

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
case "Read_Status":
	echo Status();
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

	$ferm = 0;

	Send_update($fp);	
	
	fclose($fp);

}

function CanTemp(){
	global $linea,$posicion;
	if (!$fp= fopen("Parametros.txt","r+")){
		echo "no abrio";
	}
	
	fseek($fp,$linea+$posicion);

	$tmp=fwrite($fp, "0", 1);	
	Send_update($fp);
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
	
	if (!$fp= fopen("Parametros.txt",'r+')){
		echo "no abrio";
	}
	
	fseek($fp,$linea+14);
	if($_POST['fer_mad'] == "Fermentar") {
		fwrite($fp,"0",1);
	}else {
		fwrite($fp,"1",1);
		}
	Send_update($fp);
	fclose($fp);

}

function Status(){

	global $linea;

	if(!$fp=fopen("Parametros.txt", "r")){
		echo "No abrio";
	}
	else{
		fseek($fp, $linea+14);
		$modo=fread($fp,1);
		if($modo == 1)
			$fmodo = 'Madurando';
		else
			$fmodo = 'Fermentando';
	}
	fclose($fp);
	return $fmodo;
}



function OnOff(){

	global $linea;

	if(!$fp=fopen("Parametros.txt", "r")){
		echo "No abrio";
	}
	else{
		fseek($fp, $linea+12);
		$OnOff=fread($fp,1);
	}
	fclose($fp);
	return $OnOff;

}



function Send_update($fp){
	global $cantFerm;
	fseek($fp,SEEK_SET);
	fseek($fp,16*$cantFerm,1);
	
	while(fread($fp,1)!=0){
		fread($fp,1);
		$ferm++;
	}

	fseek($fp,SEEK_SET);
	fseek($fp,(16*$cantFerm)+($ferm*2),1);

	fwrite($fp,$_POST['fermentador'],1);

}