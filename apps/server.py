import web
from service import adder, basicauthenticator, addkeyhandler, mapstorage
from web.wsgiserver import CherryPyWSGIServer

# Configure the location of the SSL certificates
CherryPyWSGIServer.ssl_certificate = "/etc/ssl/certs/server.crt"
CherryPyWSGIServer.ssl_private_key = "/etc/ssl/certs/server.key"
        
# Configure the URL to handler mappings
urls = (
    '/addkey/(.*)', 'AddKeyHandler',
    '/getkey/(.*)', 'GetKeyHandler'
)

# Authenticator processor method
def handleAuth(handle):
    authenticator = basicauthenticator()
    authenticator.authenticate("","")
    return handle()

# Add key python handler wrapper
st = mapstorage()
addkey = addkeyhandler(st)
class AddKeyHandler:
    def PUT(self, key_id):
        addkey.handle(key_id, web.data())
        return web.OK()

class GetKeyHandler:
    def GET(self, key_id):
        return addkey.get(key_id).getStatus()

# This needs to be removed
class hello:
    def __init__(self):
        self.adder = adder()
    def POST(self, name):
        return self.adder.add(web.data())

# Wire everything together and launch the server
if __name__ == "__main__":
    app = web.application(urls, globals())
    app.add_processor(handleAuth)
    app.run()
