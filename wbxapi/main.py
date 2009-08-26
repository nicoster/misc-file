from google.appengine.ext import webapp 
from google.appengine.ext.webapp.util import run_wsgi_app 
 
class sso(webapp.RequestHandler): 
  def get(self): 
    self.post();
    
  def post(self):
    cmd = self.request.get("cmd");
    task = self.request.get("task");
    self.response.headers['Content-Type'] = 'text/xml' 

    self.response.out.write(file('sso.xml', 'r').read())


class cas(webapp.RequestHandler): 
  def get(self): 
    self.post();
    
  def post(self):
    cmd = self.request.get("cmd");
    task = self.request.get("task");
    user = self.request.get("username");
    passwd = self.request.get("password");
    self.response.headers['Content-Type'] = 'text/xml' 

    if cmd == 'getwebextoken' and user == 'nickx@sz.webex.com' and passwd == 'P&ss97' :
      self.response.out.write(file('logincas.xml', 'r').read())
    else:
      self.response.out.write(file('logincas_err.xml', 'r').read())
 
class wapi(webapp.RequestHandler): 

  def post(self):
    cmd = self.request.get("cmd");
    task = self.request.get("task");
    
    self.response.headers['Content-Type'] = 'text/xml' 
    
    if cmd == 'login':
      self.response.out.write(file('loginwapi.xml', 'r').read())
    else:
      if task == 'InitialConfig':
        self.response.out.write(file('initcfg.xml', 'r').read())
      else:
        self.response.out.write(file('wapi.xml', 'r').read())
        
  def get(self): 
    self.post();
 
application = webapp.WSGIApplication([
    ('/wbxconnect/op.do', wapi),
    ('/cas/auth.do', cas),
    ('/cas/FederatedSSO', sso),
  ], 
  debug=True) 
 
def main(): 
  run_wsgi_app(application) 
 
if __name__ == "__main__": 
  main()