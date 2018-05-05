<?php 


function getInfo(){

	$birras=file('listabirras.txt');
	

	return $birras[0];
}

echo getInfo();