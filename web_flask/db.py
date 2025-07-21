import sqlite3

def conecta():
    cnx = sqlite3.connect("temperaturas.sqlite")
    return cnx

def inserta(temp, hum, persona):
    sentencia = "insert into temp_hum(temperatura,humedad,persona) values(?,?,?)"

    mi_cnx = conecta()
    cur = mi_cnx.cursor()
    resp = cur.execute(sentencia,(temp,hum,persona))
    mi_cnx.commit()
    last_row = str(cur.lastrowid)
    datos = cur.execute("select * from temp_hum where id=" + last_row).fetchone()
    mi_cnx.close()
    return datos

def ver_todos():
    mi_cnx = conecta()
    cur = mi_cnx.cursor()
    datos = cur.execute("select * from temp_hum").fetchall()
    mi_cnx.close()
    return datos