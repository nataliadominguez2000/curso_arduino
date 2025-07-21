import sqlite3

connection = sqlite3.connect('temperaturas.sqlite')


creacion = """
    -- drop table if exists temp_hum ;
    CREATE TABLE temp_hum (
    id INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL,
    persona TEXT(30),
    temperatura REAL,
    humedad REAL,
    tstamp TIMESTAMP DEFAULT CURRENT_TIMESTAMP NOT NULL
);

"""

cur = connection.cursor()

cur.execute(creacion)

connection.commit()
connection.close()

