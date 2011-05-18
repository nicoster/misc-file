#include "common.h"


void main()
{
	int size_q;	queue<int> q;	queue<char> p;	q.push(42);	q.push(100);	q.push(49);	q.push(201);	size_q=q.size();	cout<<"size of q is: "<<size_q<<endl;	while(!q.empty())	{		cout<< q.front()<<endl;		q.pop();	}	p.push('c');	p.push('a');	p.push('d');	p.push('m');	p.push('h');	cout<<p.front()<<endl;	size_q=p.size();	cout<<"size of p is:"<<size_q<<endl;	while(!p.empty())	{		cout<<p.front()<<endl;		p.pop();	}}