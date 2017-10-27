var net = require('net');
var server = net.createServer(function (socket) {
	
  socket.on('data',function(s){
    console.log(s.toString());
    socket.write('hello client\r\n');
	//socket.emit('foo', 'hello client foo\r\n');
  });  
  
  socket.on('foo',function(s){
    console.log(s.toString());
    //socket.emit('foo', 'hello client foo\r\n');
  });
});

server.listen(1337, "192.168.91.132");
