var socket=io("https://vanhao.herokuapp.com");
// var socket=io("http://localhost:8000/");
socket.on("server_reply_1",function(data){
	if(data == "ON"){
		document.getElementById("stt_1").innerHTML = "Bật";
	}else{
		document.getElementById("stt_1").innerHTML = "Tắt";
	}});

socket.on("server_reply_2",function(data){
	if(data == "ON"){
		document.getElementById("stt_2").innerHTML = "Bật";
	}else{
		document.getElementById("stt_2").innerHTML = "Tắt";
	}
	
});


$(document).ready(function(){
	$("#turn_on_led_1").click(function(){
		socket.emit("led_1","ON");
	});
	$("#turn_on_led_2").click(function(){
		socket.emit("led_2","ON");
	});
	$("#turn_off_led_1").click(function(){
		socket.emit("led_1","OFF");
	});
	$("#turn_off_led_2").click(function(){
		socket.emit("led_2","OFF");
	});
	$("#get_stt").click(function(){
		socket.emit("Update");
	});
});
