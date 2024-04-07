from os import name
from bottle import run, route

@route('/')
@route('/hello/<name>')
def hello(name):
 return "Hello " + name

run(host='localhost', port=8000, debug=True)