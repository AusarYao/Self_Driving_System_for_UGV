var http = require('http');

var app = http.createServer(function ejecute(request, response){});
var io = require('socket.io').listen(app);


io.on('connection', function(socket) {
        socket.on('message', function(data){
            console.log("recieved data:");
            console.log(data);

            var bufArr = new ArrayBuffer(4);
            var bufView = new Uint8Array(bufArr);
            bufView[0]=6;
            bufView[1]=7;
            bufView[2]=8;
            bufView[3]=9;
            socket.emit('message',bufArr);
        });
});

app.listen(3000, '192.168.4.165');