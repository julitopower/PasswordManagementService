import web
from adder import PAdder
from web.wsgiserver import CherryPyWSGIServer

CherryPyWSGIServer.ssl_certificate = "/etc/ssl/certs/server.crt"
CherryPyWSGIServer.ssl_private_key = "/etc/ssl/certs/server.key"
        
urls = (
    '/(.*)', 'hello'
)
app = web.application(urls, globals())

class hello:
    def __init__(self):
        self.adder = PAdder()
    def POST(self, name):
        return self.adder.add(web.data())

if __name__ == "__main__":
    app.run()
