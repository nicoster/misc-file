function foo(){
	this.a = 1;
}

var bar = //function Bar()
{
	a:2,
	zoo:foo,
	zoo2: function(){
		this.a = 3;
	}
};

//var bar = new Bar;

bar.zoo();

console.log(bar);

bar.zoo2();

console.log(bar);