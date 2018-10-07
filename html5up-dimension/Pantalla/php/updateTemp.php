<?php

	exec("mode /dev/ttyUSB0 BAUD=9600 PARITY=N data=8 stop=1 xon=off");

	$fp= @fopen("/dev/ttyUSB0","w");
		
		if($fp){
			echo "Conectado";
			$lectura= @fread($fp,16);
			echo "   ".$lectura."    ";
			
		}else{
			echo "Desconectado";
			echo "   ".$fp."    ";
		}
