var
_r_function = /^function\b *([$\w\u00FF-\uFFFF]+) *\(/m;
function showIt(func) {
var name = (!(func instanceof Function) ? 'unknow type' : _r_function.test(func.toString()) ? RegExp.$1 : 'anonymous');
alert('-> ' + name); }
function enumStack(callback) { var f = arguments.callee; while (f.caller) {
callback( f = f.caller ); }
}
function level_n() { enumStack(showIt);
}
function level_2() { // ...
level_n(); }
function test() { level_2();
}
test();