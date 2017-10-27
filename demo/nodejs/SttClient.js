var net = require('net');

var client = net.connect({port: 8050, host: '182.18.47.17'},
    function() { 		
	
	console.log('connected to server!');  
	
	var myData = new Buffer([0xdf, 0x00, 0x00, 0x00, 0xdf, 0x00, 0x00,  0x00, 0xb1, 0x02, 0x00, 0x00]);
	var str = 'type@=loginreq/username@=auto_cP6EaIt6S0/password@=6c44e5cd17f0019c64b042e4a745412a/roompass@=/roomid@=3071/devid@=91194F0305393FF9C92F963E18AC9539/rt@=1431498307/vk@=fec990a974007471c28590731a323268/ver@=20150506/';

	client.write(myData.toString('binary') + str.toString('binary') + '\0', 'binary');
});

client.on('data', function(data) {
	console.log(data.toString('utf-8'));	
	client.destroy();
});

client.on('end', function() {
  console.log('disconnected from server');
}); 
