<!DOCTYPE html>
<hmtl>
	<head>
		<meta charset="utf-8">
		<title>Dados - Arduino </title>

		</head >

		<body>
			<h1>DADOS</h1>

			<table width="500" border="1" cellspacing="2" cellpadding="5">

			<tr>
			        <td>ID</td>
				<td>DATA</td>
				<td>S1</td>
				<td>s2</td>				
			        <td>s3</td>
			</tr>
			
<?php

	include("conecta.php");
	$resultado = mysql_query("select * from tabelaarduino");

		while ($linha = mysql_fetch_array ($resultado))

		{
		echo'<tr>';
		echo'<td>'.$linha["id"].'</td>';
		echo'<td>'.$linha["evento"].'</td>';
		echo'<td>'.$linha["sensor1"].'</td>';
		echo'<td>'.$linha["sensor2"].'</td>';			
		echo'<td>'.$linha["sensor3"].'</td>';
		echo'</tr>';	
		}

?>

                </table>
		</body>
</html>
