#include "mainPage.h"

// HTML-код главной страницы управления нагрузкой
const char* htmlMainPage = R"rawliteral(
<!DOCTYPE html>
<html>
<head>
<meta charset="UTF-8"> <!-- Указываем кодировку страницы -->
  <title>Управление нагрузкой</title>
  <style>
    body {
      display: flex;
      justify-content: center;
      align-items: center;
      height: 100vh;
      margin: 0;
      font-family: Arial, sans-serif;
      background-color: #f0f0f0;
    }
    .control-button {
      width: 20vh;
      height: 20vh;
      font-size: 2em;
      border: none;
      cursor: pointer;
      border-radius: 5px;
      color: white;
      transition: background-color 0.3s;
    }
    .on {
      background-color: #ff4d4d; /* Красный цвет для кнопки "ОТКЛ" */
    }
    .off {
      background-color: #4caf50; /* Зеленый цвет для кнопки "ВКЛ" */
    }
    .settings-button {
      position: absolute;
      bottom: 20px;
      right: 20px;
      width: 50px;
      height: 50px;
      background-color: #ddd;
      border: none;
      border-radius: 50%;
      cursor: pointer;
      font-size: 24px;
      display: flex;
      justify-content: center;
      align-items: center;
    }
  </style>
</head>
<body>
  <button id="controlButton" class="control-button on" onclick="toggleLoad()">ОТКЛ</button>
  <button class="settings-button" onclick="goToSettings()">&#9881;</button>

  <script>
    let loadOn = true; // Переменная для состояния нагрузки

    function toggleLoad() {
      loadOn = !loadOn; // Переключаем состояние
      const button = document.getElementById('controlButton');
      if (loadOn) {
        button.classList.remove('off');
        button.classList.add('on');
        button.textContent = 'ОТКЛ';
      } else {
        button.classList.remove('on');
        button.classList.add('off');
        button.textContent = 'ВКЛ';
      }

      // Отправка запроса на сервер для управления нагрузкой
      fetch(`/toggleLoad?state=${loadOn ? 'on' : 'off'}`);
    }

    function goToSettings() {
      window.location.href = '/settings'; // Переход на страницу настроек
    }
  </script>
</body>
</html>
)rawliteral";