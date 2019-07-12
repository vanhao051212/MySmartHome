var socket=io("https://vanhao.herokuapp.com");
// var socket=io("http://localhost:8000/");
socket.on("server_reply_1",function(data){
	if(data == "ON"){
		document.getElementById("stt_1").innerHTML = "Bật";
	}else{
		document.getElementById("stt_1").innerHTML = "Tắt";
	}
});

socket.on("server_reply_2",function(data){
	if(data == "ON"){
		document.getElementById("stt_2").innerHTML = "Bật";
	}else{
		document.getElementById("stt_2").innerHTML = "Tắt";
	}	
});

socket.on("server_reply_3",function(data){
	if(data == "ON"){
		document.getElementById("stt_3").innerHTML = "Bật";
	}else{
		document.getElementById("stt_3").innerHTML = "Tắt";
	}
});

socket.on("server_reply_4",function(data){
	if(data == "ON"){
		document.getElementById("stt_4").innerHTML = "Bật";
	}else{
		document.getElementById("stt_4").innerHTML = "Tắt";
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
	$("#turn_on_fan_1").click(function(){
		socket.emit("fan_1","ON");
	});
	$("#turn_on_fan_2").click(function(){
		socket.emit("fan_2","ON");
	});
	$("#turn_off_fan_1").click(function(){
		socket.emit("fan_1","OFF");
	});
	$("#turn_off_fan_2").click(function(){
		socket.emit("fan_2","OFF");
	});	
	
	$("#get_stt").click(function(){
		socket.emit("Update");
	});
});
