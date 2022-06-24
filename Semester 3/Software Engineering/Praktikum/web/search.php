<?php
require_once(__DIR__ . '/vendor/autoload.php');
session_start();
if(!isset($_SESSION["email"]) || !isset($_SESSION["pw"]) || !isset($_SESSION["id"])){
  header("Location: index.php");
  exit;
}

?>

<!DOCTYPE html>
<html lang="en" dir="ltr">
  <head>
    <link rel="stylesheet" href="style.css">
    <meta charset="utf-8">
    <title>Suche - PfotenFreunde</title>
    <link rel="icon" type="image/x-icon" href="img/favicon.png">
  </head>
  <body>
    <div class="flex-container">
      <div class="ContentLeft1">
        <div>
          <img style="object-fit: contain; width: 200px;" src="img/logo.png" class="logo">
        </div>
        <a class="navbtns1 active" href="search.php">Suche</a><br>
        <a class="navbtns2" href="friends.php">Freunde</a><br>
        <a class="navbtns3" href="chat.php">Nachrichten</a><br>
        <a class="navbtns4" href="profiles.php">Haustierprofile</a><br>
        <a class="logout" href="logout.php">Logout</a><br>
        <a class="language" href="en/search.php">Auf Englisch!</a>
      </div>
      <div class="ContentMiddle1">
        <div class="search">
          <form action="search.php" method="post">
            <input class="searchbar" type="text" name="search" placeholder="Profile suchen" autocomplete="off">
            <input class="submit" type="submit" name="submit" value="Suchen">
          </form>
        </div>
        <div class="results">
          <?php
            if(isset($_POST["submit"])){
            $key = $_POST["search"];
            $searchApi = new OpenAPI\Client\Api\SearchApi();
            $searchApi->getConfig()
              ->setUsername($_SESSION['email'])        
              ->setPassword($_SESSION['pw']);
            $search = $searchApi->searchUserGet($key);
          
            foreach($search as $search){
              if($search->getId() != $_SESSION["id"]){
          ?>
                  <a href="userprofiles.php?id=<?php echo $search->getId(); ?>" class="search-results"><?php echo $search->getName(); ?></a>
                  <?php
             }
            }
          }
          ?>
        </div>
      </div>
    </div>
  </body>
</html>
