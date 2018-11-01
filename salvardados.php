<?php

include ("conecta.php");

	$sensor1 = $_GET['sensor1'];
	$sensor2 = $_GET['sensor2'];
	$sensor3 = $_GET['sensor3'];

	$sql_insert = "insert into tabelaarduino (sensor1,sensor2,sensor3) values ('$sensor1','$sensor2','$sensor3')";
	mysql_query($sql_insert);

		if($sql_insert) 
			{
			echo "Salvo com sucesso";
			} else { 
		echo "Ocorreu um erro";
	}

?>
