<?php
require_once('../vendor/autoload.php');
session_start();
if (!isset($_SESSION["email"]) || !isset($_SESSION["pw"]) || !isset($_SESSION["id"])) {
  header("Location: index.php");
  exit;
}
$friendsApi = new \OpenAPI\Client\Api\FriendApi();
$friendsApi->getConfig()
  ->setUsername($_SESSION['email'])
  ->setPassword($_SESSION['pw']);

if (isset($_POST["submitaccept"])) {
  $friendsApi->friendRequestIdPost($_POST["id"], 2);
} else {
}
if (isset($_POST["submitdecline"])) {
  $friendsApi->friendRequestIdPost($_POST["id"], 1);
} else {
}

?>

<!DOCTYPE html>
<html lang="en" dir="ltr">

<head>
  <link rel="stylesheet" href="../style.css">
  <meta charset="utf-8">
  <title>Friends- PfotenFreunde</title>
  <link rel="icon" type="image/x-icon" href="../img/favicon.png">
</head>

<body>
  <div class="flex-container">
    <div class="ContentLeft1">
      <div>
        <img style="object-fit: contain; width: 200px;" src="../img/logo.png" class="logo">
      </div>
      <a class="navbtns1" href="search.php">Search</a><br>
      <a class="navbtns2 active" href="friends.php">Friends</a><br>
      <a class="navbtns3" href="chat.php">Chat</a><br>
      <a class="navbtns4" href="profiles.php">Pet profiles</a><br>
      <a class="logout" href="logout.php">Logout</a><br>
      <a class="language" href="../friends.php">In German!</a>
    </div>
    <div class="ContentMiddle1">
      <?php
      $receiver = $_SESSION["id"];
      $requests = $friendsApi->friendRequestGet();
      $userApi = new \OpenAPI\Client\Api\UserApi();
      $userApi->getConfig()
        ->setUsername($_SESSION['email'])
        ->setPassword($_SESSION['pw']);

      foreach ($requests as $req) {
        $user = $userApi->userIdGet($req->getSenderId());
      ?>
        <div class="forms">
          <form method="post">
            <input type="hidden" name="id" value="<?php echo $req->getId(); ?>">
            <input type="submit" class="submitbtn" name="submitaccept" value="Accept <?php echo $user->getName(); ?>'s friend request">
          </form>
          <input type="hidden" name="id" value="<?php echo $req->getId(); ?>">
          <input type="submit" class="submitbtn" name="submitdecline" value="Decline <?php echo  $user->getName(); ?>'s friend request">
          </form>
        </div>
      <?php
      } ?>
      <div class="tablediv2">
        <table class="table">
          <thead>
            <tr>
              <th>Name</th>
              <th></th>
            </tr>
          </thead>
          <tbody>
            <?php
            $friends = $friendsApi->friendUserIdGet($receiver);
            foreach ($friends as $friend) {
            ?>
              <tr>
                <td>
                  <?php echo $friend->getName(); ?>
                </td>
                <td class="td2">
                  <form action="chat.php?user=<?php echo $friend->getId(); ?>" method="post">
                    <input type="submit" class="submitchat" name="submitchat" value="Open new Chat">
                  </form>
                </td>
              </tr>
            <?php
            }
            ?>
          </tbody>
        </table>
      </div>
    </div>
  </div>
</body>
</html>