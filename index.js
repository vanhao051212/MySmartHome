var express = require("express");
var app = express();

app.use(express.static("public"));
app.set("view engine","ejs");
app.set("views","./views");

var server = require("http").Server(app);
var io = require("socket.io")(server);

server.listen(process.env.PORT || 8000);
// server.listen(8000);

var dt=["",""];
var Status;
io.on("connection",function(socket){
	socket.on("led_1",function(data){
		dt[0]=data;
		io.sockets.emit("server_reply_1",dt[0]);
	});
	socket.on("led_2",function(data){
		dt[1]=data;
		io.sockets.emit("server_reply_2",dt[1]);
	});
	socket.on("Client_update_1_on",function(){
		socket.broadcast.emit("server_reply_1","ON");
	});
	socket.on("Client_update_1_off",function(){
		socket.broadcast.emit("server_reply_1","OFF");
	});
	socket.on("Client_update_2_on",function(){
		socket.broadcast.emit("server_reply_2","ON");
	});
	socket.on("Client_update_2_off",function(){
		socket.broadcast.emit("server_reply_2","OFF");
	});
	socket.on("Update",function(){
		io.sockets.emit("Update");
	});
});


app.get("/",function(req,res){
	res.render("trangchu",{
		dt1: dt[0],
		dt2: dt[1],

	});

});

app.get("/:stt",function(req,res){
	Status = req.params.stt;
	if (Status=="1on"){
		res.render("1on");
	}
	if (Status=="1off"){
		res.render("1off");
	}
});
