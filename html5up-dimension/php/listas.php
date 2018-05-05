<?php 


function getBirra(){

	$birras=file('listabirras.txt');
	$listas = '<option value="0">Elige una opción</option>';
	foreach ($birras as $clave=>$birra) {
		$listas .= "<option value='$clave'>$birra</option>";
	}

	return $listas;
}

echo getBirra();