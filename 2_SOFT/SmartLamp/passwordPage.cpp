#include "passwordPage.h"

// HTML код страницы
// const char* htmlPasswordPage = R"rawliteral(
// <!DOCTYPE html>
// <html lang="ru">
// <head>
//     <meta charset="UTF-8">
//     <meta name="viewport" content="width=device-width, initial-scale=1.0">
//     <title>Ввод пароля</title>
//     <style>
//         * {
//             box-sizing: border-box; /* Устанавливаем box-sizing для всех элементов */
//             margin: 0;
//             padding: 0;
//         }
//         body {
//             font-family: Arial, sans-serif;
//             margin: 0;
//             padding: 0;
//             background-color: #f4f4f9;
//             display: flex;
//             justify-content: center;
//             align-items: center;
//             height: 100vh;
//         }
//         .container {
//             width: 100%;
//             max-width: 400px;
//             background-color: #fff;
//             padding: 20px;
//             border-radius: 10px;
//             box-shadow: 0 0 15px rgba(0, 0, 0, 0.1);
//         }
//         h1 {
//             text-align: center;
//             color: #333;
//             margin-bottom: 20px;
//         }
//         form {
//             display: flex;
//             flex-direction: column;
//             gap: 15px;
//         }
//         label {
//             font-weight: bold;
//             color: #555;
//         }
//         input[type="password"] {
//             width: 100%;
//             padding: 10px;
//             font-size: 16px;
//             border: 1px solid #ccc;
//             border-radius: 5px;
//         }
//         input[type="checkbox"] {
//             margin-right: 10px;
//         }
//         button {
//             width: 100%;
//             padding: 12px;
//             font-size: 18px;
//             background-color: #4CAF50;
//             color: white;
//             border: none;
//             border-radius: 5px;
//             cursor: pointer;
//             transition: background-color 0.3s;
//         }
//         button:hover {
//             background-color: #45a049;
//         }
//         .checkbox-container {
//             display: flex;
//             align-items: center;
//         }
//     </style>
// </head>
// <body>
// )rawliteral";


const char* cssStyles2 = R"rawliteral(
  <style>
* {
    box-sizing: border-box;
    margin: 0;
    padding: 0;
}
body {
    font-family: Arial, sans-serif;
    margin: 0;
    padding: 0;
    background-color: #f4f4f9;
    display: flex;
    justify-content: center;
    align-items: center;
    height: 100vh;
}
.container {
    width: 100%;
    max-width: 400px;
    background-color: #fff;
    padding: 20px;
    border-radius: 10px;
    box-shadow: 0 0 15px rgba(0, 0, 0, 0.1);
}
h1 {
    text-align: center;
    color: #333;
    margin-bottom: 20px;
}
form {
    display: flex;
    flex-direction: column;
    gap: 15px;
    align-items: center;
}
label {
    font-weight: bold;
    color: #555;
}
input[type="password"] {
    width: 100%;
    padding: 10px;
    font-size: 16px;
    border: 1px solid #ccc;
    border-radius: 5px;
}
input[type="checkbox"] {
    margin-right: 10px;
}
button {
    width: 100%;
    padding: 12px;
    font-size: 18px;
    background-color: #4CAF50;
    color: white;
    border: none;
    border-radius: 5px;
    cursor: pointer;
    transition: background-color 0.3s;
}
button:hover {
    background-color: #45a049;
}
.checkbox-container {
    display: flex;
    align-items: flex-start;
}
</style>
)rawliteral";

const char* htmlPasswordPage = R"rawliteral(
<!DOCTYPE html>
<html lang="ru">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Ввод пароля</title>
    <link rel="stylesheet" type="text/css" href="/style.css">
</head>
<body>

<div class="container">
    <h1>Ввод пароля</h1>
    <form action="/setPassword" method="POST">
        <label for="password">Пароль:</label>
        <input type="password" id="password" name="password" >
        
        <div class="checkbox-container">
            <input type="checkbox" id="noPassword" name="noPassword" %PLACEHOLDER_DO_NOT_USE_PASSWORD%>
            <label for="noPassword">Вход без пароля</label>
        </div>
        
        <button type="submit">Подтвердить</button>
    </form>
</div>

</body>
</html>
)rawliteral";


// const char* htmlPasswordPage2 = R"rawliteral(
// <div class="container">
//     <h1>Ввод пароля</h1>
//     <form action="/setPassword" method="POST">
//         <label for="password">Пароль:</label>
//         <input type="password" id="password" name="password" >
        
//         <div class="checkbox-container">
//             <input type="checkbox" id="noPassword" name="noPassword" %PLACEHOLDER_DO_NOT_USE_PASSWORD%>
//             <label for="noPassword">Вход без пароля</label>
//         </div>
        
//         <button type="submit">Подтвердить</button>
//     </form>
// </div>

// </body>
// </html>
// )rawliteral";
