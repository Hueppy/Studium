<?php
require_once(__DIR__ . '/vendor/autoload.php');
session_start();
if (!isset($_SESSION["email"]) || !isset($_SESSION["pw"]) || !isset($_SESSION["id"])) {
  header("Location: index.php");
  exit;
}

$chatroomApi = new \OpenAPI\Client\Api\ChatroomApi();
$chatroomApi->getConfig()
  ->setUsername($_SESSION['email'])
  ->setPassword($_SESSION['pw']);
$chatroomModel = new \OpenAPI\Client\Model\Chatroom();

if (isset($_POST["submitchat"])) {
  $chatid = $chatroomApi->chatroomPost($chatroomModel);
  $chatroomApi->chatroomIdUserPost($chatid, $_SESSION["id"]);
  $chatroomApi->chatroomIdUserPost($chatid, $_GET["user"]);
  header("Location: chat.php?id=$chatid");
}

if (isset($_POST["submitmsg"])) {
  $chatid = $_GET["id"];
  $msg = new \OpenAPI\Client\Model\Message();
  $msg->setSenderId($_SESSION["id"]);
  $msg->setChatroomId($chatid);
  $msg->setText($_POST["chatmessages"]);

  $chatroomApi->chatroomIdMessagesPost($chatid, $msg);
}

?>

<!DOCTYPE html>
<html lang="en" dir="ltr">

<head>
  <link rel="stylesheet" href="style.css">
  <meta charset="utf-8">
  <title>Chat - PfotenFreunde</title>
  <link rel="icon" type="image/x-icon" href="img/favicon.png">
</head>

<body>
  <div class="flex-container">
    <div class="ContentLeft1">
      <div>
        <img style="object-fit: contain; width: 200px;" src="img/logo.png" class="logo">
      </div>
      <a class="navbtns1" href="search.php">Suche</a><br>
      <a class="navbtns2" href="friends.php">Freunde</a><br>
      <a class="navbtns3 active" href="chat.php">Nachrichten</a><br>
      <a class="navbtns4" href="profiles.php">Haustierprofile</a><br>
      <a class="logout" href="logout.php">Logout</a><br>
      <a class="language" href="en/chat.php">Auf Englisch!</a>
    </div>
    <div class="ContentMiddle1">
      <div class="chat">
        <?php
        if (isset($_GET["id"])) {
        ?>
          <div id="chat2" class="chat2">
            <table class="chattable">
              <tbody>
                <?php
                $messages = $chatroomApi->chatroomIdMessagesGet($_GET["id"]);
                $userApi = new \OpenAPI\Client\Api\UserApi();
                $userApi->getConfig()
                  ->setUsername($_SESSION['email'])
                  ->setPassword($_SESSION['pw']);

                foreach ($messages as $msg) {
                  $user = $userApi->userIdGet($msg->getSenderId());
                ?>
                  <tr>
                    <td><?php echo $user->getName(); ?></td>
                    <td><?php echo $msg->getText(); ?></td>
                  </tr>
              <?php
                }
              
              ?>
              </tbody>
            </table>
            <form method="post">
              <textarea name="chatmessages" class="textareachat"></textarea>
              <input type="submit" name="submitmsg" value="Nachricht senden">
            </form>
            <?php
            }else{
              $meApi = new \OpenAPI\Client\api\MeApi();
              $meApi->getConfig()
                ->setUsername($_SESSION['email'])
                ->setPassword($_SESSION['pw']);
              $chatrooms = $meApi->meChatroomsGet();
              ?>
              <div>
                <table>
                  <thead>
                    <tr>
                      <th>Chats</th>
                    </tr>
                  </thead>
                  <tbody>
                    <?php foreach($chatrooms as $chats){  
                    ?>
                      <tr>
                        <td>
                          <a class="chatlinks" href="chat.php?id=<?php echo $chats->getId(); ?>">
                           <?php 
                             $users = $chatroomApi->chatroomIdUserGet($chats->getId());
                              foreach($users as $user){
                                echo "{$user->getName()} ";
                              }
                            ?>
                          </a>
                        </td>
                      </tr>
                    <?php }?>
                  </tbody>
                </table>
              </div>
              <?php
            } 
            ?>
          </div>
      </div>
    </div>
  </div>
</body>
<script>
  var elem = document.getElementById('chat2');
  elem.scrollTop = elem.scrollHeight;
</script>
</html>