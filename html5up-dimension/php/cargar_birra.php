<?php 

function getInfo(){
	$campos=array('Cocinadas','Ultima','TempMaxF','TempMinF','TempMaxM','TempMinM','Inercia','Litros','Tiempo');

	$birras=file('listabirras.txt');
	$i=0;
	foreach ($campos as $campo) {
		$prueba[$campo]=$birras[$i];
		$i+=1;
	}

	return $prueba;
}

echo  json_encode(getInfo());