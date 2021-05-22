const char index_html[] PROGMEM = R"rawliteral(
<html>
<body>
<form method="GET" action="/on">
    <input type="submit" value="ON" style = "height: 200px; width:400px">
</form>

<form method="GET" action="/off">
    <input type="submit" value="OFF" style = "height: 200px; width:400px">
</form>


<h1>
Red 0-255
<form method="GET" action = '/color'>
    <input type ="text" name = 'red' id="red" style = "height: 100px; width:200px">
    <br>
Green 0-255 
<br>
    <input type ="text" name = 'green' id="green" style = "height: 100px; width:200px">
    <br>
Blue 0-255
<br>
    <input type ="text" name = 'blue' id="blue" style = "height: 100px; width:200px">
    <br>
<input type ="submit" style = "height: 100px; width:200px">
</form>

</h1>
</body>
</html>
)rawliteral";
