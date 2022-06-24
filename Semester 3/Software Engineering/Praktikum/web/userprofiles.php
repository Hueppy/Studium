<?php
require_once(__DIR__ . '/vendor/autoload.php');
session_start();
if(!isset($_SESSION["email"]) || !isset($_SESSION["pw"]) || !isset($_SESSION["id"])){
  header("Location: index.php");
  exit;
}
$friendsApi = new \OpenAPI\Client\Api\FriendApi();
$friendsApi->getConfig()
  ->setUsername($_SESSION['email'])        
  ->setPassword($_SESSION['pw']);

$senderid = $_SESSION["id"];
$profileid = $_GET["id"];

if(isset($_POST["submit"])){
  $friendsApi->friendUserIdPost($profileid);
  header("Location: search.php");
}else {
}
if(isset($_POST["submitcancel"])){
  $friendsApi->friendUserIdDelete($profileid);
}else {
}
?>

<!DOCTYPE html>
<html lang="en" dir="ltr">
  <head>
    <link rel="stylesheet" href="style.css">
    <meta charset="utf-8">
    <title>Profile - PfotenFreunde</title>
    <link rel="icon" type="image/x-icon" href="img/favicon.png">
  </head>
  <body>
    <div class="flex-container">
      <div class="ContentLeft1">
        <div>
          <img style="object-fit: contain; width: 200px;" src="../img/logo.png" class="logo">
        </div>
        <a class="navbtns1" href="search.php">Suche</a><br>
        <a class="navbtns2" href="friends.php">Freunde</a><br>
        <a class="navbtns3" href="chat.php">Nachrichten</a><br>
        <a class="navbtns4" href="profiles.php">Haustierprofile</a><br>
        <a class="logout" href="logout.php">Logout</a><br>
        <a class="language" href="en/profiles.php">Auf Englisch!</a>
      </div>
      <div class="ContentMiddle1">
          <form method="post">
            <input type="hidden" name="sender_id" value="<?php echo $senderid; ?>">
            <input type="hidden" name="receiver_id" value="<?php echo $profileid; ?>">
            <button type="submit" name="submit" value="Freund hinzufügen">Freund hinzufügen</button>
          </form>
      </div>
    </div>
  </body>
</html>
