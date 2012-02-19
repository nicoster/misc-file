function o(x){console.log(x);}

function Foo(){}

function Bar(){this.nick = 'xiao';}

var bar1 = new Bar();
o(bar1);

var Bar_prototype = Bar.prototype;
Bar.prototype = Foo.prototype;

Bar_prototype.only = 'you';

var bar2 = new Bar();
o(bar1);
o(bar2);
o(bar1.only);
o(bar2.only);