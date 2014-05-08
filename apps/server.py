import web
from adder import PAdder
from basicauthenticator import PBasicAuthenticator
from web.wsgiserver import CherryPyWSGIServer

CherryPyWSGIServer.ssl_certificate = "/etc/ssl/certs/server.crt"
CherryPyWSGIServer.ssl_private_key = "/etc/ssl/certs/server.key"
        
urls = (
    '/(.*)', 'hello'
)

def handleAuth(handle):
    authenticator = PBasicAuthenticator()
    authenticator.authenticate("","")
    return handle()



class hello:
    def __init__(self):
        self.adder = PAdder()
    def POST(self, name):
        return self.adder.add(web.data())

if __name__ == "__main__":
    app = web.application(urls, globals())
    app.add_processor(handleAuth)
    app.run()
