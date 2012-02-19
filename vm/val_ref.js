function o(log){console.log(log);}

var str = 'abcde\n';
o(typeof str);
var obj = new String(str);
o(typeof obj);
function newToString() { return 'hello, world!';
}
function func(val) { val.toString = newToString;
}

func(str); 
console.log(str);
console.log(obj);

var obj2 = obj;
func(obj2); 
console.log(obj2);

(function foo(){});
//console.log(foo);

str = 'abcdef';
var obj1 = new String(str); 
var obj2 = new String(str);
o(obj1 == obj2); 
o(obj1 === obj2);


var o1 = {};
var o2 = {};
var str = '123';
var num = 1;
var b0 = false;
var b1 = true;
var ref = new String();

global = 1;
o(delete global);
//   o(global);

var local = 2;
o(delete local);
o(local);
//1=2;
o([1, 2,(3,4,5),6]);

o(['push'] ['length']);

function MyObject(){}

o()
o(MyObject.prototype.constructor);
delete MyObject.prototype.constructor;
o(MyObject.prototype.constructor);
