<?php


switch($_POST['modo']) {
case"Update":
	echo Update();
	break;
case "Set":
	echo json_encode(setTemp());
	break;
}

function Update() {

if (!$fp= fopen("Archivo.txt","r")){
	echo "no abrio";
}
fseek($fp,($_POST['fermentador']-1)*12);
$tmp= fread($fp,13);
fclose($fp);

return $tmp;


}

function setTemp() {

if (!$fp= fopen("Parametros.txt","r+")){
	echo "no abrio";
}
fseek($fp,($_POST['fermentador']-1)*12);

$tmp=fwrite($fp, $_POST['temp'], 13);

//$tmp= fread($fp,512);
fclose($fp);

//return $tmp;
}
