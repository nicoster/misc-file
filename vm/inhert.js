Object.prototype.inherit = function(baseConstructor) {
  this.prototype = baseConstructor.prototype;
  this.prototype.constructor = this;
};
Object.prototype.method = function(name, func) {
  this.prototype[name] = func;
};

function StrangeArray(){}
StrangeArray.inherit(Array);
StrangeArray.method("push2", function(value) {
  Array.prototype.push.call(this, value);
  Array.prototype.push.call(this, value);
});

var strange = new StrangeArray();
strange.push2(4);
console.log(strange);

function Foo(){this.a='b';}
console.log(new Foo());

