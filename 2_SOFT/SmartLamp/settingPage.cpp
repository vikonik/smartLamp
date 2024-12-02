#include "settingPage.h"
// HTML код страницы
const char* htmlSettingPage = R"rawliteral(
<!DOCTYPE html>
<html lang="ru">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Настройки устройства</title>
    <style>
        * {
            box-sizing: border-box;
            margin: 0;
            padding: 0;
        }
        body {
            font-family: Arial, sans-serif;
            background-color: #f4f4f9;
            padding: 20px;
        }
        .container {
            max-width: 600px;
            margin: 0 auto;
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
        .section {
            margin-bottom: 30px;
        }
        .section h2 {
            font-size: 20px;
            color: #555;
            margin-bottom: 10px;
        }
        form {
            display: flex;
            flex-direction: column;
            gap: 15px;
        }
        label {
            font-weight: bold;
            color: #555;
        }
        input[type="text"],
        input[type="password"],
        input[type="number"] {
            width: 100%;
            padding: 10px;
            font-size: 16px;
            border: 1px solid #ccc;
            border-radius: 5px;
        }
        select {
            width: 100%;
            padding: 10px;
            font-size: 16px;
            border: 1px solid #ccc;
            border-radius: 5px;
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
    </style>
</head>
<body>

<div class="container">
    <h1>Настройки устройства</h1>

    <!-- Раздел настроек MQTT -->
    <div class="section">
        <h2>Настройки MQTT</h2>
        <form action="/saveMQTTSettings" method="POST">
            <label for="mqtt-server">Сервер MQTT:</label>
            <input type="text" id="mqtt-server" name="mqttServer" required value="%PLACEHOLDER_MQTT_SERVER%">

            <label for="mqtt-port">Порт MQTT:</label>
            <input type="number" id="mqtt-port" name="mqttPort" required value="%PLACEHOLDER_MQTT_SPORT%">

            <label for="mqtt-client-id">Идентификатор клиента:</label>
            <input type="text" id="mqtt-client-id" name="mqttClientID" required value="%PLACEHOLDER_CLIENT_ID%">

            <label for="mqtt-username">Имя пользователя MQTT:</label>
            <input type="text" id="mqtt-username" name="mqttUsername" value="%PLACEHOLDER_USER_NAME%">

            <label for="mqtt-password">Пароль MQTT:</label>
            <input type="password" id="mqtt-password" name="mqttPassword" value="%PLACEHOLDER_MQTT_PASSWORD%">

            <label for="mqtt-subscribe-topic">Тема подписки:</label>
            <input type="text" id="mqtt-subscribe-topic" name="mqttSubscribeTopic" value="%PLACEHOLDER_MQTT_SUBSCRIBE_TOPIC%">

            <label for="mqtt-publish-topic">Тема публикации:</label>
            <input type="text" id="mqtt-publish-topic" name="mqttPublishTopic" value="%PLACEHOLDER_MQTT_PUBLISH_TOPIC%">

            <label for="mqtt-qos">QoS (Качество обслуживания):</label>
            <select id="mqtt-qos" name="mqttQoS">
				%PLACEHOLDER_MQTT_QOS%
            </select>

            <label for="mqtt-keep-alive">Интервал Keep Alive (секунды):</label>
            <input type="number" id="mqtt-keep-alive" name="mqttKeepAlive" required value="%PLACEHOLDER_MQTT_KEEP_ALIVE%">

            <label for="mqtt-retain">Флаг Retain:</label>
            <select id="mqtt-retain" name="mqttRetain">
				%PLACEHOLDER_MQTT_RETAIN%
            </select>

            <label for="mqtt-clean-session">Чистая сессия:</label>
            <select id="mqtt-clean-session" name="mqttCleanSession">
				%PLACEHOLDER_MQTT_CLEAN_SESSION%
            </select>

            <button type="submit">Сохранить MQTT настройки</button>
        </form>
    </div>

    <!-- Раздел сетевых настроек -->
<div class="section">
    <h2>Сетевые настройки</h2>
    <form action="/saveNetworkSettings" method="POST">
        <!-- Настройки IP-адресов -->
        <div style="display: flex; gap: 20px;">
            <!-- Настройки клиента -->
            <div>
                <div>
                    <label for="use-StaticIP-client">
                        <input type="checkbox" id="use-StaticIP-client" name="useStaticIpClient">
                        Статический адрес
                    </label>
					<br>
                </div>
				<br>
                <div>
                    <label for="client-ip">IP-адрес в режиме клиента:</label>
                    <input type="text" id="client-ip" name="clientIP" required>
                </div>
            </div>
            
            <!-- Настройки точки доступа -->
            <div>
                <div>
                    <label for="use-StaticIP-server">
                        <input type="checkbox" id="use-StaticIP-server" name="useStaticIpServer">
                        Статический адрес

                    </label>
					<br>
                </div>
				<br>
                <div>
                    <label for="ap-ip">IP-адрес в режиме точки доступа:</label>
                    <input type="text" id="ap-ip" name="apIP" required>
                </div>
            </div>
        </div>

     <!-- Сетевое имя устройства -->
        <div style="display: flex; flex-direction: column; gap: 5px;">
          <label for="device-name">Сетевое имя:</label>
          <div style="display: flex; align-items: center; gap: 5px;">
            <input type="text" id="device-name" name="deviceName" required style="flex-grow: 1;">
            <span>.local</span>
          </div>
        </div>
        <!--  имя хоста -->
        <div style="display: flex; flex-direction: column; gap: 5px;">
            <label for="host-name">Имя хоста:</label>
            <input type="text" id="host-name" name="hostName" required>
        </div>	
        <!-- Кнопка сохранения -->
        <button type="submit">Сохранить сетевые настройки</button>
    </form>
</div>



    <!-- Раздел изменения пароля -->
    <div class="section">
        <h2>Изменение пароля</h2>
        <form action="/changePassword" method="POST">
            <label for="new-password">Новый пароль:</label>
            <input type="password" id="new-password" name="newPassword" required>

            <button type="submit">Изменить пароль</button>
        </form>
    </div>
</div>

</body>
</html>
)rawliteral";