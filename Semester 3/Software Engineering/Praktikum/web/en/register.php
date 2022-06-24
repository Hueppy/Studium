<!DOCTYPE html>
<html lang="en" dir="ltr">
  <head>
    <link rel="stylesheet" href="../style.css">
    <script src="../myScript.js"></script>
    <meta charset="utf-8">
    <title>Registration - PfotenFreunde</title>
    <link rel="icon" type="image/x-icon" href="../img/favicon.png">
  </head>
  <body>
    <?php
    if(isset($_POST["submit"])) {
      if($_POST["pw"] != $_POST["pw2"]) {
        echo '<span style="color:white;">Passwörter stimmen nicht überein!</span>';
      }
      
      require_once('../vendor/autoload.php');

      $loginApi = new OpenAPI\Client\Api\LoginApi();
      $loginApi->loginPost($_POST['email'], $_POST['pw']);

      $person = new OpenAPI\Client\Model\Person();
      $person
        ->setName($_POST["username"])
        ->setSurname($_POST["surname"])
        ->setTelephone($_POST["telephone"])
        ->setEmail($_POST['email'])
        ->setAge($_POST['age'])
        ->setSex($_POST['sex']);
      $address = new OpenAPI\Client\Model\Address();
      $address
        ->setStreet($_POST['street'])
        ->setZip($_POST['zip'])
        ->setCity($_POST['city']);
      $person->setAddress($address);
        
      $personApi = new OpenAPI\Client\Api\PersonApi();
      $personApi->getConfig()
        ->setUsername($_POST['email'])        
        ->setPassword($_POST['pw']);
      $personApi->personPost($person);

      $message = urlencode('Account was created!');
      header("Location: index.php?$message");
    }
    ?>
    <div class="loginform">
      <img src="../img/logo.png" class="logo">
      <h1 class="txt-h1">Create Account</h1>
      <form action="register.php" method="post" autocomplete="off">
        <input type="text" name="username" placeholder="Name" class="name" maxlength="18" required>
        <input type="text" name="surname" placeholder="Surname" class="name" maxlength="40" required><br>
        <input type="email" name="email" placeholder="E-mail address" class="email" maxlength="50" required>
        <input type="tel" name="telephone" placeholder="Telephonenumber" class="tel" required><br>
        <input type="text" name="street" placeholder="Street" class="street" required>
        <input type="text" name="zip" pattern="[0-9]*" class="zip" placeholder="ZIP-Code" required><br>
        <input type="text" name="city" placeholder="City" class="city" required>
        <input type="number" name="age" placeholder="Age" class="age" required><br>
        <p class="sex">Sex: <input type="radio" name="sex" value="Male" required>Male
        <input type="radio" name="sex" value="Female">Female</p>
        <p style="color:white;">Institution? <input type="text" name="homepage" placeholder="www.example.com (Optional)" class="institution"><br>
        <input type="hidden" name="role" value="1">
        <input type="password" name="pw" placeholder="Password" class="pw" required>
        <input type="password" name="pw2" placeholder="Repeat password" class="pw" required><br>
        <button type="submit" name="submit" class="formsubmit">Register</button>
      </form>
      <br>
      <p class="txt-p1">Already a member? <a href="index.php" class="hyperlinks">Login</a></p>
      <div class="dropdown">
        <button onclick="myFunction()" class="dropbtn">Language</button>
        <div id="myDropdown" class="dropdown-content">
          <a href="../register.php">German</a>
        </div>
      </div>
      <script>
        function myFunction() {
          document.getElementById("myDropdown").classList.toggle("show");
        }
        window.onclick = function(event) {
          if (!event.target.matches('.dropbtn')) {
            var dropdowns = document.getElementsByClassName("dropdown-content");
            var i;
            for (i = 0; i < dropdowns.length; i++) {
              var openDropdown = dropdowns[i];
              if (openDropdown.classList.contains('show')) {
                openDropdown.classList.remove('show');
              }
            }
          }
        }
      </script>
    </div>
  </body>
</html>
