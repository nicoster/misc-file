var net = require('net');

var server = net.createServer(function (socket) {
  socket.write("Echo server\r\n");
  socket.setEncoding('utf8');
  socket.pipe(socket);
  socket.on('data', function(data){
    console.log(data);
  });
});

server.listen(1337, "192.168.0.100");
