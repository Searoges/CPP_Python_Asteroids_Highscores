import socket
from http.server import BaseHTTPRequestHandler, HTTPServer
import time

#https://www.pythoncentral.io/introduction-to-sqlite-in-python/

#https://docs.python.org/2/library/json.html

hostName = ""
hostPort = 80

class MyServer(BaseHTTPRequestHandler):

	def do_GET(self):

		content_length = int(self.headers['Content-Length'])  # <--- Gets the size of data
		post_data = self.rfile.read(content_length)  # <--- Gets the data itself

		print("GET: ", post_data);

		self.send_response(200)
		self.send_header('Content-type', 'text/html')
		self.end_headers()
		self.wfile.write("GET request".encode())
		self.wfile.write(post_data)
		self.wfile.write("GET response".encode())

	def do_POST(self):
		content_length = int(self.headers['Content-Length'])  # <--- Gets the size of data
		post_data = self.rfile.read(content_length)  # <--- Gets the data itself

		print( "POST: ", post_data);

		self.send_response(200)
		self.send_header('Content-type','text/html')
		self.end_headers()
		self.wfile.write("POST request".encode())
		self.wfile.write(post_data)
		self.wfile.write("POST response".encode())



myServer = HTTPServer((hostName, hostPort), MyServer)
print(time.asctime(), "Server Starts - %s:%s" % (hostName, hostPort))

try:
	myServer.serve_forever()
except KeyboardInterrupt:
	pass

myServer.server_close()
print(time.asctime(), "Server Stops - %s:%s" % (hostName, hostPort))