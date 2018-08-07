const char page_config[] PROGMEM = R"=====(
<!DOCTYPE html>
<html>
<head>
    <meta charset="utf-8" />
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <title>Roller shutter</title>
    <meta name="viewport" content="width=device-width, initial-scale=1">
    <link rel="stylesheet" type="text/css" media="screen" href="main.css" />
</head>
<style>
    body {
        font-family: 'Segoe UI', Tahoma, Geneva, Verdana, sans-serif
    }
    .menu a {
        margin-left: 30px;
    }
    .hr {
        border: 1px solid gray;
    }
    .save {
        width: 100px;
        height: 40px;
        margin-top: 50px;
    }
    .reset-settings {
        margin-top: 100px;
    }
    .input {
        width: 400px;
    }
</style>
<body>
    <div class="menu">
        <a href="/">Main</a>
        <a href="/config">Config</a>
    </div>
    <hr class="hr">
    <form action="/save" method="POST">
        Wifi name: <input class="input" type="text" name="wifiname" value="{wifiname}"><br>
        Wifi pass: <input class="input" type="password" name="wifipassword" value="{wifipass}"><br>
        TimeForLedsSwitchedOn: <input class="input" type="number" name="TimeForLedsSwitchedOn" value="{TimeForLedsSwitchedOn}"><br>
        DelayForNextStairToSwitchOn: <input class="input" type="number" name="DelayForNextStairToSwitchOn" value="{DelayForNextStairToSwitchOn}"><br>
        MillisCountForFullBrightness: <input class="input" type="number" name="MillisCountForFullBrightness" value="{MillisCountForFullBrightness}"><br>
        StairsCount: <input class="input" type="number" name="StairsCount" value="{StairsCount}"><br>
		InfoUrlSensorUp <input class="input" type="text" name="InfoUrlSensorUp" value="{InfoUrlSensorUp}"><br>
        PortSensorUp: <input class="input" type="number" name="PortSensorUp" value="{PortSensorUp}"><br>
        UriSensorUp: <input class="input" type="text" name="UriSensorUp" value="{UriSensorUp}"><br>
		InfoUrlSensorDown <input class="input" type="text" name="InfoUrlSensorDown" value="{InfoUrlSensorDown}"><br>
        PortSensorDown: <input class="input" type="number" name="PortSensorDown" value="{PortSensorDown}"><br>
        UriSensorDown: <input class="input" type="text" name="UriSensorDown" value="{UriSensorDown}"><br>
        <input class="save" type="submit" value="Save">
    </form>

    <form class="reset-settings" action="/resetsettings" method="POST">
        <input type="submit" value="Reset settings">
    </form>
</body>
</html>
)=====";