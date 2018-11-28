const char page_config[] PROGMEM = R"=====(
<!DOCTYPE html>
<html>
<head>
    <meta charset="utf-8" />
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <title>Stairs driver</title>
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
        Wifi pass: <input class="input" type="password" name="wifipassword" value="{wifipass}">
        <br><br>
        1 stair channel: <input class="input" type="number" name="channel1" value="{channel1}" min="0" max="15"><br>
        2 stair channel: <input class="input" type="number" name="channel2" value="{channel2}" min="0" max="15"><br>
        3 stair channel: <input class="input" type="number" name="channel3" value="{channel3}" min="0" max="15"><br>
        4 stair channel: <input class="input" type="number" name="channel4" value="{channel4}" min="0" max="15"><br>
        5 stair channel: <input class="input" type="number" name="channel5" value="{channel5}" min="0" max="15"><br>
        6 stair channel: <input class="input" type="number" name="channel6" value="{channel6}" min="0" max="15"><br>
        7 stair channel: <input class="input" type="number" name="channel7" value="{channel7}" min="0" max="15"><br>
        8 stair channel: <input class="input" type="number" name="channel8" value="{channel8}" min="0" max="15"><br>
        9 stair channel: <input class="input" type="number" name="channel9" value="{channel9}" min="0" max="15"><br>
        10 stair channel: <input class="input" type="number" name="channel10" value="{channel10}" min="0" max="15"><br>
        11 stair channel: <input class="input" type="number" name="channel11" value="{channel11}" min="0" max="15"><br>
        12 stair channel: <input class="input" type="number" name="channel12" value="{channel12}" min="0" max="15"><br>
        13 stair channel: <input class="input" type="number" name="channel13" value="{channel13}" min="0" max="15"><br>
        14 stair channel: <input class="input" type="number" name="channel14" value="{channel14}" min="0" max="15"><br>
        15 stair channel: <input class="input" type="number" name="channel15" value="{channel15}" min="0" max="15"><br>
        16 stair channel: <input class="input" type="number" name="channel16" value="{channel16}" min="0" max="15"><br>
        <br><br>
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

	<form class="reset-settings" action="/restart" method="POST">
        <input type="submit" value="Restart">
    </form>
</body>
</html>
)=====";