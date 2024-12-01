#include "passwordPage.h"

// HTML код страницы
const char* htmlPasswordPage = R"rawliteral(
<!DOCTYPE html>
<html>
  <head>
    <title>ESP8266 Web Access</title>
    <style>
      body { font-family: Arial, sans-serif; }
      .container { max-width: 400px; margin: auto; padding: 20px; text-align: center; }
      input[type=password] { padding: 10px; margin: 10px; width: 80%; }
      input[type=submit] { padding: 10px 20px; background-color: #4CAF50; color: white; border: none; cursor: pointer; }
      input[type=submit]:hover { background-color: #45a049; }
    </style>
  </head>
  <body>
    <div class="container">
      <h2>Enter Password</h2>
      <form action="/setPassword" method="POST">
        <input type="password" name="password" placeholder="Enter password" required>
        <input type="submit" value="Submit">
      </form>
    </div>
  </body>
</html>
)rawliteral";
