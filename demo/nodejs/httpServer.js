var  http = require('http')
    , socketio = require('socket.io');
 
var server = http.createServer(function(req, res) {
    res.writeHead(200, { 'Content-type': 'text/html'});
    console.log('Listening at: http://localhost:8080');
});

server.listen(1337, "192.168.91.132");

//添加一个连接监听器
socketio.listen(server).on('connection', function (client) {
    //监听成功
    client.on('message', function (msg) {
        console.log('Message Received: ', msg);
           client.send('message', msg);
    });
    client.on("disconnect", function() {
        console.log("Server has disconnected");
    })
});
