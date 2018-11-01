<?
header('Content-type: text/html; charset=UTF-8');
##################################################
## Verificando se passaram os campos obrigatorios
##################################################

$required = array('database', 'table');

$error = false;
foreach($required as $field) {
    if (empty($_POST[$field])) {
        $error = true;
    }
}
if ($error) {
    echo "Você não me deu todos os campos obrigatórios";
    exit();
}

$database=$_POST['database'];
$table=$_POST['table'];

##################################################
## Abrindo o banco de dados
##################################################

$dir = "sqlite:/var/www/es/ulisses/sqlite/${database}.sqlite";
$dbh = new PDO("$dir") or die("Não consegui abrir o banco de dados");
$dbh->exec("SET CHARACTER SET utf8");
$dbh->exec("set names utf8");
$dbh->setAttribute(PDO::ATTR_ERRMODE, PDO::ERRMODE_EXCEPTION);

##################################################
## Verificando se whereArgs foi enviado
##################################################

$required = array('whereClause', 'whereArgs');

$has_where = true;
foreach($required as $field) {
    if (empty($_POST[$field])) {
        $has_where = false;
    }
}


##################################################
## Preparando a consulta SQL
##################################################

$query="";
if ($has_where) {
    $clause=$_POST['whereClause'];
    $args  =$_POST['whereArgs'];
    $query =  "SELECT * FROM $table WHERE $clause=\"$args\";";
} else {
    $query =  "SELECT * FROM $table;";
}

##################################################
## Realizando a consulta e devolvendo ao usuário
##################################################

$stmt=$dbh->query($query);
echo json_encode($stmt->fetchAll(PDO::FETCH_ASSOC));
?>
