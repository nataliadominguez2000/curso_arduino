from flask import Flask, render_template,request,redirect,url_for
import db

# Envío de datos
# curl -d "persona=prueba&hum=99&temp=12" http://127.0.0.1:5000/datos
# https://www.luisllamas.es/arduino-dht11-dht22/
# https://programarfacil.com/blog/arduino-blog/sensor-dht11-temperatura-humedad-arduino/


app = Flask(__name__)


@app.route('/')
def index():
    resp = db.ver_todos()
 #   print(resp)
    return render_template("tabla.html",filas=resp)

@app.route('/datos',methods = ['POST'])
def send_data():
    persona = request.form.get('persona')
    temp = request.form.get('temp')
    hum = request.form.get('hum')
    resp = db.inserta(temp,hum,persona)
    print(resp)
    return "" #redirect(url_for('index'))

@app.rou

    