<?php 

$usuario = "root";
$senha = "";
$host = "localhost";
//$selecionabd = "bancoarduino";

$conexao = mysql_connect($host,$usuario,$senha);
$selecionabd = mysql_select_db('bancoarduino',$conexao);

	
	if($conexao)
		{
			echo "Conectou com sucesso";
		} else {
			echo "Ocorreu um erro";
			}

?>
