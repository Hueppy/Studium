<!DOCTYPE html>
<html lang="en" dir="ltr">
  <head>
    <link rel="stylesheet" href="style.css">
    <script src="myScript.js"></script>
    <meta charset="utf-8">
    <title>Login - PfotenFreunde</title>
    <link rel="icon" type="image/x-icon" href="img/favicon.png">
  </head>
  <body>
    <?php
    if(isset($_POST["submit"])){
      require_once(__DIR__ . '/vendor/autoload.php');

      $meApi = new OpenAPI\Client\Api\MeApi();
      $meApi->getConfig()
        ->setUsername($_POST['email'])
        ->setPassword($_POST['pw']);
      
      try {
        $meApi->meStatusPost(1);
        $me = $meApi->meGet();

        session_start();
        $_SESSION['email'] = $_POST['email'];
        $_SESSION['pw'] = $_POST['pw'];
        $_SESSION['id'] = $me->getId();

        header("Location: profiles.php");
      } catch (Exception) {
        echo '<span style="color:white;">Login fehlgeschlagen!</span>';
      }
    }
    ?>
    <div class="loginform">
      <img src="img/logo.png" class="logo">
      <h1 class="txt-h1">Login</h1>
      <form action="index.php" method="post" autocomplete="off">
        <input type="email" name="email" placeholder="E-Mail Adresse" class="email" maxlength="40" required><br>
        <input type="password" name="pw" placeholder="Passwort" class="pw" required><br>
        <button type="submit" name="submit" class="formsubmit">Einloggen</button>
      </form>
      <br>
      <p class="txt-p1">Noch keinen Account? <a href="register.php" class="hyperlinks"> Registrieren</a></p>
      <div class="dropdown">
        <button onclick="myFunction()" class="dropbtn">Sprache</button>
        <div id="myDropdown" class="dropdown-content">
          <a href="en/index.php">Englisch</a>
        </div>
      </div>
    </div>
  </body>
</html>
