var http = require("http");

var data = 'kw=荷韵';
var options = {
  host: 'm.sz-map.com',
  port: 80,
  path: '/search',
  method: 'POST',
	headers:{
		'Content-Length':Buffer.byteLength(data),
		'Content-Type':'application/x-www-form-urlencoded'
	}
};

var req = http.request(options, function(res) {
  console.log('STATUS: ' + res.statusCode);
  console.log('HEADERS: ' + JSON.stringify(res.headers));
  res.setEncoding('utf8');
  res.on('data', function (chunk) {
    console.log('BODY: ' + chunk);
  });
});

req.on('error', function(e) {
  console.log('problem with request: ' + e.message);
});

// write data to request body
req.write(data);
req.end();