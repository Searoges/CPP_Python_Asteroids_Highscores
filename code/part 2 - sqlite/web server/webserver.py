import socket
from http.server import BaseHTTPRequestHandler, HTTPServer
import time
import sqlite3

hostName = ""
hostPort = 80
#https://www.pythoncentral.io/introduction-to-sqlite-in-python/
#https://docs.python.org/2/library/sqlite3.html
conn = sqlite3.connect(':memory:')

c = conn.cursor()
c.execute("create table highscores (name varchar(20), score int)")

c.execute("insert into highscores (name, score) values ('Me', 3000)");
c.execute("insert into highscores (name, score) values ('Me', 2000)");
c.execute("insert into highscores (name, score) values ('Me', 1000)");

c.execute("insert into highscores (name, score) values ('You', 3000)");
c.execute("insert into highscores (name, score) values ('You', 2000)");
c.execute("insert into highscores (name, score) values ('You', 1000)");
conn.commit()

for row in c.execute("select * from highscores where name == 'Me' order by score desc"):
        print(row)

class MyServer(BaseHTTPRequestHandler):

	def do_GET(self):

		content_length = int(self.headers['Content-Length'])  # <--- Gets the size of data
		post_data = self.rfile.read(content_length)  # <--- Gets the data itself

		print("GET: ", post_data);

		self.send_response(200)
		self.send_header('Content-type', 'text/html')
		self.end_headers()

		result = ""
		for row in c.execute("select * from highscores where name == 'Me' order by score desc"):
			for val in row:
				if(type(val) is int):
					result += str(val)
				else:
					result += val

				result += " "

		self.wfile.write(result.encode())

		print("GET RESPONSE ", result)

	def do_POST(self):
		content_length = int(self.headers['Content-Length'])  # <--- Gets the size of data
		post_data = self.rfile.read(content_length)  # <--- Gets the data itself

		print( "POST: ", post_data)

		c.execute(post_data.decode())

		self.send_response(200)

myServer = HTTPServer((hostName, hostPort), MyServer)
print(time.asctime(), "Server Starts - %s:%s" % (hostName, hostPort))

try:
	myServer.serve_forever()
except KeyboardInterrupt:
	pass

myServer.server_close()
print(time.asctime(), "Server Stops - %s:%s" % (hostName, hostPort))